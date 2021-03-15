namespace Hash{
	typedef unsigned int uint;
	const uint S=13,S1=32-S,M=1996090921,_inf=~0u>>1;
	struct node{
		int x,y,t;
	}h[(1<<S)+1005];
	int T=1;
	inline void insert(int x,int y){
		node *p=h+((uint)x*M>>S1);
		for (;p->t==T;++p)
			if (p->x==x){p->y=y; return;}
		p->t=T; p->x=x; p->y=y;
	}
	inline int* find(int x){
		for (node *p=h+((uint)x*M>>S1);p->t==T;++p)
			if (p->x==x)return &p->y;
		return 0;
	}
	inline void erase(int x){  //error
		for (node *p=h+((uint)x*M>>S1);p->t==T;++p)
			if (p->x==x){p->x=_inf; return;}
	}
	/*inline void erase(int x){
		for (node *p=h+((uint)x*M>>S1);p->t==T;++p)
			if (p->x==x){
				for (node *q=p+1;q->t==T;++q)
					if (h+((uint)q->x*M>>S1)<=p){p->x=q->x; p->y=q->y; p=q;}
				p->t=0; return;
			}
	}*/
} using namespace Hash;

class MyHashMap {
public:
	/** Initialize your data structure here. */
	MyHashMap() {
		++T;
	}
	/** value will always be non-negative. */
	void put(int key, int value) {
		insert(key,value);
	}
	/** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
	int get(int key) {
		int *p=find(key);
		return p?*p:-1;
	}
	/** Removes the mapping of the specified value key if this map contains a mapping for the key */
	void remove(int key) {
		erase(key);
	}
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

