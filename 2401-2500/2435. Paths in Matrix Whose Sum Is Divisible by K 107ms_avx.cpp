#include<immintrin.h>
const int N=50005,P=1000000007;
int f[N][56] __attribute__((aligned(32)));
int _f0[56] __attribute__((aligned(32)));
int *f0=_f0,n,m,k;
inline int id(int x,int y){return x*m+y;}
__attribute__((target("avx2")))
inline void add(int *a,int *b){
	for (int i=0;i<k;i+=8){
		__m256i v=_mm256_add_epi32(_mm256_load_ps((float*)a+i),_mm256_load_ps((float*)b+i)),
			ge=_mm256_cmpgt_epi32(v,_mm256_set1_epi32(P-1));
		_mm256_store_ps((float*)a+i,_mm256_sub_epi32(v,_mm256_and_si256(_mm256_set1_epi32(P),ge)));
	}
}
inline void shift(int *a,int *b,int d){
    memcpy(a+d,b,sizeof(int)*(k-d));
	memcpy(a,b+k-d,sizeof(int)*d);
}
class Solution {
public:
	__attribute__((target("avx2")))
	int numberOfPaths(vector<vector<int>>& a, int k) {
		n=a.size(); m=a[0].size(); ::k=k;
		for (int i=0;i<n;++i)
			for (int j=0;j<m;++j)a[i][j]%=k;
		f0[0]=1; for (int i=1;i<k;++i)f0[i]=0;
		for (int i=0;i<n;++i)
			for (int j=0;j<m;++j){
				if (i&&j){
					memcpy(f0,f[id(i-1,j)],sizeof(int)*k);
					add(f0,f[id(i,j-1)]);
				}
				else if (i)memcpy(f0,f[id(i-1,j)],sizeof(int)*k);
				else if (j)memcpy(f0,f[id(i,j-1)],sizeof(int)*k);
				shift(f[id(i,j)],f0,a[i][j]);
			}
		return f[id(n-1,m-1)][0];
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

