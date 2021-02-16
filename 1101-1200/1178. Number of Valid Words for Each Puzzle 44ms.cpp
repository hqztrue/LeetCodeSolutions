const int N=100005;
int cnt[1<<26],V[N];
class Solution {
public:
	//Hash<int,int> cnt;
	vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
		vector<int> res(puzzles.size());
		//cnt.clear();
		int *m=V;
		for (string &s:words){
			int v=0;
			for (char &c:s)v|=1<<(c-'a');
			++cnt[v];
			*m++=v;
		}
		int n1=0;
		for (string &str:puzzles){
			int v=0,v1=1<<(str[0]-'a'),s=cnt[v1];
			for (int i=1;i<7;++i)v|=1<<(str[i]-'a');
			for (int u=v;u;u=(u-1)&v)
				s+=cnt[u|v1];
				//cnt.add(u|v1,s);
			res[n1++]=s;
		}
		for (int *i=V;i!=m;++i)cnt[*i]=0;
		return res;
	}
};

//IO
int _IO=[](){
	std::ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

