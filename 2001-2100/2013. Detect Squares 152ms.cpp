/***************************************************
Author: hqztrue
https://github.com/hqztrue/LeetCodeSolutions
Complexity: O(n^{2/3}) per operation
If you find this solution helpful, plz give a star:)
***************************************************/
const int N=5005,M=1005;
int c[M][M],t[M][M],pre[M][M],x[N],y[N],p1;
vector<int> vx[M],vy[M];
vector<vector<int>> q;
class DetectSquares {
public:
	DetectSquares() {
		p1=1; q.clear();
		for (int i=0;i<M;++i)vx[i].clear(),vy[i].clear();
	}
	void add(const vector<int> &p) {
		int x0=p[0],y0=p[1];
		x[p1]=x0; y[p1++]=y0;
		if (++c[x0][y0]==1)vx[x0].push_back(y0),vy[y0].push_back(x0);
	}
	int count(const vector<int> &p) {
		int x0=p[0],y0=p[1],S=(int)pow(p1,2./3)*2+1,ans=0,
			s1=vx[x0].size(),s2=vy[y0].size(),&t0=t[x0][y0];
		q.push_back(p);
		if (s1<=s2&&(s1<=S||p1-t0>S)){
			for (int y1:vx[x0]){
				int x1=x0-y1+y0,_c=c[x0][y1];
				if (x1>=0&&x1<M)ans+=_c*c[x1][y0]*c[x1][y1];
				x1=x0+y1-y0;
				if (x1>=0&&x1<M)ans+=_c*c[x1][y0]*c[x1][y1];
			}
			ans-=2*c[x0][y0]*c[x0][y0]*c[x0][y0];
		}
		else if (s1>s2&&(s2<=S||p1-t0>S)){
			for (int x1:vy[y0]){
				int y1=y0-x1+x0,_c=c[x1][y0];
				if (y1>=0&&y1<M)ans+=c[x0][y1]*_c*c[x1][y1];
				y1=y0+x1-x0;
				if (y1>=0&&y1<M)ans+=c[x0][y1]*_c*c[x1][y1];
			}
			ans-=2*c[x0][y0]*c[x0][y0]*c[x0][y0];
		}
		else {
			ans=pre[x0][y0];
			for (int i=t0+1;i<p1;++i)--c[x[i]][y[i]];
			for (int i=t0+1;i<p1;++i){
				int X=x[i],Y=y[i]; ++c[X][Y];
				if (X==x0&&Y==y0)continue;
				if (X==x0){
					int y1=Y,x1=x0-y1+y0;
					if (x1>=0&&x1<M)ans+=c[x1][y0]*c[x1][y1];
					x1=x0+y1-y0;
					if (x1>=0&&x1<M)ans+=c[x1][y0]*c[x1][y1];
				}
				if (Y==y0){
					int x1=X,y1=y0-x1+x0;
					if (y1>=0&&y1<M)ans+=c[x0][y1]*c[x1][y1];
					y1=y0+x1-x0;
					if (y1>=0&&y1<M)ans+=c[x0][y1]*c[x1][y1];
				}
				if (X-Y==x0-y0||X+Y==x0+y0)ans+=c[x0][Y]*c[X][y0];
			}
		}
		t0=p1-1; pre[x0][y0]=ans;
		return ans;
	}
	~DetectSquares(){
		for (int i=1;i<p1;++i)c[x[i]][y[i]]=0;
		for (auto &p:q)t[p[0]][p[1]]=pre[p[0]][p[1]]=0;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

