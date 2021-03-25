const int N=2005,inf=~0u>>1;
struct treap{
	struct node{
		node *l,*r;int key,key1,fix,size;
		void update(){
			size=l->size+r->size+1;
		}
	};
	inline static int _rand(){static unsigned int x=31253125;x+=(x<<4)+(x<<21)+1;return x&=0x7fffffff;}
	node a[N],*root,*null;int len;
	void clear(){
		len=0;root=null=new node;  //srand(time(0));
		null->l=null->r=null;null->size=0;null->fix=inf;
	}
	treap(){clear();}
	node *newnode(int key,int key1){
		node *x=a+(++len);x->l=x->r=null;
		x->size=1;x->key=key;x->key1=key1;x->fix=_rand();
		return x;
	}
	void zig(node *&x){
		node *y=x->l;x->l=y->r;y->r=x;
		x->update();y->update();x=y;
	}
	void zag(node *&x){
		node *y=x->r;x->r=y->l;y->l=x;
		x->update();y->update();x=y;
	}
	void insert(node *&x,int key,int key1){
		if (x==null)x=newnode(key,key1);
		else if (key<=x->key){
			insert(x->l,key,key1);++x->size;
			if (x->l->fix<x->fix)zig(x);
		}
		else {
			insert(x->r,key,key1);++x->size;
			if (x->r->fix<x->fix)zag(x);
		}
	}
	node *find(node *x,int key){
		if (x==null)return null;
		if (key==x->key)return x;
		if (key<x->key)return find(x->l,key);
		else return find(x->r,key);
	}
	void del(node *&x,int key){
		if (x==null)return;
		if (x->key==key)
			if (x->l==null||x->r==null)
				if (x->l==null)x=x->r;
				else x=x->l;
			else if (x->l->fix<x->r->fix)
					zig(x),del(x->r,key),x->update();
				else zag(x),del(x->l,key),x->update();
		else if (key<x->key)del(x->l,key),x->update();
			else del(x->r,key),x->update();
	}
	node *findkth(node *root,int k){
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
	node *fmin(node *x){while (x->l!=null)x=x->l;return x;}
	node *fmax(node *x){while (x->r!=null)x=x->r;return x;}
	void print(node *x){
		if (x==null)return;
		print(x->l);
		printf("nie %d %d\n",x->key,x->key1);
		print(x->r);
	}
}; typedef treap::node node;
treap a;
class RangeModule {
public:
	RangeModule() {
		a.clear();
	}
	void addRange(int l, int r) {
		node *x=a.succ(a.root,l-1),*y;
		while (x!=a.null&&r>=x->key){
			r=max(r,x->key1); y=a.succ(a.root,x->key);
			a.del(a.root,x->key); x=y;
		}
		y=x==a.null?a.fmax(a.root):a.pred(a.root,x->key);
		if (y!=a.null&&y->key1>=l)y->key1=max(y->key1,r);
		else a.insert(a.root,l,r);
	}
	bool queryRange(int l, int r) {
		node *x=a.pred(a.root,l+1);
		return x!=a.null&&x->key1>=r;
	}
	void removeRange(int l, int r) {
		node *x=a.succ(a.root,l-1),*y;
		while (x!=a.null&&r>x->key)
			if (x->key1<=r){
				y=a.succ(a.root,x->key);
				a.del(a.root,x->key); x=y;
			}
			else {
				x->key=r;
				break;
			}
		y=x==a.null?a.fmax(a.root):a.pred(a.root,x->key);
		if (y!=a.null){
			if (r<y->key1)a.insert(a.root,r,y->key1);
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

