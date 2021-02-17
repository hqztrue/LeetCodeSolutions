const int N=55,P=1000000007,mul=173;
typedef long long ll;
size_t get_hash(vector<int> &v){
	static size_t P=1000000007,M=173;
	int n=v.size(); size_t res=0;
	/*unordered_set<int> S;
	for (int i=0;i<n;++i)S.insert(v[i]);
	for (int i=0;i<S.bucket_count();++i){
		vector<int> u(S.begin(i),S.end(i)); sort(u.begin(),u.end());
		for (int j=0;j<u.size();++j)res=((long long)res*M+u[j])%P;
	}*/
	sort(v.begin(),v.end());
	for (int j=0;j<v.size();++j)res=((long long)res*M+v[j])%P;
	return ((long long)res*M+n)%P;
}
struct point{
	int x,y;
}q[N*N];
int pw[N*N];
class Solution {
public:
	int numDistinctIslands2(vector<vector<int>>& grid) {
		int n=grid.size(),m=grid[0].size(),ans=0;
		unordered_set<int> S;
		for (int i=0;i<n;++i)
			for (int j=0;j<m;++j)
				if (grid[i][j]){
					int h=0,t=1,xmin=i,xmax=i,ymin=j,ymax=j;
					q[0].x=i; q[0].y=j; grid[i][j]=0;
					while (h<t){
						point &p=q[h++]; int i=p.x,j=p.y;
						if (i+1<n&&grid[i+1][j]){
							q[t].x=i+1; q[t++].y=j;
							grid[i+1][j]=0; if (i+1>xmax)xmax=i+1;
						}
						if (i-1>=0&&grid[i-1][j]){
							q[t].x=i-1; q[t++].y=j;
							grid[i-1][j]=0; if (i-1<xmin)xmin=i-1;
						}
						if (j+1<m&&grid[i][j+1]){
							q[t].x=i; q[t++].y=j+1;
							grid[i][j+1]=0; if (j+1>ymax)ymax=j+1;
						}
						if (j-1>=0&&grid[i][j-1]){
							q[t].x=i; q[t++].y=j-1;
							grid[i][j-1]=0; if (j-1<ymin)ymin=j-1;
						}
					}
					for (int k=0;k<t;++k)q[k].x-=xmin,q[k].y-=ymin;
					int W=xmax-xmin+1,H=ymax-ymin+1,tmp,h1=1;
					//vector<int> v;
					for (int I=0;I<=1;++I){
						for (int J=0;J<4;++J){
							int h=0;
							for (int k=0;k<t;++k)h=(h+pw[q[k].x*H+q[k].y])%P;
							h=((ll)h*mul+W)%P; h=((ll)h*mul+H)%P;
							h1=(ll)h1*h; //v.push_back(h);
							if (J<4){
								for (int k=0;k<t;++k)tmp=W-1-q[k].x,q[k].x=q[k].y,q[k].y=tmp;
								swap(W,H);
							}
						}
						if (!I)for (int k=0;k<t;++k)q[k].x=W-1-q[k].x;
					}
					//h1=get_hash(v);
					if (S.find(h1)==S.end())S.insert(h1),++ans;
				}
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	for (int i=0,j=1;i<N*N;++i)
		pw[i]=j,j=(ll)j*mul%P;
	return 0;
}();

