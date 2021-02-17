typedef unsigned int uint;
#define pop __builtin_popcount
#define ctz __builtin_ctz
const int N=30005,W=32;
struct node{
	node *prev,*next;
}a[N],*null=new node;
int c[10][N],c1[10],c2[10]; uint cnt[N/W+1];
class Solution {
public:
	string ans;
	const string& minInteger(string &num, int k) {
		int n=num.size(); char *s=&num[0]; ans="";
		for (int i=0;i<10;++i)c1[i]=c2[i]=0;
		for (int i=0;i<n;++i){
			char &ch=s[i]; ch-='0'; c[ch][c1[ch]++]=i;
		}
		for (int i=0;i<10;++i)c[i][c1[i]++]=n;
		memset(cnt,0xFF,sizeof(uint)*(n/W+1));
		for (int i=0;i<n-1;++i)a[i].next=a+i+1; a[n-1].next=null; null->prev=a+n-1;
		for (int i=1;i<n;++i)a[i].prev=a+i-1; a[0].prev=null; null->next=a;
		for (int ch=0;ch<=9;++ch){
			int sum=0,*c=::c[ch];
			for (int i=0;i<c1[ch]-1;++i){
				if (k<n-ans.size()-1)break;
				int j1=i?c[i-1]:0,j=c[i];
				while (j1/W<j/W)sum+=pop(cnt[j1>>5]>>(j1&31)),j1=(j1/W+1)*W;
				sum+=pop(cnt[j>>5]&((1u<<(j&31))-(1u<<(j1&31))));
				k-=sum; ans.push_back(ch+'0'); cnt[j>>5]-=1u<<(j&31);
				a[j].next->prev=a[j].prev; a[j].prev->next=a[j].next;
				++c2[s[j]];
			}
		}
		node *cur=null->next,*end=null; uint h=0;
		if (cur==null)goto end;
		for (int i=0;i<=k;++i){
			end=end->next; char ch=s[end-a]; h|=1u<<ch;
		}
		while (1){
			if (cur==null)break;
			int ch=ctz(h),j=c[ch][c2[ch]];
			++c2[ch]; ans.push_back(ch+'0');
			int sum=0; for (node *p=a+j;p!=cur;p=p->prev)++sum; k-=sum;
			a[j].next->prev=a[j].prev; a[j].prev->next=a[j].next;
			if (c[ch][c2[ch]]>end-a)h-=1u<<ch;
			if (a+j==cur)cur=cur->next;
			if (a+j==end)end=end->prev;
			if (!sum&&end->next!=null)end=end->next,h|=1u<<s[end-a];
			else for (int i=1;i<=min(k+sum,n-(int)ans.size())-min(k+1,n-(int)ans.size());++i){
				ch=s[end-a]; end=end->prev;
				if (c[ch][c2[ch]]>end-a)h-=1u<<ch;
			}
		}
		end:return ans;
	}
};

//IO
int _IO=[](){
	std::ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

