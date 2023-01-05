const int N=105;
int mi[N][N],ma[N][N];
inline void upd_mi(int &x,int y){if (y<x)x=y;}
inline void upd_ma(int &x,int y){if (y>x)x=y;}
class Solution {
public:
	bool isThereAPath(vector<vector<int>>& a) {
		int n=a.size(),m=a[0].size(),t=(n+m-1)/2;
		if ((n+m-1)%2)return 0;
		for (int i=0;i<n;++i)memset(mi[i],0x3f,sizeof(int)*m),memset(ma[i],0,sizeof(int)*m);
		mi[0][0]=ma[0][0]=a[0][0];
		for (int i=0;i<n;++i)
			for (int j=0;j<m;++j){
				int x=a[i][j];
				if (i>=1)upd_mi(mi[i][j],mi[i-1][j]+x),upd_ma(ma[i][j],ma[i-1][j]+x);
				if (j>=1)upd_mi(mi[i][j],mi[i][j-1]+x),upd_ma(ma[i][j],ma[i][j-1]+x);
			}
		return mi[n-1][m-1]<=t&&ma[n-1][m-1]>=t;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

