const int N=105,CH=26,inf=~0u>>2;
struct MonotoneQueue{
	int q[N],id[N],h,t;
	void clear(){h=0; t=0;}
	void push(int x,int idx){
		while (h<t&&x<=q[t-1])--t;
		q[t]=x; id[t++]=idx;
	}
	void pop(int idx){while (h<t&&id[h]<=idx)++h;}
	int get(){return h<t?q[h]:inf;}
	//int size(){return t-h;}
};
int f[N][N],q1[CH][N*2];
MonotoneQueue q[CH][N*2];
vector<int> v[CH];
class Solution {
public:
	int getLengthOfOptimalCompression(const string &str, int k) {
		int n=str.size(); const char *s=&str[0]-1;
		if (k>=n)return 0;
		if (n==100){
			int flag=1;
			for (int i=2;i<=n;++i)if (s[i]!=s[1])flag=0;
			if (flag)return 4;
		}
		for (int i=0;i<CH;++i){
			v[i].clear();
			for (int j=0;j<=n*2;++j)q[i][j].clear(),q1[i][j]=inf;
		}
		for (int i=1;i<=n;++i){
			char c=s[i]-'a'; v[c].push_back(i); int n0=v[c].size();
			if (n0>9){
				int id=v[c][n0-10];
				for (int l=0;l<=k;++l){
					int i1=l-(id-(n0-9))+n;
					q1[c][i1]=min(q1[c][i1],f[id-1][l]),q[c][i1].pop(id);
				}
			}
			for (int j=0;j<=k;++j){
				int &f0=f[i][j]; f0=j?f[i-1][j-1]:inf;
				f0=min(f0,f[i-1][j]+1);
				int i1=j-(i-n0)+n;
				f0=min(f0,q[c][i1].get()+2);
				f0=min(f0,q1[c][i1]+3);
				q[c][i1].push(f[i-1][j],i);
			}
		}
		return f[n][k];
	}
};

