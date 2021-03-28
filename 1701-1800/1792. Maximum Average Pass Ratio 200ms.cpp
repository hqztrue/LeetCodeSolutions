const int N=100005;
const double eps=1e-8;
struct node{
	int d,b; double g;
	void get(){g=d/((double)b*(b+1));}
	bool operator <(const node &A)const{return g<A.g;}
}a[N];
inline int f(int d,int b,double y){
	return sqrt(d*y+0.25)-b+0.5+eps;
}
class Solution {
public:
	void find(node *a,int n,int r){
		if (r==0)return;
		int mid=rand()%n; long long s=0; double v=a[mid].g;
		//nth_element(a,a+mid,a+n);
		int i=0,j=n-1;
		do {
			while (a[i].g<v)++i;
			while (a[j].g>v)--j;
			if (i<=j){
				swap(a[i],a[j]);
				++i; --j;
			}
		}while (i<=j);
		mid=i-1; v=1./v;
		for (int i=mid+1;i<n;++i)s+=f(a[i].d,a[i].b,v);
		if (s>=r)find(a+mid+1,n-mid-1,r);
		else {
			for (int i=mid+1;i<n;++i){
				int t=f(a[i].d,a[i].b,v);
				a[i].b+=t; r-=t; a[i].get();
			}
			if (n==1)++a[0].b,--r,a[0].get();
			find(a,n,r);
		}
	}
	double maxAverageRatio(vector<vector<int>>& c, int k) {
		int n=0; double ans=0;
		for (int i=0;i<c.size();++i)
			if (c[i][0]!=c[i][1])a[n].d=c[i][1]-c[i][0],a[n].b=c[i][1],a[n].get(),++n;
		if (!n)return 1;
		find(a,n,k);
		for (int i=0;i<n;++i)ans-=double(a[i].d)/a[i].b;
		return 1+ans/c.size();
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

