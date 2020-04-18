1. 数组长度array.length，字符串长度str.length()

2. 类中，static方法只能调用static变量（存疑）

3. 输入:BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))

4. 数组声明 int[] arr = new int[10]

5. 动态数组声明 ArrayList<String> list = new ArrayList<String>()

6. 字符串按下标访问 str.charAt(position)

7. 复制数组

   1.  int [] numbersCopy = Arrays.copyOf(numbers, numbers.length);
   2. int [] numbersCopy = Arrays.copyOfRange(numbers, 2,6);

8. arrayList查找元素对应下标 int thomasIndex = cats.indexOf(thomas);

9. 快速for循环 for (Cat cat: cats) 

10. 迭代器

    1. Iterator<Cat> catIterator = cats.iterator();// Create an iterator
    2. while(catIterator.hasNext())

11. 类中static函数

    1. 不需要声明类的具体对象，即可调用

12. 字符串

    1. str.charAt(pos) 取某一个下标
    2. str.length() 获取长度
    3. 判断输入完成 string == null || string.isEmpty()

13. 数组

    1. int[] list = new int[个数]
    2. 

14. 动态数组

    1. 声明 ArrayList<String> list = new ArrayList<String>()
    2. 索引调用 list.get(pos)
    3. 获取大小 list.size()
    4. 删除 list.remove(pos)，list.remove(str)

15. try catch

    1.             try{
                   ​    Thread.sleep(100);
                   }
                   catch(InterruptedException e){
                   }

16. Date

    1. 获取毫秒 

       ```
       long miao = new Date().getTime();
       ```

    2. 

17. Map

    1. 声明 

       ```
       Map<String,String> map = new Map<String,String>();
       ```

    2. 遍历1

       ```
       for (Map.Entry<String,String> pair : map.entrySet())
       	System.out.println(pair.getKey() + " - " + pair.getValue());
       ```

    3. 遍历2

       ```
       Iterator<Map.Entry<Integer,String>> it=map.entrySet().iterator();
       		while(it.hasNext()){
       			Map.Entry<Integer,String> entry=it.next();
       			System.out.println("key="+entry.getKey()+","+"value="+entry.getValue());
       		}
       
       ```

    4. 获取集合 

       1. 获取所有对集合 entrySet()
       2. 获取所有键集合 keySet()
       3. 获取所有值集合 values()

       ```
       ArrayList<String> valuesList = new ArrayList<String>(map.values());
       ```

    5. 添加对 pus(key, value)

    6. 获取指定键的值 get(key)

    7. 检查存在

       1. 检查指定键是否存在 containsKey(key)
       2. 检查指定值是否存在 containsValue(value)
       3. 检查映射是否为空 isEmpty()

    8. 清除映射 clear()

    9. 删除指定键的值 remove(key)

       ```
       HashMap<String, String> copy = new HashMap<String, String>(map);
               for (Map.Entry<String, String> pair : copy.entrySet()) {
                   if (pair.getValue().equals(value))
                       map.remove(pair.getKey());
               }
       ```

    10. 

18. 集合

    1. 添加 add, addAll

    2. 删除 remove, removeAll

    3. 检查指定元素是否存在 contains, containsAll

    4. 删除元素需要使用迭代器

       ```
       Iterator <Integer> iter = set.iterator();
         while(iter.hasNext()) {
          Integer temp = iter.next();
          if (temp > 10)
          iter.remove();
       ```

    5. 

19. Date

    1. getMonth 获取月份，注意是从0开始

20. collections

    1. 排序 Collections.sort(某个数组)
    2. 最大最小值 Collections.max Collections.min
    3. 倒序 Collections.reverse(某个数组)
    4. 打乱顺序 Collections.shuffle(某个数组)
    5. 传递一个不可变列表 Collections.unmodifiableList()
    6. 交换 Collections.swap(数组，数组索引1，数组索引2)
       1. 数组索引可以使用ArrayList.indexOf()
    7. 检查两个数据集合是否具有至少一个相同元素 disjoint

21. LinkedList

    1. 双向链表

    2. 插入

       1. 插入头部 addFirst
       2. 插入尾部 addLast

    3. 查找

       1. 输出头部 peekFirst()
       2. 输出尾部 peekLast()

    4. 查找并删除

       1. 头部 pollFirst()
       2. 尾部 pollLast()

    5. 返回包含列表项的数组

       1. toArray() 

       ```
       Car[] carsArray = cars.toArray(new Car[3]);
       ```

22. HashMap

    1. 判断是否包含 containsKey() containsValue()
    2. 是否为空 isEmpty()
    3. 合并HashMap map1.putAll(map2)

23. 堆栈

    1. 声明 StackTraceElement[] stack = Thread.currentThread().getStackTrace()
    2. 获取堆栈中函数名 getMethodName()
    3. 返回上一层调用当前函数的函数名 Thread.currentThread().getStackTrace()[2].getMethodName();
    4. 获取类名 getClassName()

24. exception

    1. 想要在函数中抛出exception，需要在函数声明时throws对应想要抛出的exception类型

       ```
           public static void handleExceptions() throws FileSystemException {
               try{
                   BEAN.throwExceptions();
               } catch(FileSystemException e1) {
                   BEAN.log(e1);
                   throw e1;
                   // throw e1;
               } catch(IOException e2) {
                   BEAN.log(e2);
               } 
           }
       ```

    2. 显示发生异常的堆栈跟踪

       ```
           public static void printStack(Throwable throwable) {
               System.out.println(throwable);
               for (StackTraceElement element : throwable.getStackTrace()) {
                   System.out.println(element);
               }
           }
       ```

25. 文件输入流InputStream

    1. available() 返回可读取的字节数
    2. close() 关闭输入流
    3. read() 返回流中下一个可用字节的整数表示，若达到末尾则返回-1
    4. read(byte[] buffer, int byteOffset, int byteCount) 将部分字节读取到缓冲区，并返回读取的字节数
    5. skip(long byteCount) 跳过输入流中的byteCount数量字节

26. 文件流

    1. InputStream 输入流
    2. OutputStream 输出流

27. 文件输出流 OutputStream

    1. close() 关闭输出流
    2. flush() 清除输出缓冲区
    3. write(int oneByte) ， write(byte[] buffer), write(bytep[] buffer, int offset, int count) 写入

28. 在类和接口中，被拓宽强制转换后，方法的实现以原类为主，但是方法的种类和数量以新类为主