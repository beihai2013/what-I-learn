# TLS、SSL、HTTPS区别

## SSL

secure sockets layer，安全通讯端层。用于网络线路加密

## TLS

transport layer security，传输层安全性。更新、更安全的SSL版本，其安全性凭证称为SSL

## HTTPS

hyper text transfer protocol secure，超级文字传输协议安全。

会在网站受到SSL凭证保护时再网址中出现

# TLS发展历史

SSL->TLS1.0->TLS1.1->TLS1.2->TLS1.3

SSL 3.0存在设计漏洞，故更新为TLS

所有TLS版本在RFC 6176中删除了对SSL的兼容

## 贵宾犬攻击

Google设计了一个名为Padding Oracle On Downgraded Legacy Encryption（POODLE，贵宾狗）的攻击行动，利用上述的降级功能突破了SSL 3.0的密码安全防护，因而可用来窃取原本应是加密的cookies或Tokens。Google并戏称「这是只会咬人的贵宾狗」，外界也因此将该漏洞命名为「贵宾犬」

## TLS 1.1与TLS 1.0差异

添加对CBC攻击的保护

支持对IANA登记的参数



# TLS的工作流程

TLS与高层的应用层协议解耦，对应用层协议透明

TLS基于TCP协议

TLS采用主从式架构，必须配置客户端和服务端

- 当客户端连接到支持TLS协议的服务器要求创建安全连接并列出了受支持的[密码包](https://zh.wikipedia.org/wiki/密码套件)（包括[加密算法](https://zh.wikipedia.org/wiki/加密算法)、[散列算法](https://zh.wikipedia.org/wiki/散列算法)等），握手开始。
- 服务器从该列表中决定密码包，并通知客户端。
- 服务器发回其[数字证书](https://zh.wikipedia.org/wiki/数字证书)，此证书通常包含服务器的名称、受信任的[证书颁发机构](https://zh.wikipedia.org/wiki/证书颁发机构)（CA）和服务器的公钥。
- 客户端确认其颁发的证书的有效性。
- 为了生成会话密钥用于安全连接，客户端使用服务器的公钥加密随机生成的密钥，并将其发送到服务器，只有服务器才能使用自己的私钥解密。
- 利用随机数，双方生成用于加密和解密的对称密钥。这就是TLS协议的握手，握手完毕后的连接是安全的，直到连接（被）关闭。如果上述任何一个步骤失败，TLS握手过程就会失败，并且断开所有的连接。