typedef long long ll;
const int N=100000,P=1000000007;
int r[N],r1[N],l[N]; ll ans;
namespace Hash{
	typedef unsigned int uint;
	const uint S=16,S1=32-S,M=1996090921,_inf=~0u>>1;
	#define H(x) ((uint)x*M>>S1)
	struct node{
		int x,y,t;
	}h[(1<<S)+105];
	int T=1;
	inline void insert(int x){
		node *p=h+H(x);
		for (;p->t==T;++p)
			if (p->x==x){ans+=++p->y; return;}
		p->t=T; p->x=x; p->y=0;
	}
	inline int* find(int x){
		for (node *p=h+H(x);p->t==T;++p)
			if (p->x==x)return &p->y;
		return 0;
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
inline int rev(int x){return x<N?r[x]:r1[x%N]*l[x/N]+r[x/N];}
class Solution {
public:
	int countNicePairs(vector<int>& a) {
		int n=a.size(); ans=0; ++T;
		for (int i=0;i<n;++i)insert(a[i]-rev(a[i]));
		return ans%P;
	}
};
//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	l[0]=1;
	for (int x=1;x<N;x*=10)
		for (int i=x;i<x*10;++i)
			r[i]=r[i/10]+i%10*l[i/10],r1[i]=r1[i/10]/10+i%10*(N/10),l[i]=x*10;
	return 0;
}();

