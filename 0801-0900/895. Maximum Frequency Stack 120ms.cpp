const int N=10005;
namespace Hash{
	typedef unsigned int uint;
	const uint S=15,S1=32-S,M=1996090921;
	struct node{
		int x,y,t;
	}h[(1<<S)+1005];
	int T=1;
	inline int insert(int x,int y){
		node *p=h+((uint)x*M>>S1);
		for (;p->t==T;++p)
			if (p->x==x)return p->y+=y;
		p->t=T; p->x=x; return p->y=y;
	}
	inline int* find(int x){
		for (node *p=h+((uint)x*M>>S1);p->t==T;++p)
			if (p->x==x)return &p->y;
		return 0;
	}
} using namespace Hash;
vector<int> v[N];
class FreqStack {
public:
	int m;
	FreqStack() {
		m=-1; ++T;
	}
	void push(int x) {
		int f=insert(x,1);
		v[f].push_back(x);
		if (f>m)m=f;
	}
	int pop() {
		int x=v[m].back(); v[m].pop_back();
		insert(x,-1);
		if (v[m].empty())--m;
		return x;
	}
	~FreqStack() {
		for (int i=0;i<=m;++i)v[i].clear();
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

