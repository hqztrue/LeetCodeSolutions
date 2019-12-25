//IO
int _IO=[](){
	std::ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

template<class T>
struct Vector{
	typedef T* it;typedef it iterator;
	it Mem,End,MemEnd;
	Vector(){Mem=new T[3];End=Mem;MemEnd=Mem+3;}
	Vector(const Vector<T> &v){*this=v;}
	Vector(int n){
		Mem=new int[n];End=Mem+n;MemEnd=Mem+n;
	}
	Vector(int n,T x){
		Mem=new T[n];End=Mem+n;MemEnd=Mem+n;
		for (int i=0;i<n;++i)Mem[i]=x;
	}
	Vector<T>& operator =(const Vector<T> &v){
		delete[] Mem; Mem=new T[v.capacity()];
		MemEnd=Mem+v.capacity(); End=Mem+v.size();
		memcpy(Mem,v.Mem,sizeof(T)*v.size());
	}
	Vector<T>& operator =(const vector<T> &v){
		delete[] Mem; Mem=new T[v.capacity()];
		MemEnd=Mem+v.capacity(); End=Mem+v.size();
		memcpy(Mem,v.begin(),sizeof(T)*v.size());
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
	void pop_back(){
		--End;if (End-Mem<(MemEnd-Mem)>>2)Shrink();
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

const int N=20005,S=150;
int n;
Vector<int> V[N];
inline int _rand(){static unsigned int x=31253125;x+=(x<<4)+1;x&=0x7fffffff;return x;}  //x+=(x<<4)+(x<<21)+1;
class MajorityChecker {
public:
	int *a;
	MajorityChecker(vector<int>& arr) {
        a=&arr[0]; register int *a=this->a; n=arr.size();
		for (register int i=0;i<n;++i)V[a[i]].clear();
		for (register int i=0;i<n;++i)V[a[i]].push_back(i);
    }
    int query(int left, int right, int threshold) {
		register int *a=this->a;
        const int M=8;  //20
		for (register int i=0;i<M;++i){
			register int t=left+_rand()%(right-left+1);
			Vector<int> &v=V[a[t]];
			register int *p=lower_bound(v.Mem,v.End,left),*p1=p+threshold-1;  //upper_bound(v.begin(),v.end(),right)
			if (p1<v.End&&*p1<=right)return a[t];
		}
		return -1;
    }
};


