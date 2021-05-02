const int N=40005,W=32;
template<int N>
struct LinearDisjointSet{
	int f[N/W+2]; uint c[N/W+2];
	void init(int n){
		//for (int i=0;i<=n/W+1;++i)f[i]=i,c[i]=~0;
		iota(f,f+n/W+2,0);
		memset(c,0xFF,sizeof(int)*(n/W+2));
	}
	int _find(int x){
		if (f[x]==x)return x;
		return f[x]=_find(f[x]);
	}
	void _del(int x){f[x]=x+1;}
	int find(int x){
		int y=x/W,z=x%W; uint t=c[y]>>z<<z;
		if (t)return y*W+__builtin_ctz(t);
		y=_find(y+1); return y*W+__builtin_ctz(c[y]);
	}
	void del(int x){int y=x/W;c[y]&=~(1u<<x%W);if (!c[y])_del(y);}
};
LinearDisjointSet<N> D;
class Solution {
public:
	int eatenApples(vector<int>& _a, vector<int>& _d) {
		int *a=&_a[0],*d=&_d[0],n=_a.size(),ans=0,m=0;
		for (int i=0;i<n;++i)m=max(m,i+d[i]);
		D.init(m+1);
		for (int i=n-1;i>=0;--i){
			for (int j=0;j<a[i];++j){
				int t=D.find(m-(i+d[i]));
				if (t<=m-1-i)++ans,D.del(t);
				else break;
			}
		}
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

