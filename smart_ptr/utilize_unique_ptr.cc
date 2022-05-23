#include<iostream>
#include<memory>
class student{
    public:
        student(){printf("student:constructor\n");}
        ~student(){}
        student(const student&s){printf("student:copy constructor\n");}
        student(student&&s){printf("student:move constructor\n");}
        student operator=(const student&s){
            printf("student:copy opeartor\n");
            return s;
        }
        student operator=(student&&s){
            printf("student:move opeartor\n");
            return s;
        }
};

void pass_unique_ptr(std::unique_ptr<student> u){
    printf("COULD pass_unique_ptr\n");
}
void pass_unique_ptr_reference(std::unique_ptr<student>& u){
    printf("COULD pass_unique_ptr\n");
}
void pass_unique_ptr_reference(std::unique_ptr<student>&& u){
    printf("COULD pass_unique_ptr\n");
}
int main(){
    std::unique_ptr<student> u = std::make_unique<student>();
    // pass_unique_ptr(u); unique_ptr无法通过复制构造函数来传递参数
    pass_unique_ptr(std::move(u)); //unique_ptr可以通过移动构造函数来传递参数
    pass_unique_ptr_reference(u);   //unique_ptr可以通过引用来传递参数
    pass_unique_ptr_reference(std::move(u));    //unique_ptr可以通过引用来传递参数

    // std::unique_ptr<student> new_u = u; //unique_ptr无法通过拷贝复制运算符来初始化
    std::unique_ptr<student> new_u = std::move(u);  //unique_ptr可以通过拷贝移动运算符来初始化
    return 0;
}