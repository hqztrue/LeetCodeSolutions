const int N=105;
int x[N],y[N],w[N],h[N],u[N],id[N],S[N],L[N],s,n;
typedef unsigned long long ull;
inline ull _rand(){static ull x=3125312531253125LL;x+=(x<<4)+(x>>21)+1;return x&=0x7fffffffffffffffLL;}
class Solution {
public:
	Solution(vector<vector<int>>& r) {
		int s1=0,l1=0; n=r.size(); s=0;
		for (int i=0;i<n;++i)
			x[i]=r[i][0],y[i]=r[i][1],w[i]=r[i][2]-x[i]+1,h[i]=r[i][3]-y[i]+1,u[i]=w[i]*h[i],s+=u[i],u[i]*=n;
		for (int i=0;i<n;++i)
			if (u[i]<s)S[s1++]=i;
			else if (u[i]>s)L[l1++]=i;
		while (s1){
			int i=S[--s1],j=L[--l1];
			id[i]=j; u[j]+=u[i]-s;
			if (u[j]<s)S[s1++]=j;
			else if (u[j]>s)L[l1++]=j;
		}
	}
	vector<int> pick() {
		int t=_rand()%n,j=_rand()%s<u[t]?t:id[t],k=_rand()%(w[j]*h[j]);
		return {x[j]+k/h[j],y[j]+k%h[j]};
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

