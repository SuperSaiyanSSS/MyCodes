+ 形参 formal parameter
+ 实参 actual parameter

#### 传值参数(value parameter) 
在函数执行前，把实参复制给形参。复制过程是由形参类型的复制构造函数(copy constructor)完成的。在函数结束后，形参类型的析构函数(destructor)负责释放形式参数。

#### 引用参数(reference parameter) 
各个实参是各个形参的别名，在函数执行前，程序没有复制实参的值，在函数结束后，也没有调用析构函数。

模板函数的参数类型是一个变量，它的值由编译器决定

#### 引用返回(reference return) 
函数返回类型增加一个后缀&，返回的是一个引用。引用只是一个别名，不是一种数据类型，也不占存储单元。

 const 用于常量引用与const型引用返回

#### 签名(signature) 
由该函数的形参类型以及形参个数确定。任何两个同名函数不能有同样的签名。

#### 函数重载(fuction overloading) 
定义多个同名函数的机制

关于C++函数结束之前一定要delete之前new的数组以及函数里面定义变量的问题？

必须要 delete，只有指向这两个数组的两个指针才是局部变量。如果没有在函数内部 delete，函数结束后指向这两个数组的指针就会被销毁，无法释放这两个数组占用的内存。2. 在函数内定义的静态变量会在程序运行期间一直占用内存，不管函数有没有被调用。

异常
+ 抛出异常 throw
+ 处理异常 catch(类型 变量)
          catch(...){}  捕获所有类型的异常

动态生成二维、多维数组 需要依次生成之前的数组
```
x = new int* [numOfRows]
for(int i=0;i<numOfRows;i++){
    x[i] = new int [numOfColumns];
}
```
delete []x 释放数组x的空间
```
for(int i=0;i<numOfRows;i++){
    delete [] x[i];
}
delete []x;
x = NULL;
```
比类名多了一个前缀~的函数：析构函数
析构函数通常为{} 如果创建了动态数组，那么当对象超过作用域时，析构函数需要释放动态数组空间，这时的析构函数就不是空函数。

成员函数如果不在类声明体里实现吗，而在外部实现，就必须使用作用域说明符(scope resolution operator):: 以指明该函数是其类的成员函数

