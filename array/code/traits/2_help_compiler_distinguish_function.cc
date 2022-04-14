#include<iostream>

class random_access_iterator_tag{};
class bidirectional_iterator_tag{};

class random_access_iterator{};
class bidirectional_iterator{};

template<typename iterator,typename dis>
void advance(iterator vector_it,dis d,random_access_iterator_tag){
    std::cout<<"advance vector"<<std::endl;
}

template<typename iterator,typename dis>
void advance(iterator list_it,dis d,bidirectional_iterator_tag){
    std::cout<<"advance list"<<std::endl;
}

int main(){
    advance(random_access_iterator(),5,random_access_iterator_tag());
    //编译成功 
    //输出
    //advance 
    //vector
}