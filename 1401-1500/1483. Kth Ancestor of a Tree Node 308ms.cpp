const int N=50005,L=16,M=12;
int ch[N],sta[N],d[N],h[N],sz[N],nxt[N],mark[N],stk[N],chain[N*2],c1[N],id[N],msk[N],
	g[N],kth[1<<M][M],_fa[N/M][L],*fa[N],*p,D,len,fa1,id1,_id1;
void pre(){
	for (int i=1;i<(1<<M);++i){
		kth[i][0]=__builtin_ctz(i);
		for (int j=1;j<M;++j)kth[i][j]=kth[i-(i&-i)][j-1];
	}
}
class TreeAncestor {
public:
	void dfs1(int x){
		id[id1++]=x; g[x]=_id1;
		for (int i=sta[x];i<sta[x+1];++i){
			int y=ch[i]; msk[y]=msk[x]|(1<<id1-_id1); dfs1(y);
		}
	}
	void dfs(int x){
		d[x]=D; stk[D++]=x; sz[x]=1; h[x]=0; nxt[x]=mark[x]=-1; bool flag=1;
		for (int i=sta[x];i<sta[x+1];++i){
			int y=ch[i]; dfs(y);
			sz[x]+=sz[y];
			if (sz[y]>M)flag=0,mark[x]=mark[y];
			if (h[y]>h[x])h[x]=h[y],nxt[x]=y;
		}
		--D; ++h[x];
		if (sz[x]<=M)flag=0;
		if (flag){
			mark[x]=x; fa[x]=_fa[fa1++];
			for (int i=0;i<L&&(1<<i)<=D;++i)fa[x][i]=stk[D-(1<<i)];
		}
		for (int i=sta[x];i<sta[x+1];++i){
			int y=ch[i];
			if (mark[x]!=-1&&sz[y]<=M)_id1=id1,msk[y]=1,dfs1(y);
			if (y!=nxt[x]){
				len+=h[y];
				for (int z=y;z!=-1;z=nxt[z])chain[c1[z]=--len]=z;
				len+=h[y];
				for (int end=len+h[y],z=x;z!=-1&&len<end;z=p[z])chain[len++]=z;
			}
		}
	}
	TreeAncestor(int n, vector<int>& _p) {
		p=&_p[0];
		if (!kth[2][1])pre();
		memset(sta,0,sizeof(int)*n);
		for (int i=1;i<n;++i)++sta[p[i]];
		for (int i=0,s=0,t;i<n;++i)t=sta[i],sta[i]=s,s+=t;
		for (int i=1;i<n;++i)ch[sta[p[i]]++]=i;
		for (int i=n;i;--i)sta[i]=sta[i-1]; sta[0]=0;
		D=len=fa1=id1=0; dfs(0); len+=h[0];
		for (int z=0;z!=-1;z=nxt[z])chain[c1[z]=--len]=z; len+=h[0];
		if (sz[0]<=M)_id1=id1,msk[0]=1,dfs1(0);
	}
	int getKthAncestor(int x, int k) {
		k=d[x]-k; if (k<0)return -1;
		if (mark[x]==-1){
			int y=id[g[x]];
			if (k<d[y])x=p[y];
			else return id[g[x]+kth[msk[x]][k-d[y]]];
		}
		x=mark[x];
		if (d[x]==k)return x;
		int l=31-__builtin_clz(d[x]-k); x=fa[x][l];
		return chain[c1[x]+d[x]-k];
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();


