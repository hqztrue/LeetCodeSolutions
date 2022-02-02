const int N=12;
int f[1<<N];
class Solution {
public:
	int maxProduct(string _s) {
		int n=_s.size(),ans=0; char *s=&_s[0];
		memset(f,0,sizeof(int)*(1<<n));
		for (int i=0;i<n;++i)f[1<<i]=1;
		for (int i=1;i<n;++i)
			for (int j=0;j+i<n;++j)
				for (int k=0;k<1<<(i-1);++k){
					int t=k<<(j+1),cur=1<<j|1<<(j+i)|t;
					if (s[j]==s[j+i])f[cur]=f[t]+2;
					else f[cur]=max(f[1<<j|t],f[1<<(j+i)|t]);
				}
		for (int i=0;i<(1<<n);++i)ans=max(ans,f[i]*f[(1<<n)-1-i]);
		return ans;
	}
};

