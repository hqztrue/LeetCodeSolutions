static const int N=405,L=5005,CH=26;  //160005
struct node{
	node *son[CH];int sum;
};
node a[L];int res[N],l;
void clear(){memset(a,0,sizeof(node)*(l+1)); l=0;}
inline int get(char ch){return ch-'a';}
struct prefix{
	int id; const char *s; node *x;
}p[N];
class Solution {
public:
	string abbre(const string &s){
		if (s.length()<=3)return s;
		return s[0]+to_string(s.length()-2)+s.back();
	}
	string abbre1(const string &s,int l){
		if (s.length()-l<=3)return s.substr(l);
		return s[l]+to_string(s.length()-l-2)+s.back();
	}
	vector<string> wordsAbbreviation(vector<string> &d) {
		int n=d.size(); vector<string> ans(n);
		unordered_map<string, vector<int> > M;
		for (int i=0;i<n;++i){
			string s1=abbre(d[i]);
			M[s1].emplace_back(i);
			ans[i]=s1;
		}
		for (auto &s:M){
			int m=s.second.size();
			if (m<2)continue;
			clear();
			for (int i=0;i<m;++i)p[i].id=i,p[i].s=&d[s.second[i]][0],p[i].x=a;
			for (int I=0;m;++I){
				for (int i=0,c;i<m;++i){
					c=get(p[i].s[I]); node *&x=p[i].x;
					if (!x->son[c])x->son[c]=a+(++l);
					x=x->son[c]; ++x->sum;
				}
				for (int i=0;i<m;++i)
					if (p[i].x->sum==1)res[p[i].id]=I,p[i--]=p[--m];
			}
			m=s.second.size();
			for (int i=0;i<m;++i){
				string &cur=d[s.second[i]]; int l=res[i];
				if (l>=cur.length()-3)ans[s.second[i]]=cur;
				else ans[s.second[i]]=cur.substr(0,l)+abbre1(cur,l);
			}
		}
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

