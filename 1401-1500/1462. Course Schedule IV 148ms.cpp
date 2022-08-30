const int N=105,W=64,NL=3;
typedef unsigned long long ull;
struct Edge{
	#define Mx 10005
	int link[Mx],next[Mx],son[Mx],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
	}
}e;
int f[N],f1[N],in[N];
void toposort(int n){
	int h=0,t=0;
	for (int i=0;i<n;++i)in[i]=0;
	for (int i=0;i<n;++i)
		for (int p=e.son[i];p;p=e.next[p])++in[e.link[p]];
	for (int i=0;i<n;++i)if (!in[i])f[t++]=i;
	while (h<t){
		int i=f[h++];
		for (int p=e.son[i];p;p=e.next[p]){
			int j=e.link[p]; --in[j];
			if (!in[j])f[t++]=j;
		}
	}
	for (int i=0;i<n;++i)f1[f[i]]=i;
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
	int L=max((int)floor(log2(max(n/W,1)))-1,1),n1=(n-1)/L+1,n2=(n-1)/W+1;
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
void transitive_closure(int a[],int l,int r,int n){
	static int b[N*N],c[N*N],d[N*N];
	if (l+1==r)return;
	int mid=(l+r+1)/2,n1=mid-l,n2=r-mid;
	transitive_closure(a,l,mid,n);
	transitive_closure(a,mid,r,n);
	for (int i=0;i<n1;++i)
		for (int j=0;j<n1;++j)b[i*n1+j]=a[(l+i)*n+(l+j)];
	for (int i=0;i<n1;++i){
		for (int j=0;j<n2;++j)c[i*n1+j]=a[(l+i)*n+(mid+j)];
		if (n1>n2)c[i*n1+n2]=0;
	}
	bool_mat_mul_word(b,c,d,n1);  //bool_mat_mul
	for (int i=0;i<n2;++i)
		for (int j=0;j<n2;++j)c[i*n1+j]=a[(mid+i)*n+(mid+j)];
	if (n1>n2){
		for (int i=0;i<n2;++i)c[i*n1+n2]=0;
		for (int i=0;i<n1;++i)c[n2*n1+i]=0;
	}
	bool_mat_mul_word(d,c,b,n1);
	for (int i=0;i<n1;++i)
		for (int j=0;j<n2;++j)a[(l+i)*n+(mid+j)]=b[i*n1+j];
}
int a[N*N];
class Solution {
public:
	vector<bool> checkIfPrerequisite(int n, vector<vector<int>>& edges, vector<vector<int>>& q) {
		int m=edges.size(),qnum=q.size();
		vector<bool> ans(qnum);
		for (int i=0;i<n;++i)memset(a,0,sizeof(int)*n*n);
		e.clear();
		for (int i=0;i<m;++i)e.addedge(edges[i][0],edges[i][1]);
		toposort(n);
		for (int i=0;i<n;++i)a[i*n+i]=1;
		for (int i=0;i<n;++i)
			for (int p=e.son[i];p;p=e.next[p]){
				int j=e.link[p];
				a[f1[i]*n+f1[j]]=1;
			}
		transitive_closure(a,0,n,n);
		for (int i=0;i<qnum;++i)
			ans[i]=a[f1[q[i][0]]*n+f1[q[i][1]]];
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

