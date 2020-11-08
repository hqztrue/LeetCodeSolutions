namespace Hash{
	typedef unsigned int uint;
	const uint S=17,S1=32-S,M=1996090921;
	struct node{
		int x,y,t;
	}h[(1<<S)+1005];
	int T=1;
	void insert(int x){
		node *p=h+((uint)x*M>>S1);
		for (;p->t==T;++p)
			if (p->x==x){++p->y; return;}
		p->t=T; p->x=x; p->y=1;
	}
	int find(int x){
		for (node *p=h+((uint)x*M>>S1);p->t==T;++p)
			if (p->x==x)return p->y;
		return 0;
	}
} using namespace Hash;

class FirstUnique {
public:
	vector<int> a;
	int id;
	FirstUnique(vector<int>& nums) {
		int n=nums.size(); a=nums; id=0; ++T;
		for (int i=0;i<n;++i)insert(a[i]);
	}
	int showFirstUnique() {
		int n=a.size();
		while (id<n&&find(a[id])>1)++id;
		return id==n?-1:a[id];
	}
	void add(int v) {
		a.push_back(v);
		insert(v);
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();


