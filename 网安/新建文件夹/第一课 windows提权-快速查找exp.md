#### 命令

systeminfo>micropoor.txt&(for %i in (KB977165 KB2160329 KB2503665 KB2592799  KB2707511 KB2829361 KB2850851 KB3000061   KB3045171 KB3077657 KB3079904  KB3134228 KB3143141  KB3141780)do @type micropoor.txt|@find /i "%i"||@echo %i you can fuck)&del /f /q /a micropoor.txt

#### 知识点补充

exploit，“利用”，指系统漏洞。

本节为查找windows官方提供的漏洞，如KB2707511

#### 解释

首先明确一点，&为连接符，无论前面结果如何都会执行后面的命令；||为组合命令，左边的命令失败后执行右边命令

命令过长，进行分割

1. systeminfo>micropoor.txt

将系统信息输入到micropoor.txt中。系统信息包括系统已经修补的漏洞

2.1 for %i in (KB977165 KB2160329 KB2503665 KB2592799  KB2707511 KB2829361 KB2850851 KB3000061   KB3045171 KB3077657 KB3079904  KB3134228 KB3143141  KB3141780)do @type micropoor.txt

以%i为形式变量，循环遍历这些KB漏洞，并显示micropoor的内容

2.2 @find /i "%i"

不论大小写【/i】的在micropoor.txt中查找是否存在%i的内容

2.3 @echo %i you can fuck

若%i存在，则不执行当前命令；否则说明当前系统未修补%i漏洞，输出到命令行显示

3. del /f /q /a micropoor.txt

强制安静删除创建的micropoor.txt