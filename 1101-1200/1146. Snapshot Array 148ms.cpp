const int N=50005;
template<class T>
class RAL{
private:
	struct node; struct root_node;
	#define SIZE 10000
	static node* Newnode(const T& key,node *l,node *r){
		static node *A=NULL,*A1;
		if (A==NULL||A1==A+SIZE)A=new node[SIZE],A1=A;
		A1->key=key;A1->l=l;A1->r=r;return A1++;
	}
	static root_node* Newroot_node(const T& key,node *l,node *r,root_node *next,size_t size){
		static root_node *A=NULL,*A1;
		if (A==NULL||A1==A+SIZE)A=new root_node[SIZE],A1=A;
		A1->key=key;A1->l=l;A1->r=r;A1->next=next;A1->size=size;
		return A1++;
	}
	#undef SIZE
	struct node{
		node *l,*r;T key;
		node* modify(size_t x,const T& new_key,size_t size)const{
			if (!x)return Newnode(new_key,l,r);
			else if (x<=size)return Newnode(key,l->modify(x-1,new_key,size>>1),r);
			else return Newnode(key,l,r->modify(x-size-1,new_key,size>>1));
		}
	};
	struct root_node:public node{
		root_node *next;size_t size;
		root_node* modify(const T& new_key,size_t x)const{
			if (x<size){
				node *tmp=node::modify(x,new_key,size>>1);
				return Newroot_node(tmp->key,tmp->l,tmp->r,next,size);
			}
			else return Newroot_node(node::key,node::l,node::r,next->modify(new_key,x-size),size);
		}
	};
	struct reference{
		reference(RAL *_A,size_t _x):A(_A),x(_x){}
		T operator =(reference key){T T_key=key;A->modify(x,T_key);return T_key;}
		T operator =(const T& key){A->modify(x,key);return key;}
		operator const T&(){return A->find(x);}
		private:
		RAL *A;size_t x;
	};
	root_node *first; size_t cnt;
	RAL(root_node *_first,size_t _cnt):first(_first),cnt(_cnt){}
	void show_error()const{printf("error\n");system("pause");for (;;);}
public:
	RAL():first(NULL),cnt(0){}
	RAL(const RAL &x){*this=x;}
	RAL(size_t size){resize(size);}
	RAL(size_t size,const T& key){resize(size,key);}
	~RAL(){}
	const RAL& operator =(const RAL &x){
		first=x.first;cnt=x.cnt;return *this;
	}
	void push_front(const T& key){
		if (first==NULL||first->next==NULL||first->size!=first->next->size)
			first=Newroot_node(key,NULL,NULL,first,1),++cnt;
		else first=Newroot_node(key,first,first->next,first->next->next,first->size*2+1),++cnt;
	}
	void pop_front(){
		if (!cnt)show_error();
		if (first->size==1)first=first->next,--cnt;
		else {
			node *L=first->l,*R=first->r;
			first=Newroot_node(L->key,L->l,L->r,
				Newroot_node(R->key,R->l,R->r,first->next,first->size>>1),
				first->size>>1),--cnt;
		}
	}
	const T& find(size_t x)const{
		if (x>=cnt)show_error();
		for (root_node *now=first;now;x-=now->size,now=now->next)if (x<now->size){
			node *y=now;size_t size=now->size>>1;
			for (;;size>>=1)
				if (!x)return y->key;
				else if (x<=size)--x,y=y->l;else y=y->r,x-=size+1;
		}
		return *(new T);
	}
	void modify(size_t x,const T& key){
		if (x>=cnt)show_error();
		first=first->modify(key,x);
	}
	//const T& operator [](size_t x)const{return find(x);}
	reference operator [](size_t x){
		if (x>=cnt)show_error();
		return reference(this,x);
	}
	bool empty()const{return cnt==0;}
	size_t size(){return cnt;}
	void clear(){first=NULL;cnt=0;}
	void resize(size_t size,const T& key=*(new T())){
		clear();while (size--)push_front(key);
	}
};
RAL<int> root[N];
class SnapshotArray {
public:
	int T;
	SnapshotArray(int l) {
		T=0; root[0].resize(l);
	}
	void set(int idx, int val) {
		root[T].modify(idx,val);
	}
	int snap() {
		root[T+1]=root[T];
		return T++;
	}
	int get(int idx, int snap_id) {
		return root[snap_id].find(idx);
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();


