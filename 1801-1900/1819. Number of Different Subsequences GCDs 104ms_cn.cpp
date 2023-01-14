const int N=200005;
bool v[N];
class Solution {
public:
	int countDifferentSubsequenceGCDs(vector<int>& a) {
		int ans=0,m=0,m1;
		for (auto &i:a)if (!v[i])v[i]=1,m=max(m,i),++ans; m1=m/3;
		for (int i=1;i<=m1;++i)if (!v[i]){
			int g=0;
			for (int j=i+i;j<=m;j+=i)
				if (v[j]){
					g=gcd(g,j);
					if (g==i){++ans; break;}
				}
		}
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
