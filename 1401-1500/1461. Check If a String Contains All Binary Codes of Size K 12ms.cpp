bool c[500005];
class Solution {
public:
	bool hasAllCodes(const string &_s, int k) {
		int n=_s.size(),l=1<<k,t=0,cnt=0,mask=l-1; const char *s=&_s[0];
		if (n<k+l-1)return 0;
		memset(c,0,sizeof(bool)*l);
		for (int i=0;i<k-1;++i)t=(t<<1)|(s[i]-'0');
		for (int i=k-1;cnt<l&&i<n;++i){
			t=(t<<1)&mask|(s[i]-'0');
			if (!c[t]){c[t]=1; ++cnt;}
		}
		return cnt==l;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

