const int N=100005;
int c[N];
class Solution {
public:
	vector<int> distinctNumbers(vector<int>& _a, int k) {
		int n=_a.size(),*a=&_a[0],cnt=0;
		vector<int> ans(n-k+1);
		for (int *i=a,*end=a+k;i<end;++i)if (!c[*i]++)++cnt;
		ans[0]=cnt;
		for (int i=0;i<n-k;++i){
			if (!--c[a[i]])--cnt;
			if (!c[a[i+k]]++)++cnt;
			ans[i+1]=cnt;
		}
		for (int *i=a+n-k,*end=a+n;i<end;++i)c[*i]=0;
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

