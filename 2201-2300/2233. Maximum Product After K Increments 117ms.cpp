const int P=1000000007;
typedef long long ll;
inline int exp(int x,int y,int z){
	int ans=1;
	while (y){
		if (y&1)ans=(ll)ans*x%z;
		x=(ll)x*x%z;y>>=1;
	}
	return ans;
}
class Solution {
public:
	int maximumProduct(vector<int>& _a, int k) {
		int n=_a.size(),*a=&_a[0],l=0,r=n;
		while (k&&l<r){
			int mid=(l+r)/2;
			nth_element(a+l,a+mid,a+r);
			ll cnt=(ll)a[mid]*mid-(l?(ll)a[l-1]*l:0);
			for (int i=l;i<mid;++i)cnt-=a[i];
			if (cnt>k)r=mid;
			else k-=cnt,l=mid+1;
		}
		ll ans=l?(ll)exp(a[l-1]+k/l,l-k%l,P)*exp((a[l-1]+k/l+1),k%l,P)%P:1;
		for (int i=l;i<n;++i)ans=ans*a[i]%P;
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

