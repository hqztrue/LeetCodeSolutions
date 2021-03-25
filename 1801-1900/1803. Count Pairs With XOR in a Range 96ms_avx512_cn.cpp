#include<immintrin.h>
#define us unsigned short
const int N=20005,U=31;
us a[N] __attribute__((aligned(64)));
class Solution {
public:
	__attribute__((no_sanitize_address,no_sanitize_memory))
	__attribute__((target("avx512bw")))
	int countPairs(vector<int>& _a, us l, us r) {
		int n=_a.size(),ans=0,d=0;
		for (int i=0;i<n;++i)a[i]=_a[i];
		sort(a,a+n);
		__m512i L=_mm512_set1_epi16(l),R=_mm512_set1_epi16(r);
		for (int i=1;i<n;++i){
			if (a[i]!=a[i-1]){
				us x=a[i]; __m512i X=_mm512_set1_epi16(x); d=0;
				for (__m512i *I=(__m512i*)a,*end=(__m512i*)(a+(i&~U));I!=end;++I){
					__m512i Y=_mm512_xor_si512(X,*I);
					d+=__builtin_popcount(_mm512_cmpge_epi16_mask(Y,L)&_mm512_cmple_epi16_mask(Y,R));
				}
				for (int j=i&~U;j<i;++j){int y=x^a[j]; d+=y>=l&&y<=r;}
			}
			ans+=d;
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

