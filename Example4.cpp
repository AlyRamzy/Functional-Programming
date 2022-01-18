#include <bits/stdc++.h>

using namespace std;

// compose for 2 arguments (The base case for composition)
template<typename T1,typename T2>
auto compose(T1 func1 , T2 func2)
{
    return [func1,func2](auto x){ return func1(func2(x));};
    
}

// composition for n arguments
template <class F, typename... Fs> 
auto compose(F f, Fs &&... fs) {
  return compose(f,compose(fs...)); // keep reducing the args untill it reaches only two arguments and calls the base case
}

int add_one(int item)
{
    return item+1;
}

int square(int item)
{
    return item*item;
}

int minus_ten(int item)
{
    return item-10;
}

int main()
{
    auto composed = compose(add_one,square,minus_ten);
    cout <<composed(100);

    return 0;
}