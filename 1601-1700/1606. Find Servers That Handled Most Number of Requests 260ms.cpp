const int N=200005,W=32;
int c[N/2],flag[N],*pos[N/2];
struct node{
	int t,id;
}_V[N];
void radix_sort(node *&A,int l,int r){  //a[i]>=0
	//const int base=65535,W=16;
	const int base=2047,W=11;
	//const int base=255,W=8;
	const int T=(32-1)/W+1;
	static node B[N];
	static int s[base+1];
	A+=l-1;r-=l-1; int _l=l; l=1;
	node *a=A,*b=B; int x=0;
	for (int i1=1;i1<=T;++i1){
		for (int i=0;i<=base;++i)s[i]=0;
		for (int i=1;i<=r;++i)++s[a[i].t>>x&base];
		for (int i=1;i<=base;++i)s[i]+=s[i-1];
		for (int i=r;i>=1;--i)b[s[a[i].t>>x&base]--]=a[i];
		swap(a,b); x+=W;
	}
	if (a!=A)A=B-_l+1; //for (int i=1;i<=r;++i)A[i]=a[i];
}
uint a1[N/W+5],a2[N/W/W+5],a3[N/W/W/W+5],a4;  //[0,2^20)
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
inline void del(uint x){
	if (a1[x>>5]&get_bit(x))
		if (!(a1[x>>5]-=get_bit(x)))
			if (!(a2[x>>10]-=get_bit(x>>5)))
				if (!(a3[x>>15]-=get_bit(x>>10)))
					a4-=get_bit1(x>>15);
}
inline int get_min(){
	//if (!a4)return -1;
	uint x=min_bit(a4);
	x=(x<<5)+min_bit(a3[x]);
	x=(x<<5)+min_bit(a2[x]);
	return (x<<5)+min_bit(a1[x]);
}
class Solution {
public:
	int k,cur;
	int enc(int x){return x+(cur-x+k)/k*k;}
	vector<int> busiestServers(int k, vector<int>& a, vector<int>& l) {
		int n=a.size(); node *p=_V,*V=_V; this->k=k; cur=0;
		memset(c,0,sizeof(int)*k); init(n+k);
		for (int i=0;i<n;++i){
			p->t=a[i]; p->id=i; ++p;
			p->t=a[i]+l[i]; p->id=i; ++p;
		}
		radix_sort(V,0,n*2-1);
		for (node *p=V,*end=V+n*2;p!=end;++p)
			if (p->t==a[p->id])flag[p-V]=-1;
			else pos[p->id]=p-V+flag;
		for (int i=0;i<k;++i)add(i);
		for (int i=0;i<n*2;++i)
			if (flag[i]>=0)add(enc(flag[i]));
			else if (flag[i]==-1){
				cur=V[i].id;
				if (a4){
					int t=get_min();
					++c[t%k]; *pos[cur]=t; del(t);
				}
				else *pos[cur]=-2;
			}
		vector<int> res; int m=*max_element(c,c+k);
		for (int i=0;i<k;++i)if (c[i]==m)res.push_back(i);
		return res;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

