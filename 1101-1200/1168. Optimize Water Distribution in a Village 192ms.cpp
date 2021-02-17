const int N=20005;
int f[N];
int find(int x){
	if (f[x]==x)return x;
	return f[x]=find(f[x]);
}
inline void link(int x,int y){f[find(x)]=find(y);}
typedef vector<int> *T;
void radix_sort_fast(T A[],int l,int r){  //a[i]>=0, -O2
	const int base=255;
	static T B[N];
	static int s[base+1];
	A+=l-1;r-=l-1;l=1;
	T *a=A,*b=B;
	{
		for (int i=0;i<=base;++i)s[i]=0;
		for (int i=1;i<=r;++i)++s[(*a[i])[2]&base];
		for (int i=1;i<=base;++i)s[i]+=s[i-1];
		for (int i=r;i>=1;--i)b[s[(*a[i])[2]&base]--]=a[i];
		swap(a,b);
	}
	{
		for (int i=0;i<=base;++i)s[i]=0;
		for (int i=1;i<=r;++i)++s[(*a[i])[2]>>8&base];
		for (int i=1;i<=base;++i)s[i]+=s[i-1];
		for (int i=r;i>=1;--i)b[s[(*a[i])[2]>>8&base]--]=a[i];
		swap(a,b);
	}
	{
		for (int i=0;i<=base;++i)s[i]=0;
		for (int i=1;i<=r;++i)++s[(*a[i])[2]>>16&base];
		for (int i=1;i<=base;++i)s[i]+=s[i-1];
		for (int i=r;i>=1;--i)b[s[(*a[i])[2]>>16&base]--]=a[i];
		swap(a,b);
	}
	{
		for (int i=0;i<=base;++i)s[i]=0;
		for (int i=1;i<=r;++i)++s[(*a[i])[2]>>24&base];
		for (int i=1;i<=base;++i)s[i]+=s[i-1];
		for (int i=r;i>=1;--i)b[s[(*a[i])[2]>>24&base]--]=a[i];
		swap(a,b);
	}
	if (a!=A)for (int i=1;i<=r;++i)A[i]=a[i];
}
vector<int> *a[N];
class Solution {
public:
	int minCostToSupplyWater(int n, vector<int>& w, vector<vector<int>>& p) {
		int m=p.size(),cnt=n,s=0;
		p.resize(m+n);
		for (int i=0;i<n;++i){
			p[m+i].push_back(0);
			p[m+i].push_back(i+1);
			p[m+i].push_back(w[i]);
		}
		m+=n;
		for (int i=0;i<m;++i)a[i]=&p[i];
		radix_sort_fast(a,0,m-1);
		for (int i=0;i<=n;++i)f[i]=i;
		for (int i=0;i<m;++i){
			int f1=find((*a[i])[0]),f2=find((*a[i])[1]);
			if (f1!=f2){
				f[f1]=f2; --cnt; s+=(*a[i])[2];
			}
		}
		return s;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

