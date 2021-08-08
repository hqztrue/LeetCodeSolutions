/***************************************************
Author: hqztrue
https://github.com/hqztrue/LeetCodeSolutions
Complexity: O(U log U)
If you find this solution helpful, plz give a star:)
***************************************************/
const double pi=2*asin(1);
#define N 2105
struct cpx{
	double x,y;
	cpx(double _x=0,double _y=0):x(_x),y(_y){}
	void clear(){x=y=0;}
};
inline cpx operator +(const cpx &a,const cpx &b){return cpx(a.x+b.x,a.y+b.y);}
inline cpx operator -(const cpx &a,const cpx &b){return cpx(a.x-b.x,a.y-b.y);}
inline cpx operator *(const cpx &a,const cpx &b){return cpx(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
cpx f[N],aa[N];
char str[N];
int ans[N],n;
struct DFT{
	cpx a[N];
	void cal(int n,int s,int t){
		if (n==1)return;
		int j=n>>1;
		cal(j,s,t+1);cal(j,s+(1<<t),t+1);
		for (int i=0;i<j;++i){
			int p=s+(i<<(t+1));
			cpx w=f[i<<t]*a[p+(1<<t)];
			aa[i]=a[p]+w;aa[i+j]=a[p]-w;
		}
		for (int i=0;i<n;++i)a[s+(i<<t)]=aa[i];
	}
};
DFT a,b,c;
int cnt[N],s[N];
class Solution {
public:
	int triangleNumber(vector<int>& v) {
		int ans=0,n0=v.size(),n1=0; n=0;
		memset(cnt,0,sizeof(cnt));
		for (int i=0;i<n0;++i)++cnt[v[i]],n=max(n,v[i]),n1+=v[i]>0;
		++n; int tmp=1;
		while (tmp<n)tmp<<=1;
		for (int i=0;i<=tmp<<1;++i)a.a[i].clear(),b.a[i].clear();
		for (int i=1;i<n;++i)a.a[i].x=b.a[i].x=cnt[i]; cnt[0]=0;
		for (int i=1;i<n;++i)ans-=cnt[i]*cnt[i/2],cnt[i]+=cnt[i-1];
		n=tmp<<1;
		for (int i=0;i<n;++i)f[i]=cpx(cos(2*pi*i/n),sin(2*pi*i/n));
		a.cal(n,0,0);b.cal(n,0,0);
		for (int i=0;i<n;++i)c.a[i]=a.a[i]*b.a[i];
		for (int i=0;i<n;++i)f[i].y*=-1;
		c.cal(n,0,0);
		for (int i=1;i<n;++i)s[i]=s[i-1]+(int)(c.a[i].x/n+0.1);
		for (int i=0;i<n0;++i)ans+=s[v[i]];
		ans=n1*(n1-1)*(n1-2)/6-ans/2;
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

