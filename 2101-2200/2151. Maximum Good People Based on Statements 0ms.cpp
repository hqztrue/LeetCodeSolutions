const int N=15;
#define I(x) __builtin_ctz(x)
int a[N][N],q[N],v[N],ans,n;
class Solution {
public:
	bool upd(int &mask,int &state,int i,int x){
		int h=0,t=1,fixed=0; q[0]=i; v[0]=x;
		fixed|=1<<i; state|=x<<i;
		while (h<t){
			i=q[h]; x=v[h++];
			if (x){
				for (int m=mask;m;m-=m&-m){
					int j=I(m),v0=a[i][j];
					if (v0==2)continue;
					if ((fixed&(1<<j))==0)fixed|=1<<j,state|=v0<<j,q[t]=j,v[t++]=v0;
					else if (((state&(1<<j))>0)!=v0)return 0;
				}
			}
			for (int m=mask;m;m-=m&-m){
				int j=I(m),v0=a[j][i];
				if (v0==2||v0==x)continue;
				if ((fixed&(1<<j))==0)fixed|=1<<j,q[t]=j,v[t++]=0;
				else {
					if (!(state&(1<<j)))continue;
					if (v0!=x)return 0;
				}
			}
		}
		mask-=fixed;
		return 1;
	}
	void dfs(int mask,int state){
		if (!mask){
			ans=max(ans,__builtin_popcount(state));
			return;
		}
		int i=I(mask),j=-1;
		for (int m=mask;m;m-=m&-m){
			int t=I(m);
			if (a[i][t]!=2||a[t][i]!=2){j=t; break;}
		}
		if (j<0){
			dfs(mask-(1<<i),state|(1<<i));
			return;
		}
		if (a[i][j]!=2)swap(i,j);
		int mask1=mask,state1=state;
		if (upd(mask1,state1,i,0))dfs(mask1,state1);
		if (upd(mask,state,i,1))dfs(mask,state);
	}
	int maximumGood(vector<vector<int>>& st) {
		n=st.size(); ans=0;
		for (int i=0;i<n;++i)
			for (int j=0;j<n;++j)a[i][j]=st[i][j];
		dfs((1<<n)-1,0);
		return ans;
	}
};

