const int N=200005;
bool v[N];
class Solution {
public:
	int countDifferentSubsequenceGCDs(vector<int>& a) {
		int ans=0,m=0,m1;
		for (auto &i:a)v[i]=1,m=max(m,i); m1=m/2;
		for (int i=1;i<=m1;++i){
			int g=0;
			for (int j=i;j<=m;j+=i)
				if (v[j]){
					g=__gcd(g,j);
					if (g==i){++ans; break;}
				}
		}
		for (int i=m1+1;i<=m;++i)ans+=v[i];
		for (auto &i:a)v[i]=0;
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

