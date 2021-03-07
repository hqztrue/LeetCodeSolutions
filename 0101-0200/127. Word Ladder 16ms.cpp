typedef unsigned int uint;
const int N=5005,L0=10,L=N*L0; const uint mul=131;
int vis[N],q[N],v1; uint hsh[N],mul1[L0];
vector<int> v[L];
namespace Hash{
	const uint S=16,S1=32-S,M=1996090921;
	struct node{
		int x,t;
		vector<int> *y;
	}h[(1<<S)+1005];
	int T=1;
	inline void insert(int x,int y){
		node *p=h+((uint)x*M>>S1);
		for (;p->t==T;++p)
			if (p->x==x){p->y->push_back(y); return;}
		p->t=T; p->x=x; p->y=v+(v1++); p->y->push_back(y);
	}
	inline vector<int>** find(int x){
		for (node *p=h+((uint)x*M>>S1);p->t==T;++p)
			if (p->x==x)return &p->y;
		return 0;
	}
} using namespace Hash;

class Solution {
public:
	int ladderLength(string beginWord, string endWord, vector<string>& w) {
		for (int i=0;i<v1;++i)v[i].clear();
		int n=w.size(); v1=0; ++T;
		for (int i=0;i<n-1;++i)
			if (w[i]==endWord)swap(w[i],w[n-1]);
		if (w[n-1]!=endWord)return 0;
		w.push_back(beginWord); ++n;
		mul1[0]=1; for (int i=1;i<L0;++i)mul1[i]=mul1[i-1]*mul;
		for (int i=0;i<n;++i){
			int l=w[i].size(); uint h0=0;
			for (char *p=&w[i][0],*end=p+l;p!=end;++p)h0=h0*mul+*p;
			for (char *p=&w[i][0],*end=p+l;p!=end;++p){
				uint h1=h0-*p*mul1[end-1-p];
				insert(h1,i);
			}
			hsh[i]=h0;
		}
		for (int i=0;i<n;++i)vis[i]=0; vis[n-1]=1;
		int l=0,r=1,ans=1; q[0]=n-1;
		while (l<r){
			int r1=r; ++ans;
			for (;l<r;++l){
				int i=q[l]; uint h0=hsh[i];
				for (char *p=&w[i][0],*end=p+w[i].size();p!=end;++p){
					uint h1=h0-*p*mul1[end-1-p];
					vector<int>** pt=find(h1);
					if (*pt){
						vector<int> &vec=*(*pt);
						for (int j:vec)
							if (!vis[j]){
								q[r1++]=j,vis[j]=1;
								if (j==n-2)return ans;
							}
						*pt=0;
					}
				}
			}
			l=r; r=r1;
		}
		return 0;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

