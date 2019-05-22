#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<map>
#include<vector>
//#include<ext/hash_map>
using namespace std;
//using namespace __gnu_cxx;
#if __cplusplus>199711L  //c++11
#include<unordered_map>
#endif
const int N=1005;
template<int S>
struct BitSet{
	#define W 5
	#define mask 31
	#define get_size(n) ((n)<1?0:((n)+mask)>>W)
	#define all_u 4294967296LL
	#define size_t unsigned int
	typedef unsigned int uint;
	uint a[get_size(S)];int size;
	void clear(){memset(a,0,sizeof(uint)*size);}
	BitSet():size(get_size(S)){clear();}
	BitSet(uint x):size(get_size(S)){clear();a[0]=x;}
	BitSet(const BitSet<S> &x):size(get_size(S)){*this=x;}
	BitSet& set(int x,int y){
		if (y<0||y>1){printf("error!\n");return *this;}
		int X=x>>W,Y=x&mask;
		if (y)a[X]|=1<<Y;else a[X]&=~(1<<Y);
		return *this;
	}
	uint find(uint x){uint X=x>>W,Y=x&mask;return (a[X]>>Y)&1u;}
	uint operator [](uint x){return find(x);}
	BitSet& operator =(const BitSet &y){
		memcpy(a,y.a,sizeof(uint)*size);
		//uint *startA=a,*startB=y.a,*endA=a+size;
		//while (startA!=endA)*startA++=*startB++;
		//for (int i=0;i<size;++i)a[i]=y.a[i];
		return *this;
	}
	BitSet<S> operator |(const BitSet<S> &y){
		BitSet<S> res;
		for (int i=0;i<size;++i)res.a[i]=a[i]|y.a[i];
		return res;
	}
	BitSet<S> operator &(const BitSet<S> &y){
		BitSet<S> res;
		for (int i=0;i<size;++i)res.a[i]=a[i]&y.a[i];
		return res;
	}
	BitSet<S> operator ^(const BitSet<S> &y){
		BitSet<S> res;
		for (int i=0;i<size;++i)res.a[i]=a[i]^y.a[i];
		return res;
	}
	BitSet<S> operator +(const BitSet<S> &y){
		BitSet<S> res;static long long c[S];
		for (int i=0;i<size;++i)c[i]=a[i],c[i]+=y.a[i];
		for (int i=0;i<size;++i)c[i+1]+=c[i]>>32,res.a[i]=c[i];
		return res;
	}
	BitSet<S> operator -(const BitSet<S> &y){
		BitSet<S> res;static long long c[S];
		for (int i=0;i<size;++i)c[i]=a[i],c[i]-=y.a[i];
		for (int i=0;i<size;++i){
			if (c[i]<0)c[i]+=all_u,--c[i+1];res.a[i]=c[i];
		}
		return res;
	}
	BitSet<S> operator ~(){
		return BitSet<S>(*this).flip();
		/*BitSet<S> res;
		uint *startA=a,*startB=res.a,*endA=a+size;
		while (startA!=endA)*startB++=~*startA++;
		//for (int i=0;i<size;++i)res.a[i]=~a[i];
		return res;*/
	}
	BitSet<S>& operator =(const char *s){
		memset(a,0,sizeof(uint)*size);
		for (int i=0;i<S;++i){
			if (s[i]!='0'&&s[i]!='1')break;
			int X=i>>W,Y=i&mask;
			if (s[i]=='1')a[X]|=1<<Y;
		}
		return *this;
	}
	BitSet<S>& operator =(const int *s){
		memset(a,0,sizeof(uint)*size);
		for (int i=0;i<S;++i){
			if (s[i]!=0&&s[i]!=1)break;
			int X=i>>W,Y=i&mask;
			if (s[i]==1)a[X]|=1<<Y;
		}
		return *this;
	}
	BitSet<S>& operator <<=(uint x){
		const size_t shift=x>>5,delta=x&31,delta1=32-delta;
		if (!x)return *this;
		if (delta==0)for (size_t *i=a+size-1;i>=a+shift;--i)*i=*(i-shift);
		else {
			for (size_t *i=a+size-1;i>a+shift;--i)*i=(*(i-shift)<<delta)|(*(i-shift-1)>>delta1);
			a[shift]=a[0]<<delta;
		}
		for (size_t i=0;i<shift;++i)a[i]=0;
		return *this;
	}
	BitSet<S>& operator >>=(uint x){
		const size_t shift=x>>5,delta=x&31,delta1=32-delta,lim=size-shift-1;
		if (!x)return *this;
		if (S&31)a[size-1]&=uint((1LL<<(S&31))-1);
		if (delta==0)for (size_t *i=a;i<=a+lim;++i)*i=*(i+shift);
		else {
			for (size_t *i=a;i<a+lim;++i)*i=(*(i+shift)>>delta)|(*(i+shift+1)<<delta1);
			a[lim]=a[size-1]>>delta;
		}
		for (size_t i=lim+1;i<size;++i)a[i]=0;
		return *this;
	}
	BitSet<S> operator <<(int x)const{
		BitSet<S> res(*this);return res<<=x;
	}
	BitSet<S> operator >>(int x)const{
		BitSet<S> res(*this);return res>>=x;
	}
	BitSet<S>& operator |=(const BitSet<S> &y){
		uint *startA=a;const uint *startB=y.a,*endA=a+size;
		while (startA!=endA)*startA++|=*startB++;
		//for (int i=0;i<size;++i)a[i]|=y.a[i];
		return *this;
	}
	BitSet<S>& operator &=(const BitSet<S> &y){
		uint *startA=a;const uint *startB=y.a,*endA=a+size;
		while (startA!=endA)*startA++&=*startB++;
		//for (int i=0;i<size;++i)a[i]&=y.a[i];
		return *this;
	}
	BitSet<S>& operator ^=(const BitSet<S> &y){
		uint *startA=a;const uint *startB=y.a,*endA=a+size;
		while (startA!=endA)*startA++^=*startB++;
		//for (int i=0;i<size;++i)a[i]^=y.a[i];
		return *this;
	}
	operator bool(){return count()>0;}
	BitSet<S>& flip(){
		for (uint *start=a,*end=a+size;start!=end;*start=~*start,++start);
		return *this;
	}
	//void flip(){*this=~*this;}
	void flip(int x){a[x>>W]^=1<<(x&mask);}
	uint popcount(uint x)const{
		x=(x&0x55555555)+((x>>1)&0x55555555);
		x=(x&0x33333333)+((x>>2)&0x33333333);
		x=(x&0x0F0F0F0F)+((x>>4)&0x0F0F0F0F);
		x=(x&0x00FF00FF)+((x>>8)&0x00FF00FF);
		x=(x&0x0000FFFF)+((x>>16)&0x0000FFFF);
		return x;
	}
	int count(){
		int res=0;
		if (S&mask)a[size-1]&=(1<<(S&mask))-1;
		for (int i=0;i<size;++i)res+=popcount(a[i]);
		return res;
	}
	void reset(){
		memset(a,0,sizeof(uint)*size);
		//for (int i=0;i<size;++i)a[i]=0;
	}
	uint to_uint(){
		if (S&mask)a[size-1]&=(1<<(S&mask))-1;
		return a[0];
	}
	void print(){
		for (int i=0;i<size;++i)
			for (int j=0;j<=mask&&(i<<W)+j+1<=S;++j)printf("%d",(a[i]>>j)&1);
		printf("\n");
	}
	#undef mask
	#undef W
	#undef get_size
	#undef all_u
	#undef size_t
};
int a[N],b[N];
BitSet<N> row[2],X,Y;
unordered_map<int,vector<int> > S;
unordered_map<int,BitSet<N> > match;

class Solution {
public:
    int longestPalindromeSubseq(string s) {
		int n=s.size(),m=n;
        S.clear();match.clear();row[1].clear();
		for (int i=0;i<n;++i)a[i]=int(s[i]),S[a[i]].push_back(i);
		for (int i=0;i<m;++i)b[i]=int(s[n-1-i]);
		for (int i=0;i<m;++i)if (match.find(b[i])==match.end()){
			unordered_map<int,BitSet<N> >::iterator x=match.insert(make_pair(b[i],BitSet<N>())).first;
			for (vector<int>::iterator j=S[b[i]].begin();j!=S[b[i]].end();++j)x->second.set(*j,1);
		}
		for (int i=0,now=0;i<m;++i,now^=1)
			X=(row[now^1]|match[b[i]]).set(n,1),row[now]=(X&((X-(row[now^1]<<1).set(0,1))^X)).set(n,0);
        return row[(m-1)&1].count();
    }
};



