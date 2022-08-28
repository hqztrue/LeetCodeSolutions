typedef long long ll;
const int N=100005;
int l[N],r[N];
ll s[N];
class Solution {
public:
	vector<ll> maximumSegmentSum(vector<int>& _a, vector<int>& _q) {
		int n=_a.size(),*a=&_a[0],*q=&_q[0]; ll ans=0;
		vector<ll> res(n);
		for (int i=0;i<=n;++i)l[i]=r[i]=i,s[i]=0;
		for (int i=n-1;i>=0;--i){
			int x=q[i];
			s[l[x]]+=a[x]+s[x+1];
			res[i]=ans;
			ans=max(ans,s[l[x]]);
			r[l[x]]=r[x+1];
			l[r[x+1]]=l[x];
		}
		return res;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

