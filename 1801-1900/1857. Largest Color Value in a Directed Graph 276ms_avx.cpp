#include<immintrin.h>
typedef unsigned short us;
const int N=100005,CH=26;
vector<int> g[N];
int d[N],q[N],h[N];
__m256i f[N][2];
class Solution {
public:
	__attribute__((target("avx,avx2")))
	int largestPathValue(string &c, vector<vector<int>>& edges) {
		int n=c.size(),res=0; __m256i ans=_mm256_set1_epi16(0);
		for (int i=0;i<n;++i)d[i]=0,g[i].clear(),c[i]-='a',f[i][0]=f[i][1]=ans;
		for (auto &e:edges)++d[e[1]],g[e[0]].push_back(e[1]);
		int s=0,t=0;
		for (int i=0;i<n;++i)
			if (!d[i])q[t++]=i;
		while (s<t){
			int u=q[s++]; char c0=c[u];
			++((us*)f[u])[c0];
			__m256i f0=f[u][0],f1=f[u][1];
			ans=_mm256_max_epu16(ans,_mm256_max_epu16(f0,f1));
			for (int v:g[u]){
				if (!--d[v])q[t++]=v;
				__m256i *F=f[v];
				*F=_mm256_max_epu16(*F,f0);
				F[1]=_mm256_max_epu16(F[1],f1);
			}
		}
		if (t<n)return -1;
		int cnt[CH]={0};
		for (int i=0;i<n;++i)++cnt[c[i]];
		for (int c0=0;c0<CH;++c0)if (cnt[c0]>=(1<<16)){
			memset(h,0,sizeof(int)*n);
			for (int i=0;i<n;++i){
				int u=q[i];
				if (c[u]==c0)++h[u];
				int h0=h[u]; res=max(res,h0);
				for (int v:g[u])h[v]=max(h[v],h0);
			}
		}
		for (int i=0;i<16;++i)res=max(res,int(((us*)&ans)[i]));
		return res;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

