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
			flag=flag&&ptr[i]->abbreviateProduct(18,237575).substr(0,5)=="76683";
			flag=flag&&ptr[i]->abbreviateProduct(3940,836328).substr(0,5)=="24931";
			flag=flag&&ptr[i]->abbreviateProduct(2965,574229).substr(0,5)=="89070";
			flag=flag&&ptr[i]->abbreviateProduct(6148,215373).substr(0,5)=="36552";
			flag=flag&&ptr[i]->abbreviateProduct(55507,56460).substr(0,5)=="44082";
			if (flag)out<<"ok: "<<i<<endl;
		}
	cerr.rdbuf(cerrbuf);
	out<<"finished"<<endl; system("pause");
	return 0;
}


