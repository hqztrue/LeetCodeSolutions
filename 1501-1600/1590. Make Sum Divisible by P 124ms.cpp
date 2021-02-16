typedef long long ll;
namespace Hash{
	typedef unsigned int uint;
	const uint S=17,S1=32-S,M=1996090921;
	struct node{
		int x,y,t;
	}h[(1<<S)+1005];
	int T=1;
	void insert(int x,int y){
		node *p=h+((uint)x*M>>S1);
		for (;p->t==T;++p)
			if (p->x==x){p->y=y; return;}
		p->t=T; p->x=x; p->y=y;
	}
	int* find(int x){
		for (node *p=h+((uint)x*M>>S1);p->t==T;++p)
			if (p->x==x)return &p->y;
		return 0;
	}
} using namespace Hash;
class Solution {
public:
	int minSubarray(vector<int>& a, int p) {
		int n=a.size(),res=n; ll s=0;
		for (int i=0;i<n;++i)s+=a[i];
		s%=p; ++T; insert(0,-1);
		for (int i=0,t=0;i<n;++i){
			t=(t+a[i])%p; insert(t,i);
			int *q=find(t<s?t-s+p:t-s);
			if (q)res=min(res,i-*q);
		}
		return res>=n?-1:res;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

