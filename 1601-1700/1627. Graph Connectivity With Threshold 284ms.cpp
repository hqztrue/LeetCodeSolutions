const int N=10005;
int f[N],g[N],p[N],v[N],p1,s,t,n;
void dfs(int x){
	v[x]=s;
	//if (x>=(t+1)*2)
	for (int j=x;j>1;j=g[j]){
		int k=x/f[j];
		if (k<=t)break;
		if (!v[k])dfs(k);
	}
	if (x>t)
	for (int j=1;j<=p1;++j){
		int k=x*p[j];
		if (k>n)break;
		if (!v[k])dfs(k);
	}
}
class Solution {
public:
	vector<bool> ans;
	vector<bool>& areConnected(int n, int t, vector<vector<int>>& q) {
		if (t==0){ans.assign(q.size(),1); return ans;}
		memset(v+1,0,sizeof(int)*n); s=0; ::n=n; ::t=t;
		for (int i=1;i<=n;++i)
			if (!v[i])++s,dfs(i);
		for (vector<int> &_q:q)
			ans.emplace_back(v[_q[0]]==v[_q[1]]);
		return ans;
	}
};

//IO
int _IO=[](){
	int n=10000;
	memset(f+1,0,sizeof(int)*n); p1=0;
	for (int i=2;i<=n;++i){
		if (!f[i])f[i]=p[++p1]=i;
		for (int j=1;j<=p1&&p[j]<=f[i]&&i*p[j]<=n;++j)f[i*p[j]]=p[j],g[i*p[j]]=i;
	}
	
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();


