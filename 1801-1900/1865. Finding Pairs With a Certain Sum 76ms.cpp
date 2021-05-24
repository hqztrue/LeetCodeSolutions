const int N=100100000;
int c[N+1],*a1,*a2,n,m;
class FindSumPairs {
public:
	FindSumPairs(vector<int>& v1, vector<int>& v2) {
		sort(v1.begin(),v1.end());
		a1=&v1[0]; a2=&v2[0]; n=v1.size(); m=v2.size();
		for (int i=0;i<m;++i)++c[a2[i]];
	}
	void add(int id, int v) {
		int *p=a2+id;
		--c[*p]; *p+=v; ++c[*p];
	}
	int count(int t) {
		int ans=0;
		for (int *p=lower_bound(a1,a1+n,t-N),*end=upper_bound(a1,a1+n,t);p<end;++p)
			ans+=c[t-*p];
		return ans;
	}
	~FindSumPairs(){for (int i=0;i<m;++i)c[a2[i]]=0;}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

