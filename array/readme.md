# 从boost/array.hpp开始学习C++
   array.hpp文件位置 boost_1_77_0/boost/array.hpp
# 问题
1. 什么是hpp文件？
    hpp文件时.h文件和.cpp文件的结合体，即定义以及实现都在同一个文件中完成。

    **优点**(适合开源库的编写)
      1. project只需要include该hpp文件即可使用，无需加入cpp文件到project中进行编译
      2. 减少project中cpp文件的编译次数

    **[注意点](https://baike.baidu.com/item/HPP/4448301)**
      1. 不可包含全局对象和全局函数
      2. 类之间不可循环调用
      3. 不可使用静态成员
   
2. 什么是模板，为什么要用模板？
   很多时候，函数与类的**实现**与对**传入参数的类型**没有严格的限制。

   为了实现代码的重用，可以对函数与类处理的参数类型**进一步的抽象**，使用占位符对参数类型进行定义，参数具体的类型等模板函数(类)编译时传入的参数确定。

3. [typedef](https://www.runoob.com/cprogramming/c-typedef.html)
   1. 定义类型别名,贴几个例子
   ```
      typedef T              value_type;
      typedef T*             iterator;
      typedef const T*       const_iterator;
      typedef T&             reference;
   ```
   2. 作用域与变量的作用域等同

4. [BOOST_ASSERT_MSG](https://www.boost.org/doc/libs/1_77_0/libs/assert/doc/html/assert.html#boost_assert_msg) && assert
   1. 访问Array中元素的代码
      ```cpp
      reference operator[](size_type i) 
        { 
            return BOOST_ASSERT_MSG( i < N, "out of range" ), elems[i]; 
        }
      ```
      [`return a,b,c`](https://stackoverflow.com/questions/38943900/what-does-return-a-b-do-and-why)相当于执行`a,b,c`再返`c`
   1. BOOST_ASSERT_MSG相当于assert((expr)&&(msg))，如果expr为0则中断程序，并输出错误信息

  
   2. assert(头文件assert.h)广泛用于调试程序，调试结束后可以通过 `#define NDEBUG` 禁止assert的调用 

# TODO
1. 模板实现原理，编译相关

