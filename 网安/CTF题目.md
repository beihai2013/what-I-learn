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

