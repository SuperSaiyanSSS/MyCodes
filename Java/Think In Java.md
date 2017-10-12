# Think In Java 学习
====================

选择性看重点内容，没时间看完全书

## 第一章 对象导论

#### 包访问权限（frinedly)
当没有使用 public protected private 这些访问指定词时，包访问权限将发生作用。

在这种权限下，类可以访问在同一个包（库构件）中的其他类的成员。但是在包之外，这些成员如同指定了 private 一样

##### 拓展
Java语言中有4中访问修饰符:friendly(默认)、private、public和protected。

    public ：能被所有的类(接口、成员)访问。

    protected：只能被 【本类】 、【同一个包中的类】访问；如果在【其他包】中被访问，则必须是该成员所属类的【子类】。

    private：成员变量和方法都【只能在定义它的类中】被访问，其他类都访问不到。对成员变量的进行获取和更改，一般用get()，set() ，public 方法。实现了Java面向对象的封装思想。

    friendly（缺省）：访问权限与protected相似，但修饰类成员时不同包中的子类不能访问。

#### 组合（composition)
使用现有的类合成新的类

#### “是一个”与“像是一个”关系
* 是一个：继承只覆盖基类的方法 基类与导出类为**is-a**关系

* 像是一个：导出类型中添加了新的接口元素，这种替代并不完美，因为基类无法访问新添加的接口，为**is-like-a**关系

#### 伴随多态的可互换对象

* 前期绑定：编译器将产生一个具体函数名字的调用，运行时将这个调用解析到将要被执行的代码的**绝对地址**

然而在OOP中，程序直到运行时才能够确定代码的地址，所以当消息发送到一个泛化对象时，需要采取其他的机制

* 后期绑定：使用一小段特殊的代码来代替绝对地址调用，这段代码使用对象中存储的信息来**计算**方法体的地址

Java中后期绑定是默认行为，而C++中则需要使用virtual关键字

与弱类型的区别：编译器是否对调用参数和返回值执行类型检查

#### 单根继承结构

除C++之外的其他OOP语言均采用单根继承结构


## 第二章 一切都是对象

#### 存储到什么地方
* 寄存器
* 堆栈
* 堆

    存放所有的Java对象

* 常量存储 

    如字符串池，所有字面常量字符串和具有字符串值的常量表达式都置于特殊的静态存储区中

* 非RAM存储

    流对象和持久化对象

**特例** 基本类型

不用new来创建变量，而是创建一个**并非是引用**的变量

该变量直接存储**值**，并置于堆栈中，因此更为高效

#### Java中的数组

当创建一个数组对象时，实际上是创建了一个引用数组，并且每个引用都会初始化为一个特定值，该值拥有自己的关键字null

#### 作用域

Java不允许用小作用域内的同名变量“隐藏”大作用域的同名变量

#### 嵌入式文档 
javadoc是提取注释并输出HTML文件的工具

所有的javadoc命令都只能在" /** "注释中出现 注释结束于" */"

javadoc只能为public 和 protected成员进行文档注释

如要包含private 则使用-private作为标记

* @see 引用其他类的文档

    @see classname
* {@link package.class#member label}

* @author 
    
    @author author-information

* @param

    该标签用于方法文档中

    @param parameter-name description

* @return

    该标签用于方法文档中

    @return description

* @version

    @version version-information

* @throws

示例：
```
package com.company;
import java.util.*;

/** The first Thinking in Java example program.
 * Displays a string and today's date
 * @author SuperSaiyanSSS
 * @author supersaiyan.me
 * @version 4.0
 */
public class Main {
    /**
     *
     * @param args array of string arguments
     */
    public static void main(String[] args) {
	// write your code here
        System.out.println("HELLO! ");
        System.out.println(new Date());
    }
}
```
 