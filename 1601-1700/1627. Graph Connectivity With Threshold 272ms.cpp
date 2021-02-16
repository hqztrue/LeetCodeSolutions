const int N=10005;
int f[N],p[N],fa[N],_fa[N],p1;
int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
class Solution {
public:
	vector<bool> ans;
	vector<bool>& areConnected(int n, int t, vector<vector<int>>& q) {
		if (t==0){ans.assign(q.size(),1); return ans;}
		memcpy(fa+1,_fa+1,sizeof(int)*n);
		for (int i=t+1,end=n/2;i<=end;++i){
			int f1=find(i);
			for (int *j=p+1;;++j){
				int k=i*(*j);
				if (k>n)break;
				//int f2=find(k);
				//if (f1!=f2)
				fa[find(k)]=f1;
			}
		}
		for (int i=1;i<=n;++i)find(i);
		for (vector<int> &_q:q)
			ans.emplace_back(fa[_q[0]]==fa[_q[1]]);
		return ans;
	}
};

//IO
int _IO=[](){
	int n=10000;
	//memset(f+1,0,sizeof(int)*n); p1=0;
	for (int i=2;i<=n;++i){
		if (!f[i])f[i]=p[++p1]=i;
		for (int j=1;j<=p1&&p[j]<=f[i]&&i*p[j]<=n;++j)f[i*p[j]]=p[j];
	}
	for (int i=1;i<=n;++i)_fa[i]=i;
	p[++p1]=N;
	
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

