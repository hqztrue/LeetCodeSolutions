typedef unsigned long long ull;
const int N=1005;
struct Data{
	short g1,g2,v1,v2,id1,id2;
};
namespace Hash{
	typedef unsigned int uint;
	const uint S=15,S1=64-S,M=1234567891,_inf=~0u>>1;
	#define H(x) (x*M>>S1)
	struct node{
		ull x;
		int t;
		Data y;
	}h[(1<<S)+105];
	int T=1;
	inline Data* find(ull x){
		node *p=h+H(x);
		for (;p->t==T;++p)
			if (p->x==x)return &p->y;
		p->t=T; p->x=x; p->y={};
		return &p->y;
	}
	#undef H
} using namespace Hash;
int pre[N];
class Solution {
public:
	vector<string> getWordsInLongestSubsequence(int n, vector<string>& w, vector<int>& g) {
		++T;
		int best=0,best_id;
		for (int i=0;i<n;++i){
			int m=w[i].size();
			ull s=0;
			for (int j=0;j<m;++j)s+=(ull)(w[i][j]-96)<<(j*5);
			short g0=g[i],v0=1,id0=-1;
			for (int j=0;j<m;++j){
				ull s1=s+((ull)(28+96-w[i][j])<<(j*5));
				Data *p=find(s1);
				if (p->g1!=g0){
					if (p->v1>=v0)v0=p->v1+1,id0=p->id1;
				}
				else {
					if (p->v2>=v0)v0=p->v2+1,id0=p->id2;
				}
			}
			if (v0>best)best=v0,best_id=i;
			pre[i]=id0;
			for (int j=0;j<m;++j){
				ull s1=s+((ull)(28+96-w[i][j])<<(j*5));
				Data *p=find(s1);
				if (p->g1!=g0&&p->g2!=g0){
					if (p->v1<v0){
						p->g2=p->g1,p->v2=p->v1,p->id2=p->id1;
						p->g1=g0,p->v1=v0,p->id1=i;
					}
					else if (p->v2<v0)p->g2=g0,p->v2=v0,p->id2=i;
				}
				else {
					if (p->g1==g0&&p->v1<v0)p->g1=g0,p->v1=v0,p->id1=i;
					if (p->g2==g0&&p->v2<v0)p->g2=g0,p->v2=v0,p->id2=i;
					if (p->v1<p->v2)swap(p->g1,p->g2),swap(p->v1,p->v2),swap(p->id1,p->id2);
				}
			}
		}
		vector<string> ans;
		for (int j=best_id;j>=0;j=pre[j])ans.push_back(w[j]);
		reverse(ans.begin(),ans.end());
		return ans;
	}
};
