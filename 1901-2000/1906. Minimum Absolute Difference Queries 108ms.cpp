const int N=100015,U=100,L=10,D=14;
inline int gap(__int128 x){
	int s=1; __int128 y=x;
	if (y&x>>1)goto l1;else x|=x>>1,s+=1;
	if (y&x>>2)goto l2;else x|=x>>2,s+=2;
	if (y&x>>4)goto l3;else x|=x>>4,s+=4;
	if (y&x>>8)goto l4;else x|=x>>8,s+=8;
	if (y&x>>16)goto l5;else x|=x>>16,s+=16;
	if (y&x>>32)goto l6;else x|=x>>32,s+=32;
	if (!(y&x>>32))x|=x>>32,s+=32;
	l6:if (!(y&x>>16))x|=x>>16,s+=16;
	l5:if (!(y&x>>8))x|=x>>8,s+=8;
	l4:if (!(y&x>>4))x|=x>>4,s+=4;
	l3:if (!(y&x>>2))x|=x>>2,s+=2;
	l2:if (!(y&x>>1))x|=x>>1,s+=1;
	l1:return s;
}
__int128 f[D][N/L+1],c[N],c1[N];
int M[N/L],*a;
inline __int128 Q_ST(int x,int y){
	if (x>y)return 0;
	int z=M[y-x+1]; __int128 *f0=f[z];
	return f0[x]|f0[y-(1<<z)+1];
}
inline __int128 Q(int x,int y){
	int xx=x/L,yy=y/L; __int128 t=Q_ST(xx+1,yy-1);
	if (xx<yy)t|=c1[x]|c[y];
	else for (int i=x;i<=y;++i)t|=(__int128)1<<a[i];
	return t;
}
class Solution {
public:
	vector<int> minDifference(vector<int>& _a, vector<vector<int>>& q) {
		int n=_a.size(),m=q.size(); vector<int> ans(m);
		n=(n+L-1)/L*L; _a.resize(n); a=&_a[0];
		for (int i=0;i<n/L;++i){
			c[i*L]=(__int128)1<<a[i*L];
			for (int j=i*L+1;j<(i+1)*L;++j)c[j]=c[j-1]|(__int128)1<<a[j];
			c1[i*L+L-1]=(__int128)1<<a[i*L+L-1];
			for (int j=i*L+L-2;j>=i*L;--j)c1[j]=c1[j+1]|(__int128)1<<a[j];
		}
		int nn=n/L,d=(int)log2(max(nn,1));
		for (int i=0;i<nn;++i)f[0][i]=c1[i*L];
		for (int j=1;j<=d;++j){
			__int128 *f0=f[j-1],*f1=f[j]; int j1=1<<(j-1);
			for (int i=0;i<nn-(1<<j);++i)f1[i]=f0[i]|f0[i+j1];
		}
		for (int i=0;i<m;++i){
			__int128 t=Q(q[i][0],q[i][1]); int v=gap(t);
			ans[i]=v>100?-1:v;
		}
		return ans;
	}
};

//IO
int _IO=[](){
	M[0]=-1; for (int i=1;i<N/L;++i)M[i]=!(i&(i-1))?M[i-1]+1:M[i-1];
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

