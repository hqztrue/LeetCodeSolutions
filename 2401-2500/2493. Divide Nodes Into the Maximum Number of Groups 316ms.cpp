const int N=505,W=64,NL=3;
typedef unsigned long long ull;
void clear_mat(int *a,int n){memset(a,0,sizeof(int)*n*n); for (int i=0;i<n;++i)a[i*n+i]=1;}
void print_mat(int *a,int n){
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j)printf("%d%c",a[i*n+j],j==n-1?'\n':' ');
	puts("");
}
void bool_mat_mul1(int a[],int b[],int c[],int n){  //O(n^3/w)
	static bitset<N> A[N],B[N];
	for (int i=0;i<n;++i)A[i].reset(),B[i].reset();
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j)A[i][j]=a[i*n+j],B[i][j]=b[j*n+i];
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j)c[i*n+j]=(A[i]&B[j]).any();
}
void bool_mat_mul_bf(int a[],int b[],int c[],int n){
	memset(c,0,n*n*sizeof(int));
	for (int i=0;i<n;++i)
		for (int k=0;k<n;++k)if (a[i*n+k]){
			int *_b=b+k*n,*_c=c+i*n;
			for (int j=0;j<n;++j)_c[j]|=_b[j];
			//for (int *_b=b+k*n,*_c=c+i*n,*end=_b+n;_b!=end;*_c++|=*_b++);
		}
}
void bool_mat_mul_word(int a[],int b[],int c[],int n){  //n<=W, O(n^3/w)
	assert(n<=W);
	static ull A[N],B[N];
	memset(A,0,sizeof(ull)*n);
	memset(B,0,sizeof(ull)*n);
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j){
			A[i]|=(ull)a[i*n+j]<<j;
			B[j]|=(ull)b[i*n+j]<<i;
		}
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j)c[i*n+j]=(A[i]&B[j])>0;
}
void bool_mat_mul(int a[],int b[],int c[],int n){  //O(n^3/(w log n))
	if (n<=4){bool_mat_mul_bf(a,b,c,n); return;}
	if (n<=W){bool_mat_mul_word(a,b,c,n); return;}
	static ull f[N/W+1][N/NL][N/W+1],B[N/NL][N],ans[N][N/W+1];
	int L=max((int)floor(log2(max(n/W,1)))-1,3),n1=(n-1)/L+1,n2=(n-1)/W+1;
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
vector<int> v[N];
int a[10][N*N],b[N*N],c[N*N],ones[N*N],id[N],vis[N],q[N],col[N];
int diam(int n){
	if (n==1)return 0;
	int i1=0,ans=0,s=sizeof(int)*n*n;
	clear_mat(b,n);
	for (;(1<<(i1+1))<=n;++i1){
		bool_mat_mul(a[i1],a[i1],a[i1+1],n);
		if (!memcmp(a[i1+1],ones,s))break;
	}
	for (;i1>=0;--i1){
		bool_mat_mul(b,a[i1],c,n);
		if (memcmp(c,ones,s))memcpy(b,c,s),ans+=1<<i1;
	}
	return ans+1;
}
class Solution {
public:
	int magnificentSets(int n, vector<vector<int>>& edges) {
		int ans=0;
		for (int i=0;i<n;++i)vis[i]=0,v[i].clear();
		if (!ones[0])for (int i=0;i<N*N;++i)ones[i]=1;
		for (auto &e:edges){
			int x=e[0],y=e[1]; --x; --y;
			v[x].push_back(y); v[y].push_back(x);
		}
		for (int i=0;i<n;++i)
			if (!vis[i]){
				int h=0,t=0;
				vis[i]=1; q[0]=i; id[i]=t++; col[i]=0;
				while (h<t){
					int x=q[h++],c0=col[x];
					for (auto &y:v[x])
						if (!vis[y])vis[y]=1,q[t]=y,id[y]=t++,col[y]=1-c0;
						else if (col[y]==c0)return -1;
				}
				clear_mat(a[0],t);
				for (int j=0;j<t;++j){
					int x=q[j];
					for (auto &y:v[x]){
						int x1=id[x],y1=id[y];
						a[0][x1*t+y1]=a[0][y1*t+x1]=1;
					}
				}
				ans+=diam(t)+1;
			}
		return ans;
	}
};

