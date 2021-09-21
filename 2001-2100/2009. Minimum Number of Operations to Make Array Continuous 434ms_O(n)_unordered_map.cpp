const int N=100005;
vector<int> v[N];
unordered_map<int,vector<int>> b;
class Solution {
public:
	int minOperations(vector<int>& a) {
		int n=a.size(),ans=0; b.clear();
		for (int i=0;i<n;++i)v[i].clear();
		for (auto &x:a)v[x%n].push_back(x);
		for (int i=0;i<n;++i)
			for (auto &x:v[i]){
				auto &t=b[x/n];
				if (!t.size()||t.back()!=x)t.push_back(x);
			}
		for (auto &t:b){
			vector<int> &a=t.second,c=a;
			auto it=b.find(t.first+1);
			if (it!=b.end())
				for (auto &x:it->second)c.push_back(x);
			int m=c.size(),r=1;
			for (int l=0;l<a.size();++l){
				while (r<m&&c[r]-c[l]<=n-1)++r;
				ans=max(ans,r-l);
			}
		}
		return n-ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

