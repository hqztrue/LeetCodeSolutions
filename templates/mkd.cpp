#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
#define For(i,l,r) for (int i=l;i<=r;++i)
namespace data_gen{
	inline int Rand(){return ((rand()&1)<<30)+(rand()<<15)+rand();}
	inline int Rand(int U,bool flag=0){return Rand()%U*(flag&&Rand()%2?-1:1);}
	vector<int> rand_vec(int n,int U,bool flag=0){
		vector<int> res(n);
		for (int i=0;i<n;++i)res[i]=Rand(U,flag);
		return res;
	}
	vector<vector<int>> rand_vec2D(int n,int m,int U,bool flag=0){
		vector<vector<int> > res(n);
		for (int i=0;i<n;++i)res[i]=rand_vec(m,U,flag);
		return res;
	}
	string rand_str(int n,int U=26,char c='a'){
		string res;
		for (int i=0;i<n;++i)res+=(char)(c+Rand()%U);
		return res;
	}
	template<class T>
	void print(const T &a){cout<<a;}
	template<> void print<string>(const string &s){
		printf("\"%s\"",s.c_str());
	}
	template<class T>
	void print(const vector<T> &v){
		printf("[");
		for (int i=0;i<v.size();++i){
			print(v[i]);
			printf("%s",i+1==v.size()?"":",");
		}
		printf("]");
	}
	template<class T>
	void println(const T &a){
		print(a); printf("\n");
	}
} using namespace data_gen;
int main()
{
	freopen("1.in","w",stdout);
	srand(time(0));
	int n=50,m=50,U=10000;
	vector<int> a;
	println(rand_vec(n,U));
	//println(rand_vec2D(n,m,U));
	println(Rand()%U);
	//system("pause");for (;;);
	return 0;
}


