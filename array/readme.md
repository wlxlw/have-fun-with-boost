# 从boost/array.hpp开始学习C++
   array.hpp文件位置 boost_1_77_0/boost/array.hpp
# 问题
0. [如何使用boost编程](https://www.boost.org/doc/libs/1_78_0/more/getting_started/unix-variants.html)  
   1. 首先`#include<boost/whatever.hpp>`
   2. `g++ -I path/to/boost_1_77_0 example.cpp -o example`
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
   
   很多时候，函数与类的**实现**与对**传入参数的类型**没有严格的限制。为了实现代码的重用，可以对函数与类处理的参数类型**进一步的抽象**，使用占位符对参数类型进行定义，参数具体的类型由模板函数(类)编译时传入的参数确定。

3. [typedef](https://www.runoob.com/cprogramming/c-typedef.html)
   1. 定义类型别名,贴几个例子
   ```
      typedef T              value_type;
      typedef T*             iterator;
      typedef const T*       const_iterator;
      typedef T&             reference;
   ```
   1. 作用域与变量的作用域等同

4. [BOOST_ASSERT_MSG](https://www.boost.org/doc/libs/1_77_0/libs/assert/doc/html/assert.html#boost_assert_msg) && assert
   1. 访问Array中元素的代码
      ```cpp
      reference operator[](size_type i) 
        { 
            return BOOST_ASSERT_MSG( i < N, "out of range" ), elems[i]; 
        }
      ```
      [`return a,b,c`](https://stackoverflow.com/questions/38943900/what-does-return-a-b-do-and-why)相当于执行`a,b,c`再返回`c`
   2. BOOST_ASSERT_MSG相当于assert((expr)&&(msg))，如果expr为0则中断程序，并输出错误信息

  
   3. assert(头文件assert.h)广泛用于调试程序，调试结束后可以通过 `#define NDEBUG` 禁止assert的调用 

5. [条件编译中的判断语句`#if #if !defined #if #elif #else`](https://blog.csdn.net/freeWayWalker/article/details/50035923)  
   条件编译时C语言中预处理部分的内容，是编译器编译代码时最优先处理的部分，如果宏条件符合，编译器就编译这段代码，否则编译器就忽略这段代码，**不进行编译**。  
   ```c++
   #if defined(x)
      ...code..//如果定义了x这个宏，编译器会编译code，否则直接忽略code
   ```

6. 使用模板时，占位符typename class有区别吗？  
   没有区别
# TODO
1. - [x] 阅读C++ template前两章(模板实现原理，编译相关，隐式接口与多态)
   1. - [x] 类型萃取(type trait)
   2. - [ ] 作为返回类型的模板参数(chapter 1.3.1)
   3. - [x] 模板重载的优先级 *code->* array/code/template_overload.cc  
      **模板重载时，要确保对任意一个调用，都只会有一个模板匹配**
      1. 优先匹配非模板函数
      2. 如果模板可以实例出更匹配的函数，优先选择此模板函数
      3. 模板参数推断时不允许自动类型转换，而常规函数是允许的
      4. 确保在调用某个函数模板之前，编译器已经看到了相对应的模板定义

   4. - [x] 基于vector实现模板类my_stack
      1. - [x] [`const T&` 与 `T const&`的区别](https://stackoverflow.com/questions/2640446/why-do-some-people-prefer-t-const-over-const-t) 答: 没有区别,都表示对T的常量引用
      2. - [x] *code1->* array/code/my_stack.hpp  *code2->* array/code/my_stack.cc
      3. - [x] 增加对my_stack进行特例化的代码
   
2. - [x] 魔改Array，实现类似python访问倒数第N个元素的功能(a[N], a.size()<=N<0)  
   *code->* array/code/array_with_reverse_access.cc

3. - [x] 阅读《STL源码剖析》第三章迭代器部分，结合array.hpp，[typename的前世今生](https://feihu.me/blog/2014/the-origin-and-usage-of-typename/#typename%E7%9A%84%E5%B8%B8%E8%A7%81%E7%94%A8%E6%B3%95)
   1. `typename T::is_type` typename关键字用来标记is_type是一个类型，用于解决**is_tpye是一个依赖于模板参数T的名称时，可能产生的错误，例如T是一个class，is_type是其中一个静态成员变量** 

   2. 迭代器的设计意义：是容器与算法之间进行沟通的桥梁
   
   3. 源码分析&类型萃取
      1. 简介  
         类型萃取的模板类实现的功能:**接收一个模板参数，提取这个模板参数对应的associated types**，对于迭代器，associated type包括value_type, difference_type, pointer, reference, iterator_category。**从而将模板参数对应的重要类型传递给其他模板**。  
      2. 源码分析  
         在boost/attay.hpp中，reverse_iterator是模板类reverse_iterator的别名
         ```c++
         typedef std::reverse_iterator<iterator> reverse_iterator;//将模板参数iterator传递给反向迭代器
         typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
         ```  
         查找模板类reverse_iterator -> /user/include/c++/9/bits/stl_iterator.h  
         ```c++
         template<typename _Iterator>
         class reverse_iterator
         :...//此处省略继承的代码
         {  protected:
               _Iterator current;
               typedef iterator_traits<_Iterator>		__traits_type;

            public://使用萃取模板萃取_Iterator中的重要参数名称
               typedef _Iterator					iterator_type;
               typedef typename __traits_type::difference_type	difference_type;
               typedef typename __traits_type::pointer		pointer;
               typedef typename __traits_type::reference		reference;
            ...//省略
         }
         ```
         查找模板类iterator_traits-> /user/include/c++/9/bits/stl_iterator_base_type.h  
         ```c++
         template<typename _Iterator, typename = __void_t<>>
            struct __iterator_traits { };

         template<typename _Iterator>
            struct __iterator_traits<_Iterator,
                     __void_t<typename _Iterator::iterator_category,
                           typename _Iterator::value_type,
                           typename _Iterator::difference_type,
                           typename _Iterator::pointer,
                           typename _Iterator::reference>>
            {//萃取模板参数_Iterator中的5个类型名称
               typedef typename _Iterator::iterator_category iterator_category;
               typedef typename _Iterator::value_type        value_type;
               typedef typename _Iterator::difference_type   difference_type;
               typedef typename _Iterator::pointer           pointer;
               typedef typename _Iterator::reference         reference;
            };

         template<typename _Iterator>
            struct iterator_traits
            : public __iterator_traits<_Iterator> { };
         ```
      3. 萃取 例子讲解(结合STL源码剖析第三章,与boost的advance.hpp)  
         产生原因：重载函数接收的参数不能都是模板参数（因为此时编译器无法根据传入的参数推断调用哪个函数）  
         解决方法：为此通过萃取提取模板参数对应的参数类型(模板参数对应的类中需要事先定义一个确定的类型)
         1. 重载函数接收的参数不能都是模板参数  
            *code->* array/code/traits/1_why_need_traits.cc
         2. 模板参数对应的类中事先定义一个确定的类型  
            *code->* array/code/traits/2_help_compiler_distinguish_function.cc
         3. 使用萃取简化代码，提取2中定义的类型  
            *code->* array/code/traits/3_simplify_code_iterator_traits.cc

