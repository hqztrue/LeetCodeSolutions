#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<type_traits>
using namespace std;
#define N (1<<17)
//#define N 85724
//#define mask ((1<<6)-1)
vector<int> v;
int *p;
/*template<int X>
struct Count{
	enum{res=Count<X/2>::res+(X&1)};
};
template<>
struct Count<0>{
	enum{res=0};
};*/
template<int L,int Add>
struct get_array{
	static inline void compute(){  //__attribute__((always_inline))
		get_array<L/2,Add>::compute();
		get_array<L/2,Add+1>::compute();
	}
};
template<int Add>
struct get_array<N,Add>{
	static inline void compute(){
        v.resize(N); p=&v[0];
		get_array<N/2,Add>::compute();
		get_array<N/2,Add+1>::compute();
	}
};
template<int Add>
struct get_array<1,Add>{
	static inline void compute(){
		*p++=Add;
	}
};
class Solution {
public:
    Solution(){
        get_array<N,0>::compute();
    }
    vector<int>& countBits(int num) {
		int *p=(int*)(&v); *(p+2)=*p+4*(num+1); *(p+4)=*p+4*(num+1);
		return v;
    }
};

