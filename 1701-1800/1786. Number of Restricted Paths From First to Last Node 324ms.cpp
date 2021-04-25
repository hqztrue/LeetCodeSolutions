typedef unsigned int uint;
const int N=20005,P=1000000007,inf=~0u>>1;
vector<pair<int,int> > e[N];
vector<int> seq;
int ans[N];
struct radix_heap{
	static const int W=32;
	vector<pair<uint,int> > c[W+1];
	int d[N],n; uint last;
	radix_heap():last(0){}
	int getbit(uint x){return x?32-__builtin_clz(x):0;}
	void push(uint k,int v){c[getbit(k^last)].emplace_back(k,v);}
	pair<uint,int> pop(){
		if (c[0].empty()){
			for (int i=1;i<=W;++i)
				if (!c[i].empty()){
					last=inf;
					for (auto &p:c[i])
						if (p.first<last&&p.first==d[p.second])last=p.first;
					if (last==inf){c[i].clear(); continue;}
					for (auto &p:c[i])
						if (p.first==d[p.second])c[getbit(p.first^last)].emplace_back(p);
					c[i].clear(); break;
				}
			if (c[0].empty())return make_pair(0,-1);
		}
		pair<uint,int> res=c[0].back(); c[0].pop_back();
		return res;
	}
	void SSSP(int S,int T=-1){
		for (int i=1;i<=n;++i)d[i]=inf; d[S]=0; push(0,S);
		while (1){
			auto [d0,x]=pop();
			if (x==-1||x==T)return;
			if (d0>d[x])continue;
			seq.push_back(x);
			for (auto &ed:e[x]){
				int y=ed.first,cost=ed.second;
				if (d0+cost<d[y])d[y]=d0+cost,push(d[y],y);
			}
		}
	}
};
class Solution {
public:
	int countRestrictedPaths(int n, vector<vector<int>>& edges) {
		radix_heap H; H.n=n;
		for (int i=1;i<=n;++i)e[i].clear();
		for (int i=1;i<=n;++i)ans[i]=0; ans[n]=1;
		for (auto ed:edges)e[ed[0]].emplace_back(ed[1],ed[2]),e[ed[1]].emplace_back(ed[0],ed[2]);
		seq.clear(); H.SSSP(n);
		for (int x:seq)
			for (auto &ed:e[x]){
				int y=ed.first;
				if (H.d[y]<H.d[x])ans[x]=(ans[x]+ans[y])%P;
			}
		return ans[1];
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

