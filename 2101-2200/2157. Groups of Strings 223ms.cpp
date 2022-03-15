/***************************************************
Author: hqztrue
https://github.com/hqztrue/LeetCodeSolutions
Complexity: O(L)
If you find this solution helpful, plz give a star:)
***************************************************/
namespace Hash{
	typedef unsigned int uint;
	const uint S=20,S1=32-S,M=1996090921,_inf=~0u>>1;
	#define H(x) ((uint)x*M>>S1)
	struct node{
		int x,y,z,t;
	}h[(1<<S)+105];
	int T=1;
	inline node* find(int x){
		node *p=h+H(x);
		for (;p->t==T;++p)
			if (p->x==x)return p;
		p->t=T; p->x=x; p->y=x; p->z=0;
		return p;
	}
	#undef H
} using namespace Hash;
node* query(int x){
	node *p=find(x);
	if (p->y==x)return p;
	node *q=query(p->y); p->y=q->x;
	return q;
}
const int N=20005;
int a[N];
class Solution {
public:
	vector<int> groupStrings(vector<string>& w) {
		int n=w.size(),cnt=0,ans=1; ++T;
		for (int i=0;i<n;++i){
			int s=0;
			for (char *p=&w[i][0],*end=p+w[i].size();p!=end;++p)s|=1<<(*p-'a');
			a[i]=s; int x=query(s)->x;
			for (int j=s;j;j-=j&-j){
				query(s-(j&-j))->y=x;
			}
		}
		for (int i=0;i<n;++i){
			int &z=query(a[i])->z;
			if (++z==1)++cnt;
			else ans=max(ans,z);
		}
		return {cnt,ans};
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

