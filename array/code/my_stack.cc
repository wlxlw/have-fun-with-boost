#include<my_stack.hpp>
#include<iostream>
#include<string>
int main(){
    //编译命令 my_stack.hpp和my_stack.cc处于当前目录 ->  g++ -I ./  my_stack.cc
    my_stack<char>s;
    char elems[5] = {'a','b','c','d','e'};
    for(int i=0;i<5;i++){
        s.push(elems[i]);
    }
    while(not s.empty()){
        std::cout<<s.top()<<std::endl;
        s.pop();
    }


    //测试特化的my_stack
    my_stack<std::string>s2;
    std::string strs[3]={std::string("no.1"),std::string("no.2"),std::string("no.3")};
    for(int i=0;i<3;i++){
        s2.push(strs[i]);
        printf(" %p\n",&strs[i]);
    }
        
    
}