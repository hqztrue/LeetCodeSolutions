#include<immintrin.h>
const int N=515,inf=10000;
float x[N],y[N];
class Solution {
public:
	__attribute__((target("avx2")))
	vector<int> countPoints(vector<vector<int>>& p, vector<vector<int>>& q) {
		int n=(p.size()+7)/8*8,m=q.size();
		vector<int> ans(m);
		for (int i=0;i<p.size();++i)x[i]=p[i][0],y[i]=p[i][1];
		for (int i=p.size();i<n;++i)x[i]=y[i]=inf;
		for (int i=0;i<m;++i){
			__m256 X=_mm256_set1_ps(q[i][0]),Y=_mm256_set1_ps(q[i][1]),
				R=_mm256_set1_ps(q[i][2]*q[i][2]);
			const __m256i one=_mm256_set1_epi32(1);
			__m256i res=_mm256_setzero_si256();
			for (__m256 *I=(__m256*)x,*J=(__m256*)y,*end=(__m256*)(x+n);I!=end;++I,++J){
				__m256 u=_mm256_sub_ps(X,*I),v=_mm256_sub_ps(Y,*J),
					t=_mm256_add_ps(_mm256_mul_ps(u,u),_mm256_mul_ps(v,v));
				res+=_mm256_and_si256((__m256i)_mm256_cmp_ps(t,R,_CMP_LE_OS),one);
			}
			for (int j=0;j<8;++j)ans[i]+=((int*)&res)[j];
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

