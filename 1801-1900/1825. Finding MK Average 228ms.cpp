const int N=100005,W=32;
namespace wTrie{
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
	inline bool find(uint x){
		return (a1[x>>5]>>(x&31))&1;
	}
	inline void add(uint x){
		a1[x>>5]|=get_bit(x);
		a2[x>>10]|=get_bit(x>>5);
		a3[x>>15]|=get_bit(x>>10);
		a4|=get_bit1(x>>15);
	}
	inline void del(uint x){
		if (a1[x>>5]&get_bit(x))
			if (!(a1[x>>5]-=get_bit(x)))
				if (!(a2[x>>10]-=get_bit(x>>5)))
					if (!(a3[x>>15]-=get_bit(x>>10)))
						a4-=get_bit1(x>>15);
	}
	inline int get_min(){
		if (!a4)return -1;
		uint x=min_bit(a4);
		x=(x<<5)+min_bit(a3[x]);
		x=(x<<5)+min_bit(a2[x]);
		return (x<<5)+min_bit(a1[x]);
	}
	inline int get_max(){
		if (!a4)return -1;
		uint x=max_bit(a4);
		x=(x<<5)+max_bit(a3[x]);
		x=(x<<5)+max_bit(a2[x]);
		return (x<<5)+max_bit(a1[x]);
	}
	inline int pred(uint x){
		#define P(x) ((x)&0xFFFFFFFE0u)
		#define pred_bit(x,y) ((x)&get_bit(y)-1)
		if (pred_bit(a1[x>>5],x))return P(x)+max_bit(pred_bit(a1[x>>5],x));
		x>>=5;
		if (pred_bit(a2[x>>5],x)){
			x=P(x)+max_bit(pred_bit(a2[x>>5],x));
			return (x<<5)+max_bit(a1[x]);
		}
		x>>=5;
		if (pred_bit(a3[x>>5],x)){
			x=P(x)+max_bit(pred_bit(a3[x>>5],x));
			x=(x<<5)+max_bit(a2[x]);
			return (x<<5)+max_bit(a1[x]);
		}
		x>>=5;
		if (pred_bit(a4,x)){
			x=max_bit(pred_bit(a4,x));
			x=(x<<5)+max_bit(a3[x]);
			x=(x<<5)+max_bit(a2[x]);
			return (x<<5)+max_bit(a1[x]);
		}
		return -1;
	}
	inline int succ(uint x){
		#define succ_bit(x,y) ((x)>>((y)&31))
		if (succ_bit(a1[x>>5],x)>1)return x+1+min_bit(succ_bit(a1[x>>5],x+1));
		x>>=5;
		if (succ_bit(a2[x>>5],x)>1){
			x=x+1+min_bit(succ_bit(a2[x>>5],x+1));
			return (x<<5)+min_bit(a1[x]);
		}
		x>>=5;
		if (succ_bit(a3[x>>5],x)>1){
			x=x+1+min_bit(succ_bit(a3[x>>5],x+1));
			x=(x<<5)+min_bit(a2[x]);
			return (x<<5)+min_bit(a1[x]);
		}
		x>>=5;
		if (succ_bit(a4,x)>1){
			x=x+1+min_bit(succ_bit(a4,x+1));
			x=(x<<5)+min_bit(a3[x]);
			x=(x<<5)+min_bit(a2[x]);
			return (x<<5)+min_bit(a1[x]);
		}
		return -1;
	}
} using namespace wTrie;
int a[N],b[N],c[N],n,l,r,nl,nr;
long ans;
class MKAverage {
public:
	int m,k;
	MKAverage(int _m, int _k):m(_m),k(_k) {
		init(); n=0;
	}
	void addElement(int x) {
		a[n++]=x; if (++c[x]==1)add(x);
		if (n==m){
			memcpy(b,a,sizeof(int)*n);
			nth_element(b,b+k-1,b+n);
			nth_element(b+k,b+n-k,b+n);
			ans=0; for (int i=k;i<n-k;++i)ans+=b[i];
			l=b[k-1]; nl=0; for (int j=0;j<=k-1;++j)nl+=b[j]==l;
			r=b[n-k]; nr=0; for (int j=0;j<=n-k;++j)nr+=b[j]==r;
		}
		else if (n>m){
			if (x<l){
				ans+=l;
				if (--nl==0)l=pred(l),nl=c[l];
			}
			else if (x>=r){
				ans+=r;
				if (++nr>c[r])r=succ(r),nr=1;
			}
			else ans+=x;
			int y=a[n-m-1];
			if (--c[y]==0)del(y);
			if (y>=r){
				if (--nr==0)r=pred(r),nr=c[r];
				ans-=r;
			}
			else if (y<=l){
				if (y<l&&++nl>c[l]||y==l&&nl>c[l])l=succ(l),nl=1;
				ans-=l;
			}
			else ans-=y;
		}
	}
	int calculateMKAverage() {
		return n<m?-1:ans/(m-2*k);
	}
	~MKAverage(){
		for (int i=0;i<n;++i)c[a[i]]=0;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

