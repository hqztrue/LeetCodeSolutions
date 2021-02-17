const int N=405,W=64,NL=2,S=256,inf=~0u>>1;
typedef unsigned long long ull;
void bool_mat_mul(int a[],int b[],int c[],int n){  //O(n^3/(w log n))
	static ull f[N/W+1][N/NL][N/W+1],B[N/NL][N],ans[N][N/W+1];
	int L=max((int)floor(log2(max(n/W,1))),1),n1=(n-1)/L+1,n2=(n-1)/W+1;
	for (int i=0;i<(1<<L);++i)
		for (int j=0;j<n1;++j)
			memset(f[i][j],0,sizeof(ull)*n2);
	for (int i=0;i<n;++i)memset(ans[i],0,sizeof(ull)*n2);
	for (int i=0;i<n1;++i)
		for (int j=0;j<n;++j){
			B[i][j]=0; int l=min(L,n-i*L);
			for (int k=0;k<l;++k)if (b[(i*L+k)*n+j])B[i][j]|=1ull<<k;
		}
	for (int I=0;I<(1<<L);++I)
		for (int i=0;i<n1;++i)
			for (int j=0;j<n;++j)
				if (I&B[i][j])f[I][i][j/W]|=1ull<<j%W;
	for (int i=0;i<n1;++i)
		for (int j=0;j<n;++j){
			ull x=0; int l=min(L,n-i*L);
			for (int k=0;k<l;++k)if (a[j*n+(i*L+k)])x|=1ull<<k;
			//for (int k=0;k<n2;++k)ans[j][k]|=f[x][i][k];
			ull *startA=ans[j],*startB=f[x][i],*endA=ans[j]+n2;
			while (startA!=endA)*startA++|=*startB++;
		}
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j)c[i*n+j]=(ans[i][j/W]&(1LL<<j%W))>0;
}
bitset<S> c[N][N/S+1];
int d[N],_d[N],id[N],rid[N],a[N*N],b[N*N],f[N*N],mark[N][N];
inline bool cmp(int x,int y){return d[x]<d[y];}
class Solution {
public:
	int minTrioDegree(int n, vector<vector<int>>& edges) {
		int ans=inf;
		for (int i=0;i<n;++i){
			d[i]=0,id[i]=i;
			for (int j=0;j<(n-1)/S+1;++j)c[i][j].reset();
		}
		for (auto &e:edges){
			int x=--e[0],y=--e[1];
			++d[x]; ++d[y];
		}
		sort(id,id+n,cmp);
		for (int i=0;i<n;++i)rid[id[i]]=i,_d[i]=d[i];
		for (int i=0;i<n;++i)d[i]=_d[id[i]];
		for (auto &e:edges){
			int x=rid[e[0]],y=rid[e[1]]; if (x>y)swap(x,y);
			c[x][y/S].set(y%S,1);
		}
		for (int i=0;i<n;++i)
			for (int j=0;j<n;++j)a[i*n+j]=b[i*n+j]=0,mark[i][j]=c[i][j/S][j%S];
		for (int I=0;I*S<n;++I){
			for (int i=0;i<n;++i)
				for (int j=0;j<S&&I*S+j<n;++j)a[i*n+I*S+j]=b[(I*S+j)*n+i]=c[i][I][j];
			bool_mat_mul(a,b,f,n);
			for (int i=0;i<n-2;++i)
				for (int j=i+1;j<n-1;++j)if (mark[i][j]&&f[i*n+j]){
					mark[i][j]=0;
					int k=(c[i][I]&c[j][I])._Find_first();
					ans=min(ans,d[i]+d[j]+d[I*S+k]);
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

