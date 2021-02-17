const int N=10005;
int f[N],g[N];
class Solution {
public:
	bool canWin(const string &s) {
		int n=s.size(),ans=0; f[0]=f[1]=0;
		for (int i=2;i<=n;++i){
			memset(g,0,sizeof(int)*i);
			for (int j=0;j<=(i-2)/2;++j)g[f[j]^f[i-2-j]]=1;
			for (int &f0=f[i]=0;g[f0];++f0);
		}
		for (int i=0,c=0;i<n;++i){
			c+=(s[i]=='+');
			if ((i==n-1||s[i+1]=='-')&&c)ans^=f[c],c=0;
		}
		return ans;
	}
};

