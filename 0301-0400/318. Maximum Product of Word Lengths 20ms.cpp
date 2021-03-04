#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
#define register
unsigned long long _pool[1000005],*pool1=_pool;  //15000005
struct BitSet{
	#define W 6
	#define mask 63
	#define get_size(n) ((n)<1?0:((n)+mask)>>W)
	typedef unsigned long long uint;  //typedef unsigned int uint;
	uint *a;int size,S;
	void reset(){memset(a,0,sizeof(uint)*size);}
	void init(){a=pool1;pool1+=size;reset();}  //a=new uint[size];
	BitSet(){}
	BitSet(int S_):S(S_),size(get_size(S_)){init();}
	//BitSet(uint x):size(get_size(S)){reset();a[0]=x;}
	BitSet(const BitSet &x){*this=x;}
	BitSet& set(int x,int y){
		//if (y<0||y>1){printf("error!\n");return *this;}
		int X=x>>W,Y=x&mask;
		if (y)a[X]|=1ull<<Y;else a[X]&=~(1ull<<Y);
		return *this;
	}
	int find(int x){int X=x>>W,Y=x&mask;return (a[X]>>Y)&1ull;}
	int operator [](int x){return find(x);}
	BitSet& operator =(const BitSet &y){
		size=y.size; init();
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
	BitSet& operator >>=(int x){
		int shift=x>>W; register int delta=x&mask,delta1=mask+1-delta;
		if (!x)return *this;
		correction();
		if (delta==0)for (register uint *p=a,*q=p+shift,*end=a+size-shift;p!=end;++p,++q)*p=*q;
		else {
			for (register uint *p=a,*q1=p+shift,*q2=p+shift+1,*end=a+size-shift-1;p!=end;++p,++q1,++q2)*p=(*q1>>delta)|(*q2<<delta1);
			a[size-shift-1]=a[size-1]>>delta;
		}
		memset(a+size-shift,0,sizeof(uint)*shift);
		return *this;
	}
	BitSet& operator |=(const BitSet &y){
		register uint *startA=a;const register uint *startB=y.a,*endA=a+size;
		while (startA!=endA){*startA|=*startB;++startA;++startB;}
		//for (int i=0;i<size;++i)a[i]|=y.a[i];
		return *this;
	}
	/*BitSet& operator |=(const BitSet &y){
		register uint *p0=a,*p1=p0+1,*p2=p0+2,*p3=p0+3;const register uint *q0=y.a,*q1=q0+1,*q2=q0+2,*q3=q0+3,*pend=a+((size>>2)<<2);
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
		register uint *startA=a;const register uint *startB=y.a,*endA=a+size;
		while (startA!=endA){*startA&=*startB;++startA;++startB;}
		return *this;
	}
	BitSet& operator ^=(const BitSet &y){
		register uint *startA=a;const register uint *startB=y.a,*endA=a+size;
		while (startA!=endA){*startA^=*startB;++startA;++startB;}
		return *this;
	}
	BitSet& operator +=(const BitSet &y){
		register uint t=0,*p=a,*end=a+size; const register uint *q=y.a;
		while (p!=end){
			register uint p1=*p; *p=p1+*q+t;
			t=(*p<p1)||(*q+t<t);
			++p; ++q;
		}
		return *this;
	}
	BitSet& operator -=(const BitSet &y){
		register uint t=0,*p=a,*end=a+size; const register uint *q=y.a;
		while (p!=end){
			register uint p1=*p; *p=p1-*q-t;
			t=(*p>p1)||(*q+t<t);
			++p; ++q;
		}
		return *this;
	}
	operator bool(){return count()>0;}
	BitSet& flip(){
		//for (register uint *start=a,*end=a+size;start!=end;*start=~*start,++start);
		register uint *p0=a,*p1=p0+1,*p2=p0+2,*p3=p0+3,*pend=a+((size>>2)<<2);
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
	uint to_uint(){
		correction();
		return a[0];
	}
	void print(){
		for (int i=0;i<size;++i)
			for (int j=0;j<=mask&&(i<<W)+j+1<=S;++j)printf("%I64d",(a[i]>>j)&1ull);
		printf("\n");
	}
	void correction(){if (S&mask)a[size-1]&=(1ull<<(S&mask))-1;}
	#undef mask
	#undef W
	#undef get_size
};

#define N 1005
#define CH 26
#define L 4
#define L1 7
int mask[N],len[N];
BitSet a[CH],b[L1][1<<L];
bool cmp(const string &s1,const string &s2){return s1.size()>s2.size();}
class Solution {
public:
	int maxProduct(vector<string> &v){
		int n=v.size(),ans=0;
		sort(v.begin(),v.end(),cmp);
		for (int i=0;i<n;++i){
			int t=0;
			for (int j=0;j<v[i].size();++j)t|=1<<(v[i][j]-'a');
			mask[i]=t; len[i]=v[i].size();
		}
		for (int i=0;i<CH;++i){
			a[i]=BitSet(n);
			for (int j=0;j<n;++j)
				if (mask[j]&(1<<i))a[i].set(j,1);
		}
		for (int i1=0;i1<L1;++i1){
			b[i1][0]=BitSet(n);
			for (int j=1;j<(1<<L);++j){
				int k=__builtin_clz(j),t=31-k;
				if (i1*L+t<CH)b[i1][j]=b[i1][j-(1<<t)]|a[i1*L+t];
			}
		}
		for (int i=0;i<n;++i){
			BitSet res=b[0][mask[i]&((1<<L)-1)];
			for (int i1=1;i1<L1;++i1)res|=b[i1][(mask[i]>>(L*i1))&((1<<L)-1)];
			res.flip();
			int t=res.ctz();
			if (t<n)ans=max(ans,len[i]*len[t]);
		}
		return ans;
	}
};

//IO
int _IO=[](){
	std::ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	return 0;
}();

