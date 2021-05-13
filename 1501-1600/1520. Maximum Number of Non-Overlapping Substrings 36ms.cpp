const int N=100005,CH=26;
int a[N],f[N],r[N],nxt[N],h[CH],g[CH]; char s[N];
class Solution {
public:
	vector<string> ans;
	const vector<string>& maxNumOfSubstrings(const string &str) {
		int n=str.size(),a1=-1; f[0]=0; nxt[0]=0;
		memset(h,0,sizeof(h)); memset(g,0,sizeof(g));
		for (int i=n;i;--i){
			char &c=s[i]; c=str[i-1]-'a';
			if (!g[c])g[c]=i;
		}
		for (int i=1;i<=n;++i){
			char c=s[i];
			if (!h[c])h[c]=i,a[++a1]=i,r[a1]=g[c];
			else while (h[c]<a[a1])r[a1-1]=max(r[a1-1],r[a1]),--a1;
			f[i]=f[i-1]; nxt[i]=-1;
			if (r[a1]==i&&f[a[a1]-1]+1>f[i])f[i]=f[a[a1]-1]+1,nxt[i]=a[a1]-1;
		}
		ans.clear(); int cur=n;
		while (1){
			while (nxt[cur]==-1)--cur;
			if (!cur)break;
			string s1;
			for (int i=nxt[cur]+1;i<=cur;++i)s1.push_back(s[i]+'a');
			ans.push_back(s1); --cur;
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

