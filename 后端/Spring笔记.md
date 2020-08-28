# 基本特性

## IoC：Inverse of Control 控制反转

从Spring容器中获取需要使用的对象，而不是自己创造

### 使用

#### BeanFactory

最底层基类

##### getBean

```
① 按照类型拿 bean： bean = (Bean) factory.getBean(Bean.class); 注意： 要求在 Spring 中只配置了一个这种类型的实例，否则报错。（如果有多个那 Spring 就懵了，不知道该获取哪一个）
② 按照 bean 的名字拿 bean: bean = (Bean) factory.getBean("beanName"); 注意： 这种方法不太安全，IDE 不会检查其安全性（关联性） 
③ 按照名字和类型拿 bean：（推荐） bean = (Bean) factory.getBean("beanName", Bean.class);
```

##### isSingleton

判断是否为单例

##### isPrototype

若为真，则当从容器中获取Bean时，容器会生成一个新的实例

##### getAliases

获取别名

#### ApplicationContext

BeanFactory的子接口之一，建议使用ApplicationContext而不是BeanFactory

1.**ClassPathXmlApplicationContext：** 读取classpath中的资源

```
ApplicationContext ctx = new ClassPathXmlApplicationContext("applicationContext.xml");
```

2:**FileSystemXmlApplicationContext:-** 读取指定路径的资源

```
ApplicationContext ac = new FileSystemXmlApplicationContext("c:/applicationContext.xml");
```

3.**XmlWebApplicationContext:** 需要在Web的环境下才可以运行

```
XmlWebApplicationContext ac = new XmlWebApplicationContext(); // 这时并没有初始化容器
ac.setServletContext(servletContext); // 需要指定ServletContext对象
ac.setConfigLocation("/WEB-INF/applicationContext.xml"); // 指定配置文件路径，开头的斜线表示Web应用的根目录
ac.refresh(); // 初始化容器
```



##### 与BeanFactory区别

支持国际化；支持消息机制；支持统一的资源加载；支持AOP

## AOP：Aspect Oriented Program 面向切面编程

将功能分为核心业务和周边功能，降低模块间耦合度，方便迭代