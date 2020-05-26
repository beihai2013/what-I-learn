## java类库

#### Arrays

<T>List<T> asList(T... a) 返回指定数组构造的List

void sort(Object[] a) 对数组排序

void fill(Object[] a, Object val) 用val填充数组a

boolean equals(Object[] a, Object[] a2) 检查a与a2是否相等

int binarySearch(Object[] a, Object key) 对排序后的数组进行二分查找数据

#### StringBuilder

可变的String

StringBuilder() 构造器，内传参可以为容量、字符串等

| insert(int offsetm,Object obj)          | StringBuilder | 在 offsetm 的位置插入字符串 obj                              |
| --------------------------------------- | ------------- | ------------------------------------------------------------ |
| append(Object obj)                      | StringBuilder | 在字符串末尾追加字符串 obj                                   |
| length()                                | int           | 确定 StringBuilder 对象的长度                                |
| setCharAt(int index,char ch)            | void          | 使用 ch 指定的新值设置 index 指定的位置上的字符              |
| toString()                              | String        | 转换为字符串形式                                             |
| reverse()                               | StringBuilder | 反转字符串                                                   |
| delete(int start, int end)              | StringBuilder | 删除调用对象中从 start 位置开始直到 end 指定的索引（end-1）位置的字符序列 |
| replace(int start, int end, String str) | StringBuilder | 使用一组字符替换另一组字符。将用替换字符串从 start 指定的位置开始替换，直到 end 指定的位置结束 |

#### Calendar

```
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class CalendarDemo {
    public static void main(String[] args) {
        System.out.println("完整显示日期时间：");
        // 字符串转换日期格式
        DateFormat fdate = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        String str = fdate.format(new Date());
        System.out.println(str);

        // 创建 Calendar 对象
        Calendar calendar = Calendar.getInstance();
        // 初始化 Calendar 对象，但并不必要，除非需要重置时间
        calendar.setTime(new Date());

        // 显示年份
        System.out.println("年： " + calendar.get(Calendar.YEAR));

        // 显示月份 (从0开始, 实际显示要加一)
        System.out.println("月： " + calendar.get(Calendar.MONTH));


        // 当前分钟数
        System.out.println("分钟： " + calendar.get(Calendar.MINUTE));

        // 今年的第 N 天
        System.out.println("今年的第 " + calendar.get(Calendar.DAY_OF_YEAR) + "天");

        // 本月第 N 天
        System.out.println("本月的第 " + calendar.get(Calendar.DAY_OF_MONTH) + "天");

        // 3小时以后
        calendar.add(Calendar.HOUR_OF_DAY, 3);
        System.out.println("三小时以后的时间： " + calendar.getTime());
        // 格式化显示
        str = (new SimpleDateFormat("yyyy-MM-dd HH:mm:ss:SS")).format(calendar.getTime());
        System.out.println(str);

        // 重置 Calendar 显示当前时间
        calendar.setTime(new Date());
        str = (new SimpleDateFormat("yyyy-MM-dd HH:mm:ss:SS")).format(calendar.getTime());
        System.out.println(str);

        // 创建一个 Calendar 用于比较时间
        Calendar calendarNew = Calendar.getInstance();

        // 设定为 5 小时以前，后者大，显示 -1
        calendarNew.add(Calendar.HOUR, -5);
        System.out.println("时间比较：" + calendarNew.compareTo(calendar));

        // 设定7小时以后，前者大，显示 1
        calendarNew.add(Calendar.HOUR, +7);
        System.out.println("时间比较：" + calendarNew.compareTo(calendar));

        // 退回 2 小时，时间相同，显示0
        calendarNew.add(Calendar.HOUR, -2);
        System.out.println("时间比较：" + calendarNew.compareTo(calendar));

        // calendarNew创建时间点
        System.out.println((new SimpleDateFormat("yyyy-MM-dd HH:mm:ss:SS")).format(calendarNew.getTime()));
        // calendar创建时间点
        System.out.println((new SimpleDateFormat("yyyy-MM-dd HH:mm:ss:SS")).format(calendar.getTime()));
        System.out.println("时间比较：" + calendarNew.compareTo(calendar));
    }
}
```



#### Date

```
import java.text.SimpleDateFormat;
import java.util.Date;

public class DateDemo {
    public static void main(String[] args) {
        String strDate, strTime;
        Date objDate = new Date();
        System.out.println("今天的日期是：" + objDate);
        long time = objDate.getTime();
        System.out.println("自1970年1月1日起以毫秒为单位的时间（GMT）：" + time);
        strDate = objDate.toString();
        //提取 GMT 时间
        strTime = strDate.substring(11, (strDate.length() - 4));
        //按小时、分钟和秒提取时间
        strTime = "时间：" + strTime.substring(0, 8);
        System.out.println(strTime);
        //格式化时间
        SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        System.out.println(formatter.format(objDate));
    }
}
```



#### Math

简单不赘述

#### System

```
//从指定的源数组中复制一个数组，从源数组指定的位置开始，到目标数组指定的位置
public static void arraycopy(Object src,int srcPos, Object dest,int desPos,int length)
//返回以毫秒为单位的当前时间(从1970年到现在的毫秒数)
public static long currentTimeMillis()
//终止当前正在运行的Java虚拟机，status为 0时退出
public static void exit(int status)
//  运行垃圾收集器
public static void gc()
// 取得当前系统的全部属性
public static Properties getProperties()
//获取指定键的系统属性
public static String  getProperty(String key)
```

```
import java.util.Arrays;

public class SystemDemo {
    public static void main(String[] args) {
        int[] a = {7, 8, 9, 10, 11};
        int[] b = {1, 2, 3, 4, 5, 6};
        //从数组a的第二个元素开始，复制到b数组的第三个位置 复制的元素长度为3
        System.arraycopy(a, 1, b, 2, 3);
        //输出结果
        System.out.println(Arrays.toString(b));
        System.out.println("当前时间：" + System.currentTimeMillis());
        System.out.println("java版本信息：" + System.getProperty("java.version"));
        //运行垃圾收集器
        System.gc();
        //退出
        System.exit(0);
    }
}
```



#### Random

```
import java.util.Random;

public class RandomDemo {
    public static void main(String[] args) {
        Random random = new Random();
        //随机生成一个整数 int范围
        System.out.println(random.nextInt());
        //生成 [0,n] 范围的整数  设n=100
        System.out.println(random.nextInt(100 + 1));
        //生成 [0,n) 范围的整数  设n=100
        System.out.println(random.nextInt(100));
        //生成 [m,n] 范围的整数  设n=100 m=40
        System.out.println((random.nextInt(100 - 40 + 1) + 40));
        //随机生成一个整数 long范围
        System.out.print(random.nextLong());
        //生成[0,1.0)范围的float型小数
        System.out.println(random.nextFloat());
        //生成[0,1.0)范围的double型小数
        System.out.println(random.nextDouble());
    }
}
```

## 泛型和集合

#### 泛型

定义class Test<T>

#### Collection

接口，可以用于操作List、Set和Queue

| 方法                             | 返回值   | 说明                                                         |
| -------------------------------- | -------- | ------------------------------------------------------------ |
| add(E e)                         | boolean  | 向 collection 的尾部追加指定的元素（可选操作）               |
| addAll(Collection<? extend E> c) | boolean  | 将指定 collection 中的所有元素都添加到此 collection 中（可选操作） |
| clear()                          | void     | 移除此 collection 中的所有元素（可选操作）                   |
| contains(Object o)               | boolean  | 如果此 collection 包含指定的元素，则返回 true                |
| containsAll(Collection<?> c)     | boolean  | 如果此 collection 包含指定 collection 的所有元素，则返回 true |
| equals(Object o)                 | boolean  | 比较此 collection 与指定对象是否相等                         |
| hashCode()                       | int      | 返回此 collection 的哈希码值                                 |
| isEmpty()                        | boolean  | 如果此 collection 不包含元素，则返回 true                    |
| iterator()                       | Iterator | 返回在此 collection 的元素上进行迭代的迭代器                 |
| remove(Object o)                 | boolean  | 移除此 collection 中出现的首个指定元素（可选操作）           |
| removeAll(Collection<?> c)       | boolean  | 移除此 collection 中那些也包含在指定 collection 中的所有元素（可选操作） |
| retainAll(Collection<?> c)       | boolean  | 仅保留此 collection 中那些也包含在指定 collection 的元素（可选操作） |
| size()                           | int      | 返回此 collection 中的元素数                                 |
| toArray()                        | Object[] | 返回包含此 collection 中所有元素的数组                       |
| toArray(T[] a)                   | T[]      | 返回包含此 collection 中所有元素的数组；返回数组的运行时类型与指定数组的运行时类型相同 |

#### List

一般用ArrayList初始化

| add(int index, E element)                    | void         | 在列表的指定位置插入指定元素（可选操作）                     |
| -------------------------------------------- | ------------ | ------------------------------------------------------------ |
| addAll(int index, Collection<? extends E> c) | boolean      | 将指定 collection 中的所有元素都插入到列表中的指定位置（可选操作） |
| get(int index)                               | E            | 返回列表中指定位置的元素                                     |
| indexOf(Object o)                            | int          | 返回此列表中第一次出现的指定元素的索引；如果此列表不包含该元素，则返回 -1 |
| lastIndexOf(Object o)                        | int          | 返回此列表中最后出现的指定元素的索引；如果列表不包含此元素，则返回 -1 |
| listIterator()                               | ListIterator | 返回此列表元素的列表迭代器（按适当顺序）                     |
| listIterator(int index)                      | ListIterator | 返回此列表元素的列表迭代器（按适当顺序），从列表的指定位置开始 |
| remove(int index)                            | E            | 移除列表中指定位置的元素（可选操作）                         |
| set(int index, E element)                    | E            | 用指定元素替换列表中指定位置的元素（可选操作）               |
| subList(int fromIndex, int toIndex)          | List         | 返回列表中指定的 fromIndex（包括 ）和 toIndex（不包括）之间的部分视图 |

#### Map

一般用HashMap初始化

| 方法                                    | 返回值              | 说明                                                         |
| --------------------------------------- | ------------------- | ------------------------------------------------------------ |
| clear()                                 | void                | 从此映射中移除所用映射关系（可选操作）                       |
| containsKey(Object key)                 | boolean             | 如果此映射包含指定键的映射关系，则返回 true                  |
| containsValue(Object value)             | boolean             | 如果此映射将一个或多个键映射到指定值，则返回 true            |
| entrySet()                              | Set<Map.Entry<K,V>> | 返回此映射中包含的映射关系的 Set 视图                        |
| equals(Object o)                        | boolean             | 比较指定的对象与此映射是否相等                               |
| get(Object key)                         | V                   | 返回指定键所映射的值；如果此映射不包含该键的映射关系，则返回 null |
| hashCode()                              | int                 | 返回此映射的哈希码值                                         |
| isEmpty()                               | boolean             | 如果此映射未包含键 - 值映射关系，则返回 true                 |
| keySet()                                | Set                 | 返回此映射中包含的键的 Set 视图                              |
| put(K key, V value)                     | V                   | 将指定的值与此映射中的指定键关联（可选操作）                 |
| putAll(Map<? extends K, ? extends V> m) | void                | 从指定映射中将所有映射关系复制到此映射中（可选操作）         |
| remove(Object key)                      | V                   | 如果存在一个键的映射关系，则将其从此映射中移除（可选操作）   |
| size                                    | int                 | 返回此映射中的键 - 值映射关系数                              |
| values()                                | Collection          | 返回此映射中包含的值的 Collection 视图                       |

#### Set

一般用HashSet初始化

#### Collections

| void sort(List list)                                        | 按自然升序排序                                 |
| ----------------------------------------------------------- | ---------------------------------------------- |
| void sort(List list, Comparator c)                          | 自定义排序规则排序                             |
| void shuffle(List list)                                     | 随机排序，用于打乱顺序                         |
| void reverse(List list)                                     | 反转，将列表元素顺序反转                       |
| void swap(List list, int i , int j)                         | 交换处于索引 i 和 j 位置的元素                 |
| int binarySearch(List list, Object key)                     | 二分查找，列表必须有序，返回找到的元素索引位置 |
| int max(Collection coll)                                    | 查找最大值                                     |
| int min(Collection coll)                                    | 查找最小值                                     |
| void fill(List list, Object obj)                            | 使用 obj 填充 list 所有元素                    |
| boolean replaceAll(List list, Object oldVal, Object newVal) | 使用用 newVal 替换所有的 oldVal。              |
| <K,V> Map<K,V> synchronizedMap(Map<K,V> m)                  | 将 m 包装为线程安全的 Map                      |
| List synchronizedList(List list)                            | 将 list 包装为线程安全的 List                  |

## IO

文件流

```
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

public class Test {

    public static void main(String[] args) {
        try {
            //inFile 作为输入流的数据文件必须存在，否则抛出异常
            File inFile = new File("/home/project/file1.txt");

            //file2.txt没有，系统可以创建
            File outFile = new File("file2.txt");
            FileInputStream fis = new FileInputStream(inFile);
            FileOutputStream fos = new FileOutputStream(outFile);
            int c;
            while((c = fis.read()) != -1){
                fos.write(c);
            }
            //打开了文件一定要记着关，释放系统资源
            fis.close();
            fos.close();
        }catch(FileNotFoundException e) {
            System.out.println("FileStreamsTest:" + e);
        }catch(IOException e){
            System.err.println("FileStreamTest:" + e);
        }
    }
}
```

## 网络编程

#### HttpURLConnection

用于使用Http

```
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpUrlTest {
    public static void main(String[] args) {
        try {
            //设置url
            URL shiyanlou = new URL("https://www.shiyanlou.com");
            //打开连接
            HttpURLConnection urlConnection = (HttpURLConnection)shiyanlou.openConnection();
            //设置请求方法
            urlConnection.setRequestMethod("GET");
            //设置连接超时时间
            urlConnection.setConnectTimeout(1000);
            //获取输入流
            InputStream inputStream = urlConnection.getInputStream();
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));
            //打印结果
            bufferedReader.lines().forEach(System.out::println);
            //关闭连接
            inputStream.close();
            bufferedReader.close();
            urlConnection.disconnect();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
```

#### InetAddress

用于表示IP地址

```
import java.net.InetAddress;
import java.net.UnknownHostException;

public class InetAddressDemo {
    public static void main(String[] args) {
        try {
            InetAddress shiyanlou = InetAddress.getByName("www.shiyanlou.com");
            //toString 方法将输出主机名和ip地址
            System.out.println(shiyanlou.toString());
            //获取ip地址
            String ip = shiyanlou.toString().split("/")[1];
            //根据IP地址获取主机名
            InetAddress byAddress = InetAddress.getByName(ip);
            System.out.println("get hostname by IP address:" + byAddress.getHostName());
            System.out.println("localhost: "+InetAddress.getLocalHost());
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
    }
}
```

#### Socket

客户端套接字，步骤如下

1. 建立与服务器的连接
2. 使用输出流将数据发送到服务器
3. 使用输入流读取服务器返回数据
4. 关闭连接

```
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

public class EchoClient {
    public static void main(String[] args) {
        String hostname = "127.0.0.1";
        //socket端口
        int port = 1080;
        Scanner userIn = new Scanner(System.in);
        try {
            //建立socket连接
            Socket socket = new Socket(hostname, port);
            //获取socket输出流
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            //获取输入流
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            String userInput;
            System.out.println("请输入信息：");
            //当用户输入exit时退出
            while (!"exit".equals(userInput = userIn.nextLine())) {
                out.println(userInput);
                System.out.println("收到服务端回应:" + in.readLine());
            }
            //关闭socket
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
```



#### ServerSocket

服务端套接字，步骤如下

1. 创建服务器套接字并将其绑定到特定接口
2. 等待客户端连接
3. 通过客户端套接字获取输入流，从客户端读取数据
4. 通过客户端套接字获取输出流，发送数据到客户端
5. 关闭套接字

```
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;


public class EchoServer {
    public static void main(String[] args) {
        try {
            //服务端需要使用ServerSocket类
            ServerSocket serverSocket = new ServerSocket(1080);
            //阻塞 等待客户端连接
            Socket client = serverSocket.accept();
            PrintWriter out = new PrintWriter(client.getOutputStream(), true);
            BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
            String userIn;
            while ((userIn = in.readLine()) != null) {
                System.out.println("收到客户端消息：" + userIn);
                //发回客户端
                out.println(userIn);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
```



## 反射

| 方法                                                         | 描述                       |
| ------------------------------------------------------------ | -------------------------- |
| Field getField(String name)                                  | 获取指定的域对象           |
| Field[] getFields()                                          | 返回所有的公有域对象数组   |
| Method getDeclaredMethod(String name, Class<?>... parameterTypes) | 返回指定的方法对象         |
| Method[] getMethods()                                        | 返回所有的公有方法对象数组 |
| Method[] getDeclaredMethods()                                | 返回所有方法对象数组       |
| String getName()                                             | 获取全限定名               |