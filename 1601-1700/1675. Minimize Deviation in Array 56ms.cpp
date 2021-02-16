const int N=100005,W=32,inf=~0u>>2;
int b[N];
class Solution {
public:
	int minimumDeviation(vector<int>& a) {
		int n=a.size(),ma=0,mi=inf,b1=0;
		int vmin[W+1],vmax[W+1];
		for (int i=0;i<=W;++i)vmin[i]=inf,vmax[i]=0;
		for (int i=0;i<n;++i)ma=max(ma,a[i]>>__builtin_ctz(a[i]));
		int low=ma,c=__builtin_clz(ma);
		for (int i=0;i<n;++i){
			int &t=a[i]; t<<=t&1; 
			if (t>=ma){
				t>>=c-__builtin_clz(t);
                t>>=t>ma;
				b[b1++]=t;
			}
			else low=min(low,t);
			mi=min(mi,t);
		}
		int ans=ma-mi,i0=low==mi?32:__builtin_clz(low-mi);
        b[b1++]=low;
		for (int i=0;i<b1;++i)if (b[i]<=low){
			int j=b[i]==mi?32:__builtin_clz(b[i]-mi);
			vmin[j]=min(vmin[j],b[i]); vmax[j]=max(vmax[j],b[i]);
		}
		for (int i=W,j;;i=j){
			for (j=i-1;j>=0&&!vmax[j];--j);
			if (i==i0||!vmax[j])break;
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


