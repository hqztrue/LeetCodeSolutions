typedef long long ll;
const int N=10005;
int _s[N],*s=_s+1,q[N];
inline bool cmp(int i,int j,int k){return (ll)(s[j]-s[i-1])*(k-i+1)<=(ll)(s[k]-s[i-1])*(j-i+1);}
class Solution {
public:
	double findMaxAverage(vector<int>& a, int k) {
		int n=a.size(),h=0,t=-1; double ans=-1e9;
		for (int i=0;i<n;++i)s[i]=s[i-1]+a[i];
		for (int i=k-1;i<n;++i){
			while (h<t&&cmp(q[t-1],i-k,q[t]-1))--t;
			q[++t]=i-k+1;
			while (h<t&&cmp(q[h],q[h+1]-1,i))++h;
			ans=max(ans,double(s[i]-s[q[h]-1])/(i-q[h]+1));
		}
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();


