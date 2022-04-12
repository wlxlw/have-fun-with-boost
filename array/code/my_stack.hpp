#include<vector>
#include<assert.h>
#include<string>
#include<iostream>
template<typename T>
class my_stack{
    private:
        std::vector<T>elems;
    public:
        const T& top();
        void push(T elem);
        void pop();
        const bool empty();
};

template<typename T>
const T& my_stack<T>:: top(){
    return assert(!elems.empty() && "stack is empty"), elems.back();
}

template<typename T>
void my_stack<T>:: push(T elem){
    elems.push_back(elem);
}

template<typename T>
void my_stack<T>:: pop(){
    assert(!elems.empty() && "stack is empty");
    elems.pop_back();
}

template<typename T>
const bool my_stack<T>:: empty(){
    return elems.empty();
}

// 针对string 特化
template<>
class my_stack<std::string>{
    private:
        std::vector<std::string>elems;
    public:
        const std::string& top();
        void push(std::string& elem);//传入引用进行特化
        void pop();
        const bool empty();
};

const std::string& my_stack<std::string>:: top(){
    return assert(!empty() && "stack is empty"),elems.back();
}

void my_stack<std::string>:: push(std::string& elem){
    elems.push_back(elem);
    printf("%p",&elem);
}

void my_stack<std::string>::pop(){
    assert(!empty() && "stack is empty");
    elems.pop_back();
}

const bool my_stack<std::string>:: empty(){
    return elems.empty();
}

