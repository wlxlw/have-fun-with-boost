# 为什么要设计智能指针  
  管理动态分配的内存，自动实现对内存的释放,从而减少内存泄露
# RAII(Resource Acquisition Is Initialization)与智能指针
## RAII C++语言的一种管理资源、避免泄漏的惯用法
现代C++在栈上申明对象，对象可以在堆上申请资源。在该对象被创建的时候，构造函数会在堆上申请资源；在对象的生命周期结束时，对象会自动调用析构函数释放堆上的资源
## 智能指针
1. 将任何**堆分配的资源**的所有权授予**栈分配的智能指针**，由智能指针自动管理堆内存
2. C++标准库中的智能指针
   1. unique_ptr 
      1. 定义：unique_ptr不共享指针。它不能以任何形式被**复制**(复制到另一个unique_ptr，通过值传递给函数，或者在任何需要复制的 C++ 标准库算法中使用)，但是支持**移动**。在构造unique_ptr时，推荐使用**异常安全**的make_unique辅助函数
      2. 使用：code ~/have-fun-with-boost/smart_ptr/utilize_unique_ptr.cc
          ```bash
          cd ~/have-fun-with-boost/smart_ptr
          g++ utilize_unique_ptr.cc
          ./a.out
          ```
   2. share_ptr
      1. [定义](https://docs.microsoft.com/en-us/cpp/cpp/how-to-create-and-use-shared-ptr-instances?view=msvc-170)：专为多个所有者可能必须管理内存中对象的生命周期的情况而设计，可以复制它，通过函数参数中的值传递它，并将其分配给其他shared_ptr实例。所有实例都指向同一个对象，并共享对一个“控制块”的访问权限，该控制块在shared_ptr添加新对象、超出范围或重置时增加和减少引用计数。当引用计数达到零时，控制块删除内存资源和自身。在构造unique_ptr时，推荐使用**异常安全**的make_share辅助函数
      2. 使用：code ~/have-fun-with-boost/smart_ptr/utilize_share_ptr.cc
       ```bash
       cd ~/have-fun-with-boost/smart_ptr
       g++ utilize_share_ptr.cc
       ./a.out
       ```
      2. 注意点
         1. 循环引用问题
            1. 通过share_ptr创建的几个对象之间互相引用，形成一个环，导致环上的对象引用计数值不会减小到0，内存空间不会被释放，导致内存泄漏
            2. code  `~/have-fun-with-boost/smart_ptr/share_ptr_circular_reference.cc`
   3. weak_ptr
      1. [定义](https://docs.microsoft.com/en-us/cpp/standard-library/weak-ptr-class?view=msvc-170#lock)类模板描述了一个指向由一个或多个对象管理的资源的shared_ptr对象。指向资源的weak_ptr对象**不会影响资源的引用计数，并且无法直接访问管理的对象(需要先转换成share_ptr)**。当shared_ptr管理该资源的最后一个对象被销毁时，该资源将被释放，即使有weak_ptr指向该资源的对象也是如此。此行为对于**避免数据结构中的循环**至关重要。
      2. 使用
         1. 通过weak_ptr**解决循环引用**code `~/have-fun-with-boost/smart_ptr/weak_ptr_circular_reference.cc`
         2. [构建一个对象的临时所有权](https://en.cppreference.com/w/cpp/memory/weak_ptr/lock)