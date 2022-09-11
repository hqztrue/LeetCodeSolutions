const int N=15;
int mask[N],n,m,k,ans;
class Solution {
public:
	void dfs(int i,int cnt,int cover){
		if (cnt==k){
			ans=min(ans,__builtin_popcount(cover));
			return;
		}
		dfs(i+1,cnt+1,cover|mask[i]);
		if (cnt+n-1-i>=k)dfs(i+1,cnt,cover);
	}
	int maximumRows(vector<vector<int>>& a, int k) {
		m=a.size(); n=a[0].size(); ans=m; ::k=n-k;
		for (int j=0;j<n;++j){
			mask[j]=0;
			for (int i=0;i<m;++i)mask[j]|=a[i][j]<<i;
		}
		dfs(0,0,0);
		return m-ans;
	}
};

