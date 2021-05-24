const int N=100005,P=1000000007;
int c[N];
class Solution {
public:
	int sumOfFlooredPairs(vector<int>& _a) {
		int n=_a.size(),*a=&_a[0],m=*max_element(a,a+n),ans=0;
		memset(c,0,sizeof(int)*(m+2));
		for (int i=0;i<n;++i)++c[a[i]];
		for (int i=m;i;--i)c[i]+=c[i+1];
		for (int i=1;i<=m;++i)
			if (c[i]>c[i+1]){
				long s=0;
				for (int j=i;j<=m;j+=i)s+=c[j];
				ans=(ans+s*(c[i]-c[i+1]))%P;
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

