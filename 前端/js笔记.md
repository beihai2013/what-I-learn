# debug

1. console.log
2. console.log(typeof variable)

# data structure

1. array.splice(start, num, ...arr)，会对array进行修改，返回被删除的数组
   1. 注意此函数会修改原数组，在自定义函数中会出现修改参数值的情况，并且js中是传引用修改
   2. 因此在自定义函数使用此函数时，为了防止影响原参数的值，需要声明新的变量，splice对新变量进行修改
2. array.slice(start, end+1)，不会对array进行修改

# function

1. array.reduce
2. array.map(a=>({title:a.title, b:a.name}))
   1. a不需要重新定义，代表遍历array里每一个项的临时变量
   2. 返回一个对象集合{title:"", b:""}
3. Math.max(arr)：注意arr为()。若为array，则需要变换为(...arr)
4. typeof variable：输出的是字符串，所以判断类型需要如例typeof var == "boolean"
5. toUpperCase, toLoweCase：大小写转换
6. string.substr(start, length)：字符串不能 以str[i]=“a”的形式修改，必须用=或replace函数修改
7. string.charCodeAt()：字符转ascii码
8. String.fromCharCode(num)：ascii码转字符

# string

1. string.substr(start, length)：字符串不能 以str[i]=“a”的形式修改，必须用=或replace函数修改
2. 数字转字符串 number + ""

# 面向对象

1. 构造器函数声明 


```
   function Dog(){
   this.name = name;}
```

2. 构造器函数使用

   ```
   let dog = new Dog()
   ```

3.构造器确认类型

```
dog instanceof Dog；//返回true，则为同一类型
```

4. 继承属性。与原始object中属性区分，通过以下方式定义

```
Dog.prototype.numlegs = 4;
```
5. 判断构造器类型

```
dog.constructor == Dog
```

6. 原型继承构造器

```
Son.prototype = Object.create(Father.prototype);
```

7. 原型的构造器类型更改

```
Son.prototype.constructor = Son;
```

8. 原型声明函数

```
Son.prototype.func = function(){};
```

9. 以对象为参数，可以给对象添加函数

```
let flyMixin = function(obj) {
  obj.fly = function() {
    console.log("Flying, wooosh!");
  }
};
let plane = {
  model: "777",
  numPassengers: 524
};
flyMixin(plane);
```

9. 对象里私有变量的声明方法

```
//全局变量，可在外部访问
function Bird(){
    this.var = 1;
}
let temp = new Bird();
console.log(temp.var);
//私有变量
function Bird(){
    let var = 1;
    this.getVar(){return var;}
}
```

10. 立即执行的函数

```
// 注意没有函数名，以及末尾多了括号
(function () {
  console.log("Chirp, chirp!");
})()
```



# 并行编程

## await/async

### 使用条件

function关键词前包含async关键字时，可以使用await

### 用途

await使Javascript运行暂停于此行，允许其他代码在此期间执行，知道异步函数调用返回其结果

## promise

### 基本用法

```javascript
let p = new Promise((resolve, reject)=>{
	if(...)
     	resolve()
  else
    	reject()
})
p.then(()=>{
  
}, ()=>{
  
})
```



### promise.all(iterator)

在iterator的参数对象里所有promise对象成功时才会触发成功，并将所有promise返回值的数组作为成功回调的返回值

# map

## map和foreach的区别

```javascript
[1,2,3].map(d=>d+1);// [2,3,4]
[1,2,3].foreach(d=>d+1); // undefined
```

map在对原数组进行操作时，会返回一个**新数组**

foreach是对原数组数据进行操作

### 速度

都比传统的for慢