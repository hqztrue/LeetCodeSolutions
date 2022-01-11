/***************************************************
Author: hqztrue
https://github.com/hqztrue/LeetCodeSolutions
Complexity: O(n)
If you find this solution helpful, plz give a star:)
***************************************************/
const int N=100005;
namespace Hash{
	typedef unsigned int uint;
	const uint S=18,S1=32-S,M=1996090921,_inf=~0u>>1;
	#define H(x) ((uint)x*M>>S1)
	struct node{
		int x,y,t;
	}h[(1<<S)+105];
	int T=1;
	inline void insert(int x){
		node *p=h+H(x);
		for (;p->t==T;++p)
			if (p->x==x){++p->y; return;}
		p->t=T; p->x=x; p->y=1;
	}
	inline int& find(int x){
		static int null=0;
		for (node *p=h+H(x);p->t==T;++p)
			if (p->x==x)return p->y;
		return null;
	}
	inline void erase_(int x){
		for (node *p=h+H(x);p->t==T;++p)
			if (p->x==x){p->x=_inf; return;}
	}
	inline void erase(int x){
		for (node *p=h+H(x);p->t==T;++p)
			if (p->x==x){
				for (node *q=p+1;q->t==T;++q)
					if (h+H(q->x)<=p){p->x=q->x; p->y=q->y; p=q;}
				p->t=0; return;
			}
	}
	#undef H
} using namespace Hash;
class Solution {
public:
	bool isPossibleDivide(vector<int>& _a, int k) {
		int n=_a.size(),*a=&_a[0]; ++T;
		for (int i=0;i<n;++i)insert(a[i]);
		for (int i=0;i<n;++i){
			if (!find(a[i]))continue;
			int l=a[i],r=l;
			while (find(l-1))--l;
			while (find(r+1))++r;
			while (l<=r){
				if (find(l)){
					for (int i=l;i<l+k;++i)
						if (find(i)--==0){find(i)=0; return 0;} 
				}
				else ++l;
			}
		}
		return 1;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

