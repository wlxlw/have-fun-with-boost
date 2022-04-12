//C++ template book 1.5 函数模板的重载
#include<iostream>
#include<string>
using namespace std;

template<typename T>
T my_add(T a, T b){
    cout<<"my add template<typename T> T my_add(T a, T b)"<<endl;
    return a+b;
}

template<typename T1, typename T2>
auto my_add(T1 a,T2 b){
    cout<<"template<typename T1, typename T2> auto my_add(T1 a,T2 b)"<<endl;
    return a+b;
}

template<typename T>
T my_add(T a, T b, T c){
    cout<<"my add template<typename T> T my_add(T a, T b, T c)"<<endl;
    return my_add(my_add(a,b),c);//选择调用模板时，编译器没看到int my_add(int a,int b)，因此优先调用模板T my_add(T a, T b)
}

int my_add(int a,int b){
    cout<<"int my_add(int a,int b)"<<endl;
    return a+b;
}

// template<typename T>
// T my_add(T a, T b, T c){
//     cout<<"my add template<typename T> T my_add(T a, T b, T c)"<<endl;
//     return my_add(my_add(a,b),c);
// }

int main(){
    cout<<my_add(1,2)<<endl;
    cout<<my_add(1,2.0)<<endl;
    cout<<my_add(string("hello "),string("world"))<<endl;
    cout<<my_add(1,2,3)<<endl;//确保在调用某个函数模板之前，编译器已经看到了相对应的模板定
    return 0;
}