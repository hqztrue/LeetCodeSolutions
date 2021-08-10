const int N=100005,U=10000005,W=32;
int b[N],s[U],r[N],d1;
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
	uint &p1=a1[x>>5],s=succ_bit(p1,x),y;
	if (s){
		y=((x>>5)<<5)+min_bit(s)+(x&31); r[x]=r[y];
		p1^=(1<<(min_bit(s)+(x&31)))^(1<<(x&31));
		return;
	}
	uint &p2=a2[x>>10];
	if (succ_bit(p2,x>>5)>1){
		y=(x>>5)+1+min_bit(succ_bit(p2,(x>>5)+1));
		uint &t=a1[y];
		r[x]=r[(y<<5)+min_bit(t)];
		t-=t&-t;
		if (!t)p2-=get_bit(y);
		p1|=get_bit(x); p2|=get_bit(x>>5);
		return;
	}
	uint &p3=a3[x>>15],z;
	if (succ_bit(p3,x>>10)>1){
		y=(x>>10)+1+min_bit(succ_bit(p3,(x>>10)+1));
		z=(y<<5)+min_bit(a2[y]);
		uint &t=a1[z],&q2=a2[y];
		r[x]=r[(z<<5)+min_bit(t)];
		t-=t&-t;
		if (!t)
			if (!(q2-=get_bit(z)))p3-=get_bit(y);
		p1|=get_bit(x); p2|=get_bit(x>>5); p3|=get_bit(x>>10);
		return;
	}
	if (succ_bit(a4,x>>15)>1){
		y=(x>>15)+1+min_bit(succ_bit(a4,(x>>15)+1));
		z=(y<<5)+min_bit(a3[y]);
		uint w=(z<<5)+min_bit(a2[z]);
		uint &t=a1[w],&q2=a2[z],&q3=a3[y];
		r[x]=r[(w<<5)+min_bit(t)];
		t-=t&-t;
		if (!t)
			if (!(q2-=get_bit(w)))
				if (!(q3-=get_bit(z)))a4-=get_bit(y);
		p1|=get_bit(x); p2|=get_bit(x>>5); p3|=get_bit(x>>10); a4|=get_bit1(x>>15);
		return;
	}
	++d1; p1|=get_bit(x); p2|=get_bit(x>>5); p3|=get_bit(x>>10); a4|=get_bit1(x>>15); r[x]=d1;
}
void radix_sort(int A[],int l,int r){  //a[i]>=0
	const int base=4095,W=12,T=2;
	static int B[N],s[base+1];
	A+=l-1;r-=l-1;l=1;
	int *a=A,*b=B,x=0;
	{
		for (int i=0;i<=base;++i)s[i]=0;
		for (int i=1;i<=r;++i)++s[a[i]>>x&base];
		for (int i=1;i<=base;++i)s[i]+=s[i-1];
		for (int i=r;i>=1;--i)b[s[a[i]>>x&base]--]=a[i];
		int *tmp=a;a=b;b=tmp;
		x+=W;
	}
	{
		for (int i=0;i<=base;++i)s[i]=0;
		for (int i=1;i<=r;++i)++s[a[i]>>x&base];
		for (int i=1;i<=base;++i)s[i]+=s[i-1];
		for (int i=r;i>=1;--i)::s[a[i]]=s[a[i]>>x&base]--;
	}
}
class Solution {
public:
	vector<int> longestObstacleCourseAtEachPosition(vector<int>& _a) {
		int *a=&_a[0],n=_a.size();
		vector<int> ans(n);
		for (int i=0;i<n;++i)b[i]=a[i];
		radix_sort(b,0,n-1);
		//for (int i=n-1;i>=0;--i)s[b[i]]=i;
		init(n); d1=0;
		for (int i=0;i<n;++i){
			int x=s[a[i]]++; succ(x);
			ans[i]=r[x];
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

