const int N=505,inf=~0u>>2;
struct SegTree{
	int v[N*4],M;
	void clear(int n){
		for (M=1;M-2<n;M<<=1);
		for (int i=0;i<=M*2;++i)v[i]=inf;
	}
	void modify(int x,int key){
		x+=M; v[x]=key;
		for (x>>=1;x;x>>=1)v[x]=min(v[x*2],v[x*2+1]);
	}
	int query(int l,int r){
		l+=M-1;r+=M+1;int ans=inf;
		for (;l^r^1;l>>=1,r>>=1){
			if (~l&1)ans=min(ans,v[l^1]);
			if (r&1)ans=min(ans,v[r^1]);
		}
		return ans;
	}
}up,down;
struct Info{
	int x,v;
};
vector<Info> info[N];
vector<int> row[N],col[N],tmp[N];
class Solution {
public:
	int orderOfLargestPlusSign(int n, vector<vector<int>>& a) {
		int m=a.size(),ans=0;
		up.clear(n); down.clear(n);
		for (int i=1;i<=n;++i)tmp[i].clear(),col[i].clear(),col[i].push_back(0);
		for (int i=0;i<m;++i)tmp[++a[i][0]].push_back(++a[i][1]);
		for (int i=1;i<=n;++i)
			for (int x:tmp[i])
				col[x].push_back(i);
		for (int i=1;i<=n;++i)tmp[i].clear(),row[i].clear(),row[i].push_back(0);
		for (int i=0;i<m;++i)tmp[a[i][1]].push_back(a[i][0]);
		for (int i=1;i<=n;++i)
			for (int x:tmp[i])
				row[x].push_back(i);
		
		for (int i=1;i<=n;++i)info[i].clear(),row[i].push_back(n+1),col[i].push_back(n+1);
		for (int i=1;i<=n;++i){
			for (int j=1;j<col[i].size();++j){
				int u=col[i][j-1]+1,v=col[i][j]-1,mid=(u+v)/2;
				if (u>v)continue;
				info[u].push_back({i,u});
				info[mid+1].push_back({i,inf});
				info[mid+1].push_back({i,-v});
				info[v+1].push_back({i,inf});
			}
		}
		
		for (int i=1;i<=n;++i){
			for (auto &t:info[i])
				if (t.v>0)up.modify(t.x,t.v);
				else down.modify(t.x,t.v);
			for (int j=1;j<row[i].size();++j){
				int u=row[i][j-1]+1,v=row[i][j]-1;
				while ((v-u+2)/2>ans){
					int l=u+ans,r=v-ans,res=max(i-up.query(l,r),-down.query(l,r)-i)+1;
					if (res>ans)++ans;
					else break;
				}
			}
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

