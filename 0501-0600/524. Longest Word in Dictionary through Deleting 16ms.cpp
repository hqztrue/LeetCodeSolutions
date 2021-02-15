const int N=1005,CH=26;
int q[CH][N],q1[CH],d1[N];
class Solution {
public:
	string findLongestWord(string s, vector<string>& d) {
		int n=s.size(),m=d.size();
		for (int i=0;i<CH;++i)q1[i]=0;
		for (int i=0;i<m;++i){
			int c=d[i][0]-'a';
			d1[i]=0; q[c][q1[c]++]=i;
		}
		for (int i=0;i<n;++i){
			int c=s[i]-'a',k=q1[c]; q1[c]=0;
			for (int j=0;j<k;++j){
				int id=q[c][j]; ++d1[id];
				if (d1[id]<d[id].size()){
					int c1=d[id][d1[id]]-'a';
					q[c1][q1[c1]++]=id;
				}
			}
		}
		string ans="";
		for (int i=0;i<m;++i)
			if ((d1[i]==d[i].size())&&(d[i].size()>ans.size()||d[i].size()==ans.size()&&d[i]<ans))ans=d[i];
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

