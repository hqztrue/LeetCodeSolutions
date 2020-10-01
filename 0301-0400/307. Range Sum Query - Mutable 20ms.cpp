#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int N=20005;
class NumArray {
public:
	int a[N],c[N],s[N],n;
	NumArray(vector<int>& nums) {
		n=nums.size();
		s[0]=0;
		for (int i=0;i<n;++i)s[i+1]=s[i]+nums[i];
		if (n>0)memcpy(a+1,&nums[0],n*sizeof(int));
		//memset(a+1,0,n*sizeof(int));
		//memset(c+1,0,n*sizeof(int));
		//for (int i=0;i<n;++i)update(i,nums[i]);
		for (int i=1;i<=n;++i)c[i]=s[i]-s[i-(i&-i)];
	}
	void update(int i, int val) {
		++i; int d=val-a[i]; a[i]=val;
		for (int p=i;p<=n;p+=p&-p)c[p]+=d;
	}
	int sum(int i);
	int sumRange(int i, int j) {
		return sum(j+1)-sum(i);
	}
	/*int sumRange(int i, int j) {
		int res=0;
		for (int p=j+1;p>i;)
			if (p-(p&-p)>=i)res+=c[p],p-=p&-p;
			else res+=a[p],--p;
		return res;
	}*/
};
int NumArray::sum(int i){
	int res=0;
	//for (int p=i;p;p-=p&-p)res+=c[p];  //p&=p-1
	__asm__
	(
		"mov $0,%%ecx\n"
		"begin:\n"
		"test %%eax,%%eax\n"
		"jz end\n"
		"add (%%rdx,%%rax,4),%%ecx\n"  //error: edx, eax
		"lea -0x1(%%eax),%%esi\n"
		"and %%esi,%%eax\n"
		"jmp begin\n"
		"end:\n"
		: "=c"(res)
		: "a"(i), "d"(c)
		:
	);
	return res;
}

//IO
int _IO=[](){
	std::ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	return 0;
}();

