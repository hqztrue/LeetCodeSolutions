const int N=1005;
int f[N],s[N];
class Solution {
public:
	int maxJumps(vector<int>& a, int d) {
		a.push_back(~0u>>1);
		int n=a.size(),ans=1,s1=-1,s2;
		for (int i=0;i<n;++i){
			f[i]=1;
			while (s1>=0&&a[s[s1]]<a[i]){
				for (s2=s1-1;s2>=0&&a[s[s2]]==a[s[s1]];--s2);
				for (;s1>s2;--s1){
				 	int j=s[s1];
					if (i-j<=d)f[i]=max(f[i],f[j]+1);
					if (s2>=0&&j-s[s2]<=d)f[s[s2]]=max(f[s[s2]],f[j]+1);
				}
			}
			s[++s1]=i;
		}
		for (int i=0;i<n-1;++i)ans=max(ans,f[i]);
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

