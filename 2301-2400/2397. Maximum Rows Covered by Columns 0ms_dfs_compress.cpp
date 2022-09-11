const int N=15;
int mask[N],suf[N],n,m,k,ans;
class Solution {
public:
	void dfs(int i,int cnt,int cover){
		if (cnt==k){
			ans=min(ans,__builtin_popcount(cover));
			return;
		}
		if (cnt+n-i==k)dfs(n,k,cover|suf[i]);
		else {
			dfs(i+1,cnt+1,cover|mask[i]);
			dfs(i+1,cnt,cover);
		}
	}
	int maximumRows(vector<vector<int>>& a, int k) {
		m=a.size(); n=a[0].size(); ans=m; ::k=n-k;
		for (int j=0;j<n;++j){
			mask[j]=0;
			for (int i=0;i<m;++i)mask[j]|=a[i][j]<<i;
		}
		suf[n-1]=mask[n-1]; 
		for (int i=n-2;i>=0;--i)suf[i]=suf[i+1]|mask[i];
		dfs(0,0,0);
		return m-ans;
	}
};

