const int N=50005,W=32;
int a[N*W],ans;
namespace Hash{
	typedef unsigned int uint;
	const uint S=19,S1=32-S,M=1996090921;
	struct node{
		int x,t;
	}h[(1<<S)+1005];
	int T=1;
	inline void insert(int x){
		node *p=h+((uint)x*M>>S1);
		for (;p->t==T;++p)
			if (p->x==x)return;
		p->t=T; p->x=x; ++ans;
	}
} using namespace Hash;
class Solution {
public:
	int subarrayBitwiseORs(vector<int>& v) {
		int l=0,r=0,a1=0; ans=0; ++T;
		for (int x:v){
			r=a1; a[a1++]=x;
			for (int i=l;i<r;++i)
				if (a[a1-1]!=(a[i]|x))a[a1++]=a[i]|x;
			l=r;
		}
		for (int i=0;i<a1;++i)insert(a[i]);
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

