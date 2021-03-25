const int N=10005,inf=~0u>>1;
void radix_sort(int A[],int l,int r){  //a[i]>=0
	//const int base=65535,W=16;
	//const int base=2047,W=11;
	const int base=255,W=8;
	const int T=(32-1)/W+1;
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
struct node{
	int t,id;
}b[N];
void radix_sort1(node A[],int l,int r){  //a[i]>=0
	//const int base=65535,W=16;
	//const int base=2047,W=11;
	const int base=255,W=8;
	const int T=(32-1)/W+1;
	static node B[N];
	static int s[base+1];
	A+=l-1;r-=l-1;l=1;
	node *a=A,*b=B; int x=0;
	for (int i1=1;i1<=T;++i1){
		for (int i=0;i<=base;++i)s[i]=0;
		for (int i=1;i<=r;++i)++s[a[i].t>>x&base];
		for (int i=1;i<=base;++i)s[i]+=s[i-1];
		for (int i=r;i>=1;--i)b[s[a[i].t>>x&base]--]=a[i];
		swap(a,b); x+=W;
	}
	if (a!=A)for (int i=1;i<=r;++i)A[i]=a[i];
}
class Solution {
public:
	vector<int> advantageCount(vector<int>& A, vector<int>& B) {
		int n=A.size(),j=0;
		radix_sort(&A[0],0,n-1);
		for (int i=0;i<n;++i)b[i].t=B[i],b[i].id=i;
		radix_sort1(b,0,n-1);
		for (int i=0;i<n;++i)
			if (A[i]>b[j].t){B[b[j].id]=A[i]; ++j;}
			else A[i]-=inf;
		for (int i=0;i<n;++i)
			if (A[i]<0){B[b[j].id]=A[i]+inf; ++j;}
		return B;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

