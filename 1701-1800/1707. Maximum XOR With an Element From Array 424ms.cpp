typedef unsigned int uint;
const int N=1000005,u=3,U=1<<u,L=30/u;
struct node{
	node* c[U];
	int min; uint w;
}p[N],*root=p;
int g[U][U][1<<U],p1;
void init(){
	for (int i=0;i<(1<<U);++i)
		for (int j=0;j<U;++j){
			int ma=-1,t=-1;
			for (int k=0;k<U;++k){
				if ((i&(1<<k))&&(j^k)>ma)ma=j^k,t=k;
				g[j][k][i]=t;
			}
		}
}
class Solution {
public:
	vector<int> maximizeXor(vector<int>& a, vector<vector<int>>& q) {
		int n=a.size(),m=q.size(),mi=1<<30; vector<int> ans(m);
		root->w=0; p1=0;
		for (int i=0;i<n;++i){
			node *x=root; int y=a[i];
			if (y<mi)mi=y;
			for (int j=L-1;j>=0;--j){
				int t=(y>>j*u)&(U-1);
				if (x->w&(1<<t)){
					x=x->c[t];
					int &z=x->min; if (y<z)z=y;
				}
				else {
					x->w|=1<<t;
					x=x->c[t]=p+(++p1);
					x->w=0; x->min=y;
				}
			}
		}
		for (int i=0;i<m;++i){
			node *x=root; int y=q[i][0],b=q[i][1],j;
			if (b<mi){ans[i]=-1; continue;}
			for (j=L-1;j>=0;--j){
				int t=(y>>j*u)&(U-1);
				int r=(b>>j*u)&(U-1),h=g[t][r][x->w];
				if (h<r){x=x->c[h]; break;}
				else if (x->c[h]->min>b){x=x->c[g[t][r][x->w-(1<<r)]]; break;}
				x=x->c[h];
			}
			for (--j;j>=0;--j)x=x->c[g[(y>>j*u)&(U-1)][U-1][x->w]];
			ans[i]=x->min^y;
		}
		return ans;
	}
};

//IO
int _IO=[](){
	init();
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

