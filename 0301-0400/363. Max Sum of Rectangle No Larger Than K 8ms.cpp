const int N=1505,R=10,U=500000000;
namespace Hash{
	typedef unsigned int uint;
	const uint S=8,S1=32-S,M=1996090921,_inf=~0u>>1;
	#define H(x) ((uint)x*M>>S1)
	struct node{
		int x,ma,mi,t;
	}h[(1<<S)+105];
	int T=1;
	inline void insert(int x,int y){
		node *p=h+H(x);
		for (;p->t==T;++p)
			if (p->x==x){p->ma=max(p->ma,y); p->mi=min(p->mi,y); return;}
		p->t=T; p->x=x; p->ma=p->mi=y;
	}
	inline node* find(int x){
		for (node *p=h+H(x);p->t==T;++p)
			if (p->x==x)return p;
		return 0;
	}
	#undef H
} using namespace Hash;
bool twoSumDec(vector<int> a,int ans,int k){  //>=ans,<=k?
	ans=max(ans,-U/2);
	if (ans>k)return 0;
	k+=U*2; ans+=U*2; ++T; int n=a.size(),d=k-ans+1;
	for (int i=0;i<n;++i){
		int t=ans-a[i]-U; node *p=find(t/d),*q=find(t/d+1);
		if (p&&p->ma>=t||q&&q->mi<=k-a[i]-U)return 1;
		insert((U-a[i])/d,U-a[i]);
	}
	return 0;
}
int twoSumOpt(vector<int> &a,int k){  //<=k
	int n=a.size(),res=-U,L=(n-1)/R+1;
	if (n<R){
		for (int i=0;i<n;++i)
			for (int j=i+1;j<n;++j)
				if (a[j]-a[i]<=k)res=max(res,a[j]-a[i]);
		return res;
	}
	struct{int i,j;}id[R*(R+1)/2]; int id1=0;
	for (int i=0;i<R;++i)
		for (int j=i;j<R;++j)id[id1].i=i,id[id1++].j=j;
	random_shuffle(id,id+id1);
	for (int I=0;I<id1;++I){
		int i=id[I].i,j=id[I].j; vector<int> b;
		for (int k=i*L;k<(i+1)*L&&k<n;++k)b.push_back(a[k]);
		if (j!=i)for (int k=j*L;k<(j+1)*L&&k<n;++k)b.push_back(a[k]);
		if (twoSumDec(b,res+1,k))res=twoSumOpt(b,k);
	}
	return res;
}
int a[105][N],s[N];
class Solution {
public:
	int maxSumSubmatrix(vector<vector<int>>& _a, int K) {
		int m=_a.size(),n=_a[0].size(),ans=-U;
		if (m>n){
			for (int i=0;i<n;++i)
				for (int j=0;j<m;++j)a[i][j]=_a[j][i];
			swap(n,m);
		}
		else {
			for (int i=0;i<m;++i)
				for (int j=0;j<n;++j)a[i][j]=_a[i][j];
		}
		for (int j=0;j<m;++j){
			memset(s,0,sizeof(int)*n);
			for (int k=j;k<m;++k){
				for (int i=0;i<n;++i)s[i]+=a[k][i];
				int ma=-U,t=0;
				for (int i=0;i<n;++i){
					if (t<=0)t=s[i];
					else t+=s[i];
					if (t>ma)ma=t;
				}
				if (ma<=K)ans=max(ans,ma);
				else {
					for(int i1=0;i1<n;++i1)
						for(int j1=i1,t=0;j1<n;++j1){
							t+=s[j1];
							if(t<=K&&t>ans)ans=t;
						}
					//vector<int> v; v.push_back(0);
					//for (int i=0;i<n;++i)v.push_back(v[i]+s[i]);
					//if (twoSumDec(v,ans+1,K))ans=twoSumOpt(v,K);
				}
				if (ans==K)return K;
			}
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

