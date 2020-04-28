1. 导航框架

main.html

```

<html>
<frameset rows="60,*" noresize="noresize">
    <frame src="HTML框架-导航框架-实例练习-索引.html" ></frame>
    <frame src="HTML框架-导航框架-实例练习-1.html" name="content"></frame>
</frameset>
</html>
```

HTML框架-导航框架-实例练习-索引.html

```

<html>
<head>
<style>
a {
    text-decoration:none;
}
.poem {
    text-align:center;
    background-color=red;
    font-family:宋体;
    font-size:20px;
}
</style>
</head>
<body >
<p class="poem">
    <a href="HTML框架-导航框架-实例练习-1.html" target="content">推荐</a>&nbsp;&nbsp;
    <a href="HTML框架-导航框架-实例练习-2.html" target="content">诗文</a>&nbsp;&nbsp;
    <a href="HTML框架-导航框架-实例练习-3.html" target="content">名句</a>&nbsp;&nbsp;
    <a href="HTML框架-导航框架-实例练习-4.html" target="content">作者</a>&nbsp;&nbsp;
    <a href="HTML框架-导航框架-实例练习-5.html" target="content">古籍</a>&nbsp;&nbsp;
</p>
</body>
</html>
```

跳转的核心设置为main.html第二个frame中的name，与HTML框架-导航框架-实例练习-索引.html中的target

2. 初始页面跳转至页面的某个部分

```
<html>

<frameset cols="20%,80%">

 <frame src="/example/html/frame_a.html">
 <frame src="/example/html/link.html#C10">

</frameset>

</html>
```

3. 带标题的 文本框

```
<form>
	<fieldset>
	<legend>健康信息</legend>
	身高:<input type="text"/>
	体重:<input type="text"/>
	</fieldset>
</form>
```

4 图片映射

```
<area
shape="circle"
coords="180,139,14"
href ="/example/html/venus.html"
target ="_blank"
alt="Venus" />
```

5 链接外部样式表

```
<link rel="stylesheet" type="text/css" href="/html/csstest1.css" >
```

6 检测浏览器是否支持js

```
<script type="text/javascript">
document.write("Hello World!")
</script>
<noscript>Sorry, your browser does not support JavaScript!</noscript>
```

7 浮动菜单

```
<html>
<head>
<style type="text/css">
ul
{
float:left;
width:100%;
padding:0;
margin:0;
list-style-type:none;
}
a
{
float:left;
width:7em;
text-decoration:none;
color:white;
background-color:purple;
padding:0.2em 0.6em;
border-right:1px solid white;
}
a:hover {background-color:#ff3300}
li {display:inline}
</style>
</head>

<body>
<ul>
<li><a href="#">Link one</a></li>
<li><a href="#">Link two</a></li>
<li><a href="#">Link three</a></li>
<li><a href="#">Link four</a></li>
</ul>

<p>
在上面的例子中，我们把 ul 元素和 a 元素浮向左浮动。li 元素显示为行内元素（元素前后没有换行）。这样就可以使列表排列成一行。ul 元素的宽度是 100%，列表中的每个超链接的宽度是 7em（当前字体尺寸的 7 倍）。我们添加了颜色和边框，以使其更漂亮。
</p>

</body>
</html>

```

