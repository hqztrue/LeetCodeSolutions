const int N=405,W=64,inf=~0u>>1;
bitset<N> c[N];
int d[N],_d[N],id[N],rid[N];
inline bool cmp(int x,int y){return d[x]<d[y];}
class Solution {
public:
	int minTrioDegree(int n, vector<vector<int>>& edges) {
		int ans=inf;
		for (int i=0;i<n;++i)d[i]=0,id[i]=i,c[i].reset();
		for (auto &e:edges){
			int x=--e[0],y=--e[1];
			++d[x]; ++d[y];
		}
		sort(id,id+n,cmp);
		for (int i=0;i<n;++i)rid[id[i]]=i,_d[i]=d[i];
		for (int i=0;i<n;++i)d[i]=_d[id[i]];
		for (auto &e:edges){
			int x=rid[e[0]],y=rid[e[1]]; if (x>y)swap(x,y);
			c[x].set(y,1);
		}
		for (int i=0;i<n-2;++i){
			if (d[i]*3>=ans)break;
			for (int j=i+1;j<n-1;++j)if (c[i][j]){
				if (d[i]+d[j]*2>=ans)break;
				int k=(c[i]&c[j])._Find_first();
				if (k<n)ans=min(ans,d[i]+d[j]+d[k]);
			}
		}
		return ans<inf?ans-6:-1;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

