typedef long long ll;
typedef unsigned int uint;
#define N 100005
int f[N],p[N],p1=0;
int fa[N],_fa[N],s[N];
void get_prime(int p[],int n){
	p1=0; memset(f+1,0,sizeof(int)*n);
	for (int i=2;i<=n;++i)if (!f[i]){
		p[++p1]=i; f[i]=i;
		if ((ll)i*i<=n)for (int j=i*i;j<=n;j+=i)f[j]=i;
	}
	for (int i=1;i<N;++i)_fa[i]=i;
}
int find(int x){
	if (fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
class Solution {
public:
	int largestComponentSize(vector<int>& a) {
		if (!p1)get_prime(p,N-1);
		int n=a.size(),ans=0;
		//for (int i=1;i<=p1;++i)fa[p[i]]=p[i];
		//int u=*max_element(a.begin(),a.end())+1;
		memset(s,0,sizeof(s));
		memcpy(fa,_fa,sizeof(fa));
		for (int i=0;i<n;++i){
			int x=a[i],cur=0,r1,r2=0;
			while (x>1){
				cur=f[x]; r1=find(cur);
				if (!r2)r2=r1,++s[r2];
				else if (r1!=r2)fa[r1]=r2,s[r2]+=s[r1];
				do {x/=cur;}while (!x%cur);
			}
			ans=max(ans,s[r2]);
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


