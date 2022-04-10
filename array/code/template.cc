#include<vector>
#include<iostream>
#include<string>
#include <typeinfo>
#include<assert.h>
using namespace std;

//函数模板 https://www.runoob.com/cplusplus/cpp-templates.html
template <typename T> //T为函数参数类型的占位符
T add(const T a,const T b){
    return a+b;
}

template<typename T,typename U> //T U为函数参数类型的占位符
T sub(const T a,const U b){
    //cout<<typeid(a).name()<<" "<<typeid(b).name()<<endl;
    return a-b;
}

void test_add(){
    int a = 1,b=2;
    cout<<a<<"+"<<b<<"="<<add(a,b)<<endl;

    double c = 1.5,d=2.3;
    cout<<c<<"+"<<d<<"="<<add(c,d)<<endl;

    string e="abc",f="def";
    cout<<e<<"+"<<f<<"="<<add(e,f)<<endl;

    cout<<"6.1-2="<<sub(6.1,2)<<endl;
}


//类模板
template<class T,std::size_t N>
class Array{
    private:
        T elems[N];
    public:
        typedef T*  iterator;
        typedef T   value_type;
        typedef T&  reference;      
}; 

//assert
int test(int a){
    return 3000,1111, a,45;
}
int main() {
    test_add();
    cout<<test(1);
}