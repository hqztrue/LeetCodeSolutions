const int N=200005,inf=~0u>>1;
int s[N],s1[N],l,l1;
class Solution {
public:
	int minimumSubarrayLength(vector<int>& a, int k) {
		if (!k)return 1;
		int n=a.size(),ans=n+1;
		l=l1=0; s[0]=s1[0]=0;
		for (int i=0;i<n;++i){
			s1[l1+1]=s1[l1]|a[i]; ++l1;
			while ((s[l]|s1[l1])>=k){
				ans=min(ans,l+l1);
				if (!l){
					l=(l1+1)/2;
					for (int j=1;j<=l;++j)s[j]=s[j-1]|a[i-l1+l+1-j];
					l1-=l;
					for (int j=1;j<=l1;++j)s1[j]=s1[j-1]|a[i-l1+j];
				}
				--l;
			}
		}
		return ans==n+1?-1:ans;
	}
};
