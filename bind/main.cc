#include <iostream>
#include <boost/bind/bind.hpp>
int f(int a,int b){printf("%d+%d\n",a,b);return a+b; }
int f(int a,int b,int c){return a+b+c;}

struct F{
    int operator()(int a,int b){printf("%d+%d\n",a,b);return a+b; }
};

struct X{
    bool f(int a,int b){printf("%d+%d\n",a,b);return a+b; }
};
int main(){
    //绑定函数
        //绑定函数的所有参数
        boost::bind(f,1,2)();//f(1,2)
        //绑定部分参数，使用占位符标记没有绑定的参数
        boost::bind(f,boost::placeholders::_1,2)(10);//f(10,2)
    //绑定函数对象
        F f_object;
        boost::bind<int>(f_object,boost::placeholders::_1,boost::placeholders::_1)(100); //bind<返回值>(函数对象，参数...)(传入的参数)

    //绑定成员函数  
        X x;
        std::shared_ptr<X>ptr_x(new X);
        //传入的第一个参数时指向成员函数的指针，使用时就和绑定函数对象类似
        boost::bind(&X::f,boost::ref(x),boost::placeholders::_1,6)(666);
        boost::bind(&X::f,&x,1,2)();
        boost::bind(&X::f,ptr_x, 20,30)();
}