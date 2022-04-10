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

