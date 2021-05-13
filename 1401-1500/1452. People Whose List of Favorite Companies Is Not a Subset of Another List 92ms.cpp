const int N=105,M=50005;
bitset<N> a[M];
vector<int> b[N],c[N];
int I;
namespace Hash{
	typedef unsigned int uint;
	const uint S=17,S1=32-S,M=1996090921,_inf=~0u>>1;
	#define H(x) ((uint)x*M>>S1)
	struct node{
		int x,y,z,t;
	}h[(1<<S)+105];
	int T=1;
	inline void insert(int x){
		node *p=h+H(x);
		for (;p->t==T;++p)
			if (p->x==x){++p->y; return;}
		p->t=T; p->x=x; p->y=1; p->z=++I;
	}
	inline node* find(int x){
		for (node *p=h+H(x);p->t==T;++p)
			if (p->x==x)return p;
		return 0;
	}
	#undef H
} using namespace Hash;
/*inline uint gethash(const char *_str){
	const uint seed=131;uint h=0;const char *str=_str;
	while (*str)h=h*seed+*str++;
	return h;
}*/
inline uint gethash(const char *s,int l){  //aligned, little endian
	const uint mul=131; uint res=0;
	for (--l;(l+1)%4;--l)res=(res<<8)+s[l];
	for (const uint *i=(const uint*)(s+l-3),*end=(const uint*)s;i>=end;--i)res=res*mul+*i;
	return res;
}
class Solution {
public:
	vector<int> peopleIndexes(vector<vector<string>>& v) {
		int n=v.size(); vector<int> ans; I=0; ++T; 
		for (int i=0;i<n;++i)
			for (auto &j:v[i])insert(gethash(&j[0],j.size()));
		for (int i=0;i<n;++i){
			b[i].clear();
			for (auto &j:v[i]){
				node* t=find(gethash(&j[0],j.size()));
				c[t->y].push_back(t->z);
			}
			for (int j=1;j<=n;++j)b[i].insert(b[i].end(),c[j].begin(),c[j].end()),c[j].clear();
			for (auto &j:b[i])a[j].set(i,1);
		}
		for (int i=0;i<n;++i){
			bitset<N> t=a[b[i][0]];
			for (int j=1;j<b[i].size();++j){
				t&=a[b[i][j]];
				if (j%5==0&&t.count()==1)break;
			}
			if (t.count()==1)ans.push_back(i);
		}
		for (int i=1;i<=I;++i)a[i].reset();
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

