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
	inline void read_char_arr(char a[],int &n){
		n=0; while (*p++!='[');
		while (1){
			while (*p<'A'||*p>'Z'&&*p<'a'&&*p!=']'||*p>'z')*p++;
			if (*p==']'){++p; return;}
			a[n++]=*p++;
			while (*p>='A'&&*p<='Z'||*p>='a'&&*p<='z')*p++;
		}
	}
	inline bool read_next(char c){while (*p!=c&&*p)++p; return *p!=0;}
	inline bool read_next_digit(){while (*p&&(*p<'0'||*p>'9'))++p; return *p!=0;}
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
	inline void print(char *s){while (*s)*o++=*s++;}
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

//hash
template<class T>
struct Gethash{
	size_t operator ()(const T &x)const{return x;}
};
template<> size_t Gethash<int>::operator ()(const int &x)const{return x;}
template<> size_t Gethash<long long>::operator ()(const long long &x)const{return x^(x>>32);}
template<> size_t Gethash<float>::operator ()(const float &x)const{static Gethash<int> h; return h(*((int*)&x));}  //assert(sizeof(float)==sizeof(int));
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
	//void operator =(const Hash &y){}
	void Grow(){
		static double rate=1.7;Hash<Tkey,Tvalue,_Hash> res(max_size*2,size_t(rate*max_size*2));
		for (size_t i=0;i<P;++i)
			for (node *j=v[i];j;j=j->next)res.insert(j->first,j->second);
		free();*this=res;
	}
	void build(size_t L,size_t p){
		P=p;len=0;max_size=L;++L;key=new node[L];
		v=new node*[p];memset(v,0,sizeof(node*)*p);
	}
	Hash(size_t len=3,size_t p=5){build(len,p);}
	void clear(){len=0;memset(v,0,sizeof(node*)*P);}
	//void clear(){free();build(3,5);}
	Tvalue& insert(const Tkey &x,const Tvalue &y=Tvalue()){
		//if (&find_(x)){Tvalue *null=NULL;return *null;}
		if (len==max_size)Grow();size_t x1=gethash(x)%P;
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
	void erase(const Tkey &x){
		size_t x1=gethash(x)%P;
		for (node *i=v[x1],*pre=0;i;pre=i,i=i->next)if (i->first==x)
			if (!pre)v[x1]=i->next;else pre->next=i->next;
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
	~Hash(){}
	/*void print(){
		for (size_t i=0;i<P;++i)
			for (node *j=v[i];j;j=j->next)printf("H[%d]=%d\n",j->first,j->second);
	}*/
};

//fast hash
namespace Hash{
	typedef unsigned int uint;
	const uint S=24,S1=32-S,M=1996090921;
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
} using namespace Hash;

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

//main
int _main=[](){
	//FILE *fout=fopen("./user.out","w");
	while (1){
		if (!read_next('['))break;
		
	} 
	exit(0);
	return 0;
}();


