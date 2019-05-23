#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;
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
	int find(int x){int X=x>>W,Y=x&mask;return (a[X]>>Y)&1ull;}
	int operator [](int x){return find(x);}
	BitSet& operator =(const BitSet &y){
		memcpy(a,y.a,sizeof(uint)*size);
		return *this;
	}
	BitSet<S> operator |(const BitSet<S> &y){return BitSet<S>(*this)|=y;}
	BitSet<S> operator &(const BitSet<S> &y){return BitSet<S>(*this)&=y;}
	BitSet<S> operator ^(const BitSet<S> &y){return BitSet<S>(*this)^=y;}
	BitSet<S> operator +(const BitSet<S> &y){
		BitSet<S> res; uint t=0;
		register uint *p=a,*r=res.a,*end=a+size; const register uint *q=y.a;
		while (p!=end){
			register uint p1=*p; *r=p1+*q+t;
			t=(*r<p1)||(p1+t<t);
			++p; ++q; ++r;
		}
		return res;
	}
	BitSet<S> operator -(const BitSet<S> &y){
		BitSet<S> res; uint t=0;
		register uint *p=a,*r=res.a,*end=a+size; const register uint *q=y.a;
		while (p!=end){
			register uint p1=*p; *r=p1-*q-t;
			t=(*r>p1)||(p1+t<t);
			++p; ++q; ++r;
		}
		return res;
	}
	BitSet<S> operator ~(){return BitSet<S>(*this).flip();}
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
		int shift=x>>W; register int delta=x&mask,delta1=mask+1-delta;
		if (!x)return *this;
		if (delta==0)for (register uint *p=a+size-1,*q=p-shift,*end=a+shift-1;p!=end;--p,--q)*p=*q;
		else {
			for (register uint *p=a+size-1,*q1=p-shift,*q2=p-shift-1,*end=a+shift;p!=end;--p,--q1,--q2)*p=(*q1<<delta)|(*q2>>delta1);
			a[shift]=a[0]<<delta;
		}
		memset(a,0,sizeof(uint)*shift); //for (register uint *p=a,*end=a+shift;p!=end;++p)*p=0;
		return *this;
	}
	BitSet<S>& operator >>=(int x){
		int shift=x>>W; register int delta=x&mask,delta1=mask+1-delta;
		if (!x)return *this;
		if (S&mask)a[size-1]&=(1ull<<(S&mask))-1;
		if (delta==0)for (register uint *p=a,*q=p+shift,*end=a+size-shift;p!=end;++p,++q)*p=*q;
		else {
			for (register uint *p=a,*q1=p+shift,*q2=p+shift+1,*end=a+size-shift-1;p!=end;++p,++q1,++q2)*p=(*q1>>delta)|(*q2<<delta1);
			a[size-shift-1]=a[size-1]>>delta;
		}
		memset(a+size-shift,0,sizeof(uint)*shift);
		return *this;
	}
	BitSet<S> operator <<(int x)const{return BitSet<S>(*this)<<=x;}
	BitSet<S> operator >>(int x)const{return BitSet<S>(*this)>>=x;}
	BitSet<S>& operator |=(const BitSet<S> &y){
		register uint *startA=a;const register uint *startB=y.a,*endA=a+size;
		while (startA!=endA){*startA|=*startB;++startA;++startB;}
		//for (int i=0;i<size;++i)a[i]|=y.a[i];
		return *this;
	}
	/*BitSet<S>& operator |=(const BitSet<S> &y){
		register uint *p0=a,*p1=p0+1,*p2=p0+2,*p3=p0+3;const register uint *q0=y.a,*q1=q0+1,*q2=q0+2,*q3=q0+3,*pend=a+((size>>2)<<2);
		while (p0!=pend){
			*p0|=*q0; p0+=4; q0+=4;
			*p1|=*q1; p1+=4; q1+=4;
			*p2|=*q2; p2+=4; q2+=4;
			*p3|=*q3; p3+=4; q3+=4;
		}
		for (int i=0;i<(size&3);++i)*p0++=*q0++;
		return *this;
	}*/
	BitSet<S>& operator &=(const BitSet<S> &y){
		register uint *startA=a;const register uint *startB=y.a,*endA=a+size;
		while (startA!=endA){*startA&=*startB;++startA;++startB;}
		return *this;
	}
	BitSet<S>& operator ^=(const BitSet<S> &y){
		register uint *startA=a;const register uint *startB=y.a,*endA=a+size;
		while (startA!=endA){*startA^=*startB;++startA;++startB;}
		return *this;
	}
	operator bool(){return count()>0;}
	BitSet<S>& flip(){
		for (register uint *start=a,*end=a+size;start!=end;*start=~*start,++start);
		return *this;
	}
	//void flip(){*this=~*this;}
	void flip(int x){a[x>>W]^=1ull<<(x&mask);}
	int popcount(uint x)const{
		x=(x&0x5555555555555555ull)+((x&0xaaaaaaaaaaaaaaaaull)>>1);
		x=(x&0x3333333333333333ull)+((x&0xccccccccccccccccull)>>2);
		x=(x&0x0f0f0f0f0f0f0f0full)+((x&0xf0f0f0f0f0f0f0f0ull)>>4);
		x=(x&0x00ff00ff00ff00ffull)+((x&0xff00ff00ff00ff00ull)>>8);
		x=(x&0x0000ffff0000ffffull)+((x&0xffff0000ffff0000ull)>>16);
		return (x&0x00000000ffffffffull)+(x>>32);
	}
	int count(){
		int res=0;
		if (S&mask)a[size-1]&=(1ull<<(S&mask))-1;
		for (int i=0;i<size;++i)res+=__builtin_popcountll(a[i]);  //popcount
		return res;
	}
	uint to_uint(){
		if (S&mask)a[size-1]&=(1ull<<(S&mask))-1;
		return a[0];
	}
	void print(){
		for (int i=0;i<size;++i)
			for (int j=0;j<=mask&&(i<<W)+j+1<=S;++j)printf("%I64d",(a[i]>>j)&1ull);
		printf("\n");
	}
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
