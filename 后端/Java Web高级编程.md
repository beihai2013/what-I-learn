# 第3章 创建第一个Servlet 

## 3.1 创建第一个Servlet

### 3.1.1 选择要继承的Servlet类

顶层类 javax.serlvet.GenericServlet

一般继承 javax.servlet.HttpServlet，提供以下空方法

```
GET doGet() 从指定URL获取资源
HEAD doHead() 与GET一致，只返回页面头部数据
POST doPost() 处理Web表单
PUT doPut() 存储URL提供的实体
DELETE doDelete() 删除有URL表示的资源
OPTIONS doOptions() 返回支持的HTTP方法
TRACE doTrace() 诊断
```

### 3.1.2 使用初始化方法和销毁方法

```
init()在servlet启动时调用
```

```
destroy()在servlet不再接受请求之后立即调用
```

两者用于调试

## 3.2 配置可部署的Servlet

在web.xml中配置

```xml
<serlvet>
  /// 创建servlet实例
	<servlet-name></servlet-name>
  <servlet-class>实现了servlet功能的java文件</servlet-class>
  <load-on-startup>1</load-on-startup>//数字越大启动越晚
</servlet>
<servlet-mapping>
  /// 将servlet实例映射到URL
  <servlet-name></servlet-name>
  <url-pattern>/hello</url-pattern>
</servlet-mapping>
```

1. 可一个servlet映射到多个URL
2. 一个servlet可以创建多个servlet实例。在servlet中通过this.getServletName()获得具体实例名

## 3.3 了解doGet、doPost和其他方法

### 3.3.1 HttpServletRequest的方法

1. 获取请求参数

   ```
   getParameter() 获取参数单个值。多值时返回第一个值。
   getParameterValues() 获取参数值的数组。
   getParameterMap() 返回包含所有参数名值对
   getParameterNames() 返回所有可用参数的名字的枚举
   ```

2. 获取请求内容相关信息

   ```
   getContentType() 返回请求的MIME类型，如text/plain等
   getContentLength()、getContentLengthLong() 返回请求正文的长度
   getCharacterEncoding() 获取编码
   ```

3. 获取请求内容

   ```
   getInputStream() 返回一个javax.servlet.ServletInputStream。针对二进制数据
   getReader() 返回一个java.io.BufferedReader。针对字符数据
   ```

4. 获取请求特有数据

   ```
   getRequestURL() 返回客户端用于创建请求的完整URL，如访问http://www.example.org/application/index.jsp?category=Books，返回http://www.example.org/application/index.jsp
   getRequestURI() 返回URL中的服务器部分，即返回/application/index.jsp
   getServletPath() 返回/index
   getHeader() 返回指定名字的头数据
   getHeaders() 返回所有指定名字的头数据集合
   getHeaderNames() 返回请求中所有头数据的名字枚举
   getIntHeader() 如果某个头的值为数字，则可返回数字。若头数据不能转换为整数，则抛出NumberFormatException异常
   getDateHeader() 如果某个头的值为时间戳，则可返回时间戳。若头数据不能转换为日期，则抛出IllegalArgumentException异常
   ```

### 3.3.2 HttpServletResponse方法
1. 编写相应正文
```
getOutputStream() 返回一个javax.servlet.ServletOutputStream。针对二进制数据
getWriter() 返回java.io.PrintWriter。针对编码字符串和字符。与getOutputStream() 不可同时调用
setContentType() 设置内容类型，以最后一次设置为准
setCharacterEncoding() 设置编码格式，以最后一次设置为准
```
2. 
```
setStatus() 设置HTTP响应状态码
getStatus() 判断当前响应的状态
sendError() 设置状态码，表示一条可选错误消息输出到响应数据，重定向到错误页面，并清空缓存
sendRedirect 将客户端重定向到另一个URL
```

## 3.4 使用参数和接受表单
在servlet定义前，使用@WebServlet注解，可以替代web.xml中配置功能
```
@WebServlet{
	name="helloServlet"
	urlPatterns={"/greeting", "/salutation", "/wazzup"}
	loadOnStartup = 1
}
```
## 3.5 使用初始化参数配置应用程序
### 3.5.1 使用初始化参数配置应用程序-<context-param>
1. 在web.xml中的设置
```xml
<context-param>
	<param-name>name</param-name>
  <param-value>value</param-value>
</context-param>
```
2. 在servlet中读取
```
ServletContext c = this.getServletContext();
c.getInitParameter("name")
```
### 3.5.2 使用Servlet初始化参数-<init-param>
```
<init-param>
	<param-name>name</param-name>
  <param-value>value</param-value>
</init-param>
```
在servlet中使用
```
ServletConfig c = this.getServletConfig();
c.getInitParameter("name")
```
## 3.6 通过表单上传文件
# 5 使用会话维持状态
## 5.1 需要会话的原因
1. 维持状态
2. 记住用户
3. 启动应用程序工作流
## 5.3 在会话中存储数据
web.xml中配置
```xml
<session-config>
	<session-timeout>30</session-timeout>
  <cookie-config>
  	<name>JSESSIONID</name> /// 定义cookie名字，默认为JESSIONID。通常不需要定义
    <domain>example.org</domain> //通常不需要定义
    <path>/shop</path> //通常不需要定义
    <comment><![CDATA[Keeps you logged in. See our privacy policy for more information.]]></comment>
    <http-only>true</http-only> /// 对应cookie的HttpOnly属性
    <secure>false</secure> /// 对应cookie的secure属性。若使用了HTTPS，则赢设置为真
    <max-age>1800</max-age> ///秒数
  </cookie-config>
  <tracking-mode>COOKIE</tracking-mode> /// 在URL中内嵌会话ID
  <tracking-mode>URL</tracking-mode>	/// 使用cookie追踪会话ID
  <tracking-mode>SSL</tracking-mode>	/// 使用SSL会话ID作为HTTP会话ID，要求所有请求为HTTPS请求
  
</session-config>
```

在servlet中使用，存储数据

```
HttpSession session = request.getSession();
if(session.getAttribute("cart")==null)
	session.setAttribute("cart",new Hashtable<Integer,Integer>());
```

在JSP中使用，获取数据

```jsp
<%
	Map<Integer,String>product=(Map<Integer,String>)request.getAttribute("products");
%>
```

在servlet中使用，删除数据

```
HttpSession session = request.getSession();
if(session.getAttribute("cart")!=null)
	session.removeAttribute("cart",new Hashtable<Integer,Integer>());
```

# 6 在JSP中使用表达式语言
## 6.2 使用EL语法
### 6.2.4 EL函数
主要是JSTL的函数。当指定JSTL函数命名空间为fn时，有以下函数可以使用
```
fn:contains(String,String) 第1个字符串是否包含第2个字符串的1个或多个实例
fn:escapeXml(String) 对字符串的特殊字符进行转义。可用于防止XSS攻击。
fn:join(String[], String) 将指定的字符串作为分隔符，将字符串数据中的字符串连接起来
fn:length(Object) 返回大小
fn:toLowerCase(String)、fn:toUpperCase(String) 大小写
fn:trim(String) 去除字符串两端空白
```
### 6.2.5 静态字段和方法访问
使用完全限定类名.字段或方法名
```
${java.lang.Integer.MAX_VALUE}
```
ps：java.lang包在jsp中已经被隐式导入，所以上式直接写作
```
${Integer.MAX_VALUE}
```
即可。

## 6.3 在EL表达式中使用作用域变量
```
pageContext
pageScope
requestScope
sessionScope
applicationScope
param
header
initParam
cookie
```
## 6.4 使用流API访问集合
### 6.4.1 了解中间操作
过滤流
```
${books.stream().filter(b->b.author=="John F. Smith")}
${[1,2,3,3,4,5,5,5,5,6].stream().distinct()}
```
操作值
接收一个lambda表达式
```
${books.stream().forEach(b->b.setLastViewed(Instant.now()))}
```
排序
接收一个java.util.Comparator<E>
```
${books.stream().sorted((b1,b2)->b1.title.compareTo(b2.title))}
${[8,3,19,5,7,-2,0].stream().sorted()}
```
限制流大小
```
${books.stream().limit(10)}
${books.stream().substream(10,20)}
```
转换流
```
${books.stream().map(b->b.title)}
```
### 6.4.2 使用终结操作
返回集合
```
${books.stream().map(b->b.title).toArray()}
${books.stream().map(b->b.title).toList()}
```