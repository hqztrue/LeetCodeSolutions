const int N=100005,W=32;
namespace wTrie{
	typedef unsigned int uint;
	uint a1[N/W+5],a2[N/W/W+5],a3[N/W/W/W+5],a4;
	#define max_bit(x) 31-__builtin_clz(x)
	#define min_bit(x) __builtin_ctz(x)
	#define get_bit(x) (1u<<((x)&31u))
	#define get_bit1(x) (1u<<(x))
	void init(int n=N){
		memset(a1,0,sizeof(uint)*(n/W+1));
		memset(a2,0,sizeof(uint)*(n/W/W+1));
		memset(a3,0,sizeof(uint)*(n/W/W/W+1));
		a4=0;
	}
	inline void add(uint x){
		a1[x>>5]|=get_bit(x);
		a2[x>>10]|=get_bit(x>>5);
		a3[x>>15]|=get_bit(x>>10);
		a4|=get_bit1(x>>15);
	}
	inline int get_min(){
		if (!a4)return -1;
		uint x=min_bit(a4);
		x=(x<<5)+min_bit(a3[x]);
		x=(x<<5)+min_bit(a2[x]);
		return (x<<5)+min_bit(a1[x]);
	}
	inline int del_min(){
		//if (!a4)return -1;
		uint x=min_bit(a4);
		x=(x<<5)+min_bit(a3[x]);
		x=(x<<5)+min_bit(a2[x]);
		x=(x<<5)+min_bit(a1[x]);
		if (!(a1[x>>5]-=get_bit(x)))
			if (!(a2[x>>10]-=get_bit(x>>5)))
				if (!(a3[x>>15]-=get_bit(x>>10)))
					a4-=get_bit1(x>>15);
		return x;
	}
} using namespace wTrie;
struct node{
	int t,id;
}_a[N],_b[N],*a,*b;
int t[N],l[N],l1[N],rev[N],n,r1;
vector<int> res;
void radix_sort(node *&a,int l,int r){  //a[i]>=0
	//const int base=65535,W=16;
	const int base=2047,W=11;
	//const int base=255,W=8;
	const int T=(32-1)/W+1;
	static int s[base+1];
	a+=l-1;r-=l-1; int x=0;
	for (int i1=1;i1<=T;++i1){
		for (int i=0;i<=base;++i)s[i]=0;
		for (int i=1;i<=r;++i)++s[a[i].t>>x&base];
		for (int i=1;i<=base;++i)s[i]+=s[i-1];
		for (int i=r;i>=1;--i)b[s[a[i].t>>x&base]--]=a[i];
		swap(a,b); x+=W;
	}
	a-=l-1;
}
void traverse(){
	uint x=get_min();
	while (1){
		res[r1++]=rev[x];
		if (!(a1[x>>5]-=get_bit(x))){
			if (!(a2[x>>10]-=get_bit(x>>5))){
				if (!(a3[x>>15]-=get_bit(x>>10))){
					if (!(a4-=get_bit1(x>>15)))break;
					x=min_bit(a4);
					x=(x<<5)+min_bit(a3[x]);
					x=(x<<5)+min_bit(a2[x]);
					x=(x<<5)+min_bit(a1[x]);
				}
				else {
					x=((x>>15)<<5)+min_bit(a3[x>>15]);
					x=(x<<5)+min_bit(a2[x]);
					x=(x<<5)+min_bit(a1[x]);
				}
			}
			else {
				x=((x>>10)<<5)+min_bit(a2[x>>10]);
				x=(x<<5)+min_bit(a1[x]);
			}
		}
		else x=(x&~31u)+min_bit(a1[x>>5]);
	}
}
class Solution {
public:
	vector<int> getOrder(vector<vector<int>>& v) {
		n=v.size(); int l0=0; res.resize(n); a=_a; b=_b;
		for (int i=0;i<n;++i)t[i]=v[i][0],l[i]=a[i].t=v[i][1],a[i].id=i;
		radix_sort(a,0,n-1);
		for (int i=0;i<n;++i)rev[l0]=a[i].id,l1[a[i].id]=l0++,a[i].t=v[i][0],a[i].id=i;
		radix_sort(a,0,n-1);
		for (int i=0,len=0,s=0;i<n;++i){
			if (!a4&&len<n&&a[len].t>s)s=a[len].t;
			while (len<n&&a[len].t<=s)add(l1[a[len++].id]);
			if (len==n){r1=i; traverse(); break;}
			int id=rev[del_min()];
			res[i]=id; if (len<n)s+=l[id];
		}
		return res;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

