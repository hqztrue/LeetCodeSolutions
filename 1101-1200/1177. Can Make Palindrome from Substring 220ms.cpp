const int N=100005;
int c[N];
vector<bool> res;
class Solution {
public:
	const vector<bool>& canMakePaliQueries(const string &_s, vector<vector<int>>& q) {
		const char *s=&_s[0]; int n=_s.size(),m=q.size(); res.resize(m);
		for (int i=0;i<n;++i)c[i+1]=c[i]^(1<<s[i]-'a');
		vector<int> *_q=&q[0];
		for (int i=0;i<m;++i){
			auto &t=_q[i];
			res[i]=t[2]>=__builtin_popcount(c[t[1]+1]^c[t[0]])/2;
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

