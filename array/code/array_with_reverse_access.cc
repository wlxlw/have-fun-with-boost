#include<iostream>
#include<assert.h>
using namespace std;

//类模板
namespace my_array{
    template<class T,std::size_t N>
    class array{
        public:
            T elems[N];
        public:
            // typedef T*  iterator;
            // typedef T   value_type;
            typedef T&  reference;
            // typedef std::size_t size_type;

            reference operator[](long long i){
                long long N_LONG_LONG = (long long)N;
                if(i>=0)
                    return assert(i<N_LONG_LONG && "n>=0 out of range"), elems[i];
                else
                    return assert(-i<=N_LONG_LONG && "n<0 out of range"), elems[N_LONG_LONG+i];
            }      
    }; 
}

int main() {
    const std::size_t N = 10;
    my_array::array<int,N> a;
    for(std::size_t i=0;i<N;i++)
        a[i]=i+1;

    // reverse access
    for(int i=-1;i>=-N;i--){
        cout<<a[i]<<" ";
    }
    cout<<endl;

    //access
    for(int i=0;i<N;i++){
        cout<<a[i]<<" ";
    }

    cout<<endl<<a[-N-1];
}