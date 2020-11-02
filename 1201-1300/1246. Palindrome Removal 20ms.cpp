const int N=105,inf=1<<30;
int f[N][N],c[N][N],c1[N],b[N],*a;
class Solution {
public:
	int F(int l,int r){
		if (l>r)return 0;
		if (f[l][r])return f[l][r];
		int ans=1+F(l+1,r);
		if (l<r&&a[l]==a[l+1])ans=min(ans,1+F(l+2,r));
		//for (int i=l+2;i<=r;++i)
		//	if (a[l]==a[i])ans=min(ans,F(l+1,i-1)+F(i+1,r));
		int *p=c[a[l]]+b[l]+1;
		if (*p==l+1)++p;
		for (;*p<=r;++p)
			ans=min(ans,F(l+1,*p-1)+F(*p+1,r));
		return f[l][r]=ans;
	}
	int minimumMoves(vector<int>& a) {
		int n=a.size(); ::a=&a[0];
		for (int i=0;i<n;++i)memset(f[i],0,sizeof(int)*n);
		memset(c1,0,sizeof(c1));
		for (int i=0;i<n;++i)b[i]=c1[a[i]],c[a[i]][c1[a[i]]++]=i;
		for (int i=0;i<N;++i)c[i][c1[i]]=inf;
		return F(0,n-1);
	}
};

