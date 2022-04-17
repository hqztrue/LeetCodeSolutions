typedef long long ll;
const int N=100005;
ll a[N];
class Solution {
public:
	int halveArray(vector<int>& b) {
		int n=b.size(),l=0,ans=0; ll s=0;
		for (int i=0;i<n;++i)a[i]=(ll)b[i]<<18,s+=a[i];
		ll s1=s/2;
		while (s>s1){
			int mid=(l+n)/2,cnt=0;
			nth_element(a+l,a+mid,a+n);
			ll v=a[mid],_s=s;
			for (int i=mid;i<n;++i){
				int t=64-__builtin_clzll(a[i]/v);
				cnt+=t; s-=a[i]-(a[i]>>t);
			}
			if (s>=s1){
				ans+=cnt;
				for (int i=mid;i<n;++i)
					while (a[i]>=v)a[i]/=2;
			}
			else {
				s=_s;
				if (l==n-1)s-=a[l],a[l]/=2,s+=a[l],++ans;
				l=mid;
			}
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

