#include<boost/move/move.hpp>
#include<string>
#include<iostream>
int main(){
    // copy str
    std::string str="abc";
    std::string copy_str = str;
    printf("%p str address\n",&str);
    printf("%p copy_str address\n",&copy_str);

    //move str
    std::string&& move_str_rvalue_reference = boost::move(str);
    printf("%p move_str_rvalue_reference\n",&move_str_rvalue_reference);

    move_str_rvalue_reference = "i can modify resource";
    std::string move_str(move_str_rvalue_reference);//此行执行完成后，move_str_rvalue_reference引用的资源移动到move_str,只有move_str能控制该资源
    move_str_rvalue_reference = "i can NOT modify resource";
    printf("%p move_str\n",&move_str);

    printf("%p str address\n",&str);

    std::string s3 = boost::move(std::string("tmp"));
    std::cout<<move_str<<std::endl;
    
    std::string tmp("123");
}