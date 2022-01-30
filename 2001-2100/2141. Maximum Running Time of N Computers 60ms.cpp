typedef long long ll;
class Solution {
public:
	int n,m;
	int solve(int l,int r,ll s0,int *a){
		if (l==r-1)return l;
		int mid=(l+r)/2; ll s=0;
		nth_element(a+l,a+mid,a+r);
		for (int i=l;i<mid;++i)s+=a[i];
		if (s+s0>=(ll)a[mid]*(n-m+mid))return solve(mid,r,s0+s,a);
		else return solve(l,mid,s0,a);
	}
	ll maxRunTime(int n, vector<int>& a) {
		this->n=n; m=a.size();
		int t=solve(0,m,0,&a[0]); ll s=0;
		for (int i=0;i<=t;++i)s+=a[i];
		return s/(n-m+t+1);
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

