typedef long long ll;
const int N=10005;
struct point{
	int x,y;
	point(){}
	point(int _x,int _y):x(_x),y(_y){}
	point operator +(const point &p)const{return point(x+p.x,y+p.y);}
}s[N];
int n,m,t;
inline bool in(int x,int y){return x*y>t&&x<=n;}
inline bool judge(int x,point &p){return x>n||(ll)t*p.x<=(ll)x*x*p.y;}
int count(){
	int _n=n,_m=m,t0=pow(t,2./3)+1,cnt=0;
	for (int i=1;i<=min(m,t/t0);++i)cnt+=max(min(t/i,n)-t0,(int)0);
	for (int i=1;i<=min(n,t/t0);++i)cnt+=max(min(t/i,m)-t0,(int)0);
	n=min(n,t0); m=min(m,t0);
	if (n*m<=t)cnt+=n*m;
	else {
		int x=t/m+1,y=t/x+1,s1=1;
		cnt+=t/m*m+y-1;
		s[0]=point(1,0); s[1]=point(0,1);
		point L,R,M;
		while (1){
			L=s[s1--];
			if (L.y==0)cnt+=(y-1)*(n-x),x=n;
			for (;in(x+L.x,y-L.y);x+=L.x,y-=L.y)
				cnt+=(2*y-L.y-1)*(L.x-1)/2+y-L.y-1;
			if (x>=n)break;
			for (R=s[s1];!in(x+R.x,y-R.y);R=s[--s1])L=R;
			for (M=L+R;;M=L+R)
				if (in(x+M.x,y-M.y))s[++s1]=R=M;
				else {
					if (judge(x+M.x,R))break;
					L=M;
				}
		}
	}
	n=_n; m=_m;
	return cnt;
}
inline double f(double t){return t*(1+log(1.*n*m/t));}
double solve(double v){
	double eps=1e-2,l=eps,r=n*m;
	while (r-l>eps){
		double mid=(l+r)/2;
		if (f(mid)<v)l=mid;
		else r=mid;
	}
	return l;
}
class Solution {
public:
	int findKthNumber(int m0, int n0, int k) {
		m=m0; n=n0;
		int l=solve(k),r=solve(k+n+m)+1;
		while (l<r){
			t=(l+r)/2;
			if (count()>=k)r=t;
			else l=t+1;
		}
		return l;
	}
};

