const int N=20005,CH=26;
int a[N],f[N*CH],c[N*CH];
int F(int x){
	if (f[x]==x)return x;
	return f[x]=F(f[x]);
}
namespace Hash{
	typedef unsigned int uint;
	const uint S=20,S1=32-S,M=1996090921,_inf=~0u>>1;
	#define H(x) ((uint)x*M>>S1)
	struct node{
		int x,y,t;
	}h[(1<<S)+105];
	int T=1,id;
	inline int find(int x){
		node *p=h+H(x);
		for (;p->t==T;++p)
			if (p->x==x)return p->y;
		p->t=T; p->x=x; p->y=++id; f[id]=id;
		return p->y;
	}
	#undef H
} using namespace Hash;
class Solution {
public:
	vector<int> groupStrings(vector<string>& w) {
		int n=w.size(),cnt=0,ans=1; ++T; id=0;
		for (int i=0;i<n;++i){
			int s=0;
			for (char *p=&w[i][0],*end=p+w[i].size();p!=end;++p)s|=1<<(*p-'a');
			int x=F(a[i]=find(s));
			for (int j=s;j;j-=j&-j)
				f[F(find(s-(j&-j)))]=x;
		}
		for (int i=1;i<=id;++i)c[i]=0;
		for (int i=0;i<n;++i){
			int &z=c[F(a[i])];
			if (++z==1)++cnt;
			else ans=max(ans,z);
		}
		return {cnt,ans};
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

