const int N=40005;
int c[N],del[N];
class Solution {
public:
	int eatenApples(vector<int>& a, vector<int>& d) {
		int n=a.size(),m=0,s=0,s1=0,t,ans=0;
		for (int i=n-1;i>=0;--i)
			if (i+d[i]>m)m=i+d[i];
		memcpy(c,&a[0],sizeof(int)*n);
		memset(c+n,0,sizeof(int)*(m+1-n));
		memset(del,0,sizeof(int)*(m+1));
		for (int i=0;i<n;++i)del[i+d[i]]+=a[i];
		for (int i=0;i<=m;++i){
			s+=c[i]; t=del[i];
			if (t){
				if (s1>=t)s1-=t;
				else s-=t-s1,s1=0;
			}
			if (s)++s1,--s,++ans;
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

