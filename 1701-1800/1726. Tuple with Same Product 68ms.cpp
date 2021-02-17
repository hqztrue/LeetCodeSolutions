namespace Hash{
	typedef unsigned int uint;
	const uint S=21,S1=32-S,M=1996090921;
	struct node{
		int x,y,t;
	}h[(1<<S)+1005];
	int T=1;
	inline void insert(int x){
		node *p=h+((uint)x*M>>S1);
		for (;p->t==T;++p)
			if (p->x==x){++p->y; return;}
		p->t=T; p->x=x; p->y=1;
	}
	inline int find(int x){
		for (node *p=h+((uint)x*M>>S1);p->t==T;++p)
			if (p->x==x){int res=p->y*(p->y-1); p->y=0; return res;}
		return 0;
	}
} using namespace Hash;

class Solution {
public:
	int tupleSameProduct(vector<int>& a) {
		int n=a.size(),ans=0; ++T;
		for (int *i=&a[0],*end=i+n;i!=end;++i)
			for (int *j=i+1;j!=end;++j)insert(*i*(*j));
		for (int *i=&a[0],*end=i+n;i!=end;++i)
			for (int *j=i+1;j!=end;++j)
				ans+=find(*i*(*j));
		return ans*4;
	}
};

