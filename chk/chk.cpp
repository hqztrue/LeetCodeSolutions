#include<bits/stdc++.h>
using namespace std;
const char* tmp_file="tmp12345.out.txt";
namespace std{ 
	ofstream ofile(tmp_file),__out;
}
streambuf *cerrbuf=cerr.rdbuf();
class Solution {
public:
	virtual int run(vector<int>& arr, int target) = 0;
};
Solution *ptr[100005]; int nsols=sizeof(ptr)/sizeof(Solution*);
#define exp10(x) pow(10.,x)
#define u_int uint
auto reduce(auto a,auto b,int c=0){return accumulate(a,b,0);}
typedef unsigned int uint;
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
#define cerr __out
//#include"codes_US.h"
#include"codes_CN.h"
#undef cerr
namespace cerrIO{
	template<class T>
	void print(const T &a){cerr<<a;}
	template<> void print<string>(const string &s){
		cerr<<"\""<<s<<"\"";
	}
	template<class T>
	void print(const vector<T> &v){
		cerr<<"[";
		for (int i=0;i<v.size();++i){
			print(v[i]);
			cerr<<(i+1==v.size()?"":",");
		}
		cerr<<"]";
	}
	template<class T>
	void println(const T &a){
		print(a); cerr<<"\n";
	}
} using namespace cerrIO;
void count(){int T=0; for (int i=0;i<nsols;++i)if (ptr[i])++T; cerr<<"#="<<T<<endl;}
void check(vector<int> a, int t, int res=-2){
	for (int i=0;i<nsols;++i)
		if (ptr[i]){
			//cerr<<"chk"<<i<<endl;
			auto _a=a;
			auto ans=ptr[i]->run(_a,t);
			if (res!=-2&&ans!=res){
				ptr[i]=0;
				cerr<<"del "<<i<<endl;
			}
		}
}
int main()
{
	//freopen("1.in","r",stdin);
	freopen(tmp_file,"w",stdout);
	srand(time(0));
	//count();
	vector<int> arr = {};
	for (auto t:arr)ptr[t]=0;
	//check({},4,1);
	for (int T=0;;++T){
		if (T%1000==0)cerr<<"T="<<T<<endl;
		int n=3,m=100,t=rand()%10;
		vector<int> a(n);
		for (int i=0;i<n;++i)a[i]=rand()%m;
		Solution* std_ptr=0;
		int std=-1;
		for (int i=0;i<nsols;++i)
			if (ptr[i]){
				//cerr<<"i="<<i<<endl;
				auto _a=a;
				auto ans=ptr[i]->run(_a,t);
				if (std_ptr==0)std_ptr=ptr[i],std=ans;
				else if (std!=ans){
					cerr<<"[";
					for (int i=0;i<n;++i)cerr<<a[i]<<(i==n-1?"]\n":",");
					cerr<<t<<endl;
					cerr<<"err"<<i<<" "<<std<<" "<<ans<<endl;
					ptr[i]=0;
				}
				//cerr<<i<<" "<<ans<<endl;
			}
	}
	cerr<<"finished"<<endl; system("pause");
	return 0;
}

