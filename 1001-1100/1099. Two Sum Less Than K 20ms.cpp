const int N=1005,R=8,U=500000000;
namespace Hash{
	typedef unsigned int uint;
	const uint S=11,S1=32-S,M=1996090921,_inf=~0u>>1;
	#define H(x) ((uint)x*M>>S1)
	struct node{
		int x,ma,mi,t;
	}h[(1<<S)+1005];
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
		a[i]+=U; int t=ans-a[i]; node *p=find(t/d),*q=find(t/d+1);
		if (p&&p->ma>=t||q&&q->mi<=k-a[i])return 1;
		insert(a[i]/d,a[i]);
	}
	return 0;
}
int twoSumOpt(vector<int> &a,int k){  //<=k
	int n=a.size(),res=-U,L=(n-1)/R+1;
	if (n<R){
		for (int i=0;i<n;++i)
			for (int j=i+1;j<n;++j)
				if (a[i]+a[j]<=k)res=max(res,a[i]+a[j]);
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
class Solution {
public:
	int twoSumLessThanK(vector<int>& a, int k) {
		int res=twoSumOpt(a,k-1);
		return res==-U?-1:res;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

