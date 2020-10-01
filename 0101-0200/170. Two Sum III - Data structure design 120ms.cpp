typedef long long ll;
const int N=10005,inf=~0u>>1;
class TwoSum {
public:
	/** Initialize your data structure here. */
	multiset<int> S;
	vector<int> a;
	int vmin,vmax,flag;
	TwoSum() {S.clear(); vmin=inf; vmax=-inf; flag=0;}
	/** Add the number to an internal data structure.. */
	void add(int x) {
		vmin=min(vmin,x); vmax=max(vmax,x);
		S.insert(x); flag=0;
	}
	/** Find if there exists any pair of numbers which sum is equal to the value. */
	bool find(int v) {
		if (!S.size()||v<(ll)2*vmin||v>(ll)2*vmax)return 0;
		if (!flag)a=vector(S.begin(),S.end()),flag=1;
		int n=a.size();
		for (int *l=&a[0],*r=&a[n-1];l!=r;)
			if (*l+*r<v)++l;
			else if (*l+*r>v)--r;
			else return 1;
		return 0;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();
