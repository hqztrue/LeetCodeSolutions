const int N=100005,inf=1<<30;
int l[N],r[N];
class Solution {
public:
	int maxWidthOfVerticalArea(vector<vector<int>>& p) {
		int n=p.size(),mi=inf,ma=-inf;
		for (int i=0;i<n;++i){
			int &x=p[i][0];
			mi=min(mi,x); ma=max(ma,x);
		}
		int d=max((ma-mi)/(n-1),1),m=(ma-mi)/d+1;
		memset(l,0x7f,sizeof(int)*m);
		memset(r,0x80,sizeof(int)*m);
		for (int i=0;i<n;++i){
			int &x=p[i][0],j=(x-mi)/d;
			if (x<l[j])l[j]=x;
			if (x>r[j])r[j]=x;
		}
		int ans=0;
		for (int i=0,j;i<m-1;i=j){
			for (j=i+1;l[j]==0x7f7f7f7f;++j);
			ans=max(ans,l[j]-r[i]);
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


