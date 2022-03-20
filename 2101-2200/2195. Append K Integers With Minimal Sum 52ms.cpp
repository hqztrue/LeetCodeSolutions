typedef long long ll;
const int N=100005;
int v[N];
namespace Hash{
	typedef unsigned int uint;
	const uint S=17,S1=32-S,M=1996090921,_inf=~0u>>1;
	#define H(x) ((uint)x*M>>S1)
	struct node{
		int x,t;
	}h[(1<<S)+105];
	int T=1;
	inline bool find(int x){
		node *p=h+H(x);
		for (;p->t==T;++p)
			if (p->x==x)return 1;
		p->t=T; p->x=x;
		return 0;
	}
	#undef H
} using namespace Hash;
class Solution {
public:
	ll minimalKSum(vector<int> &a, int k) {
		int n=a.size(),cnt=0; ll ans=0; ++T;
		memset(v+1,0,sizeof(int)*n);
		for (int x:a)
			if (x<=k){
				if (!find(x))ans+=x,++cnt;
			}
			else if (x<=k+n)v[x-k]=1;
		for (int i=1;i<=cnt;++i)
			if (v[i])ans+=k+i,++cnt; 
		return (ll)(k+cnt+1)*(k+cnt)/2-ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

