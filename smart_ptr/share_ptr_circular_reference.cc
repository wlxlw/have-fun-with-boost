#include<iostream>
#include<memory>
class B;
class C;
class A{
public:
    std::shared_ptr<B>b;
    A(){}
    ~A(){
        printf("destory A\n");
    }
};
class B{
public:
    std::shared_ptr<C>c;
    B(){}
    ~B(){
        printf("destory B\n");
    }
};
class C{
public:
    std::shared_ptr<A>a;
    C(){}
    ~C(){
        printf("destory C\n");
    }
};
void memory_leakage(){
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();
    auto c = std::make_shared<C>();
    printf("A's B ref:%ld\n",a->b.use_count());
    printf("B's C ref:%ld\n",b->c.use_count());
    printf("C's A ref:%ld\n",c->a.use_count());
    a->b = b;
    b->c = c;
    c->a = a;
    printf("A's B ref:%ld\n",a->b.use_count());
    printf("B's C ref:%ld\n",b->c.use_count());
    printf("C's A ref:%ld\n",c->a.use_count());
}
int main(){
    memory_leakage();
    //输出结果如下,a b c的析构函数都没有被调用，造成内存泄漏
    // A's B ref:0
    // B's C ref:0
    // C's A ref:0
    // A's B ref:2
    // B's C ref:2
    // C's A ref:2
}