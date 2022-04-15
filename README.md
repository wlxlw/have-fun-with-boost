# have-fun-with-boost
1. boost的下载 boost_distribution
2. TODO
   1. - [x] Array  
      1. - [x] 阅读c++ template book前两章
      2. - [x] "Code" Array添加类似python倒叙访问的功能  
         *code->* array/code/array_with_reverse_access.cc
      3. - [x] 学习模板重载，模板特例化；基于vector实现模板栈  
         *code->array/code/*(template_overload.cc, my_stack.cc,my_stack.hpp)
      4. - [x] 学习萃取
         1. 阅读《STL源码剖析第三章》，boost/iterator/advance.hpp源码
         2. 针对双向迭代器和随机访问迭代器，实现advance函数(包含萃取)  
            *code->* array/code/traits
   2. - [ ] Unordered -> unordered_map