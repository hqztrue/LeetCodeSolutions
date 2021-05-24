typedef unsigned int uint;
const int N=1<<12,W=8,M=20005;
uint a[M],a1[N/W+5],a2[N/W/W+5],a3[N/W/W/W+5],a4;
int h[8][1<<8];
#define get_bit(x) (1u<<((x)&7))
#define get_bit1(x) (1u<<(x))
void init(int n=N){
	memset(a1,0,sizeof(uint)*(n/W+1));
	memset(a2,0,sizeof(uint)*(n/W/W+1));
	memset(a3,0,sizeof(uint)*(n/W/W/W+1));
	a4=0;
}
inline void add(uint x){
	a1[x>>3]|=get_bit(x);
	a2[x>>6]|=get_bit(x>>3);
	a3[x>>9]|=get_bit(x>>6);
	a4|=get_bit1(x>>9);
}
inline uint find(uint x){
	uint t=h[x>>9][a4];
	t=(t<<3)+h[(x>>6)&7][a3[t]];
	t=(t<<3)+h[(x>>3)&7][a2[t]];
	return ((t<<3)+h[x&7][a1[t]])^x;
}
vector<int> v[N];
class Solution {
public:
	int findMaximumXOR(vector<int>& _a) {
		int n=_a.size(),l=31; uint ans=0,ans1=0; init();
		for (int i=0;i<n;++i){
			a[i]=_a[i];
			if (a[i])l=min(l,__builtin_clz(a[i]));
		}
		for (uint *p=a;p<a+n;++p)*p<<=l,add(*p>>20),v[*p>>20].push_back(*p);
		for (uint *p=a;p<a+n;++p)ans1=max(ans1,find(*p>>20));
		for (uint *p=a;p<a+n;++p)
			for (auto x:v[(*p>>20)^ans1])ans=max(ans,*p^x);
		for (uint *p=a;p<a+n;++p)v[*p>>20].clear();
		return ans>>l;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	for (int i=0;i<8;++i)
		for (int j=0;j<(1<<8);++j)
			for (int k=0;k<8;++k)
				if (j&(1<<k))h[i][j]=max(h[i][j],i^k);
	for (int i=0;i<8;++i)
		for (int j=0;j<(1<<8);++j)h[i][j]=i^h[i][j];
	return 0;
}();

