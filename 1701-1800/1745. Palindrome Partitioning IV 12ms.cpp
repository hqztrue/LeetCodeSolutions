const int N=2005,CH=26;
struct node{
	node *fail;
	int next[CH],cnt,len;
};
struct PalindromicTree{
	node pool[N],*p,*last;
	int S[N],n;
	node* newnode(int l){
		memset(p->next,0,sizeof(p->next));
		p->cnt=0; p->len=l; return p++;
	}
	void init(){
		last=p=pool; p->fail=p+1; (p+1)->fail=p;
		newnode(0); newnode(-1);
		n=0; S[n]=-1;
	}
	node* get_fail(node *x){
		while (S[n-x->len-1]!=S[n])x=x->fail;
		return x;
	}
	node* add(int c){
		c-='a'; S[++n]=c;
		node *cur=get_fail(last);
		if (!cur->next[c]){
			node *now=newnode(cur->len+2);
			now->fail=pool+get_fail(cur->fail)->next[c];
			cur->next[c]=now-pool;
		}
		last=pool+cur->next[c]; ++last->cnt;
		return last;
	}
	void count(){
		for (node *x=p-1;x>=pool;--x)x->fail->cnt+=x->cnt;
	}
};
PalindromicTree T,T1;
int len[N],len1[N],n; node *nodes[N];
class Solution {
public:
	bool checkPartitioning(string s) {
		n=s.size();
		int ans=0; T.init(); T1.init();
		if (n<=2)return 0;
		for (int i=n-1;i>=0;--i)len1[i]=T1.add(s[i])->len;
		bool flag=0; node *cur=T.pool; int maxl=0;
		for (int i=0;i<n-1;++i){
			nodes[i]=T.add(s[i]); len[i]=nodes[i]->len;
			cur=T.pool+T.get_fail(cur)->next[s[i]-'a'];
			while (cur->len>i+1-maxl)cur=cur->fail;
			if (len1[i+1]==n-i-1)
				if (i-len[i]>=0&&len[i]+len[i-len[i]]==i+1||i&&cur->len&&maxl+cur->len==i+1)flag=1;
			if (len[i]==i+1)maxl=i+1;
		}
		return flag;
	}
};

