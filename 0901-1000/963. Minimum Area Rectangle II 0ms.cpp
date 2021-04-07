typedef unsigned long long ull;
const double inf=1e10;
double ans;
namespace Hash{
	typedef unsigned int uint;
	const uint S=10,S1=32-S,M=1996090921,_inf=~0u>>1;
	#define H(x) ((uint)x*M>>S1)
	struct node{
		int x,t;
		double y;
	}h[(1<<S)+105];
	int T=1;
	inline void insert(uint x,double y){
		node *p=h+H(x);
		for (;p->t==T;++p)
			if (p->x==x){
				ans=min(ans,y-p->y); p->y=y;
				return;
			}
		p->t=T; p->x=x; p->y=y;
	}
	#undef H
} using namespace Hash;
inline uint h1(double x){ull t=*((ull*)&x); return (t>>32)^(t>>17);}
class Solution {
public:
	double minAreaFreeRect(vector<vector<int>>& p) {
		int n=p.size(); ans=inf; ++T;
		sort(p.begin(),p.end());
		for (int i=0;i<n;++i){
			uint x1=p[i][0],y1=p[i][1];
			for (int j=i+1;j<n;++j)if (p[j][1]>y1){
				uint x2=p[j][0],y2=p[j][1];
				double l=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)),t=(double)(x2-x1)/(y2-y1),d=x1*t+y1;
				insert(h1(l*3.14159+t*1.2345+d),l*sqrt(x1*x1+(y1-d)*(y1-d)));
			}
		}
		return ans==inf?0:ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

