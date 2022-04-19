#include<boost/smart_ptr.hpp>
#include<string>
#include<iostream>
int main(){
    boost::shared_ptr<std::string>p(new std::string);
    *p = "hello world";
    std::cout<<*p<<std::endl;
    boost::shared_ptr<std::string>q(p);
    return 0;
}