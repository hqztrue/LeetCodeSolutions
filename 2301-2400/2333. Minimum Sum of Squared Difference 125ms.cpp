typedef long long ll;
const int N=100005;
int a[N];
inline ll sqr(int x){return (ll)x*x;}
class Solution {
public:
	long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
		int n=nums1.size(),k=k1+k2,l=0,r=n-1;
		for (int i=0,*a1=&nums1[0],*a2=&nums2[0];i<n;++i)a[i]=abs(a1[i]-a2[i]);
		ll s=0;
		while (l<r){
			int mid=(l+r)/2;
			nth_element(a+l,a+mid,a+r+1);
			ll s0=0;
			for (int i=mid+1;i<=r;++i)s0+=a[i];
			if (s+s0-(ll)a[mid]*(n-mid-1)<=k)s+=s0,r=mid;
			else l=mid+1;
		}
		k-=s-(ll)a[l]*(n-l-1);
		int m=n-l,d=k/m;
		ll ans=(m-k%m)*sqr(max(a[l]-d,0))+k%m*sqr(max(a[l]-d-1,0));
		for (int i=0;i<l;++i)ans+=sqr(a[i]);
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

