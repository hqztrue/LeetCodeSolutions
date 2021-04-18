#include<immintrin.h>
typedef long long ll;
const int N=51008,L=505,P=1000000007;
ll f[L][N] __attribute__((aligned(32))),A[N] __attribute__((aligned(32)));
class Solution {
public:
	__attribute__((target("avx2")))
	vector<int> solve(vector<int>& _a, vector<vector<int>>& q) {
		int n=_a.size(),m=q.size(),n1=(n-1)/4*4,S=1.2*sqrt(m)+1;
		vector<int> ans(m);
		_a.resize(n1+4); int *a=&_a[0];
		for (int i=0;i<_a.size();++i)A[i]=a[i];
		for (int i=1;i<4;++i)
			for (int j=n-1;j>=0;--j)f[i][j]=a[j]+(i+j<n?f[i][i+j]:0);
		for (int i=4;i<=S;++i){
			ll *f0=f[i]; memset(f0+n1+4,0,sizeof(ll)*S);
			__m256i *J=(__m256i*)(A+n1);
			for (int j=n1;j>=0;j-=4,--J){
				__m256i X=_mm256_loadu_si256((__m256i*)(f0+i+j));
				_mm256_store_si256((__m256i*)(f0+j),_mm256_add_epi64(X,*J));
			}
		}
		for (int i=0;i<m;++i){
			int x=q[i][0],y=q[i][1];
			if (y<=S)ans[i]=f[y][x]%P;
			else {
				ll t=0;
				for (int j=x;j<n;j+=y)t+=a[j];
				ans[i]=t%P;
			}
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

