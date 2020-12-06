const int N=100005,W=32,inf=~0u>>2;
int b[N];
class Solution {
public:
	int minimumDeviation(vector<int>& a) {
		int n=a.size(),ma=0,mi=inf;
		int vmin[W+1],vmax[W+1],can[W+1];
		for (int i=0;i<=W;++i)vmin[i]=inf,vmax[i]=0,can[i]=1;
        for (int i=0;i<n;++i)b[i]=a[i]&1?a[i]*2:a[i];
		for (int i=0;i<n;++i)a[i]>>=__builtin_ctz(a[i]),ma=max(ma,a[i]);
		int c=__builtin_clz(ma);
		for (int i=0;i<n;++i){
			a[i]<<=__builtin_clz(a[i])-c;
			if (a[i]>ma)a[i]>>=1;
            a[i]=min(a[i],b[i]);
			mi=min(mi,a[i]);
		}
		int ans=ma-mi;
		for (int i=0;i<n;++i){
			int j=a[i]==mi?32:__builtin_clz(a[i]-mi);
			vmin[j]=min(vmin[j],a[i]); vmax[j]=max(vmax[j],a[i]);
			if (a[i]*2>b[i])can[j]=0;
		}
		for (int i=W,j,flag=can[W];;i=j,flag&=can[j]){
			for (j=i-1;j&&!vmax[j];--j);
			if (!vmax[j]||!flag)break;
			ans=min(ans,2*vmax[i]-vmin[j]);
		}
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();


