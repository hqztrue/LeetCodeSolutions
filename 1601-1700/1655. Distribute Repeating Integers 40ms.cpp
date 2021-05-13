const int N=10,M=1005,M1=55,inf=~0u>>2,mask=(1<<17)-1;
int f[1<<N],c[M],v[M1];
class Solution {
public:
	bool canDistribute(vector<int>& _a, vector<int>& _q) {
		int n=_a.size(),m=_q.size(),*a=&_a[0],*q=&_q[0],v1=0;
		for (int i=0;i<n;++i)++c[a[i]];
		for (int i=0;i<M;++i)if (c[i])v[v1++]=c[i],c[i]=0;
		sort(v,v+v1,greater<int>());
		for (int i=v1;i<=m;++i)v[i]=0;
		for (int i=1;i<(1<<m);++i){
			f[i]=inf;
			for (int j=0;j<m;++j)
				if ((i&(1<<j))&&f[i-(1<<j)]<inf){
					int k=i-(1<<j),id=f[k]>>17,l=f[k]&mask,l1=q[j];
					if (l+l1<=v[id])f[i]=min(f[i],f[k]+l1);
					else if (l1<=v[id+1])f[i]=min(f[i],f[k]-l+(1<<17)+l1);
				}
		}
		return f[(1<<m)-1]<inf;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

