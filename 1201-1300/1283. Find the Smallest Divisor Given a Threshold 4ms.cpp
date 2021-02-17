typedef long long ll;
const int N=100005,inf=1000000005;
inline int _rand(){static unsigned int x=1996090921;x+=(x<<4)+1;return x&=0x7fffffff;}
int c[N],d;
class Solution {
public:
	int *a,n,m; ll s;
	void reduce(int *a,int n,int r){
		if (!r||r>n)return;
		for (int i=0;i<n;++i)c[i]=a[i]/(a[i]/d+1);
		nth_element(c,c+n-r,c+n); int v=c[n-r],n1=0,p;
		for (int i=0;i<n;++i){
			int t=a[i]/(a[i]/d+1);
			if (t>v)a[n1++]=a[i];
			else if (t==v)p=a[i];
		}
		for (int i=n1;i<r;++i)a[i]=p;
	}
	void find(int *a,int n,int r){
		if (r==0)return;
		for (int i=0;i<n;++i)c[i]=a[i]/(a[i]/d+1);
		int mid=n/2,s=0,v;
		nth_element(c,c+mid,c+n); v=c[mid];
		for (int i=0;i<n;++i)s+=a[i]/(v+1)-a[i]/d;
		if (s>=r){
			int n1=0;
			for (int i=0;i<n;++i)if (a[i]/(a[i]/d+1)>v)a[n1++]=a[i];
			find(a,n1,r);
		}
		else {
			if (!v){d=v; return;}
			s=0; for (int i=0;i<n;++i)s+=a[i]/v-a[i]/d;
			d=v; if (s>=r)return;
			r-=s; reduce(a,n,r);
			find(a,min(n,r),r);
		}
	}
	double f(int x){
		double res=1.*s/x; ll s1=0;
		for (int i=0,j;i<m;++i)
			j=a[i]%x,s1+=x*(j>0)-j;  //a[_rand()%n]%x
		return res+1.*s1/x*n/m;
	}
	int smallestDivisor(vector<int>& A, int t) {
		n=A.size(); a=&A[0]; m=min(n,(int)(pow(n*log2(N),2./3)*0.05+10)); s=0; //t+=n;
		for (int i=0;i<n;++i)s+=a[i];
		if (s<=t)return 1;
		for (int i=0;i<m;++i)swap(a[i],a[i+_rand()%(n-i)]);  //random_shuffle(a,a+n);
		int l=1,r=min(inf,(int)ceil(1.*s/(max(t-n,1)))),delta=m*log2(N)*0.2+100;
		while (l<r){
			int mid=(l+r)>>1;
			if (f(mid)+delta<=t)r=mid;
			else l=mid+1;
		}
		int s1=n; d=l; for (int i=0;i<n;++i)a[i]-=1,s1+=a[i]/d;
		assert(s1<=t);
		if (t-s1>delta*2){
			s1=n; d=l-1; for (int i=0;i<n;++i)s1+=a[i]/d;
			if (s1>t)return l;
		}
		assert(t-s1<=delta*2);
		if (s1>t)return d+1;
		reduce(&a[0],n,t+1-s1);
		find(&a[0],min(n,t+1-s1),t+1-s1);
		return d+1;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

