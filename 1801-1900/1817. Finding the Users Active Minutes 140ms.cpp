const int N=10005;
int s[N],l;
namespace Hash{
	typedef unsigned int uint;
	const uint S=15,S1=32-S,M=1996090921,_inf=~0u>>1,M1=1000000007;
	#define H(x) ((uint)x*M>>S1)
	struct node{
		int x,y,t;
	}h[(1<<S)+105];
	int T=1;
	inline int insert(int x){
		node *p=h+H(x);
		for (;p->t==T;++p)
			if (p->x==x)return p->y;
		p->t=T; p->x=x; return p->y=l++;
	}
	inline bool insert_(int x){
		node *p=h+H(x);
		for (;p->t==T;++p)
			if (p->x==x)return 0;
		p->t=T; p->x=x; return 1;
	}
	#undef H
} using namespace Hash;
class Solution {
public:
	vector<int> findingUsersActiveMinutes(vector<vector<int>>& a, int k) {
		vector<int> res(k); l=1; ++T;
		for (int i=1;i<=a.size();++i)s[i]=0;
		for (auto &v:a){
			uint id=insert(v[0]);
			if (insert_(id*M1+v[1]))++s[id];
		}
		for (int i=1;i<l;++i)++res[s[i]-1];
		return res;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

