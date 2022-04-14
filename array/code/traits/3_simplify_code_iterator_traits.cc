#include<iostream>

class random_access_iterator_tag{};
class bidirectional_iterator_tag{};

class random_access_iterator{//在随机访问迭代器中标记类型
    public:
        typedef random_access_iterator_tag tag;
};
class bidirectional_iterator{//在双向迭代器中标记类型
    public:
        typedef bidirectional_iterator_tag tag;
};

template<typename iterator,typename dis>
void __advance(iterator vector_it,dis d,random_access_iterator_tag){
    std::cout<<"advance vector"<<std::endl;
}

template<typename iterator,typename dis>
void __advance(iterator list_it,dis d,bidirectional_iterator_tag){
    std::cout<<"advance list"<<std::endl;
}

template<typename T>
class iterator_traits{//从模板参数T(迭代器类型)中提取出tag
    public:
        typedef typename T::tag tag;
};

template<typename iterator,typename dis>
void advance(iterator list_it,dis d){
    __advance(list_it,d,typename iterator_traits<iterator>::tag());//依赖于模板参数的限定名，typename不能省略
}



int main(){
    // random_access_iterator it = random_access_iterator();
    advance(random_access_iterator(),5);
    advance(bidirectional_iterator(),5);
    //编译成功 
    //输出
    //advance 
    //vector
}