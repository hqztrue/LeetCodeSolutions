const int N=1005,L=27,inf=~0u>>2;
struct node{
	node *_l,*_r;
	int v,min,max;
	node(node *_l=0,node *_r=0,int _min=inf,int _max=0)
		:_l(_l),_r(_r),min(_min),max(_max),v(-1){}
	node *l(){return _l;}
	node *r(){return _r;}
}Pool[N*L*10],*p,*root;
node *t1[N],*t2[N],*t3[N],*t4[N];  //bottom, up, prefix, suffix
inline node* newnode(node *l=0,node *r=0,int x=-1){
	p->_l=l; p->_r=r;
	if (x==-1){
		p->min=l?l->min:(r?r->min:inf);
		p->max=r?r->max:(l?l->max:0);
		p->v=-1;
	}
	else p->v=p->min=p->max=x;
	return p++;
}
node* merge(node *x,node *y){
	if (!x||!y)return x?x:y;
	return newnode(merge(x->_l,y->_l),merge(x->_r,y->_r),x->v);
}
node *insert(node *x,int key,int d=L-1){
	if (d<0)return x?x:newnode(0,0,key);
	node *l=x?x->_l:0,*r=x?x->_r:0;
	if ((key>>d)&1)return newnode(l,insert(r,key,d-1));
	else return newnode(insert(l,key,d-1),r);
}
void print(node *x,int key=0,int d=L){
	if (!x)return;
	if (!x->_l&&!x->_r)printf("%d %d d=%d\n",key,x->v,d);
	else print(x->_l,key*2,d-1),print(x->_r,key*2+1,d-1);
}
struct node3;
node3* newnode3(node *a0,node *a1,node *a2);
struct node3{
	node *a[3];
	int v,min,max;
	node3(){}
	node3(node *a0,node *a1,node *a2){
		a[0]=a0; a[1]=a1; a[2]=a2;
		min=inf; max=0; v=-1;
		if (a0)min=::min(min,a0->min),max=::max(max,a0->max),v=a0->v;
		if (a1)min=::min(min,a1->min),max=::max(max,a1->max),v=a1->v;
		if (a2)min=::min(min,a2->min),max=::max(max,a2->max),v=a2->v;
	}
	node3 *l(){return newnode3(a[0]?a[0]->_l:0,a[1]?a[1]->_l:0,a[2]?a[2]->_l:0);}
	node3 *r(){return newnode3(a[0]?a[0]->_r:0,a[1]?a[1]->_r:0,a[2]?a[2]->_r:0);}
}Pool3[N*L*10],*p3;
inline node3* newnode3(node *a0,node *a1,node *a2){
	*p3=node3(a0,a1,a2);
	return p3++;
}
inline bool exist(node *x){return x;}
inline bool exist(node3 *x){return x&&(x->a[0]||x->a[1]||x->a[2]);}
int D(node *x){
	return !x?-1:max(D(x->_l),D(x->_r))+1;
}
inline int get(int x,int i){return (x>>i)&1;}
inline int msb(int x){return x?31-__builtin_clz(x):-1;}
int s_below[N],s,ans,*a;
vector<int> e[N];
class Solution {
public:
	void dfs1(int x,int fa){
		s_below[x]=a[x]; t1[x]=0;
		for (int y:e[x])
			if (y!=fa){
				dfs1(y,x);
				s_below[x]^=s_below[y];
				t1[x]=merge(t1[x],insert(t1[y],s_below[y]));
			}
	}
	void dfs2(int x,int fa,int fa1){
		if (fa1!=-1)t2[x]=insert(t2[fa],s^s_below[fa]);
		else t2[x]=0;
		for (int y:e[x])
			if (y!=fa)dfs2(y,x,fa);
	}
	void dfs3(int x,int fa){
		t3[x]=root;
		for (int y:e[x])
			if (y!=fa)dfs3(y,x);
		root=insert(root,s_below[x]);
	}
	void dfs4(int x,int fa){
		t4[x]=root;
		for (int i=e[x].size()-1;i>=0;--i){
			int y=e[x][i];
			if (y!=fa)dfs4(y,x);
		}
		root=insert(root,s_below[x]);
	}
	template<class Tnode>
	void solve(int x,int u,Tnode *root){
		int v=s^u,d=msb(u);
		if (!exist(root))return;
		// 1.1. ((A,B),C), C good. enumerate C. A,B can be the same.
		for (int I=1;I<=1;++I){
			if (d==L-1)break;
			int i=L-1,pre_dep; Tnode *cur=root,*pre=0;
			for (;i>d;--i){
				if (get(v,i)){
					if (exist(cur->l()))pre=cur->l(),pre_dep=i-1;
					if (!exist(cur->r()))break;
					else cur=cur->r();
				}
				else {
					if (!exist(cur->l()))break;
					else cur=cur->l();
				}
			}
			// special case: A=B=C
			if (d==-1&&i==d){
				ans=0; return;
			}
			if (!exist(pre))break;
			for (i=pre_dep;i>d;--i)
				pre=exist(pre->r())?pre->r():pre->l();
			if (d==-1){
				ans=min(ans,v-pre->v);
				break;
			}
			// 1.1.1. A good
			if (exist(pre->l()))ans=min(ans,v-pre->l()->max);
			// 1.1.2. B good
			if (exist(pre->r())){
				for (cur=pre->r(),i=d-1;i>=0;--i){
					if (get(u,i))cur=exist(cur->l())?cur->l():cur->r();
					else cur=exist(cur->r())?cur->r():cur->l();
				}
				ans=min(ans,v-(u^cur->v));
			}
		}
		// 1.2. (A,(B,C)), A good. enumerate A. B,C can be the same.
		for (int I=1;I<=1;++I){
			if (d==L-1)break;
			int i=L-1,pre_dep; Tnode *cur=root,*pre=0;
			for (;i>d;--i){
				if (!get(v,i)){
					if (exist(cur->r()))pre=cur->r(),pre_dep=i-1;
					if (!exist(cur->l()))break;
					else cur=cur->l();
				}
				else {
					if (!exist(cur->r()))break;
					else cur=cur->r();
				}
			}
			if (!exist(pre))break;
			for (i=pre_dep;i>d;--i)
				pre=exist(pre->l())?pre->l():pre->r();
			if (d==-1){
				ans=min(ans,pre->v-v);
				break;
			}
			// 1.2.1. C good
			if (exist(pre->r()))ans=min(ans,pre->r()->min-v);
			// 1.2.2. B good
			if (exist(pre->l())){
				for (cur=pre->l(),i=d-1;i>=0;--i){
					if (get(u,i))cur=exist(cur->r())?cur->r():cur->l();
					else cur=exist(cur->l())?cur->l():cur->r();
				}
				ans=min(ans,(u^cur->v)-v);
			}
		}
		// 1.3 & 1.4
		for (int I=1;I<=1;++I){
			if (d==-1)break; 
			int i=L-1; Tnode *cur=root;
			for (;i>d;--i){
				if (get(v,i)){
					if (!exist(cur->r()))break;
					else cur=cur->r();
				}
				else {
					if (!exist(cur->l()))break;
					else cur=cur->l();
				}
			}
			if (i>d)break;
			Tnode *_cur=cur;
			// 1.3. ((A,B),C), A&B good. enumerate A
			if (!get(v,d)){
				cur=_cur->l();
				if (!exist(cur)||cur->max<v)break;
				for (i=d-1;i>=0;--i){
					if (get(v,i))cur=cur->r();
					else {
						if (get(u,i)){
							if (exist(cur->r())){cur=cur->r(); --i; break;}
							else cur=cur->l(); 
						}
						else {
							if (exist(cur->l())&&cur->l()->max>=v)cur=cur->l();
							else {cur=cur->r(); --i; break;}
						}
					}
				}
				for (;i>=0;--i){
					if (get(u,i))cur=exist(cur->r())?cur->r():cur->l();
					else cur=exist(cur->l())?cur->l():cur->r();
				}
				ans=min(ans,(u^cur->v)-v);
			}
			// 1.4. (A,(B,C)), B&C good. enumerate C
			else {
				cur=_cur->r();
				if (!exist(cur)||cur->min>v)break;
				for (i=d-1;i>=0;--i){
					if (!get(v,i))cur=cur->l();
					else {
						if (get(u,i)){
							if (exist(cur->l())){cur=cur->l(); --i; break;}
							else cur=cur->r(); 
						}
						else {
							if (exist(cur->r())&&cur->r()->min<=v)cur=cur->r();
							else {cur=cur->l(); --i; break;}
						}
					}
				}
				for (;i>=0;--i){
					if (get(u,i))cur=exist(cur->l())?cur->l():cur->r();
					else cur=exist(cur->r())?cur->r():cur->l();
				}
				ans=min(ans,v-(u^cur->v));
			}
		}
	}
	void dfs(int x,int fa){  // Compute the solution.
		for (int y:e[x])
			if (y!=fa){
				dfs(y,x);
			}
		// Case 1. enumerate above x
		solve(x,s_below[x],x?t1[x]:0);
		// Case 2. enumerate below x
		solve(x,s^s_below[x],newnode3(t2[x],t3[x],t4[x]));
	}
	int minimumScore(vector<int>& _a, vector<vector<int>>& edges) {
		int n=_a.size();
		a=&_a[0]; s=0; p=Pool; p3=Pool3; ans=inf;
		for (int i=0;i<n;++i)s^=a[i],e[i].clear();
		for (auto &e0:edges){
			int x=e0[0],y=e0[1];
			e[x].push_back(y);
			e[y].push_back(x);
		}
		dfs1(0,-1);
		dfs2(0,-1,-1);
		root=0; dfs3(0,-1);
		root=0; dfs4(0,-1);
		dfs(0,-1);
		return ans;
	}
};
