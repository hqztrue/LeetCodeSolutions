namespace Hash{
	typedef unsigned int uint;
	const uint S=17,S1=32-S,M=1996090921;
	struct node{
		int x,y,t;
	}h[(1<<S)+1005];
	int T=1;
	inline void insert(int x,int y){
		node *p=h+((uint)x*M>>S1);
		for (;p->t==T;++p)
			if (p->x==x){p->y+=y; return;}
		p->t=T; p->x=x; p->y=y;
	}
	inline bool find(int x){
		for (node *p=h+((uint)x*M>>S1);p->t==T;++p)
			if (p->x==x&&p->y)return 1;
		return 0;
	}
} using namespace Hash;

class Solution {
public:
	int maxOperations(vector<int>& a, int k) {
		int n=a.size(),ans=0; ++T;
		for (int i=0;i<n;++i)
			if (a[i]<k){
				if (find(k-a[i]))insert(k-a[i],-1),++ans;
				else insert(a[i],1);
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

