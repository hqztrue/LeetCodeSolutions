const int N=105,inf=~0u>>2;
int s[N],f[N],f1[N],*h;
inline int c(int l,int r){
	int res=s[r]+s[l-1]-s[(l+r)/2]*2;
	if ((r-l)%2==0)res+=h[(l+r)/2];
	return res;
}
void DC(int L,int R,int l,int r){
	int M=(L+R)>>1,p=l;
	for (int i=l+1;i<=r&&i<M;++i)if (f[i]+c(i+1,M)<f[p]+c(p+1,M))p=i;
	f1[M]=f[p]+c(p+1,M);
	if (L<M)DC(L,M-1,l,p);
	if (R>M)DC(M+1,R,p,r);
}
class Solution {
public:
	int minDistance(vector<int>& a, int k) {
		int n=a.size(); h=&a[0]-1;
		sort(a.begin(),a.end());
		for (int i=1;i<=n;++i)s[i]=s[i-1]+h[i],f[i]=inf;
		f[0]=0;
		for (int i=1;i<=k;++i){
			DC(1,n,0,n-1);
			memcpy(f+1,f1+1,sizeof(int)*n);
		}
		return f[n];
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

