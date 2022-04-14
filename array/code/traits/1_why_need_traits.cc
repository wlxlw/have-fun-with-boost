#include<iostream>
//以advance函数为例
//advance函数得到两个参数,参数一p是一个迭代器，参数二n是一个长度,函数内部实现将迭代器p前进n
//下面考虑对list与vector设计advance函数
//要求只实现一个advance，以重载的方式实现对list(不支持随机访问)，vector(支持随机访问)不同的函数实现

class random_access_iterator{};
class bidirectional_iterator{};

template<typename iterator,typename dis>
void advance(iterator vector_it,dis d){
    std::cout<<"advance vector"<<std::endl;
}

template<typename iterator,typename dis>
void advance(iterator list_it,dis d){
    std::cout<<"advance list"<<std::endl;
}

int main(){
    advance(random_access_iterator(),5);
    //编译结果
    // 1_why_need_traits.cc:16:6: error: redefinition of ‘template<class iterator, class dis> void advance(iterator, dis)’
    // 16 | void advance(iterator list_it,dis d){
    //    |      ^~~~~~~
    // 1_why_need_traits.cc:11:6: note: ‘template<class iterator, class dis> void advance(iterator, dis)’ previously declared here
    // 11 | void advance(iterator vector_it,dis d){
    //    |      ^~~~~~~
    //产生这种结果的原因是编译器无法确认应该运行哪一个advance函数。两个advance接收的参数都是模板参数，在编译器看来两个advance函数没有区别。
    //因此我们需要给advance函数增加第三个参数，要求第三个参数的类型是确定的
}