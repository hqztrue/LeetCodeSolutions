const int N=200005,CH=27,P=1000000007;
namespace Hash{
	typedef unsigned int uint;
	const uint S=15,S1=32-S,M=1996090921,_inf=~0u>>1;
	#define H(x) ((uint)x*M>>S1)
	#define node Node
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
	inline int find(int x){
		for (node *p=h+H(x);p->t==T;++p)
			if (p->x==x)return p->y;
		return 0;
	}
	#undef node
	#undef H
} using namespace Hash;
inline int LOG2(uint x){  //x=2^k
	static const int tb[32]={31,0,27,1,28,18,23,2,29,21,19,12,24,9,14,3,30,26,17,22,20,11,8,13,25,16,10,7,15,6,5,4};
	return tb[x*263572066u>>27];
}
struct node{
	node *c[CH];
	uint mask,h; bool flag;
	vector<string> *p;
	uint dfs(){
		uint m=mask;
		while (m){
			uint t=m&-m; m-=t;
			h=h*P+c[LOG2(t)]->dfs()+t;
		}
		h=h*P+flag;
		if (flag)insert(h);
		return h;
	}
};
node a[N],*a1;
vector<vector<string>> ans;
void ins(vector<string> &v){
	node *x=a;
	for (auto &s:v){
		s.push_back('z'+1);
		int l=s.size();
		for (int i=0;i<l;++i){
			int t=s[i]-'a';
			if (!x->c[t]){
				x->c[t]=++a1;
				x->mask|=1<<t;
			}
			x=x->c[t];
		}
		s.pop_back();
	}
	x->flag=1; x->p=&v;
}
void dfs1(node *x){
	if (!x->flag||!x->mask||find(x->h)==1){
		if (x->flag)ans.push_back(*x->p);
		uint m=x->mask;
		while (m){
			uint t=m&-m; m-=t;
			dfs1(x->c[LOG2(t)]);
		}
	}
}
class Solution {
public:
	vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& p) {
		int n=p.size(); a1=a; ++T; ans.clear();
		for (int i=0;i<n;++i)ins(p[i]);
		a->dfs(); dfs1(a);
		memset(a,0,sizeof(node)*(a1-a+1));
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

