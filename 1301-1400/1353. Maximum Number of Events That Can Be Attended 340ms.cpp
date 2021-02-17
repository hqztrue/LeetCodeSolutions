const int N=100005,W=32;
int st[N],ed[N];
void radix_sort(int A[],int C[],int l,int r){  //a[i]>=0
	//const int base=65535,W=16;
	const int base=2047,W=11;
	//const int base=255,W=8;
	const int T=(32-1)/W+1;
	static int B[N],_C[N],s[base+1];
	A+=l-1;C+=l-1;r-=l-1;l=1;
	int *a=A,*b=B,*c=C,*d=_C,x=0;
	for (int i1=1;i1<=T;++i1){
		for (int i=0;i<=base;++i)s[i]=0;
		for (int i=1;i<=r;++i)++s[a[i]>>x&base];
		for (int i=1;i<=base;++i)s[i]+=s[i-1];
		for (int i=r;i>=1;--i){
			int &t=s[a[i]>>x&base];
			d[t]=c[i]; b[t--]=a[i];
		}
		swap(a,b); swap(c,d);
		x+=W;
	}
	if (a!=A)for (int i=1;i<=r;++i)A[i]=a[i],C[i]=c[i];
}
template<int N>
struct LinearDisjointSet{
	int f[N/W+2]; uint c[N/W+2];
	void init(int n){for (int i=0;i<=n/W+1;++i)f[i]=i,c[i]=~0;}
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
	int maxEvents(vector<vector<int>> &a) {
		int n=a.size(),ans=0;
		for (int i=0;i<n;++i)ed[i]=a[i][1],st[i]=a[i][0];
		radix_sort(ed,st,0,n-1);
		D.init(ed[n-1]+1);
		for (int i=0;i<n;++i){
			int t=D.find(st[i]);
			if (t<=ed[i])++ans,D.del(t);
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

