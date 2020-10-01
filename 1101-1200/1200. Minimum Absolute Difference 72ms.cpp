const int N=100005,U=1000000;
void radix_sort_fast(int A[],int l,int r){  //a[i]>=0, -O2
	for (int i=l;i<=r;++i)A[i]+=U;
	const int base=255;
	static int B[N],s[base+1];
	A+=l-1;r-=l-1;l=1;
	int *a=A,*b=B;
	{
		for (int i=0;i<=base;++i)s[i]=0;
		for (int i=1;i<=r;++i)++s[a[i]&base];
		for (int i=1;i<=base;++i)s[i]+=s[i-1];
		for (int i=r;i>=1;--i)b[s[a[i]&base]--]=a[i];
		int *tmp=a;a=b;b=tmp;
	}
	{
		for (int i=0;i<=base;++i)s[i]=0;
		for (int i=1;i<=r;++i)++s[a[i]>>8&base];
		for (int i=1;i<=base;++i)s[i]+=s[i-1];
		for (int i=r;i>=1;--i)b[s[a[i]>>8&base]--]=a[i];
		int *tmp=a;a=b;b=tmp;
	}
	{
		for (int i=0;i<=base;++i)s[i]=0;
		for (int i=1;i<=r;++i)++s[a[i]>>16&base];
		for (int i=1;i<=base;++i)s[i]+=s[i-1];
		for (int i=r;i>=1;--i)b[s[a[i]>>16&base]--]=a[i];
		int *tmp=a;a=b;b=tmp;
	}
	{
		for (int i=0;i<=base;++i)s[i]=0;
		for (int i=1;i<=r;++i)++s[a[i]>>24&base];
		for (int i=1;i<=base;++i)s[i]+=s[i-1];
		for (int i=r;i>=1;--i)b[s[a[i]>>24&base]--]=a[i];
		int *tmp=a;a=b;b=tmp;
	}
	if (a!=A)for (int i=1;i<=r;++i)A[i]=a[i];
	for (int i=l;i<=r;++i)A[i]-=U;
}
void insert_sort(int a[],int l,int r){
	for (int i=l+1;i<=r;++i){
		int tmp=a[i],j;
		for (j=i-1;j>=l&&a[j]>tmp;--j)a[j+1]=a[j];
		a[j+1]=tmp;
	}
}
template<class T>
void Q_plus(T a[],int s,int t){
	if (s+15>t){insert_sort(a,s,t);return;}
	int i=s,j=t,tmp,m=a[s+rand()%(t-s+1)]; //m=a[(s+t)>>1];
	do {
		while (a[i]<m)++i;
		while (a[j]>m)--j;
		if (i<=j){
			tmp=a[i]; a[i]=a[j]; a[j]=tmp;
			++i; --j;
		}
	}while (i<=j);
	if (i<t)Q_plus(a,i,t);
	if (s<j)Q_plus(a,s,j);
}
class Solution {
public:
	vector<vector<int>> ans;
	const vector<vector<int>>& minimumAbsDifference(vector<int>& a) {
		int n=a.size(),d=INT_MAX;
		//Q_plus(&a[0],0,n-1);
		radix_sort_fast(&a[0],0,n-1);
		for (int i=0;i<n-1;++i)
			if (a[i+1]-a[i]<d)d=a[i+1]-a[i];
		for (int i=0;i<n-1;++i)
			if (a[i+1]-a[i]==d)ans.push_back({a[i],a[i+1]});
		return ans;
	}
};

//IO
int _IO=[](){
	std::ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();


