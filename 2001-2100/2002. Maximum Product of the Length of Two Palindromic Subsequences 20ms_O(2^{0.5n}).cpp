const int N=12,inf=10000;
char *a,b[N]; int n,n0,n1,ans,T0,I;
struct node{
	int v,t;
}F[N][N][N/2][N/2];
int f(int l,int r,int l0,int r0){
	if (l>r)return l0>r0?0:-inf;
	node &A=F[l][r][l0][r0];
	if (A.t==T0)return A.v; A.t=T0;
	if (I&(1<<l))return A.v=f(l+1,r,l0,r0);
	else if (I&(1<<r))return A.v=f(l,r-1,l0,r0);
	else {
		A.v=max(f(l+1,r,l0,r0),f(l,r-1,l0,r0));
		if (l>n1&&l0<=r0&&a[l]==b[r0])A.v=max(A.v,f(l+1,r,l0,r0-1));
		if (r>n1&&l0<=r0&&a[r]==b[l0])A.v=max(A.v,f(l,r-1,l0+1,r0));
		if (a[l]==a[r])A.v=max(A.v,f(l+1,r-1,l0,r0)+(l==r?1:2));
	}
	return A.v;
}
class Solution {
public:
	int maxProduct(string s) {
		ans=0; a=&s[0];
		n=s.size(); n0=(n+1)/2;
		for (int T=0;T<=1;++T){
			for (I=1;I<(1<<n0);++I){
				int m=__builtin_popcount(I);
				if (m<=(n/2+1)/2){
					++T0; n1=31-__builtin_clz(I);
					for (int i=1,i0=I;i<=m;++i,i0-=i0&-i0)b[i]=a[__builtin_ctz(i0)];
					ans=max(ans,m*2*f(0,n-1,1,m));
					ans=max(ans,(m*2-1)*f(0,n-1,1,m-1));
				}
			}
			reverse(s.begin(),s.end());
		}
		return ans;
	}
};

