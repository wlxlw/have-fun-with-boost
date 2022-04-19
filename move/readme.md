# 左值与右值  
0. 推荐阅读 [右值引用简析](https://www.artima.com/articles/a-brief-introduction-to-rvalue-references)
1. 定义  
   左值与右值代表的是表达式的属性。左值表示的是对象的身份，右值表示的是对象的值
2. 区别  
   左值持久，右值短暂。  
   左值：**非临时对象**， 
   右值：**临时对象**
3. 左值引用  
   资源通过`&`绑定到左值上  
   **关键性质** 对左值引用的资源的修改，会直接改变资源本身
4. 右值引用  
   资源通过`&&`绑定到右值上  
   **关键性质** 右值引用只能绑定到一个将要销毁的对象，因此可以自由的将右值引用的资源移动到另一个对象
5. 区分左值引用和右值引用的原因  
   为了更好的实现*move*语义，进而提高程序的执行效率

# move
1. 出现的原因  
   复制操作的代价很高，而实际上很多程序无需复制即可实现 code-> move/why_need_move.cc
2. move需要完成什么任务  
   接收一个左值或者右值，返回一个**右值引用**
3. move如何实现，boost/move/utility_core.hpp源码
    ```c++
    template <class T>
    BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::remove_reference<T>::type && move(T&& t) BOOST_NOEXCEPT
    { return static_cast<typename ::boost::move_detail::remove_reference<T>::type &&>(t); }
    ``` 
    1. `remove_reference<T>::type` 移除参数T中的引用标记  
    `static_cast<T>(i)` 将i强制转换成T类型
    2. 传入的参数T是右值的情况,例如`move(string("hello"))`
       1. 推断出T是string类型
       2. `remove_reference<string>::type`为string
       3. `string&& move(string&&)`
       4. 返回`static_cast<string &&>(t)`，`t`为右值引用，强制转换后还是右值引用
    3. 传入参数T是左值引用的情况，例如`string s("hello");move(s);`
       1. 推断T是string&类型，此处发生了一个**引用折叠**`string& &&`折叠成`string &`
       2. `remove_reference<string&>::type`为string
       3. `string&& move(string& &&)`即 `string&& move(string&)`
       4. 返回`static_cast<string &&>(t)`，`t`是左值引用，强制转换后为右值引用

# 重载左值与右值
在左值与右值得概念下提高程序的效率  
   对于同一个类，在传入参数是左值时，可以提供复制语义；  
   在传入参数是右值时，可以提供移动语义(例如直接复制指针的值，并将传入的右值指针指向0)来提高程序的效率。  
   显然，可以使用函数重载来轻松实现对左值与右值得处理
   ```c++
    template <class T>
    class clone_ptr
    {
    private:
        T* ptr;
    public:
        // construction
        explicit clone_ptr(T* p = 0) : ptr(p) {}
        // destruction
        ~clone_ptr() {delete ptr;}
        // copy semantics
        clone_ptr(const clone_ptr& p)
            : ptr(p.ptr ? p.ptr->clone() : 0) {}
        clone_ptr& operator=(const clone_ptr& p)
        {
            if (this != &p)
            {
                delete ptr;
                ptr = p.ptr ? p.ptr->clone() : 0;
            }
            return *this;
        }
        // move semantics
        clone_ptr(clone_ptr&& p)//直接复制指针的值，并将原指针指向0(如果不修改原指针会出现多次delete同一个地址的错误)
            : ptr(p.ptr) {p.ptr = 0;}
        clone_ptr& operator=(clone_ptr&& p)
        {
            std::swap(ptr, p.ptr);//直接交换两个指针指向的内存地址
            return *this;
        }
        // Other operations
        T& operator*() const {return *ptr;}
        // ...
    };
   ```
# references
1. boost move源码
2. [右值应用简析](https://www.artima.com/articles/a-brief-introduction-to-rvalue-references)
3. C++ primer 16.2.5, 16.2.6, 16.2.3, 4.11.3