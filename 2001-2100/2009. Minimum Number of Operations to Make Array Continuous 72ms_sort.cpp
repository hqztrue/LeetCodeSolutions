const int N=100005;
void radix_sort(int A[],int l,int r){  //a[i]>=0
	//const int base=32767,W=15;
	const int base=2047,W=11;
	//const int base=255,W=8;
	const int T=(30-1)/W+1;
	static int B[N],s[base+1];
	A+=l-1;r-=l-1;l=1;
	int *a=A,*b=B,x=0;
	for (int i1=1;i1<=T;++i1){
		for (int i=0;i<=base;++i)s[i]=0;
		for (int i=1;i<=r;++i)++s[a[i]>>x&base];
		for (int i=1;i<=base;++i)s[i]+=s[i-1];
		for (int i=r;i>=1;--i)b[s[a[i]>>x&base]--]=a[i];
		int *tmp=a;a=b;b=tmp;
		x+=W;
	}
	if (a!=A)for (int i=1;i<=r;++i)A[i]=a[i];
}
class Solution {
public:
	int minOperations(vector<int>& _a) {
		int n=_a.size(),*a=&_a[0],ans=0;
		radix_sort(a,0,n-1);
		int m=unique(a,a+n)-a,r=1;
		for (int l=0;l<m;++l){
			while (r<m&&a[r]-a[l]<=n-1)++r;
			ans=max(ans,r-l);
		}
		return n-ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

