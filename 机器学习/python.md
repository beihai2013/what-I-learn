## Numpy

是一种多维数组，提供了很多方便的操作，并且运行效率高于python内置数组

### 包引用

```
import numpy as np
```

下面假设arr是一个数组

### 创建

1. $np.array(arr)$ 通过数组创建narrays
2. np.zeros((x轴个数，y轴个数...)) 创建全0数组
3. $np.array(arr, dtype=np.float64)$ 指定narrays的元素数据类型

### 查询

1. #### 切片 

   1. arr[5:8] 第6-8个元素，左闭右开
   2. arr[:] 所有元素
   3. arr[0,2] = arr\[0]\[2]
   4. arr[:2] 第1-2个
   5. arr[1:] 第1个到最后一个

2. #### 布尔型

   ```
   names = np.array(['Bob', 'Joe', 'Will', 'Bob', 'Will', 'Joe', 'Joe'])
   data = np.random.randn(7, 4)
   print(data[names == 'Bob'])
   ```

   

3. 

### 属性

1. arr.ndim 维度
2. arr.shape 各维度大小
3. arr.dtype 各元素数据类型

### 方法

1. $arr.astype(np.int32)$ 转换arr中元素的数据类型为int32
2. 一些数学函数，如abs,sqrt,exp等
3. $np.where(x,c,y)$=if x c else y。c和y可以是标量
4. **统计方法** sum, mean, std标准差，var方差，min最小值，max最大值，argmin最小元素的索引，argmax最大元素的索引，cumsum所有元素累积和，cumprod所有元素累积积
5. np.sort(a, axis, kind, order)。
   1. axis为排序依据轴
   2. kind有quicksort,mergesort,heapsort三种，默认quicksort
6. np.argsort() 排序后返回的索引
7. **集合操作** 
   1. $unique(x)$ 计算x中唯一元素，返回有序结果
   2. $intersect1d(x,y)$ 计算x和y的公共元素，返回有序结果
   3. $union1d(x,y)$ 计算x和y的并集，返回有序结果
   4. $in1d(x,y)$ x是否包含于y的布尔型数组
   5. $setdiff1d(x,y)$ 集合差，在x中不在y中
   6. $setxor1d(x,y)$ 集合对称差
8. np.random 提供了随机数生成的方法

1. $arr.T$ 转置矩阵
2. arr.tranponse(轴编号组成的元组)​
3. $np.dot(x,y)$ 点积
4. @ 矩阵乘法
5. np.linalg有矩阵分解和求逆和行列式的函数

## Pandas

### 包引用

import pandas as pd

### Series

序列，有三种创建方法：基于数组、基于字典、基于DataFrame中的某一行或某一列

```
arr1 = np.arange(10)
s1 = pd.Series(arr1)
dic1 = {'a':10,'b':20,'c':30,'d':40,'e':50}
s2 = pd.Series(dic1)
```

### DataFrame

#### 创建

数据框，三种创建方法：基于二维数组、基于字典、基于数据框

```
//基于二维数组
arr1 = np.array(np.arange(12)).reshape(4,3)
df1 = pd.DataFrame(arr1)
//基于字典
dic2 = {'a':[1,2,3,4],'b':[5,6,7,8],'c':[9,10,11,12],'d':[13,14,15,16]}
df2 = pd.DataFrame(dic2)
dic3 = {'one':{'a':1,'b':2,'c':3,'d':4},'two':{'a':5,'b':6,'c':7,'d':8},'three':{'a':9,'b':10,'c':11,'d':12}}
df3 = pd.DataFrame(dic3)
//基于数据框
df4 = df3[['one','three']]
```

#### 索引

```
print('s4[3]: ',s4[3])
print('s4[e]: ',s4['e'])
print("s4[1,3,5]: ",s4[[1,3,5]])
print("s4[['a','b','d','f']]: ",s4[['a','b','d','f']])
print('s4[:4]: ',s4[:4])
print("s4['c':]: ",s4['c':])
print("s4['b':'e']: ",s4['b':'e'])
```

DataFrame中的自动化对齐，会使两个运算的DataFrame数据框合成一个框，对于索引在对方数据框中没有出现的数据项，产生缺失值。

#### 查找

1. 数据前5行后5行 $student.head(), student.tail()$

2. 数据指定行 $student.loc([[0,2,4,5,7]])$

3. 数据指定列 $student[['Name','Height','Weight']].head()$ $student.loc[:,['Name','Height','Weight']].head()$

4. 条件查询

    $$student[(student['Sex']=='F') \& (student['Age']>12)][['Name','Height','Weight']]$$

5. 

#### 数学统计

```
np.random.seed(1234)
d1 = pd.Series(2*np.random.normal(size = 100)+3)
d2 = np.random.f(2,4,size = 100)
d3 = np.random.randint(1,100,size = 100)

print('非空元素计算: ', d1.count()) #非空元素计算
print('最小值: ', d1.min()) #最小值
print('最大值: ', d1.max()) #最大值
print('最小值的位置: ', d1.idxmin()) #最小值的位置，类似于R中的which.min函数
print('最大值的位置: ', d1.idxmax()) #最大值的位置，类似于R中的which.max函数
print('10%分位数: ', d1.quantile(0.1)) #10%分位数
print('求和: ', d1.sum()) #求和
print('均值: ', d1.mean()) #均值
print('中位数: ', d1.median()) #中位数
print('众数: ', d1.mode()) #众数
print('方差: ', d1.var()) #方差
print('标准差: ', d1.std()) #标准差
print('平均绝对偏差: ', d1.mad()) #平均绝对偏差
print('偏度: ', d1.skew()) #偏度
print('峰度: ', d1.kurt()) #峰度
print('描述性统计指标: ', d1.describe()) #一次性输出多个描述性统计指标
```

#### 数据本身的增删查改

1. 增行或列 $student3 = pd.concat([student,student2])$

2. 删除行或列 $student.drop([0,1,3,6])$  $student.drop(['Height','Weight'],axis=1)$

#### 缺失值处理

1. 统计缺失值数目 $sum(pd.isnull(s))$
2. 删除缺失值 $s.dropna()$
3. 用0填充缺失值 $df.fillna(0)$
4. 前项填充缺失值 $df.fillna(method='ffill')$
5. 后项填充缺失值 $df.fillna(method='bfill')$
6. 常量填充不同列 $df.fillna({'x1':1,'x2':2,'x3':3})$
7. 