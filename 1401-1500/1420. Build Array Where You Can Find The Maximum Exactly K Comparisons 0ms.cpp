typedef long long ll;
const int N=55,M=105,P=1000000007;
int _f[2][N][M];
class Solution {
public:
	int numOfArrays(int n, int m, int k) {
		auto f=_f[0],f1=_f[1]; int ans=0;
		for (int i=1;i<=m-k+1;++i)f[1][i]=1;
		for (int i=1;i<n;++i){
			for (int j=max(1,k-n+i+1);j<=k;++j){
				for (int l=j,s=0;l<=m-k+j;s=(s+f[j-1][l-1])%P,++l)
					f1[j][l]=((ll)f[j][l]*l+f[j-1][l-1]+s)%P;
			}
			swap(f,f1); memset(f1,0,sizeof(_f[0]));
		}
		for (int i=k;i<=m;++i)ans=(ans+f[k][i])%P;
		memset(f,0,sizeof(_f[0]));
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

