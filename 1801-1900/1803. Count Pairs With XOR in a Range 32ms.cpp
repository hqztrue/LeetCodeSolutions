const int W=15;
int _c[(1<<W)*2+5],*a,n;
class Solution {
public:
	//__attribute__((no_sanitize_address,no_sanitize_memory))
	int cnt(int l,int r){
		int res=0,*c=_c,*c1,u=0;
		for (int i=0;i<n;++i)if (a[i]>u)u=a[i];
		u=1<<(32-__builtin_clz(u));
		if (r>=u)res+=n*n,r=0; if (l>=u)res-=n*n,l=0;
		c1=_c+u+5; memset(c,0,sizeof(int)*u);
		for (int i=0;i<n;++i)++c[a[i]];
		for (;l!=r;l>>=1,r>>=1){
			memset(c1,0,sizeof(int)*(u>>1));
			if ((l&1)&&(r&1))
				for (int j=0;j<u;++j){
					c1[j>>1]+=c[j];
					res+=c[j]*(c[(r-1)^j]-c[(l-1)^j]);
				}
			else if ((l&1))
				for (int j=0;j<u;++j){
					c1[j>>1]+=c[j];
					res-=c[j]*c[(l-1)^j];
				}
			else if ((r&1))
				for (int j=0;j<u;++j){
					c1[j>>1]+=c[j];
					res+=c[j]*c[(r-1)^j];
				}
			else for (int j=0;j<u;++j)c1[j>>1]+=c[j];
			swap(c,c1); u>>=1;
		}
		return res/2;
	}
	int countPairs(vector<int>& _a, int l, int r) {
		a=&_a[0]; n=_a.size(); return cnt(l,r+1);
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

