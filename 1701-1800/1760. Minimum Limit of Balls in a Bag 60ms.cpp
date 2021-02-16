typedef long long ll;
const int N=100005;
int c[N],d;
class Solution {
public:
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
	int minimumSize(vector<int>& a, int t) {
		int n=a.size(); ll s=0; t+=n;
		for (int i=0;i<n;++i)s+=a[i];
		if (s<=t)return 1;
		d=t==n?*max_element(a.begin(),a.end()):(int)floor(1.*s/(t-n));
		int s1=n; for (int i=0;i<n;++i)a[i]-=1,s1+=a[i]/d;
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

