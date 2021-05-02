typedef unsigned int uint;
const int N=200005,W=32;
namespace wTrie{
	uint a1[N/W+5],a2[N/W/W+5],a3[N/W/W/W+5],a4;
	#define max_bit(x) 31-__builtin_clz(x)
	#define min_bit(x) __builtin_ctz(x)
	#define get_bit(x) (1u<<((x)&31u))
	#define get_bit1(x) (1u<<(x))
	void init(int n=N){
		memset(a1,0,sizeof(uint)*(n/W+1));
		memset(a2,0,sizeof(uint)*(n/W/W+1));
		memset(a3,0,sizeof(uint)*(n/W/W/W+1));
		a4=0;
	}
	void init1(int n=N){
		memset(a1,0xFF,sizeof(uint)*(n/W+1));
		memset(a2,0xFF,sizeof(uint)*(n/W/W+1));
		memset(a3,0xFF,sizeof(uint)*(n/W/W/W+1));
		a4=0xFFFFFFFF;
	}
	inline bool find(uint x){
		return (a1[x>>5]>>(x&31))&1;
	}
	inline void add(uint x){
		a1[x>>5]|=get_bit(x);
		a2[x>>10]|=get_bit(x>>5);
		a3[x>>15]|=get_bit(x>>10);
		a4|=get_bit1(x>>15);
	}
	inline void del(uint x){
		if (a1[x>>5]&get_bit(x))
			if (!(a1[x>>5]-=get_bit(x)))
				if (!(a2[x>>10]-=get_bit(x>>5)))
					if (!(a3[x>>15]-=get_bit(x>>10)))
						a4-=get_bit1(x>>15);
	}
	inline int get_min(){
		//if (!a4)return -1;
		uint x=min_bit(a4);
		x=(x<<5)+min_bit(a3[x]);
		x=(x<<5)+min_bit(a2[x]);
		return (x<<5)+min_bit(a1[x]);
	}
	inline int get_max(){
		if (!a4)return -1;
		uint x=max_bit(a4);
		x=(x<<5)+max_bit(a3[x]);
		x=(x<<5)+max_bit(a2[x]);
		return (x<<5)+max_bit(a1[x]);
	}
	inline int pred(uint x){
		#define P(x) ((x)&0xFFFFFFFE0u)
		#define pred_bit(x,y) ((x)&get_bit(y)-1)
		if (pred_bit(a1[x>>5],x))return P(x)+max_bit(pred_bit(a1[x>>5],x));
		x>>=5;
		if (pred_bit(a2[x>>5],x)){
			x=P(x)+max_bit(pred_bit(a2[x>>5],x));
			return (x<<5)+max_bit(a1[x]);
		}
		x>>=5;
		if (pred_bit(a3[x>>5],x)){
			x=P(x)+max_bit(pred_bit(a3[x>>5],x));
			x=(x<<5)+max_bit(a2[x]);
			return (x<<5)+max_bit(a1[x]);
		}
		x>>=5;
		if (pred_bit(a4,x)){
			x=max_bit(pred_bit(a4,x));
			x=(x<<5)+max_bit(a3[x]);
			x=(x<<5)+max_bit(a2[x]);
			return (x<<5)+max_bit(a1[x]);
		}
		return -1;
	}
	inline int succ(uint x){
		#define succ_bit(x,y) ((x)>>((y)&31))
		if (succ_bit(a1[x>>5],x)>1)return x+1+min_bit(succ_bit(a1[x>>5],x+1));
		x>>=5;
		if (succ_bit(a2[x>>5],x)>1){
			x=x+1+min_bit(succ_bit(a2[x>>5],x+1));
			return (x<<5)+min_bit(a1[x]);
		}
		x>>=5;
		if (succ_bit(a3[x>>5],x)>1){
			x=x+1+min_bit(succ_bit(a3[x>>5],x+1));
			x=(x<<5)+min_bit(a2[x]);
			return (x<<5)+min_bit(a1[x]);
		}
		x>>=5;
		if (succ_bit(a4,x)>1){
			x=x+1+min_bit(succ_bit(a4,x+1));
			x=(x<<5)+min_bit(a3[x]);
			x=(x<<5)+min_bit(a2[x]);
			return (x<<5)+min_bit(a1[x]);
		}
		return -1;
	}
} using namespace wTrie;
template<class T>
struct Vector{
	typedef T* it;typedef it iterator;
	it Mem,End,MemEnd;
	Vector(){Mem=new T[1];End=Mem;MemEnd=Mem+1;}
	Vector(const Vector<T> &v){Mem=0;*this=v;}
	Vector(int n){
		Mem=new int[n];End=Mem+n;MemEnd=Mem+n;
	}
	Vector(int n,T x){
		Mem=new T[n];End=Mem+n;MemEnd=Mem+n;
		for (int i=0;i<n;++i)Mem[i]=x;
	}
	Vector<T>& operator =(const Vector<T> &v){
		if (Mem)delete[] Mem; Mem=new T[v.capacity()];
		MemEnd=Mem+v.capacity(); End=Mem+v.size();
		memcpy(Mem,v.Mem,sizeof(T)*v.size());
		return *this;
	}
	Vector<T>& operator =(const vector<T> &v){
		delete[] Mem; Mem=new T[v.capacity()];
		MemEnd=Mem+v.capacity(); End=Mem+v.size();
		memcpy(Mem,v.begin(),sizeof(T)*v.size());
		return *this;
	}
	void to_vector(vector<T> &v){
		v.resize(End-Mem);
		for (int i=0;i<End-Mem;++i)v[i]=Mem[i];
	}
	void Grow(){
		int s=MemEnd-Mem;it NewMem=new T[s*2];
		memcpy(NewMem,Mem,sizeof(T)*s);delete[] Mem;
		Mem=NewMem;End=Mem+s;MemEnd=Mem+s*2;
	}
	void Shrink(){
		int s=MemEnd-Mem,l=End-Mem;it NewMem=new T[s>>1];
		memcpy(NewMem,Mem,sizeof(T)*(s>>1));delete[] Mem;
		Mem=NewMem;End=Mem+l;MemEnd=Mem+(s>>1);
	}
	void push_back(const T &x){
		if (End==MemEnd)Grow();*(End++)=x;
	}
	int pop_back(){
		--End; int res=*End;
		if (End-Mem<(MemEnd-Mem)>>2)Shrink();
		return res;
	}
	it begin(){return Mem;}
	it end(){return End;}
	int size()const{return End-Mem;}
	int capacity()const{return MemEnd-Mem;}
	void resize(int _size){while (size()<_size)Grow();End=Mem+_size;}
	void clear(){End=Mem;}
	T& operator [](int id){return Mem[id];}
	const T& operator [](int id)const{return Mem[id];}
	~Vector(){delete[] Mem;}
};
template<> Vector<int>::Vector(int n){
	Mem=new int[n];End=Mem+n;MemEnd=Mem+n;
	memset(Mem,0,sizeof(int)*n);
}
template<> Vector<long long>::Vector(int n){
	Mem=new long long[n];End=Mem+n;MemEnd=Mem+n;
	memset(Mem,0,sizeof(long long)*n);
}
template<> Vector<double>::Vector(int n){
	Mem=new double[n];End=Mem+n;MemEnd=Mem+n;
	memset(Mem,0,sizeof(double)*n);
}
Vector<int> v[N];
int c,m;
class DinnerPlates {
public:
	DinnerPlates(int capacity) {
		init1(); c=capacity;
	}
	void push(int x) {
		int id=get_min(); m=max(m,id);
		v[id].push_back(x);
		if (v[id].size()==c)del(id);
	}
	int pop() {
		while (m>=0&&!v[m].size())--m;
		return m==-1?-1:popAtStack(m);
	}
	int popAtStack(int id) {
		if (v[id].size()){
			int res=v[id].pop_back();
			if (v[id].size()==c-1)add(id);
			return res;
		}
		else return -1;
	}
	~DinnerPlates(){
		for (int i=0;i<=m;++i)v[i].clear();
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

