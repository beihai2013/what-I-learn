// Copyright (c) 2009 Satoshi Nakamoto
// Distributed under the MIT/X11 software license, see the accompanying
// file license.txt or http://www.opensource.org/licenses/mit-license.php.

#include "headers.h"




#pragma pack(1)
struct ircaddr
{
    int ip;
    short port;
};

string EncodeAddress(const CAddress& addr)
{
    struct ircaddr tmp;
    tmp.ip    = addr.ip;
    tmp.port  = addr.port;

    vector<unsigned char> vch(UBEGIN(tmp), UEND(tmp));
    return string("u") + EncodeBase58Check(vch);
}

bool DecodeAddress(string str, CAddress& addr)
{
    vector<unsigned char> vch;
    if (!DecodeBase58Check(str.substr(1), vch))
        return false;

    struct ircaddr tmp;
    if (vch.size() != sizeof(tmp))
        return false;
    memcpy(&tmp, &vch[0], sizeof(tmp));

    addr  = CAddress(tmp.ip, tmp.port);
    return true;
}






static bool Send(SOCKET hSocket, const char* pszSend)
{
    if (strstr(pszSend, "PONG") != pszSend)
        printf("SENDING: %s\n", pszSend);
    const char* psz = pszSend;
    const char* pszEnd = psz + strlen(psz);
    while (psz < pszEnd)
    {
        int ret = send(hSocket, psz, pszEnd - psz, 0);
        if (ret < 0)
            return false;
        psz += ret;
    }
    return true;
}

bool RecvLine(SOCKET hSocket, string& strLine)
{
    strLine = "";
    loop
    {
        char c;
        int nBytes = recv(hSocket, &c, 1, 0);
        if (nBytes > 0)
        {
            if (c == '\n')
                continue;
            if (c == '\r')
                return true;
            strLine += c;
        }
        else if (nBytes <= 0)
        {
            if (!strLine.empty())
                return true;
            // socket closed
            printf("IRC socket closed\n");
            return false;
        }
        else
        {
            // socket error
            int nErr = WSAGetLastError();
            if (nErr != WSAEMSGSIZE && nErr != WSAEINTR && nErr != WSAEINPROGRESS)
            {
                printf("IRC recv failed: %d\n", nErr);
                return false;
            }
        }
    }
}

bool RecvLineIRC(SOCKET hSocket, string& strLine)
{
    loop
    {
        bool fRet = RecvLine(hSocket, strLine);
        if (fRet)
        {
            if (fShutdown)
                return false;
            vector<string> vWords;
            ParseString(strLine, ' ', vWords);
            if (vWords[0] == "PING")
            {
                strLine[1] = 'O';
                strLine += '\r';
                Send(hSocket, strLine.c_str());
                continue;
            }
        }
        return fRet;
    }
}

bool RecvUntil(SOCKET hSocket, const char* psz1, const char* psz2=NULL, const char* psz3=NULL)
{
    loop
    {
        string strLine;
        if (!RecvLineIRC(hSocket, strLine))
            return false;
        printf("IRC %s\n", strLine.c_str());
        if (psz1 && strLine.find(psz1) != -1)
            return true;
        if (psz2 && strLine.find(psz2) != -1)
            return true;
        if (psz3 && strLine.find(psz3) != -1)
            return true;
    }
}




bool fRestartIRCSeed = false;
// 连接到IRC服务器
void ThreadIRCSeed(void* parg)
{
    loop
    {
        // 连接到名为chat.freenode.net的服务器
        struct hostent* phostent = gethostbyname("chat.freenode.net");
        CAddress addrConnect(*(u_long*)phostent->h_addr_list[0], htons(6667));

        SOCKET hSocket;
        // 可能连接了代理，也可能连接了chat.freenode.net
        if (!ConnectSocket(addrConnect, hSocket)) // 封装了套接字的connect函数，用于路由判断和代理判断
        {
            printf("IRC connect failed\n");
            return;
        }
        // 解析IRC服务器发来的消息，若三个字符串一个出现，则返回错误
        if (!RecvUntil(hSocket, "Found your hostname", "using your IP address instead", "Couldn't look up your hostname"))
        {
            closesocket(hSocket);
            return;
        }
        // 本机IP地址和端口号生成昵称
        string strMyName = EncodeAddress(addrLocalHost);

        if (!addrLocalHost.IsRoutable())
            strMyName = strprintf("x%u", GetRand(1000000000));
        // 注册本机IRC账号
        // 向IRC服务器（“chat.freenode.net”）发送昵称信息，格式为:"NICK 昵称"
        Send(hSocket, strprintf("NICK %s\r", strMyName.c_str()).c_str());
        // 向IRC服务器注册用户信息，格式为:"USER 用户名 密码"
        Send(hSocket, strprintf("USER %s 8 * : %s\r", strMyName.c_str(), strMyName.c_str()).c_str());

        // 等待服务器发送消息，004为错误号
        if (!RecvUntil(hSocket, " 004 "))
        {
            closesocket(hSocket);
            return;
        }
        Sleep(500);

        // 加入比特币频道
        // 加入比特币频道，格式为:"JOIN #bitcoin"
        Send(hSocket, "JOIN #bitcoin\r");
        // 查看频道在线用户，格式为:"WHO #bitcoin"
        Send(hSocket, "WHO #bitcoin\r");

        // 消息接收循环
        while (!fRestartIRCSeed)
        {
            string strLine;
            // RecvLineIRC将服务器发送来的消息放入strLine
            if (fShutdown || !RecvLineIRC(hSocket, strLine))
            {
                closesocket(hSocket);
                return;
            }
            if (strLine.empty() || strLine[0] != ':')
                continue;
            printf("IRC %s\n", strLine.c_str());

            vector<string> vWords;
            // 解析消息
            ParseString(strLine, ' ', vWords);
            if (vWords.size() < 2)
                continue;

            char pszName[10000];
            pszName[0] = '\0';
            // 服务器返回确认信息
            if (vWords[1] == "352" && vWords.size() >= 8)
            {
                // index 7 is limited to 16 characters
                // could get full length name at index 10, but would be different from join messages
                strcpy(pszName, vWords[7].c_str());
                printf("GOT WHO: [%s]  ", pszName);
            }

            if (vWords[1] == "JOIN") // 服务器返回确认信息
            {
                // :username!username@50000007.F000000B.90000002.IP JOIN :#channelname
                strcpy(pszName, vWords[0].c_str() + 1);
                if (strchr(pszName, '!'))
                    *strchr(pszName, '!') = '\0';
                printf("GOT JOIN: [%s]  ", pszName);
            }
            // 获取合适的比特币节点并解析
            if (pszName[0] == 'u') // 接受到#bitcoin内用户的用户名信息
            {
                CAddress addr;
                if (DecodeAddress(pszName, addr)) // 反Base58编码可以得到比特币用户地址
                {
                    CAddrDB addrdb;
                    if (AddAddress(addrdb, addr))
                        printf("new  ");
                    addr.print();
                }
                else
                {
                    printf("decode failed\n");
                }
            }
        }

        fRestartIRCSeed = false;
        closesocket(hSocket);
    }
}










#ifdef TEST
int main(int argc, char *argv[])
{
    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(2,2), &wsadata) != NO_ERROR)
    {
        printf("Error at WSAStartup()\n");
        return false;
    }

    ThreadIRCSeed(NULL);

    WSACleanup();
    return 0;
}
#endif
