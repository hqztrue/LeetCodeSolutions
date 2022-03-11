typedef long long ll;
const int N=100005;
int c[N],c0[N];
template<class T> vector<pair<T,int> > factor(T x){
	vector<pair<T,int> > res;
	for (T i=2;i*i<=x;++i)if (x%i==0){
		int cnt=0; while (x%i==0)x/=i,++cnt;
		res.push_back(make_pair(i,cnt));
	}
	if (x>1)res.push_back(make_pair(x,1));
	return res;
}
template<class T> vector<T> get_factors(T x){
	vector<pair<T,int> > p=factor(x); vector<T> a{1};
	for (int i=0;i<p.size();++i){
		int n=a.size(),t=p[i].second; T p0=p[i].first;
		for (T m=p0;t;--t,m*=p0)
			for (int j=0;j<n;++j)a.push_back(a[j]*m);
	}
	//sort(a.begin(),a.end());
	return a;
}
class Solution {
public:
	ll countPairs(vector<int>& _a, int k) {
		int *a=&_a[0],n=_a.size(),d1=0,m=*max_element(_a.begin(),_a.end()); ll ans=0;
		auto d=get_factors(k); d1=d.size();
		for (int i=0;i<n;++i)++c0[a[i]];
		for (int i=d1-1;i>=0;--i){
			c[i]=0;
			for (int j=d[i];j<=m;j+=d[i])c[i]+=c0[j],c0[j]=0;
		}
		for (int i=0;i<d1;++i){
			int t1=d[i],c1=c[i];
			if ((ll)t1*t1%k==0)ans+=(ll)c1*(c1-1)/2;
			for (int j=i+1;j<d1;++j){
				int t2=d[j],c2=c[j];
				if ((ll)t1*t2%k==0)ans+=(ll)c1*c2;
			}
		}
		//for (int i=0;i<n;++i)c0[a[i]]=0;
		memset(c0,0,sizeof(int)*(m+1));
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

