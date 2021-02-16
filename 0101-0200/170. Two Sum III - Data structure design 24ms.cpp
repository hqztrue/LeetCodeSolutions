typedef long long ll;
const int inf=~0u>>1;
namespace Hash{
	typedef unsigned int uint;
	const uint S=16,S1=32-S,M=1996090921;
	struct node{
		int x,y,t;
	}h[(1<<S)+1005];
	int T=1;
	inline void insert(int x){
		node *p=h+((uint)x*M>>S1);
		for (;p->t==T;++p)
			if (p->x==x){++p->y; return;}
		p->t=T; p->x=x; p->y=1;
	}
	inline int find(int x){
		for (node *p=h+((uint)x*M>>S1);p->t==T;++p)
			if (p->x==x)return p->y;
		return 0;
	}
} using namespace Hash;
class TwoSum {
public:
	/** Initialize your data structure here. */
	vector<int> a;
	int vmin,vmax,vmin1,vmax1;
	TwoSum() {a.clear(); vmin=vmin1=inf; vmax=vmax1=-inf; ++T;}
	/** Add the number to an internal data structure.. */
	void add(int x) {
		if (x<vmin)vmin1=vmin,vmin=x;
		else if (x<vmin1)vmin1=x;
		if (x>vmax)vmax1=vmax,vmax=x;
		else if (x>vmax1)vmax1=x;
		a.push_back(x); insert(x);
	}
	/** Find if there exists any pair of numbers which sum is equal to the value. */
	bool find(int v) {
		if (a.size()<2||v<(ll)vmin+vmin1||v>(ll)vmax+vmax1)return 0;
		int n=a.size();
		for (int i=0;i<n;++i)
			if (v-a[i]==a[i]){
				if (Hash::find(a[i])>=2)return 1;
			}
			else if (Hash::find(v-a[i]))return 1;
		return 0;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();
