#include<bits/stdc++.h>
using namespace std;
const char* tmp_file="tmp12345.out.txt";
ofstream ofile(tmp_file),out;
streambuf *cerrbuf=cerr.rdbuf();
class Solution {
public:
	virtual string abbreviateProduct(int left, int right) {out<<"func err\n"; return "";}
};
Solution *ptr[100005];
#define exp10(x) pow(10.,x)
#include"codes.h"
int main()
{
	out.basic_ios<char>::rdbuf(cerr.rdbuf());
	cerr.rdbuf(ofile.rdbuf());
	//freopen("1.in","r",stdin);
	freopen(tmp_file,"w",stdout);
	int n=sizeof(ptr)/sizeof(Solution*);
	for (int i=0;i<n;++i)
		if (ptr[i]){
			//out<<i<<" "<<ptr[i]->abbreviateProduct(6148,215373)<<endl;
			int flag=1;
			flag=flag&&ptr[i]->abbreviateProduct(6,563035).substr(0,5)=="78783";
			if (flag)out<<"ok: "<<i<<endl;
		}
	cerr.rdbuf(cerrbuf);
	out<<"finished"<<endl; system("pause");
	return 0;
}

