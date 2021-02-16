const int N=100005,inf=~0u>>1;
int s[N],s1[N],l,l1;
class Solution {
public:
	int closestToTarget(vector<int>& a, int t) {
		int n=a.size(),ans=inf;
		l=l1=0; s[0]=s1[0]=inf;
		for (int i=0;i<n;++i){
			s1[l1+1]=s1[l1]&a[i]; ++l1;
			while ((s[l]&s1[l1])<t){
				if (!l){
					l=(l1+1)/2;
					for (int j=1;j<=l;++j)s[j]=s[j-1]&a[i-l1+l+1-j];
					l1-=l;
					for (int j=1;j<=l1;++j)s1[j]=s1[j-1]&a[i-l1+j];
				}
				--l;
			}
			ans=min(ans,(s[l]&s1[l1])-t);
			if (i>=l+l1)ans=min(ans,t-(s[l]&s1[l1]&a[i-l-l1]));
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

