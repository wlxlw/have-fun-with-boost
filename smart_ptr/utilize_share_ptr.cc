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

void fun(std::shared_ptr<student> s){
    printf("fun(std::shared_ptr<student> s): references count:%ld\n",s.use_count());
}
void fun_reference(std::shared_ptr<student>& s){
    printf("fun_reference(std::shared_ptr<student>& s): references count:%ld\n",s.use_count());
}
void fun_reference(std::shared_ptr<student>&& s){
    printf("fun_reference(std::shared_ptr<student>&& s): references count:%ld\n",s.use_count());
}
int main(){
    std::shared_ptr<student> s1 = std::make_shared<student>();
    printf("references count:%ld\n",s1.use_count());
    std::shared_ptr<student> s2 = s1;
    printf("references count:%ld\n",s1.use_count());
    fun(s1);
    printf("references count:%ld\n",s1.use_count());
    fun_reference(s1);
    printf("references count:%ld\n",s1.use_count());
    fun_reference(std::move(s1));
    printf("references count:%ld\n",s1.use_count());
}