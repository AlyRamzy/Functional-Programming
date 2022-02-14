#pragma once

#include <bits/stdc++.h>

using namespace std;

// compose functions

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