const int N=50000;
void radix_sort(int A[],int l,int r){  //a[i]>=0
	//const int base=65535,W=16;
	const int base=511,W=9;
	//const int base=255,W=8;
	const int T=2;
	static int B[N+5],s[base+1];
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
int _c[N*2+5],*c=_c+N;
class Solution {
public:
	vector<int> sortArray(vector<int>& a) {
		int n=a.size();
		if (n<10000){
			for (int i=0;i<n;++i)a[i]+=N;
			radix_sort(&a[0],0,n-1);
			for (int i=0;i<n;++i)a[i]-=N;
		}
		else {
			for (int &x:a)++c[x];
			a.clear();
			for (int i=-N;i<=N;++i)
				while (c[i])--c[i],a.push_back(i);
		}
		return a;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

