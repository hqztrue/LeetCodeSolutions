const int N=1005,inf=~0u>>1;
struct BST{
	struct node{
		node *l,*r,*p;
		int key,key1;
	};
	node a[N],*root,*null;
	int len;
	void clear(){
		srand(time(0));len=0;root=null=a;
		null->l=null->r=null->p=null; null->key=0;
	}
	BST(){clear();}
	node *newnode(int key,int key1){
		node *x=a+(++len);
		x->l=x->r=x->p=null;
		x->key=key; x->key1=key1;
		return x;
	}
	void insert(int key,int key1){
		node *x=root,*y=null,*z=newnode(key,key1);
		if (root==null){root=z;return;}
		while (x!=null){
			y=x;
			if (key<x->key)x=x->l;
			else x=x->r;
		}
		z->p=y;
		if (key<y->key)y->l=z;
		else y->r=z;
	}
	node *find(node *x,int key){
		if (x==null)return null;
		if (key==x->key)return x;
		if (key<x->key)return find(x->l,key);
		else return find(x->r,key);
	}
	node *delmin(node *x){
		if (x->l==null){
			x->r->p=x->p;
			if (x->p->l==x)x->p->l=x->r;
			else x->p->r=x->r;
			return x;
		}
		else {
			node *t=delmin(x->l);
			return t;
		}
	}
	node *delmax(node *x){
		 if (x->r==null){
			x->l->p=x->p;
			if (x->p->l==x)x->p->l=x->l;
			else x->p->r=x->l;
			return x;
		}
		else {
			node *t=delmax(x->r);
			return t;
		}
	}
	void del(node *x){
		if (x->l==null&&x->r==null){
			if (x==root)root=null;
			else if (x==x->p->l)x->p->l=null;
			else x->p->r=null;
		}
		else if (x->r==null||x->l!=null&&rand()<RAND_MAX/2){
			node *tmp=delmax(x->l);
			if (x==root)root=tmp;
			else if (x==x->p->l)x->p->l=tmp;
			else x->p->r=tmp;
			tmp->l=x->l; x->l->p=tmp;
			tmp->r=x->r; x->r->p=tmp;
			tmp->p=x->p;
		}
		else {
			node *tmp=delmin(x->r);
			if (x==root)root=tmp;
			else if (x==x->p->l)x->p->l=tmp;
			else x->p->r=tmp;
			tmp->l=x->l; x->l->p=tmp;
			tmp->r=x->r; x->r->p=tmp;
			tmp->p=x->p;
		}
	}
	node *pred(node *x,int key){
		if (x==null)return null;
		if (x->key>=key)return pred(x->l,key);
		else {
			node *res=pred(x->r,key);
			return res==null?x:res;
		}
	}
	node *succ(node *x,int key){
		if (x==null)return null;
		if (x->key<=key)return succ(x->r,key);
		else {
			node *res=succ(x->l,key);
			return res==null?x:res;
		}
	}
	node *pred(node *x){
		if (x==null)return null;
		if (x->l!=null)return fmax(x->l);
		while (x==x->p->l)x=x->p;
		return x->p;
	}
	node *succ(node *x){
		if (x==null)return null;
		if (x->r!=null)return fmin(x->r);
		while (x==x->p->r)x=x->p;
		return x->p;
	}
	node *fmin(node *x){while (x->l!=null)x=x->l;return x;}
	node *fmax(node *x){while (x->r!=null)x=x->r;return x;}
	void print(node *x){
		if (x==null)return;
		print(x->l);
		printf("nie %d %d\n",x->key,x->key1);
		print(x->r);
	}
}; typedef BST::node node;
BST a[3];
class MyCalendarTwo {
public:
	MyCalendarTwo() {
		for (int i=0;i<=2;++i)a[i].clear();
		a[0].insert(-inf,inf);
	}
	bool book(int l, int r) {
		node *x=a[2].pred(a[2].root,l);
		if (x!=a[2].null&&x->key1>l)return 0;
		x=x==a[2].null?a[2].fmin(a[2].root):a[2].succ(x);
		if (x!=a[2].null&&x->key<r)return 0;
		for (int i=1;i>=0;--i){
			x=a[i].pred(a[i].root,l);
			if (x!=a[i].null){
				if (x->key1>l){
					a[i+1].insert(l,min(x->key1,r));
					if (x->key1>r)a[i].insert(r,x->key1);
					x->key1=l;
				}
				x=a[i].succ(x);
			}
			else x=a[i].fmin(a[i].root);
			while (x!=a[i].null&&x->key<r){
				a[i+1].insert(x->key,min(x->key1,r));
				if (x->key1<=r){
					node *y=a[i].succ(x); a[i].del(x); x=y;
				}
				else {
					x->key=r;
					break;
				}
			}
		}
		return 1;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

