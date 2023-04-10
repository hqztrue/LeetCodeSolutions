/***************************************************
Author: hqztrue
https://github.com/hqztrue/LeetCodeSolutions
Complexity: 
If you find this solution helpful, plz give a star:)
***************************************************/

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

//fastIO
namespace Read{
	const int S=1000000;
	char _str[S],*p=_str;
	inline void read(char &c){while (*p<'!'||*p>'~')p++; c=*p++;}
	inline bool read_next(char c){while (*p!=c&&*p)++p; return *p!=0;}
	inline bool read_next_digit(){while (*p&&(*p<'0'||*p>'9'))++p; return *p!=0;}
	inline void read(int &x){
		bool sign=0; x=0; while (*p<'0'||*p>'9')if (*p++=='-')sign=1;
		while (*p>='0'&&*p<='9')x=x*10+*p++-48;if (sign)x=-x;
	}
	inline void read(double &x){
		bool sign=0; x=0; while (*p<'0'||*p>'9')if (*p++=='-')sign=1;
		while (*p>='0'&&*p<='9')x=x*10+*p++-48;
		if (*p=='.'){
			double tmp=1; ++p;
			while (*p>='0'&&*p<='9')tmp*=0.1,x+=tmp*(*p++-48);
		}
		if (sign)x=-x;
	}
	inline void read(char *s){
		while (*p<'0'||*p>'z')p++;
		while (*p>='0'&&*p<='z')*s++=*p++;
		*s=0;
	}
	inline void read_arr(int a[],int &n){
		n=0; while (*p++!='[');
		while (1){
			int x=0; bool sign=0;
			while (*p<'0'||*p>'9'&&*p!=']')if (*p++=='-')sign=1;
			if (*p==']'){++p; return;}
			while (*p>='0'&&*p<='9')x=x*10+*p++-48;
			if (sign)a[n++]=-x; else a[n++]=x;
		}
	}
	inline void read_double_arr(double a[],int &n){
		n=0; while (*p++!='[');
		while (1){
			if (*p==']'){++p; return;}
			double v=0; read(v); a[n++]=v;
		}
	}
	inline void read_char_arr(char a[],int &n){
		n=0; while (*p++!='[');
		while (1){
			while (*p<'A'||*p>'Z'&&*p<'a'&&*p!=']'||*p>'z')*p++;
			if (*p==']'){++p; return;}
			a[n++]=*p++;
			while (*p>='A'&&*p<='Z'||*p>='a'&&*p<='z')*p++;
		}
	}
	vector<int> read_int_vec(){
		vector<int> res;
		read_next('['); ++p;
		while (*p!=']'){
			int t; read(t);
			res.push_back(t);
		}
		++p; return res;
	}
	vector<vector<int> > read_int_vec2D(){
		vector<vector<int> > res;
		read_next('['); ++p;
		while (*p!=']'){
			res.emplace_back(read_int_vec());
		}
		return res;
	}
	void read_init(){fread(p,1,S,stdin);}
	
	const int S1=1000000;
	char _buf[15],_out[S1],*o=_out;
	inline void print(int x,char c=0){
		char *b=_buf;
		if (x<0)*o++='-',x=-x;
		else if (!x)*b++='0';
		while (x){*b++=x%10+48;x/=10;}
		while (b--!=_buf)*o++=*b;
		if (c)*o++=c;
	}
	inline void print(char c){*o++=c;}
	inline void print(const char *s){while (*s)*o++=*s++;}
	inline void print(int a[],int n){
		print('[');
		for (int i=0;i<n;++i){
			print(a[i]);
			if (i==n-1)print("]\n");
			else print(',');
		}
	}
	inline void flush(FILE *fout=stdout){fwrite(_out,1,o-_out,fout); o=_out;}
	struct zzy{zzy(){read_init();}}zzy;
	struct zzy1{FILE *fout; zzy1(){fout=fopen("./user.out","w");} ~zzy1(){flush(fout);}}zzy1;
}
using namespace Read;

//const uint M=mt19937(chrono::steady_clock::now().time_since_epoch().count())()|1;
//fast hash
namespace Hash{
	typedef unsigned int uint;
	const uint S=15,S1=32-S,M=1996090921,_inf=~0u>>1;
	#define H(x) ((uint)x*M>>S1)
	struct node{
		int x,y,t;
	}h[(1<<S)+105];
	int T=1;
	inline void insert(int x,int y){
		node *p=h+H(x);
		for (;p->t==T;++p)
			if (p->x==x){p->y=y; return;}
		p->t=T; p->x=x; p->y=y;
	}
	inline int* find(int x){
		for (node *p=h+H(x);p->t==T;++p)
			if (p->x==x)return &p->y;
		return 0;
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

//hash
template<class T>
struct Gethash{
	size_t operator ()(const T &x)const{return x;}
};
template<> size_t Gethash<int>::operator ()(const int &x)const{return x;}
template<> size_t Gethash<long long>::operator ()(const long long &x)const{return x^(x>>32);}
template<> size_t Gethash<float>::operator ()(const float &x)const{static Gethash<int> h; return h(*((int*)&x));}  //assert(sizeof(float)==sizeof(int));
//template<> size_t Gethash<double>::operator ()(const double &x)const{long long t=*((long long*)&x); return (t>>32)^(t>>17);}
template<> size_t Gethash<double>::operator ()(const double &x)const{static Gethash<long long> h; return h(*((long long*)&x));}
template<> size_t Gethash<char*>::operator ()(char *const &_str)const{
	const size_t seed=131;size_t hash=0;char *str=_str;
	while (*str)hash=hash*seed+*str++;
	return hash;
}
template<> size_t Gethash<string>::operator ()(const string &s)const{
	size_t hash=5381;
	for (string::const_iterator i=s.begin();i!=s.end();++i)hash+=(hash<<5)+*i;
	return hash;
}
template<> size_t Gethash<pair<int,int> >::operator ()(const pair<int,int> &x)const{return (x.first<<15)+(x.first>>8)+x.second;}
template<class Tkey,class Tvalue=bool,class _Hash=Gethash<Tkey> >
struct Hash{
	_Hash gethash;
	struct node{
		Tkey first;Tvalue second;node *next;
		node():next(0){}
		node(const Tkey &x,const Tvalue &y,node *_next=0):first(x),second(y),next(_next){}
	};
	node **v,*key;size_t len,P,max_size;
	struct iterator{
		size_t i;node *j;Hash<Tkey,Tvalue,_Hash> *H;
		iterator(){}
		iterator(size_t _i,node *_j,Hash<Tkey,Tvalue,_Hash> *_H):i(_i),j(_j),H(_H){go();}
		void go(){
			if (i<H->P&&!j){
				for (++i;i<H->P&&!H->v[i];++i);
				if (i==H->P)j=0;else j=H->v[i];
			}
		}
		node operator *(){return *j;}
		iterator& operator ++(){j=j->next;go();return *this;}
		iterator operator ++(int){iterator res=*this;++*this;return res;}
		iterator& operator --(){
			if (j==H->v[i]){for (--i;!H->v[i];--i);for (j=H->v[i];j->next;j=j->next);}
			else {node *k=j;for (j=H->v[i];j->next!=k;j=j->next);}
			return *this;
		}
		iterator operator --(int){iterator res=*this;--*this;return res;}
		node* operator ->()const{return j;}
		inline friend bool operator ==(const iterator &x,const iterator &y){return x.i==y.i&&x.j==y.j;}
		inline friend bool operator !=(const iterator &x,const iterator &y){return x.i!=y.i||x.j!=y.j;}
		bool operator !(){return i==H->P;}
		operator bool(){return i!=H->P;}
	};
	iterator begin(){return iterator(0,v[0],this);}
	iterator end(){return iterator(P,0,this);}
	void operator =(const Hash<Tkey,Tvalue,_Hash> &y){
		free(); len=y.len; P=y.P; max_size=y.max_size;
		key=new node[max_size+1]; memcpy(key,y.key,sizeof(node)*(len+1));
		ptrdiff_t d=key-y.key;
		for (int i=0;i<=len;++i)if (key[i].next)key[i].next+=d;
		v=new node*[P]; for (int i=0;i<P;++i)v[i]=y.v[i]?y.v[i]+d:y.v[i];
	}
	void Grow(){
		static double rate=1.7; Hash<Tkey,Tvalue,_Hash> res(max_size*2,size_t(rate*max_size*2));
		for (size_t i=0;i<P;++i)
			for (node *j=v[i];j;j=j->next)res.insert(j->first,j->second);
		free(); memcpy(this,&res,sizeof(Hash<Tkey,Tvalue,_Hash>));
	}
	void build(size_t L,size_t p){
		P=p;len=0;max_size=L;++L;key=new node[L];
		v=new node*[P];memset(v,0,sizeof(node*)*P);
	}
	Hash(size_t len=3,size_t p=5){build(len,p);}
	void clear(){len=0;memset(v,0,sizeof(node*)*P);}
	//void clear(){free();build(3,5);}
	Tvalue& insert(const Tkey &x,const Tvalue &y=Tvalue()){
		//if (&find_(x)){Tvalue *null=NULL;return *null;}
		if (len==max_size)Grow(); size_t x1=gethash(x)%P;
		key[++len]=node(x,y,v[x1]);v[x1]=key+len;
		return key[len].second;
	}
	void insert_(const Tkey &x,const Tvalue &y=Tvalue()){
		size_t x1=gethash(x)%P;
		for (node *i=v[x1];i;i=i->next)
			if (i->first==x){i->second=y; return;}
		if (len==max_size)Grow(),x1=gethash(x)%P;
		key[++len]=node(x,y,v[x1]);v[x1]=key+len;
	}
	Tvalue& insert(const pair<Tkey,Tvalue> &p){return insert(p.first,p.second);}
	int erase(const Tkey &x){
		size_t x1=gethash(x)%P;
		for (node *i=v[x1],*pre=0;i;pre=i,i=i->next)if (i->first==x){
			if (!pre)v[x1]=i->next;else pre->next=i->next;
			return 1;
		}
		return 0;
	}
	void erase(iterator x){
		if (x.j==v[x.i])v[x.i]=x->next;
		else {node *y=x->next;--x;x->next=y;}
	}
	Tvalue* find_(const Tkey &x){
		size_t x1=gethash(x)%P;
		for (node *i=v[x1];i;i=i->next)
			if (i->first==x)return &i->second;
		return NULL;
	}
	iterator find(const Tkey &x){
		size_t x1=gethash(x)%P;
		for (node *i=v[x1];i;i=i->next)
			if (i->first==x)return iterator(x1,i,this);
		return end();
	}
	Tvalue& operator [](const Tkey &x){
		Tvalue *res=find_(x);if (res==0)return insert(x);return *res;
	}
	bool empty(){return len==0;}
	size_t size(){return len;}
	size_t count(const Tkey &x){return find_(x)?1:0;}
	void free(){delete[] key;delete[] v;}
	~Hash(){}  //free();
	/*void print(){
		for (size_t i=0;i<P;++i)
			for (node *j=v[i];j;j=j->next)printf("H[%d]=%d\n",j->first,j->second);
	}*/
};

template<int S>
struct BitSet{
	#define W 6
	#define mask 63
	#define get_size(n) ((n)<1?0:((n)+mask)>>W)
	typedef unsigned long long uint;  //typedef unsigned int uint;
	uint a[get_size(S)];int size;
	void reset(){memset(a,0,sizeof(uint)*size);}
	BitSet():size(get_size(S)){reset();}
	BitSet(uint x):size(get_size(S)){reset();a[0]=x;}
	BitSet(const BitSet<S> &x):size(get_size(S)){*this=x;}
	BitSet& set(int x,int y){
		//if (y<0||y>1){printf("error!\n");return *this;}
		int X=x>>W,Y=x&mask;
		if (y)a[X]|=1ull<<Y;else a[X]&=~(1ull<<Y);
		return *this;
	}
	int find(int x)const{int X=x>>W,Y=x&mask;return (a[X]>>Y)&1ull;}
	int operator [](int x)const{return find(x);}
	BitSet& operator =(const BitSet &y){
		memcpy(a,y.a,sizeof(uint)*size);
		return *this;
	}
	BitSet<S> operator |(const BitSet<S> &y)const{return BitSet<S>(*this)|=y;}
	BitSet<S> operator &(const BitSet<S> &y)const{return BitSet<S>(*this)&=y;}
	BitSet<S> operator ^(const BitSet<S> &y)const{return BitSet<S>(*this)^=y;}
	BitSet<S> operator +(const BitSet<S> &y)const{return BitSet<S>(*this)+=y;}
	BitSet<S> operator -(const BitSet<S> &y)const{return BitSet<S>(*this)-=y;}
	BitSet<S> operator <<(int x)const{return BitSet<S>(*this)<<=x;}
	BitSet<S> operator >>(int x)const{return BitSet<S>(*this)>>=x;}
	BitSet<S> operator ~()const{return BitSet<S>(*this).flip();}
	BitSet<S>& operator =(const char *s){
		memset(a,0,sizeof(uint)*size);
		for (int i=0;i<S;++i){
			if (s[i]!='0'&&s[i]!='1')break;
			int X=i>>W,Y=i&mask;
			if (s[i]=='1')a[X]|=1ull<<Y;
		}
		return *this;
	}
	BitSet<S>& operator =(const int *s){
		memset(a,0,sizeof(uint)*size);
		for (int i=0;i<S;++i){
			if (s[i]!=0&&s[i]!=1)break;
			int X=i>>W,Y=i&mask;
			if (s[i]==1)a[X]|=1ull<<Y;
		}
		return *this;
	}
	BitSet<S>& operator <<=(int x){
		int shift=x>>W; int delta=x&mask,delta1=mask+1-delta;
		if (!x)return *this;
		if (delta==0)for (uint *p=a+size-1,*q=p-shift,*end=a+shift-1;p!=end;--p,--q)*p=*q;
		else {
			for (uint *p=a+size-1,*q1=p-shift,*q2=p-shift-1,*end=a+shift;p!=end;--p,--q1,--q2)*p=(*q1<<delta)|(*q2>>delta1);
			a[shift]=a[0]<<delta;
		}
		memset(a,0,sizeof(uint)*shift); //for (uint *p=a,*end=a+shift;p!=end;++p)*p=0;
		return *this;
	}
	BitSet<S>& operator >>=(int x){
		int shift=x>>W; int delta=x&mask,delta1=mask+1-delta;
		if (!x)return *this;
		correction();
		if (delta==0)for (uint *p=a,*q=p+shift,*end=a+size-shift;p!=end;++p,++q)*p=*q;
		else {
			for (uint *p=a,*q1=p+shift,*q2=p+shift+1,*end=a+size-shift-1;p!=end;++p,++q1,++q2)*p=(*q1>>delta)|(*q2<<delta1);
			a[size-shift-1]=a[size-1]>>delta;
		}
		memset(a+size-shift,0,sizeof(uint)*shift);
		return *this;
	}
	BitSet<S>& operator |=(const BitSet<S> &y){
		uint *startA=a;const uint *startB=y.a,*endA=a+size;
		while (startA!=endA){*startA|=*startB;++startA;++startB;}
		//for (int i=0;i<size;++i)a[i]|=y.a[i];
		return *this;
	}
	/*BitSet<S>& operator |=(const BitSet<S> &y){
		uint *p0=a,*p1=p0+1,*p2=p0+2,*p3=p0+3;const uint *q0=y.a,*q1=q0+1,*q2=q0+2,*q3=q0+3,*pend=a+((size>>2)<<2);
		while (p0!=pend){
			*p0|=*q0; p0+=4; q0+=4;
			*p1|=*q1; p1+=4; q1+=4;
			*p2|=*q2; p2+=4; q2+=4;
			*p3|=*q3; p3+=4; q3+=4;
		}
		for (int i=0;i<(size&3);++i)*p0++|=*q0++;
		return *this;
	}*/
	BitSet<S>& operator &=(const BitSet<S> &y){
		uint *startA=a;const uint *startB=y.a,*endA=a+size;
		while (startA!=endA){*startA&=*startB;++startA;++startB;}
		return *this;
	}
	BitSet<S>& operator ^=(const BitSet<S> &y){
		uint *startA=a;const uint *startB=y.a,*endA=a+size;
		while (startA!=endA){*startA^=*startB;++startA;++startB;}
		return *this;
	}
	BitSet<S>& operator +=(const BitSet<S> &y){
		uint t=0,*p=a,*end=a+size; const uint *q=y.a;
		while (p!=end){
			uint p1=*p; *p=p1+*q+t;
			t=(*p<p1)||(*q+t<t);
			++p; ++q;
		}
		return *this;
	}
	BitSet<S>& operator -=(const BitSet<S> &y){
		uint t=0,*p=a,*end=a+size; const uint *q=y.a;
		while (p!=end){
			uint p1=*p; *p=p1-*q-t;
			t=(*p>p1)||(*q+t<t);
			++p; ++q;
		}
		return *this;
	}
	operator bool(){return count()>0;}
	BitSet<S>& flip(){
		//for (uint *start=a,*end=a+size;start!=end;*start=~*start,++start);
		uint *p0=a,*p1=p0+1,*p2=p0+2,*p3=p0+3,*pend=a+((size>>2)<<2);
		while (p0!=pend){
			*p0=~*p0; p0+=4;
			*p1=~*p1; p1+=4;
			*p2=~*p2; p2+=4;
			*p3=~*p3; p3+=4;
		}
		for (int i=0;i<(size&3);++i,++p0)*p0=~*p0;
		return *this;
	}
	//void flip(){*this=~*this;}
	void flip(int x){a[x>>W]^=1ull<<(x&mask);}
	/*inline friend int popcount(uint x){
		x-=(x&0xaaaaaaaaaaaaaaaaull)>>1;
		x=((x&0xccccccccccccccccull)>>2)+(x&0x3333333333333333ull);
		x=((x>>4)+x)&0x0f0f0f0f0f0f0f0full;
		return (x*0x0101010101010101ull)>>56;
	}*/
	int count(){
		int res=0;
		correction();
		for (int i=0;i<size;++i)res+=__builtin_popcountll(a[i]);  //popcount
		return res;
	}
	int clz(){
		correction();
		int res=0;
		if (a[size-1])res=__builtin_clzll(a[size-1])-(mask+1-(S&mask));
		else {
			res+=S&mask;
			for (int i=size-2;i>=0;--i)
				if (a[i]){res+=__builtin_clzll(a[i]); break;}
				else res+=mask+1;
		}
		return res;
	}
	int ctz(){
		correction();
		int res=0;
		for (int i=0;i<size;++i)
			if (a[i]){res+=__builtin_ctzll(a[i]); break;}
			else res+=mask+1;
		return min(res,S);
	}
	int ffs(){
		int res=ctz()+1;
		if (res==S+1)res=0;
		return res;
	}
	int _Find_first(){return ffs();}
	int _Find_next(int x){
		correction();
		if (x<0){
			if (a[0]&1)return 0;
			x=0;
		}
		int d=(x&mask)+1;
		if (d<=mask&&a[x>>W]>>d)return __builtin_ctzll(a[x>>W]>>d)+d+(x&~mask);
		for (int i=(x>>W)+1;i<size;++i)
			if (a[i])return (i<<W)+__builtin_ctzll(a[i]);
		return S;
	}
	uint to_uint(){
		correction();
		return a[0];
	}
	void print()const{
		for (int i=0;i<size;++i)
			for (int j=0;j<=mask&&(i<<W)+j+1<=S;++j)printf("%I64d",(a[i]>>j)&1ull);
		printf("\n");
	}
	void correction(){if (S&mask)a[size-1]&=(1ull<<(S&mask))-1;}
	#undef mask
	#undef W
	#undef get_size
};

//dynamic length
struct BitSet{
	#define W 6
	#define mask 63
	#define get_size(n) ((n)<1?0:((n)+mask)>>W)
	typedef unsigned long long uint;  //typedef unsigned int uint;
	uint *a;int size,S;
	void reset(){memset(a,0,sizeof(uint)*size);}
	BitSet(int S=1):S(S),size(get_size(S)){
		a=new uint[get_size(S)]; reset();
	}
	void resize(int S){
		this->S=S; size=get_size(S);
		delete[] a; a=new uint[get_size(S)]; reset();
	}
	//BitSet(uint x):size(get_size(S)){reset();a[0]=x;}
	BitSet(const BitSet &x):size(x.size),S(x.S){a=new uint[size]; *this=x;}
	BitSet& set(int x,int y){
		//if (y<0||y>1){printf("error!\n");return *this;}
		int X=x>>W,Y=x&mask;
		if (y)a[X]|=1ull<<Y;else a[X]&=~(1ull<<Y);
		return *this;
	}
	int find(int x)const{int X=x>>W,Y=x&mask;return (a[X]>>Y)&1ull;}
	int operator [](int x)const{return find(x);}
	BitSet& operator =(const BitSet &y){
		memcpy(a,y.a,sizeof(uint)*size);
		return *this;
	}
	BitSet operator |(const BitSet &y)const{return BitSet(*this)|=y;}
	BitSet operator &(const BitSet &y)const{return BitSet(*this)&=y;}
	BitSet operator ^(const BitSet &y)const{return BitSet(*this)^=y;}
	BitSet operator +(const BitSet &y)const{return BitSet(*this)+=y;}
	BitSet operator -(const BitSet &y)const{return BitSet(*this)-=y;}
	BitSet operator <<(int x)const{return BitSet(*this)<<=x;}
	BitSet operator >>(int x)const{return BitSet(*this)>>=x;}
	BitSet operator ~()const{return BitSet(*this).flip();}
	BitSet& operator =(const char *s){
		memset(a,0,sizeof(uint)*size);
		for (int i=0;i<S;++i){
			if (s[i]!='0'&&s[i]!='1')break;
			int X=i>>W,Y=i&mask;
			if (s[i]=='1')a[X]|=1ull<<Y;
		}
		return *this;
	}
	BitSet& operator =(const int *s){
		memset(a,0,sizeof(uint)*size);
		for (int i=0;i<S;++i){
			if (s[i]!=0&&s[i]!=1)break;
			int X=i>>W,Y=i&mask;
			if (s[i]==1)a[X]|=1ull<<Y;
		}
		return *this;
	}
	BitSet& operator <<=(int x){
		int shift=x>>W; int delta=x&mask,delta1=mask+1-delta;
		if (!x)return *this;
		if (delta==0)for (uint *p=a+size-1,*q=p-shift,*end=a+shift-1;p!=end;--p,--q)*p=*q;
		else {
			//printf("s %d\n",shift);
			for (uint *p=a+size-1,*q1=p-shift,*q2=p-shift-1,*end=a+shift;p!=end;--p,--q1,--q2)*p=(*q1<<delta)|(*q2>>delta1);
			a[shift]=a[0]<<delta;
		}
		memset(a,0,sizeof(uint)*shift); //for (uint *p=a,*end=a+shift;p!=end;++p)*p=0;
		return *this;
	}
	BitSet& operator >>=(int x){
		int shift=x>>W; int delta=x&mask,delta1=mask+1-delta;
		if (!x)return *this;
		correction();
		if (delta==0)for (uint *p=a,*q=p+shift,*end=a+size-shift;p!=end;++p,++q)*p=*q;
		else {
			for (uint *p=a,*q1=p+shift,*q2=p+shift+1,*end=a+size-shift-1;p!=end;++p,++q1,++q2)*p=(*q1>>delta)|(*q2<<delta1);
			a[size-shift-1]=a[size-1]>>delta;
		}
		memset(a+size-shift,0,sizeof(uint)*shift);
		return *this;
	}
	BitSet& operator |=(const BitSet &y){
		uint *startA=a;const uint *startB=y.a,*endA=a+size;
		while (startA!=endA){*startA|=*startB;++startA;++startB;}
		//for (int i=0;i<size;++i)a[i]|=y.a[i];
		return *this;
	}
	/*BitSet& operator |=(const BitSet &y){
		uint *p0=a,*p1=p0+1,*p2=p0+2,*p3=p0+3;const uint *q0=y.a,*q1=q0+1,*q2=q0+2,*q3=q0+3,*pend=a+((size>>2)<<2);
		while (p0!=pend){
			*p0|=*q0; p0+=4; q0+=4;
			*p1|=*q1; p1+=4; q1+=4;
			*p2|=*q2; p2+=4; q2+=4;
			*p3|=*q3; p3+=4; q3+=4;
		}
		for (int i=0;i<(size&3);++i)*p0++|=*q0++;
		return *this;
	}*/
	BitSet& operator &=(const BitSet &y){
		uint *startA=a;const uint *startB=y.a,*endA=a+size;
		while (startA!=endA){*startA&=*startB;++startA;++startB;}
		return *this;
	}
	BitSet& operator ^=(const BitSet &y){
		uint *startA=a;const uint *startB=y.a,*endA=a+size;
		while (startA!=endA){*startA^=*startB;++startA;++startB;}
		return *this;
	}
	BitSet& operator +=(const BitSet &y){
		uint t=0,*p=a,*end=a+size; const uint *q=y.a;
		while (p!=end){
			uint p1=*p; *p=p1+*q+t;
			t=(*p<p1)||(*q+t<t);
			++p; ++q;
		}
		return *this;
	}
	BitSet& operator -=(const BitSet &y){
		uint t=0,*p=a,*end=a+size; const uint *q=y.a;
		while (p!=end){
			uint p1=*p; *p=p1-*q-t;
			t=(*p>p1)||(*q+t<t);
			++p; ++q;
		}
		return *this;
	}
	operator bool(){return count()>0;}
	BitSet& flip(){
		//for (uint *start=a,*end=a+size;start!=end;*start=~*start,++start);
		uint *p0=a,*p1=p0+1,*p2=p0+2,*p3=p0+3,*pend=a+((size>>2)<<2);
		while (p0!=pend){
			*p0=~*p0; p0+=4;
			*p1=~*p1; p1+=4;
			*p2=~*p2; p2+=4;
			*p3=~*p3; p3+=4;
		}
		for (int i=0;i<(size&3);++i,++p0)*p0=~*p0;
		return *this;
	}
	//void flip(){*this=~*this;}
	void flip(int x){a[x>>W]^=1ull<<(x&mask);}
	/*inline friend int popcount(uint x){
		x-=(x&0xaaaaaaaaaaaaaaaaull)>>1;
		x=((x&0xccccccccccccccccull)>>2)+(x&0x3333333333333333ull);
		x=((x>>4)+x)&0x0f0f0f0f0f0f0f0full;
		return (x*0x0101010101010101ull)>>56;
	}*/
	int count(){
		int res=0;
		correction();
		for (int i=0;i<size;++i)res+=__builtin_popcountll(a[i]);  //popcount
		return res;
	}
	int clz(){
		correction();
		int res=0;
		if (a[size-1])res=__builtin_clzll(a[size-1])-(mask+1-(S&mask));
		else {
			res+=S&mask;
			for (int i=size-2;i>=0;--i)
				if (a[i]){res+=__builtin_clzll(a[i]); break;}
				else res+=mask+1;
		}
		return res;
	}
	int ctz(){
		correction();
		int res=0;
		for (int i=0;i<size;++i)
			if (a[i]){res+=__builtin_ctzll(a[i]); break;}
			else res+=mask+1;
		return min(res,S);
	}
	int ffs(){
		int res=ctz()+1;
		if (res==S+1)res=0;
		return res;
	}
	int _Find_first(){return ffs();}
	int _Find_next(int x){
		correction();
		if (x<0){
			if (a[0]&1)return 0;
			x=0;
		}
		int d=(x&mask)+1;
		if (d<=mask&&a[x>>W]>>d)return __builtin_ctzll(a[x>>W]>>d)+d+(x&~mask);
		for (int i=(x>>W)+1;i<size;++i)
			if (a[i])return (i<<W)+__builtin_ctzll(a[i]);
		return S;
	}
	uint to_uint(){
		correction();
		return a[0];
	}
	void print()const{
		for (int i=0;i<size;++i)
			for (int j=0;j<=mask&&(i<<W)+j+1<=S;++j)printf("%I64d",(a[i]>>j)&1ull);
		printf("\n");
	}
	void correction(){if (S&mask)a[size-1]&=(1ull<<(S&mask))-1;}
	~BitSet(){delete[] a;}
	#undef mask
	#undef W
	#undef get_size
};

template<int N>
struct LinearDisjointSet{
	int f[N/W+2]; uint c[N/W+2];
	void init(int n){for (int i=0;i<=n/W+1;++i)f[i]=i,c[i]=~0;}
	int _find(int x){
		if (f[x]==x)return x;
		return f[x]=_find(f[x]);
	}
	void _del(int x){f[x]=x+1;}
	int find(int x){
		int y=x/W,z=x%W; uint t=c[y]>>z<<z;
		if (t)return y*W+__builtin_ctz(t);
		y=_find(y+1); return y*W+__builtin_ctz(c[y]);
	}
	void del(int x){int y=x/W;c[y]&=~(1u<<x%W);if (!c[y])_del(y);}
};
LinearDisjointSet<N> D;

void radix_sort(int A[],int l,int r){  //a[i]>=0
	//const int base=65535,W=16;
	const int base=2047,W=11;
	//const int base=255,W=8;
	const int T=(32-1)/W+1;
	static int B[N],s[base+1];
	A+=l-1;r-=l-1;l=1;
	int *a=A,*b=B,x=0;
	for (int i1=1;i1<=T;++i1){
		for (int i=0;i<=base;++i)s[i]=0;
		for (int i=1;i<=r;++i)++s[a[i]>>x&base];
		for (int i=1;i<=base;++i)s[i]+=s[i-1];
		for (int i=r;i>=1;--i)b[s[a[i]>>x&base]--]=a[i];
		int *tmp=a;a=b;b=tmp;
		x+=W;
	}
	if (a!=A)for (int i=1;i<=r;++i)A[i]=a[i];
}

namespace wTrie{
	typedef unsigned int uint;
	const int N=1<<20,W=32;  //[0,2^20)
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
		if (!a4)return -1;
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

__attribute__((no_sanitize_address,no_sanitize_memory))
__attribute__((target("avx,avx2,avx512bw")))

//main
int _main=[](){
	//FILE *fout=fopen("./user.out","w");
	while (1){
		if (!read_next('['))break;
		
	}
	exit(0);
	return 0;
}();

