const int N=2005,inf=~0u>>1;
int _f[N*2],_g[N*2],nxt[N];
class Solution {
public:
    int makeArrayIncreasing(vector<int>& a, vector<int>& b) {
        int n=a.size(),*f0=_f,*f1=_f+n+1,*g0=_g,*g1=_g+n+1,len=1,ans=-1;
		sort(b.begin(),b.end()); b.resize(unique(b.begin(),b.end())-b.begin());
		for (int i=0;i<a.size();++i)
			nxt[i]=upper_bound(b.begin(),b.end(),a[i])-b.begin();
		for (int i=0;i<(n+1)*2;++i)f0[i]=inf;
		f0[0]=a[0]; f0[1]=b[0];
		g0[0]=nxt[0]; g0[1]=1;
		for (int i=1;i<n;++i){
			for (int j=len;j>=0;--j){
				int &v=f0[j];
				if (v==inf)break;
				if (v<a[i]&&a[i]<f1[j])f1[j]=a[i],g1[j]=nxt[i];
				if (g0[j]<b.size()&&b[g0[j]]<f1[j+1])f1[j+1]=b[g0[j]],g1[j+1]=g0[j]+1;
				v=inf;
			}
			++len; while (f1[len]==inf&&len)--len;
			swap(f0,f1); swap(g0,g1);
		}
		for (int i=0;i<=n;++i)
			if (f0[i]<inf){ans=i;break;}
		return ans;
    }
};


