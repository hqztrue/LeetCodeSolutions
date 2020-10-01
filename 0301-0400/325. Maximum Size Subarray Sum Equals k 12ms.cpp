namespace Hash{
	typedef unsigned int uint;
	const uint S=15,S1=32-S,M=1996090921;
	struct node{
		int x,y,t;
	}h[(1<<S)+1005];
	int T=1;
	void insert(int x,int y){
		node *p=h+((uint)x*M>>S1);
		for (;p->t==T;++p)
			if (p->x==x)return;
		p->t=T; p->x=x; p->y=y;
	}
	int* find(int x){
		for (node *p=h+((uint)x*M>>S1);p->t==T;++p)
			if (p->x==x)return &p->y;
		return 0;
	}
} using namespace Hash;
class Solution {
public:
	int maxSubArrayLen(vector<int>& a, int k) {
		int n=a.size(),s=0,res=0;
		++T; insert(0,-1);
		for (int i=0;i<n;++i){
			s+=a[i];
			int *p=find(s-k);
			if (p)res=max(res,i-*p);
			insert(s,i);
		}
		return res;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

