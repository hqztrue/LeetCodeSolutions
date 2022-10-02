const int N=100005;
int s[N],s1[N];
class Solution {
public:
	vector<int> smallestSubarrays(vector<int>& _a) {
		int n=_a.size(),*a=&_a[0],l=0,l1=0;
		vector<int> ans(n);
		for (int i=n-1;i>=0;--i){
			s1[l1+1]=s1[l1]|a[i]; ++l1;
			while (1){
				if (!l){
					l=(l1+1)/2; l1-=l;
					for (int j=1;j<=l;++j)s[j]=s[j-1]|a[i+l1-1+j];
					for (int j=1;j<=l1;++j)s1[j]=s1[j-1]|a[i+l1-j];
				}
				if ((s[l]|s1[l1])!=(s[l-1]|s1[l1])||!l1)break;
				--l;
			}
			ans[i]=l+l1;
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
