const int N=205;
int p[N],m0,m; double d;
class Cashier {
public:
	Cashier(int _n, int _d, vector<int>& products, vector<int>& prices) {
		m0=_n; m=0; d=1-0.01*_d;
		for (int i=0;i<products.size();++i)p[products[i]]=prices[i];
	}
	double getBill(const vector<int> &_a, const vector<int> &b) {
		const int *a=&_a[0]; int n=_a.size(),s=0;
		for (int i=0;i<n;++i)s+=p[a[i]]*b[i];
		return ++m%m0==0?s*d:s;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

