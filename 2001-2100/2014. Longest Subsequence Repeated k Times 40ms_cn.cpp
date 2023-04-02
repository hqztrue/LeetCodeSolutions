const int N=2005;
int c[255],_next[N][26],(*nxt)[26]=&_next[2],n,m,k;
char b[N];
string a,ans;
inline bool check(const string &t){
	int m=t.size(),cur;
	if (!m)return 1;
	if (k>40){
		bool flag=0;
		for (int i=0;i<10;++i){
			int p=rand()%n; cur=p-1;
			for (auto &ch:t)cur=nxt[cur][ch-'a'];
			if (cur>=0&&cur-p<=7){flag=1; break;}
		}
		if (!flag)return 0;
	}
	cur=-1;
	for (int i=0;i<k;++i){
		for (auto &ch:t)cur=nxt[cur][ch-'a'];
		if (cur<0)return 0;
	}
	return 1;
}
void dfs(string &t){
	if (!check(t))return;
	if (t.size()>ans.size()||t.size()==ans.size()&&t>ans)ans=t;
	for (int i=0;i<m;++i)if (!i||b[i]!=b[i-1]){
		char ch=b[i]; --m;
		for (int j=i;j<m;++j)b[j]=b[j+1];
		t.push_back(ch);
		dfs(t);
		t.pop_back();
		for (int j=m;j>i;--j)b[j]=b[j-1];
		++m; b[i]=ch;
	}
}
class Solution {
public:
	string longestSubsequenceRepeatedK(string s, int k) {
		m=0; ::k=k; a=ans="";
		for (int i='a';i<='z';++i)c[i]=0;
		for (auto &ch:s)++c[ch];
		for (auto &ch:s)if (c[ch]>=k)a.push_back(ch);
		n=a.size();
		for (int i=0;i<26;++i)nxt[-2][i]=nxt[n-1][i]=-2;
		for (int i=n-2;i>=-1;--i){
			memcpy(nxt[i],nxt[i+1],sizeof(int)*26);
			nxt[i][a[i+1]-'a']=i+1;
		}
		for (int i='a';i<='z';++i)
			for (int j=0;j<c[i]/k;++j)b[m++]=i;
		string _s; dfs(_s);
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();
