typedef long long ll;
class Solution {
public:
	ll kSum(vector<int>& nums, int k) {
		int n=nums.size(),m=min(k,n),*a=&nums[0];
		ll s=0;
		for (int &x:nums)
			if (x>0)s+=x;
			else x=-x;
		nth_element(a,a+m,a+n);
		sort(a,a+m);
		priority_queue<pair<ll,int>> Q;
		Q.emplace(s,-1);
		for (int T=1;T<k;++T){
			auto [s,i]=Q.top();
			Q.pop();
			if (i+1<m){
				Q.emplace(s-a[i+1],i+1);
				if (i>=0)Q.emplace(s+a[i]-a[i+1],i+1);
			}
		}
		return Q.top().first;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

