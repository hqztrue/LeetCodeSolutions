#include<bits/stdc++.h>
using namespace std;
const char* tmp_file="tmp12345.out.txt";
ofstream ofile(tmp_file),out;
streambuf *cerrbuf=cerr.rdbuf();
class Solution {
public:
	virtual int eatenApples(vector<int>& apples, vector<int>& days) {
		out<<"func err\n"; return -1;
	}
};
Solution *ptr[100005]; int nsols=sizeof(ptr)/sizeof(Solution*);
#define exp10(x) pow(10.,x)
typedef unsigned int uint;
#include"codes_CN.h"
void check(vector<int> a, vector<int> b, int t){
	for (int i=0;i<nsols;++i)
		if (ptr[i]){
			//out<<"chk"<<i<<endl;
			vector<int> _a=a,_b=b;
			auto ans=ptr[i]->eatenApples(_a,_b);
			if (ans!=t){
				ptr[i]=0;
				out<<"del "<<i<<endl;
			}
		}
}
int main()
{
	out.basic_ios<char>::rdbuf(cerr.rdbuf());
	cerr.rdbuf(ofile.rdbuf());
	//freopen("1.in","r",stdin);
	freopen(tmp_file,"w",stdout);
	//srand(time(0));
	check({8,8,3,6,8,1,1,1,1,5},{1,2,1,1,5,10,9,8,7,2},15);
	check({8,5,6,3,5,4,0,9,0,0},{2,1,2,3,5,4,0,3,0,0},10);
	for (int T=0;;++T){
		//if (T%10000==0)out<<"T="<<T<<endl;
		int n=10,m=10;
		//int n=1000,m=10;
		vector<int> a(n),b(n);
		for (int i=0;i<n;++i){
			a[i]=rand()%m;
			b[i]=a[i]==0?0:rand()%m+1;
		}
		Solution* std_ptr=0;
		int std=-1;
		for (int i=0;i<nsols;++i)
			if (ptr[i]){
				vector<int> _a=a,_b=b;
				auto ans=ptr[i]->eatenApples(_a,_b);
				if (std_ptr==0)std_ptr=ptr[i],std=ans;
				else if (std!=ans){
					out<<"[";
					for (int i=0;i<n;++i)out<<a[i]<<(i==n-1?"]\n":",");
					out<<"[";
					for (int i=0;i<n;++i)out<<b[i]<<(i==n-1?"]\n":",");
					out<<"err"<<i<<" "<<std<<" "<<ans<<endl;
					ptr[i]=0;
				}
				//out<<i<<" "<<ans<<endl;
			}
	}
	cerr.rdbuf(cerrbuf);
	out<<"finished"<<endl; system("pause");
	return 0;
}

