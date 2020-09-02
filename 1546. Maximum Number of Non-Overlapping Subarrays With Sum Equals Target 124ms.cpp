namespace Hash{
	typedef unsigned int uint;
	const uint S=18,S1=32-S,M=1996090921;
	struct node{
		int x,y,t;
	}h[(1<<S)+1005];
	int T=0;
	void insert(int x,int y){
		node *p=h+((uint)x*M>>S1);
		for (;p->t==T;++p)
			if (p->x==x){p->y=y; return;}
		p->t=T; p->x=x; p->y=y;
	}
	int* find(int x){
		for (node *p=h+((uint)x*M>>S1);p->t==T;++p)
			if (p->x==x)return &p->y;
		return 0;
	}
}; using namespace Hash;
const int N=100005;
class Solution {
public:
	int maxNonOverlapping(vector<int>& a, int t) {
		int n=a.size(),s=0,cur=-1,cnt=0;
		++T; insert(0,-1);
		for (int i=0;i<n;++i){
			s+=a[i];
			int *p=find(s-t);
			if (p&&cur<=*p)++cnt,cur=i;
			insert(s,i);
		}
		return cnt;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

