const int N=100005;
int c[N];
class Solution {
public:
	vector<int> findOriginalArray(vector<int>& a) {
		vector<int> res;
		for (auto &x:a)++c[x];
		int m=a.size()<50000?*max_element(a.begin(),a.end())/2:50000;
		if (c[0]%2){
			for (auto &x:a)c[x]=0;
			return {};
		}
		for (int i=0;i<c[0]/2;++i)res.push_back(0);
		for (int i=1;i<=m;++i)
			if (c[i]){
				if ((c[i*2]-=c[i])<0){
					c[i*2]=0;
					for (auto &x:a)c[x]=0;
					return {};
				}
				while (c[i]--)res.push_back(i);
			}
		int t=accumulate(c+m+1,c+(m+1)*2,0);
		for (auto &x:a)c[x]=0;
		return t?vector<int>():res;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

