const int N=100005,inf=~0u>>1;
int a[N],b[N],d[N];
class Solution {
public:
	int minDays(vector<int> &v, int m, int k) {
		int n=v.size(),l=0,l1,t,s,c,ans=-1; if (m*k>n)return -1;
		for (int i=0;i<n;++i)a[l]=v[i],b[l++]=1;
		for (int i=0;i<=n;++i)d[i]=i/k;
		while (1){
			int L=n>1000?5:1,T[5];
			for (int i=0;i<L;++i){
				do{T[i]=a[rand()%l];}while (T[i]==0||T[i]==inf);
			}
			sort(T,T+L); t=T[L/2];
			s=c=0;
			for (int i=0;i<l;++i)
				if (a[i]<=t)c+=b[i];
				else s+=d[c],c=0;
			s+=c/k;
			if (s>=m){
				ans=t;
				for (int i=0;i<l;++i)if (a[i]>=t)a[i]=inf;
			}
			else {
				for (int i=0;i<l;++i)if (a[i]<=t)a[i]=0;
			}
			l1=0;
			for (int i=1;i<l;++i)
				if (a[i]==a[l1])b[l1]+=b[i];
				else {
					if (a[i]==inf&&a[l1]==0&&l1>=1&&a[l1-1]==inf)m-=d[b[l1]],--l1;
					else ++l1,a[l1]=a[i],b[l1]=b[i];
				}
			l=l1+1;
			if (l<4){
				l1=0;
				for (int i=0;i<l;++i)if (a[i]>0&&a[i]<inf)l1=1;
				if (!l1)return ans;
			}
		}
	}
};

//IO
int _IO=[](){
	std::ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

