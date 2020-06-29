const int N=205;
int l[N][N],r[N][N],t[N][N],b[N][N],L[N],R[N];
class Solution {
public:
	int largest1BorderedSquare(vector<vector<int>>& grid) {
		int n=grid.size(),m=grid[0].size();
		for (int i=0;i<n;++i){
			l[i][0]=grid[i][0];
			for (int j=1;j<m;++j)l[i][j]=grid[i][j]?l[i][j-1]+1:0;
			r[i][m-1]=grid[i][m-1];
			for (int j=m-2;j>=0;--j)r[i][j]=grid[i][j]?r[i][j+1]+1:0;
		}
		for (int j=0;j<m;++j){
			t[0][j]=grid[0][j];
			for (int i=1;i<n;++i)t[i][j]=grid[i][j]?t[i-1][j]+1:0;
			b[n-1][j]=grid[n-1][j];
			for (int i=n-2;i>=0;--i)b[i][j]=grid[i][j]?b[i+1][j]+1:0;
		}
		int ans=0;
		for (int d=-max(n,m);d<=max(n,m);++d){
			int cur=-1,head=-1,tail=-1;
			vector<vector<int> > del(n+m);
			for (int i=0;i<n+m;++i)L[i]=R[i]=-1;
			for (int i=max(0,d);i<min(n,m+d);++i){
				int j=i-d;
				int len=min(t[i][j],l[i][j]),len1=min(b[i][j],r[i][j]);
				if (len1){
					if (tail!=-1)R[tail]=i;
					L[i]=tail; tail=i;
					if (head==-1)head=i;
					del[i+len1-1].push_back(i);
				}
				if (cur==-1&&head!=-1&&head<=i-ans)cur=head;
				while (cur!=-1&&R[cur]!=-1&&R[cur]<=i-ans)cur=R[cur];
				while (cur!=-1&&i-cur+1<=len){
					ans=i-cur+1;
					cur=L[cur];
				}
				for (int k=0;k<del[i].size();++k){
					int p=del[i][k];
					if (p==cur)cur=L[p];
					if (p==head)head=R[head];
					if (p==tail)tail=L[tail];
					if (L[p]!=-1)R[L[p]]=R[p];
					if (R[p]!=-1)L[R[p]]=L[p];
				}
			}
		}
		return ans*ans;
	}
};

