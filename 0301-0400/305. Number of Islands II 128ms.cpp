const int N=105,dir[]={-1,0,1,0,-1};
int f[N*N];
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
class Solution {
public:
	vector<int> numIslands2(int n, int m, vector<vector<int>>& positions) {
		vector<int> res; int cnt=0;
		memset(f,0x99,sizeof(int)*n*m);
		for (const auto &p:positions){
			int id=p[0]*m+p[1];
			if (f[id]>=0){res.push_back(cnt); continue;}
			f[id]=id; ++cnt; int r1=find(id);
			for (int i=0;i<4;++i){
				int x=p[0]+dir[i],y=p[1]+dir[i+1],id1=x*m+y;
				if (x<0||x>=n||y<0||y>=m||f[id1]<0)continue;
				int r2=find(id1);
				if (r1!=r2)f[r2]=r1,--cnt;
			}
			res.push_back(cnt);
		}
		return res;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

