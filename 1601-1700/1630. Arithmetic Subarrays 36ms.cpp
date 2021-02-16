typedef unsigned int uint;
typedef long long ll;
const int N=505,W=32,D=4,inf=1<<30,P=1000000007,U=100000;  //D=(int)log2(N/W)+1
int a[N+W];
namespace RMinQ{
	int f[D][N/W+1],M[N/W],stack[W];
	struct node{
		uint state[W]; int *a;
		int Q(int x,int y){return a[x+__builtin_ctz(state[y]>>x)];}
		void init(int *_a){
			int *s1=stack; *s1=0; state[0]=1; a=_a;
			for (int i=1;i<W;++i){
				state[i]=state[i-1];
				while (s1>=stack&&a[i]<=a[*s1])state[i]-=1<<*(s1--);
				*(++s1)=i;state[i]+=1<<i;
			}
		}
	}c[N/W+1];
	void build(int n){
		int nn=n/W,d=(int)log2(max(nn,1)); M[0]=-1;
		for (int i=1;i<nn;++i)M[i]=!(i&(i-1))?M[i-1]+1:M[i-1];
		for (int i=0;i<=nn;++i){
			int &f0=f[0][i],*_a=a+i*W; c[i].init(_a); f0=inf;
			for (int j=0;j<W;++j)f0=min(f0,_a[j]);
		}
		for (int j=1;j<=d;++j){
			int *f0=f[j-1],*f1=f[j],j1=1<<(j-1);
			for (int i=1;i<=nn-(1<<j);++i)f1[i]=min(f0[i],f0[i+j1]);
		}
	}
	inline int Q_ST(int x,int y){
		if (x>y)return inf;
		int z=M[y-x+1],*f0=f[z]; return min(f0[x],f0[y-(1<<z)+1]);
	}
	inline int Q(int x,int y){
		int xx=x/W,yy=y/W; x%=W; y%=W;
		return min(Q_ST(xx+1,yy-1),xx<yy?min(c[xx].Q(x,W-1),c[yy].Q(0,y)):c[xx].Q(x,y));
	}
} //using namespace RMinQ;
namespace RMaxQ{
	int f[D][N/W+1],M[N/W],stack[W];
	struct node{
		uint state[W]; int *a;
		int Q(int x,int y){return a[x+__builtin_ctz(state[y]>>x)];}
		void init(int *_a){
			int *s1=stack; *s1=0; state[0]=1; a=_a;
			for (int i=1;i<W;++i){
				state[i]=state[i-1];
				while (s1>=stack&&a[i]>=a[*s1])state[i]-=1<<*(s1--);
				*(++s1)=i;state[i]+=1<<i;
			}
		}
	}c[N/W+1];
	void build(int n){
		int nn=n/W,d=(int)log2(max(nn,1)); M[0]=-1;
		for (int i=1;i<nn;++i)M[i]=!(i&(i-1))?M[i-1]+1:M[i-1];
		for (int i=0;i<=nn;++i){
			int &f0=f[0][i],*_a=a+i*W; c[i].init(_a); f0=-inf;
			for (int j=0;j<W;++j)f0=max(f0,_a[j]);
		}
		for (int j=1;j<=d;++j){
			int *f0=f[j-1],*f1=f[j],j1=1<<(j-1);
			for (int i=1;i<=nn-(1<<j);++i)f1[i]=max(f0[i],f0[i+j1]);
		}
	}
	inline int Q_ST(int x,int y){
		if (x>y)return -inf;
		int z=M[y-x+1],*f0=f[z]; return max(f0[x],f0[y-(1<<z)+1]);
	}
	inline int Q(int x,int y){
		int xx=x/W,yy=y/W; x%=W; y%=W;
		return max(Q_ST(xx+1,yy-1),xx<yy?max(c[xx].Q(x,W-1),c[yy].Q(0,y)):c[xx].Q(x,y));
	}
} //using namespace RMaxQ;

int g[N],_s[N],*s=_s+1,R=rand()%P;
inline int exp(int x,int y){
	int ans=1;
	while (y){
		if (y&1)ans=(ll)ans*x%P;
		x=(ll)x*x%P; y>>=1;
	}
	return ans;
}
class Solution {
public:
	vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
		int n=nums.size(),m=l.size(); vector<bool> ans(m);
		for (int i=0;i<n;++i)a[i]=nums[i]+U;
		RMinQ::build(n); RMaxQ::build(n); s[-1]=0;
		for (int i=0;i<n;++i)g[i]=exp(R,a[i]),s[i]=(s[i-1]+g[i])%P;
		for (int i=0;i<m;++i){
			int mi=RMinQ::Q(l[i],r[i]),ma=RMaxQ::Q(l[i],r[i]),d=l[i]<r[i]?(ma-mi)/(r[i]-l[i]):0;
			if (ma-mi!=d*(r[i]-l[i]))continue;
			if (d==0){ans[i]=1; continue;}
			d=exp(R,d);
			int s0=(ll)exp(R,mi)*(1-exp(d,r[i]-l[i]+1))%P*exp(1-d,P-2)%P;
			ans[i]=(s[r[i]]-s[l[i]-1]-s0)%P==0;
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

