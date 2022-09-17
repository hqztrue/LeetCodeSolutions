const int U=100000,U1=318,U2=1005,M=17,inf=0x3f3f3f3f;
int v[U1],c[M+1],f[U2];
class Solution {
public:
	int minimumFinishTime(vector<vector<int>>& a, int t, int m) {
		int n=a.size();
		memset(v,0x3f,sizeof(v));
		memset(c,0x3f,sizeof(c));
		memset(f,0x3f,sizeof(f));
		for (auto &b:a){
			int f=b[0],r=b[1];
			if (r<U1)v[r]=min(v[r],f);
			else {
				c[1]=min(c[1],f);
				if (f<2*U1)c[2]=min(c[2],f*(r+1));
			}
		}
		for (int i=2;i<U1;++i)
			for (int j=1,k=v[i];k<=U*2;++j,k=k*i+v[i])c[j]=min(c[j],k);
		for (int i=1;i<=M;++i)c[i]+=t;
		f[0]=-t;
		for (int i=1;i<=m;++i)
			for (int j=1;j<=min(M,i);++j)
				f[i]=min(f[i],f[i-j]+c[j]);
		return f[m];
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();
