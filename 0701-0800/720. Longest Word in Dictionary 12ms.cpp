const int N=1005,L=30,CH=26,mul=131;
namespace Hash{
	typedef unsigned int uint;
	const uint S=12,S1=32-S,M=1996090921;
	struct node{
		int x,t;
	}h[(1<<S)+1005];
	int T=1;
	inline void insert(int x){
		node *p=h+((uint)x*M>>S1);
		for (;p->t==T;++p)
			if (p->x==x)return;
		p->t=T; p->x=x;
	}
	inline bool find(int x){
		for (node *p=h+((uint)x*M>>S1);p->t==T;++p)
			if (p->x==x)return 1;
		return 0;
	}
} using namespace Hash;

vector<int> v[L+1];
inline uint gethash(char *s,int l){  //aligned, little endian
	uint res=0;
	for (--l;(l+1)%4;--l)res=(res<<8)+s[l];
	for (uint *i=(uint*)(s+l-3),*end=(uint*)s;i>=end;--i)res=res*mul+*i;
	return res;
}
class Solution {
public:
	string longestWord(vector<string>& w) {
		string *ans=new string();
		for (int i=1;i<=L;++i)v[i].clear();
		for (int i=0;i<w.size();++i)v[w[i].size()].push_back(i);
		++T; insert(0); uint m=1;
		for (int i=1;i<=L;++i){
			for (int j=0;j<v[i].size();++j){
				string &str=w[v[i][j]];
				uint t=gethash(&str[0],i-1);
				if (find(t)){
					insert(m*(str[i-1]<<(i-1)%4*8)+t);
					if (ans->size()<i||*ans>str)ans=&str;
				}
			}
			if (i%4==0)m*=mul;
			if (ans->size()<i)break;
		}
		return *ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

