// Copyright (c) 2009 Satoshi Nakamoto
// Distributed under the MIT/X11 software license, see the accompanying
// file license.txt or http://www.opensource.org/licenses/mit-license.php.


//
// Why base-58 instead of standard base-64 encoding?
// - Don't want 0OIl characters that look the same in some fonts and
//      could be used to create visually identical looking account numbers.
// - A string with non-alphanumeric characters is not as easily accepted as an account number.
// - E-mail usually won't line-break if there's no punctuation to break at.
// - Doubleclicking selects the whole number as one word if it's all alphanumeric.
//
//译：58位是因为祛除了0OIl几个视觉上容易混淆的字符

static const char* pszBase58 = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

// 转换成Base58码格式
inline string EncodeBase58(const unsigned char* pbegin, const unsigned char* pend)
{
    CAutoBN_CTX pctx;
    CBigNum bn58 = 58;
    CBigNum bn0 = 0;

    // Convert big endian data to little endian
    // 将大端数据变为小端数据
    // Extra zero at the end make sure bignum will interpret as a positive number
    // 在末尾添加0，保证大数能够被解析为正数
    vector<unsigned char> vchTmp(pend-pbegin+1, 0);
    reverse_copy(pbegin, pend, vchTmp.begin());

    // Convert little endian data to bignum
    CBigNum bn;
    // 将vchTmp进行格式转换后，值传递给bn
    bn.setvch(vchTmp);

    // Convert bignum to string
    string str;
    // str.reserve(int len) 将str的大小设置为len
    str.reserve((pend - pbegin) * 138 / 100 + 1);
    // 除数
    CBigNum dv;
    // 余数
    CBigNum rem;
    while (bn > bn0)
    {
        // 大数除法，int BN_div(BIGNUM *dv, BIGNUM *rem, const BIGNUM *a, const BIGNUM *d,BN_CTX *ctx);
        // dv=a/d, rem=a%d, pctx用处待定
        if (!BN_div(&dv, &rem, &bn, &bn58, pctx))
            throw bignum_error("EncodeBase58 : BN_div failed");
        bn = dv;
        unsigned int c = rem.getulong();
        // 对应的Base58编码字符
        str += pszBase58[c];
    }

    // Leading zeroes encoded as base58 zeros
    for (const unsigned char* p = pbegin; p < pend && *p == 0; p++)
        str += pszBase58[0];

    // Convert little endian string to big endian
    // 将小端数据转换为大端数据
    reverse(str.begin(), str.end());
    return str;
}
// 重载
inline string EncodeBase58(const vector<unsigned char>& vch)
{
    return EncodeBase58(&vch[0], &vch[0] + vch.size());
}

// 从Base58解码
inline bool DecodeBase58(const char* psz, vector<unsigned char>& vchRet)
{
    CAutoBN_CTX pctx;
    vchRet.clear();
    CBigNum bn58 = 58;
    CBigNum bn = 0;
    CBigNum bnChar;
    while (isspace(*psz))
        psz++;

    // Convert big endian string to bignum
    for (const char* p = psz; *p; p++)
    {
        const char* p1 = strchr(pszBase58, *p);
        if (p1 == NULL)
        {
            while (isspace(*p))
                p++;
            if (*p != '\0')
                return false;
            break;
        }
        bnChar.setulong(p1 - pszBase58);
        if (!BN_mul(&bn, &bn, &bn58, pctx))
            throw bignum_error("DecodeBase58 : BN_mul failed");
        bn += bnChar;
    }

    // Get bignum as little endian data
    vector<unsigned char> vchTmp = bn.getvch();

    // Trim off sign byte if present
    if (vchTmp.size() >= 2 && vchTmp.end()[-1] == 0 && vchTmp.end()[-2] >= 0x80)
        vchTmp.erase(vchTmp.end()-1);

    // Restore leading zeros
    int nLeadingZeros = 0;
    for (const char* p = psz; *p == pszBase58[0]; p++)
        nLeadingZeros++;
    vchRet.assign(nLeadingZeros + vchTmp.size(), 0);

    // Convert little endian data to big endian
    reverse_copy(vchTmp.begin(), vchTmp.end(), vchRet.end() - vchTmp.size());
    return true;
}

inline bool DecodeBase58(const string& str, vector<unsigned char>& vchRet)
{
    return DecodeBase58(str.c_str(), vchRet);
}




// 检查是否能够编码为Base58，在头部添加4个空字符，进行EcodeBase58
inline string EncodeBase58Check(const vector<unsigned char>& vchIn)
{
    // add 4-byte hash check to the end
    vector<unsigned char> vch(vchIn);
    uint256 hash = Hash(vch.begin(), vch.end());
    vch.insert(vch.end(), (unsigned char*)&hash, (unsigned char*)&hash + 4);
    return EncodeBase58(vch);
}

inline bool DecodeBase58Check(const char* psz, vector<unsigned char>& vchRet)
{
    if (!DecodeBase58(psz, vchRet))
        return false;
    if (vchRet.size() < 4)
    {
        vchRet.clear();
        return false;
    }
    uint256 hash = Hash(vchRet.begin(), vchRet.end()-4);
    if (memcmp(&hash, &vchRet.end()[-4], 4) != 0)
    {
        vchRet.clear();
        return false;
    }
    vchRet.resize(vchRet.size()-4);
    return true;
}

inline bool DecodeBase58Check(const string& str, vector<unsigned char>& vchRet)
{
    return DecodeBase58Check(str.c_str(), vchRet);
}






static const unsigned char ADDRESSVERSION = 0;

inline string Hash160ToAddress(uint160 hash160)
{
    // add 1-byte version number to the front
    vector<unsigned char> vch(1, ADDRESSVERSION);
    vch.insert(vch.end(), UBEGIN(hash160), UEND(hash160));
    return EncodeBase58Check(vch);
}

inline bool AddressToHash160(const char* psz, uint160& hash160Ret)
{
    vector<unsigned char> vch;
    if (!DecodeBase58Check(psz, vch))
        return false;
    if (vch.empty())
        return false;
    unsigned char nVersion = vch[0];
    if (vch.size() != sizeof(hash160Ret) + 1)
        return false;
    memcpy(&hash160Ret, &vch[1], sizeof(hash160Ret));
    return (nVersion <= ADDRESSVERSION);
}

inline bool AddressToHash160(const string& str, uint160& hash160Ret)
{
    return AddressToHash160(str.c_str(), hash160Ret);
}

inline bool IsValidBitcoinAddress(const char* psz)
{
    uint160 hash160;
    return AddressToHash160(psz, hash160);
}

inline bool IsValidBitcoinAddress(const string& str)
{
    return IsValidBitcoinAddress(str.c_str());
}




inline string PubKeyToAddress(const vector<unsigned char>& vchPubKey)
{
    return Hash160ToAddress(Hash160(vchPubKey));
}
