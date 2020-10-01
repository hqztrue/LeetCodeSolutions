typedef unsigned int uint;
namespace Hash1{
	const uint S=15,S1=32-S,M0=1996090921;
	struct node{
		int x,t;
	}h[(1<<S)+1005];
	int T=1;
	bool insert(uint x){
		node *p=h+((uint)x*M0>>S1);
		for (;p->t==T;++p)
			if (p->x==x)return 1;
		p->t=T; p->x=x;
		return 0;
	}
	/*int* find(int x){
		for (node *p=h+((uint)x*M0>>S1);p->t==T;++p)
			if (p->x==x)return &p->y;
		return 0;
	}*/
}; using namespace Hash1;
const int N=100005;
const uint M=29;
int a[N];
class Solution {
public:
	bool differByOne(vector<string>& a) {
		int n=a.size(),m=a[0].size();
		vector<uint> h(n);
		for (int i=0;i<n;++i){
			uint &h0=h[i];
			for (char *s=&a[i][0],*end=s+m;s!=end;++s)h0=h0*M+*s;
		}
		uint mul=1;
		for (int j=m-1;j>=0;--j,mul*=M,++T)
			for (int i=0;i<n;++i)
				if (insert(h[i]-a[i][j]*mul))return 1;
		return 0;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();


