const int N=2005,inf=~0u>>1;
struct RBtree{
	#define black 0
	#define red 1
	struct node{
		node *l,*r,*p;
		int key,key1,size; int col;
		void update(){
			size=l->size+r->size+1;
		}
	};
	node a[N];
	int len;node *root,*null;
	void clear(){
		len=0;root=null=newnode(0,0);
		null->l=null->r=null->p=null;
		null->size=0;null->col=black;
	}
	RBtree(){clear();}
	node *newnode(int key,int key1){
		node *x=a+(++len);
		x->l=x->r=x->p=null;
		x->size=1;x->col=red;
		x->key=key;x->key1=key1;return x;
	}
	void zig(node *x){
		node *y=x->l; x->l=y->r;
		if (y->r!=null)y->r->p=x;
		y->p=x->p;
		if (x->p==null)root=y;
		else if (x==x->p->l)x->p->l=y;
		else x->p->r=y;
		y->r=x; x->p=y;
		x->update();y->update();
	}
	void zag(node *x){
		node *y=x->r; x->r=y->l;
		if (y->l!=null)y->l->p=x;
		y->p=x->p;
		if (x->p==null)root=y;
		else if (x==x->p->l)x->p->l=y;
		else x->p->r=y;
		y->l=x; x->p=y;
		x->update();y->update();
	}
	void insert(int key,int key1){
		node *x=root,*y=null,*fa=root->p,*z=newnode(key,key1);
		if (root==null){root=z;root->col=black;return;}
		while (x!=null){
			++(y=x)->size;
			if (key<x->key)x=x->l;
			else x=x->r;
		}
		z->p=y;
		if (key<y->key)y->l=z;
		else y->r=z;
		x=z;
		while (1){
			y=x->p;
			if (y==fa){root=x;x->col=black;return;}
			if (y->col==black)return;
			z=y->p;
			if (x==y->r&&y==z->l){zag(y);zig(z);y->col=black;}
			else if (x==y->l&&y==z->r){zig(y);zag(z);y->col=black;}
			else if (x==y->l&&y==z->l){zig(z);x->col=black;x=y;}
			else if (x==y->r&&y==z->r){zag(z);x->col=black;x=y;}
		}
	}
	void replace(node *x,node *y){
		if (x->p==null)root=y;
		else if (x==x->p->l)x->p->l=y;
		else x->p->r=y;
		y->p=x->p;
	}
	void del(node *z){
		node *y=z,*x; bool c1=y->col;
		for (x=z;x!=null;x=x->p)--x->size;
		if (z->l==null){x=z->r; replace(z,z->r);}
		else if (z->r==null){x=z->l; replace(z,z->l);}
		else {
			y=fmin(z->r); c1=y->col; x=y->r;
			if (y->p==z)x->p=y;
			else {
				replace(y,y->r);
				for (node *w=y->p;w!=z;w=w->p)--w->size;
				y->r=z->r; y->r->p=y;
			}
			replace(z,y); y->l=z->l; y->l->p=y;
			y->col=z->col; y->update();
		}
		if (c1==black){
			while (x!=root&&x->col==black){
				if (x==x->p->l){
					node *w=x->p->r;
					if (w->col==red){
						w->col=black; x->p->col=red;
						zag(x->p); w=x->p->r;
					}
					if (w->l->col==black&&w->r->col==black){w->col=red; x=x->p;}
					else {
						if (w->r->col==black){
							w->l->col=black; w->col=red;
							zig(w); w=x->p->r;
						}
						w->col=x->p->col; x->p->col=black;
						w->r->col=black; zag(x->p); x=root;
					}
				}
				else {
					node *w=x->p->l;
					if (w->col==red){
						w->col=black; x->p->col=red;
						zig(x->p); w=x->p->l;
					}
					if (w->l->col==black&&w->r->col==black){w->col=red; x=x->p;}
					else {
						if (w->l->col==black){
							w->r->col=black; w->col=red;
							zag(w); w=x->p->l;
						}
						w->col=x->p->col; x->p->col=black;
						w->l->col=black; zig(x->p); x=root;
					}
				}
			}
			x->col=black;
		}
	}
	node *find(node *x,int key){
		if (x==null)return null;
		if (key==x->key)return x;
		if (key<x->key)return find(x->l,key);
		else return find(x->r,key);
	}
	node *findkth(int k){
		node *x=root;
		while (k){
			if (k==x->l->size+1)break;
			if (k<=x->l->size)x=x->l;
			else k-=x->l->size+1,x=x->r;
		}
		return x;
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
		printf("nie %d l=%d r=%d col=%d\n",x->key,x->l->key,x->r->key,x->col);
		print(x->r);
	}
	#undef red
	#undef black
}; typedef RBtree::node node;
RBtree a;
class RangeModule {
public:
	RangeModule() {
		a.clear();
	}
	void addRange(int l, int r) {
		node *x=a.succ(a.root,l-1),*y;
		while (x!=a.null&&r>=x->key){
			r=max(r,x->key1); y=a.succ(x);
			a.del(x); x=y;
		}
		y=x==a.null?a.fmax(a.root):a.pred(x);
		if (y!=a.null&&y->key1>=l)y->key1=max(y->key1,r);
		else a.insert(l,r);
	}
	bool queryRange(int l, int r) {
		node *x=a.pred(a.root,l+1);
		return x!=a.null&&x->key1>=r;
	}
	void removeRange(int l, int r) {
		node *x=a.succ(a.root,l-1),*y;
		while (x!=a.null&&r>x->key)
			if (x->key1<=r){
				y=a.succ(x);
				a.del(x); x=y;
			}
			else {
				x->key=r;
				break;
			}
		y=x==a.null?a.fmax(a.root):a.pred(x);
		if (y!=a.null){
			if (r<y->key1)a.insert(r,y->key1);
			if (y->key1>l)y->key1=l;
		}
	}
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

