const int N=505;
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
	operator bool()const{return count()>0;}
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
int a[N],b[N],n,m;
BitSet<N> row[2],X,Y;
map<int,vector<int> > S;
map<int,BitSet<N> > match;
class Solution {
public:
	int minDistance(string A, string B) {
		n=A.size(); m=B.size(); S.clear();match.clear();row[1].reset();
		for (int i=0;i<n;++i)a[i]=A[i]-'a',S[a[i]].push_back(i);
		for (int i=0;i<m;++i)b[i]=B[i]-'a';
		for (int i=0;i<m;++i)if (match.find(b[i])==match.end()){
			map<int,BitSet<N> >::iterator x=match.insert(make_pair(b[i],BitSet<N>())).first;
			for (vector<int>::iterator j=S[b[i]].begin();j!=S[b[i]].end();++j)x->second.set(*j,1);
		}
		for (int i=0,now=0;i<m;++i,now^=1)
			X=(row[now^1]|match[b[i]]).set(n,1),row[now]=(X&((X-(row[now^1]<<1).set(0,1))^X)).set(n,0);
		return n+m-2*row[(m-1)&1].count();
	}
};

//IO
int _IO=[](){
	std::ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	return 0;
}();

