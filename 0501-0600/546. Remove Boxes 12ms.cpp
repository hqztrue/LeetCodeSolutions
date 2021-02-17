const uint N=105,W=10,mask=~0u>>W;
uint f[N][N][N],T=0;
int *b;
class Solution {
public:
	uint dfs(int i,int j,int k){
		uint &f0=f[i][j][k];
		if ((f0>>(32-W))==T)return f0&mask;
		int j1=j;
		while (i<j&&b[j-1]==b[j])--j,++k;
		if ((f[i][j][k]>>(32-W))==T){
			f0=f[i][j][k];
			for (;j<j1;)++j,--k,f[i][j][k]=f0;
			return f0&mask;
		}
		f0=(k+1)*(k+1); if (i<j)f0+=dfs(i,j-1,0);
		if (i<j&&b[i]==b[j])f0=max(f0,dfs(i+1,j,k+1));
		for (int l=i+1;l<j;++l)
			if (b[l]==b[j])f0=max(f0,dfs(i,l-1,0)+dfs(l+1,j,k+1));
		f0|=T<<(32-W);
		return (f[i][j][k]=f0)&mask;
	}
	int removeBoxes(vector<int>& boxes) {
		int n=boxes.size(); b=&boxes[0]; ++T;
		return dfs(0,n-1,0);
	}
};

