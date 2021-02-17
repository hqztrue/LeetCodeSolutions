const int N=100005,W=32;
namespace Hash{
	typedef unsigned int uint;
	const uint S=17,S1=32-S,M=1996090921;
	struct node{
		int x,y,t;
	}h[(1<<S)+1005];
	int T=1;
	inline void insert(int x,int y){
		node *p=h+((uint)x*M>>S1);
		for (;p->t==T;++p)
			if (p->x==x)return;
		p->t=T; p->x=x; p->y=y;
	}
	inline int* find(int x){
		for (node *p=h+((uint)x*M>>S1);p->t==T;++p)
			if (p->x==x)return &p->y;
		return 0;
	}
} using namespace Hash;

int d1;
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
inline void succ(uint x){
	#define succ_bit(x,y) ((x)>>((y)&31))
	uint &p1=a1[x>>5],s=succ_bit(p1,x);
	if (s>=1){
		p1^=(1<<(min_bit(s)+(x&31)))^(1<<(x&31));
		return;
	}
	uint &p2=a2[x>>10],y;
	if (succ_bit(p2,x>>5)>1){
		y=(x>>5)+1+min_bit(succ_bit(p2,(x>>5)+1));
		uint &t=a1[y]; t-=t&-t;
		if (!t)p2-=get_bit(y);
		p1|=get_bit(x); p2|=get_bit(x>>5);
		return;
	}
	uint &p3=a3[x>>15],z;
	if (succ_bit(p3,x>>10)>1){
		y=(x>>10)+1+min_bit(succ_bit(p3,(x>>10)+1));
		z=(y<<5)+min_bit(a2[y]);
		uint &t=a1[z],&q2=a2[y]; t-=t&-t;
		if (!t)
			if (!(q2-=get_bit(z)))p3-=get_bit(y);
		p1|=get_bit(x); p2|=get_bit(x>>5); p3|=get_bit(x>>10);
		return;
	}
	if (succ_bit(a4,x>>15)>1){
		y=(x>>15)+1+min_bit(succ_bit(a4,(x>>15)+1));
		z=(y<<5)+min_bit(a3[y]);
		uint w=(z<<5)+min_bit(a2[z]);
		uint &t=a1[w],&q2=a2[z],&q3=a3[y]; t-=t&-t;
		if (!t)
			if (!(q2-=get_bit(w)))
				if (!(q3-=get_bit(z)))a4-=get_bit(y);
		p1|=get_bit(x); p2|=get_bit(x>>5); p3|=get_bit(x>>10); a4|=get_bit1(x>>15);
		return;
	}
	++d1; p1|=get_bit(x); p2|=get_bit(x>>5); p3|=get_bit(x>>10); a4|=get_bit1(x>>15);
}
class Solution {
public:
	int minOperations(vector<int>& t, vector<int>& a) {
		int n=t.size(),m=a.size(),c1=0; ++T;
		for (int i=0;i<n;++i)insert(t[i],i);
		init(n); d1=0;
		for (int i=0,*p;i<m;++i)
			if (p=find(a[i]))succ(*p);
		return n-d1;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

