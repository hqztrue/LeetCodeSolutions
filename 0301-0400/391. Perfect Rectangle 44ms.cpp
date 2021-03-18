constexpr int N=10505,inf=~0u>>1,U=1<<15;
int cnt;
namespace Hash{
	typedef unsigned int uint;
	constexpr uint S=16,S1=32-S,M=1996090921,_inf=~0u>>1;
	#define H(x) ((uint)x*M>>S1)
	struct node{
		int x,y,t;
	}h[(1<<S)+1005];
	int T=1;
	inline void insert(int x){
		node *p=h+H(x);
		for (;p->t==T;++p)
			if (p->x==x){cnt-=p->y*2; p->y^=1; return;}
		p->t=T; p->x=x; p->y=1;
	}
	inline bool find(int x){
		for (node *p=h+H(x);p->t==T;++p)
			if (p->x==x)return p->y;
		return 0;
	}
	inline int count(){
		int s=0;
		for (node *p=h,*end=h+(1<<S)+1005;p!=end;++p)s+=p->t==T&&p->y;
		return s;
	}
	inline void erase_(int x){
		for (node *p=h+H(x);p->t==T;++p)
			if (p->x==x){p->x=_inf; return;}
	}
	inline void erase(int x){
		for (node *p=h+H(x);p->t==T;++p)
			if (p->x==x){
				for (node *q=p+1;q->t==T;++q)
					if (h+H(q->x)<=p){p->x=q->x; p->y=q->y; p=q;}
				p->t=0; return;
			}
	}
	#undef H
} using namespace Hash;
class Solution {
public:
	bool isRectangleCover(vector<vector<int>>& a) {
		uint s=0,mi_x=inf,mi_y=inf,ma_x=0,ma_y=0; ++T; cnt=a.size()*4;
		for (auto &r:a){
			uint x1=r[0]+U,y1=r[1]+U,x2=r[2]+U,y2=r[3]+U;
			s+=(x2-x1)*(y2-y1); mi_x=min(mi_x,x1); ma_x=max(ma_x,x2); mi_y=min(mi_y,y1); ma_y=max(ma_y,y2);
			insert((x1<<16)+y1); insert((x1<<16)+y2); insert((x2<<16)+y1); insert((x2<<16)+y2);
		}
		if (s!=(ma_x-mi_x)*(ma_y-mi_y)||!find((mi_x<<16)+mi_y)||!find((mi_x<<16)+ma_y)||!find((ma_x<<16)+mi_y)||!find((ma_x<<16)+ma_y))return 0;
		return cnt==4;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

