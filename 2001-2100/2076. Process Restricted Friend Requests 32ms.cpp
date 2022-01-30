const int N=1005;
int f[N],c[N*N],e[N];
vector<int*> d[N];
int find(int x){
	if (f[x]==x)return x;
	return f[x]=find(f[x]);
}
inline int h(int x,int y){return x<y?x*N+y:y*N+x;}
class Solution {
public:
	vector<bool> friendRequests(int n, vector<vector<int>>& a, vector<vector<int>>& q) {
		int m=q.size();
		vector<bool> ans(m);
		for (int i=0;i<n;++i)f[i]=i,d[i].clear();
		for (int i=0;i<a.size();++i){
			int x=a[i][0],y=a[i][1];
			e[i]=x^y;
			d[x].push_back(e+i);
			d[y].push_back(e+i);
			int h0=h(x,y); c[h0]=1;
		}
		for (int i=0;i<m;++i){
			int x=find(q[i][0]),y=find(q[i][1]);
			if (x==y){ans[i]=1; continue;}
			if (!c[h(x,y)]){
				if (d[x].size()>d[y].size())swap(x,y);
				for (auto t:d[x]){
					int y0=*t^x,h0=h(y,y0);
					c[h(x,y0)]=0; *t=y^y0; c[h0]=1;
					d[y].push_back(t);
				}
				f[x]=y; ans[i]=1;
			}
			else ans[i]=0;
		}
		for (int i=0;i<n;++i)
			if (find(i)==i)
				for (auto t:d[i])c[h(i,*t^i)]=0;
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

