# 基本特性

## IoC：Inverse of Control 控制反转

从Spring容器中获取需要使用的对象，而不是自己创造[1]

IoC是一种软件设计模式，组装器（即Spring Framework）在运行时而不是编译时绑定对象。可以在不同的环境中切换而无须重新编译代码。[2]



### 使用[1]

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

### 概念

切入点、通知、切面（切入点+通知，即在什么时机什么地方，做什么增强）、织入

### AspectJ注解

@Before，@Around，@After，@AfterReturning，@AfterThrowing、@Around（环绕通知，可同时完成前置和后置通知）

### 定义切点

```
execution(* pojo.Landlord.service())

execution：代表执行方法的时候会触发
* ：代表任意返回类型的方法
pojo.Landlord：代表类的全限定名
service()：被拦截的方法名称
```

### 栗子

```
package aspect;

import org.aspectj.lang.annotation.After;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;
import org.aspectj.lang.annotation.Pointcut;
import org.springframework.stereotype.Component;

@Component
@Aspect
class Broker {

	@Pointcut("execution(* pojo.Landlord.service())")
	public void lService() {
	}

	@Before("lService()")
	public void before() {
		System.out.println("带租客看房");
		System.out.println("谈价格");
	}

	@After("lService()")
	public void after() {
		System.out.println("交钥匙");
	}
}
```

## 应用程序消息

松耦合消息系统，使用发布-订阅模式[2]

# 上下文[1]

共享应用模块，但不共享数据。实现了隔离

# 实现

## 装配Bean

1. 隐式Bean的发现机制和自动装配。
2. Java接口和类中配置实现
3. XML方式

### XML方式

#### 不同属性的装配

```
package pojo;

import java.util.List;
import java.util.Map;
import java.util.Properties;
import java.util.Set;

public class ComplexAssembly {
	
	private Long id;
	private List<String> list;
	private Map<String, String> map;
	private Properties properties;
	private Set<String> set;
	private String[] array;

    /* setter and getter */
}
<bean id="complexAssembly" class="pojo.ComplexAssembly">
    <!-- 装配Long类型的id -->
    <property name="id" value="1"/>
    
    <!-- 装配List类型的list -->
    <property name="list">
        <list>
            <value>value-list-1</value>
            <value>value-list-2</value>
            <value>value-list-3</value>
        </list>
    </property>
    
    <!-- 装配Map类型的map -->
    <property name="map">
        <map>
            <entry key="key1" value="value-key-1"/>
            <entry key="key2" value="value-key-2"/>
            <entry key="key3" value="value-key-2"/>
        </map>
    </property>
    
    <!-- 装配Properties类型的properties -->
    <property name="properties">
        <props>
            <prop key="prop1">value-prop-1</prop>
            <prop key="prop2">value-prop-2</prop>
            <prop key="prop3">value-prop-3</prop>
        </props>
    </property>
    
    <!-- 装配Set类型的set -->
    <property name="set">
        <set>
            <value>value-set-1</value>
            <value>value-set-2</value>
            <value>value-set-3</value>
        </set>
    </property>
    
    <!-- 装配String[]类型的array -->
    <property name="array">
        <array>
            <value>value-array-1</value>
            <value>value-array-2</value>
            <value>value-array-3</value>
        </array>
    </property>
</bean>
```

#### 命名空间装配（未弄明白）

c-命名空间、p-命名空间、util命名空间

```
<!-- 引入 c-命名空间之前 -->
<bean name="student1" class="pojo.Student">
    <constructor-arg name="id" value="1" />
    <constructor-arg name="name" value="学生1"/>
</bean>

<!-- 引入 c-命名空间之后 -->
<bean name="student2" class="pojo.Student"
      c:id="2" c:name="学生2"/>
```

### 注解方式

#### @Componet

需要使用创建一个StudentConfig文件，@ComponetScan，扫描当前包的路径

```
// Student.java
package pojo;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

@Component(value = "student1")
public class Student {

	@Value("1")
	int id;
	@Value("student_name_1")
	String name;

    // getter and setter
}
//StudentConfig.java
package pojo;
import org.springframework.context.annotation.ComponentScan;

@ComponentScan
public class StudentConfig {
}
```

#### @ComponentScan

放在某一个包下，默认表示扫描当前包中的类。

也可以配置参数后扫描指定类

```
@ComponentScan(basePackageClasses = pojo.Student.class)
public class StudentConfig {
}
```

#### @Autowired（未看懂）

自动装配

# 参考

[1] github.com

[2] 《Java Web高级编程》





### 12.4 启动Spring Framework

#### 12.4.1 使用部署描述符启动Spring

在xml中配置