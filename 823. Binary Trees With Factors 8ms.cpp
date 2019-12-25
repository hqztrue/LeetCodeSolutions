//IO
int _IO=[](){
	std::ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

template<class T>
struct Gethash{
	size_t operator ()(const T &x)const{return x;}
};
template<> size_t Gethash<int>::operator ()(const int &x)const{return x;}
template<> size_t Gethash<long long>::operator ()(const long long &x)const{return x;}
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
		iterator& operator ++(){j=j->next;go();}
		iterator operator ++(int){iterator res=*this;++*this;return res;}
		iterator& operator --(){
			if (j==H->v[i]){for (--i;!H->v[i];--i);for (j=H->v[i];j->next;j=j->next);}
			else {node *k=j;for (j=H->v[i];j->next!=k;j=j->next);}
		}
		iterator operator --(int){iterator res=*this;--*this;return res;}
		node* operator ->(){return j;}
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
	Tvalue& insert(const Tkey &x,const Tvalue &y=0){
		//if (&find_(x)){Tvalue *null=NULL;return *null;}
		if (len==max_size)Grow();size_t x1=gethash(x)%P;
		key[++len]=node(x,y,v[x1]);v[x1]=key+len;
		return key[len].second;
	}
	Tvalue& insert(const pair<Tkey,Tvalue> &p){return insert(p.first,p.second);}
	void erase(const Tkey &x){
		size_t x1=gethash(x)%P;
		for (node *i=v[x1],*pre=0;i;pre=i,i=i->next)if (i->first==x){
			if (!pre)v[x1]=i->next;else pre->next=i->next;
		}
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
	void add(const Tkey &x,int &s){
		size_t x1=gethash(x)%P;
		for (node *i=v[x1];i;i=i->next)
			if (i->first==x){s+=i->second; return;}
		//Tvalue *null=NULL;return *null;
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

typedef long long ll;
const int N=1005,P=1000000007;
inline int mul_mod_int_asm(int a,int b,int p){
	int res;
	__asm__ __volatile__("imull %%ebx\n idivl %%ecx":"=d"(res):"a"(a),"b"(b),"c"(p));
	return res;
}
class Solution {
	Hash<int,int> M;
public:
	int s[N]; ll s1[N];
	Solution(){M.build(N,10007);};
    int numFactoredBinaryTrees(vector<int>& A) {
		M.clear();
		sort(A.begin(),A.end());
		int n=A.size(),max=A[n-1]; ll ans=0;
		for (int i=0;i<n;++i)s1[i]=1,M[A[i]]=i;
		for (int i=0;i<n;++i){
			s[i]=s1[i]%P;
			int k=upper_bound(&A[0],&A[0]+i,max/A[i])-&A[0];
			for (int j=0;j<k;++j){
				int *p=M.find_(A[i]*A[j]);
				if (p)s1[*p]+=mul_mod_int_asm(s[i]*2,s[j],P);
			}
			if (A[i]<=max/A[i]){
				int *p=M.find_(A[i]*A[i]);
				if (p)s1[*p]+=mul_mod_int_asm(s[i],s[i],P);
			}
            ans+=s[i];
		}
        return ans%P;
    }
};


