#include<boost/move/move.hpp>
#include<string>
#include<iostream>
template<typename T>
void swap(T&a, T&b){
    T tmp = a;  //copy
    a = b;  //copy
    b = tmp;    //copy
}

template<typename T>
void swap_with_move(T&a, T&b){
    T tmp = boost::move(a);
    a = boost::move(b);
    b = boost::move(tmp);
}

int main(){
    std::string s1="abc",s2="def";
    swap(s1,s2);
    std::cout<<s1<<" "<<s2<<std::endl;
    swap_with_move(s1,s2);
    std::cout<<s1<<" "<<s2<<std::endl;
    return 0;
}