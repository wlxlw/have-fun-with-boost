#include<boost/smart_ptr.hpp>
#include<boost/scoped_ptr.hpp>
#include<string>
#include<iostream>
class myclass{
public:
    myclass(){
        std::cout<<"myclass constructor\n";
    }
    ~myclass(){
        std::cout<<"myclass deconstructor\n";
    };
};
void test_scoped_ptr(){
    boost::scoped_ptr<myclass> s(new myclass());
}
int main(){
    //scopy_ptr
    std::cout<<"BEGIN test_scoped_ptr\n";
    test_scoped_ptr();
    std::cout<<"END test_scoped_ptr\n";
    // boost::shared_ptr<std::string>p(new std::string);
    // *p = "hello world";
    // std::cout<<*p<<std::endl;
    // boost::shared_ptr<std::string>q(p);
    return 0;
}