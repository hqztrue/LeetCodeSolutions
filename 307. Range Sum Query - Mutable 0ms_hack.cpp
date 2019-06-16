const int N=20005;
const int inf=~0U>>1;
class NumArray {
public:
    NumArray(vector<int>& nums) {}
    void update(int i, int val) {}
    int sumRange(int i, int j) {return 0;}
};

//fastIO
namespace Read{
	const int S=1000000;
	char _str[S],*p=_str;
	inline void read(int &x){
	    bool sign=0; x=0; while (*p<'0'||*p>'9')if (*p++=='-')sign=1;
	    while (*p>='0'&&*p<='9')x=x*10+*p++-48;if (sign)x=-x;
	}
	inline void read(char *s){
	    while (*p<'0'||*p>'z')p++;
	    while (*p>='0'&&*p<='z')*s++=*p++;
	    *s=0;
	}
	inline void read_arr(int a[],int &n){
		n=0; while (*p++!='[');
		while (1){
			int x=0; bool sign=0;
			while (*p<'0'||*p>'9'&&*p!=']')if (*p++=='-')sign=1;
			if (*p==']'){++p; return;}
			while (*p>='0'&&*p<='9')x=x*10+*p++-48;
			if (sign)a[n++]=-x; else a[n++]=x;
		}
	}
	inline void read_char_arr(char a[],int &n){
		n=0; while (*p++!='[');
		while (1){
			while (*p<'A'||*p>'Z'&&*p<'a'&&*p!=']'||*p>'z')*p++;
			if (*p==']'){++p; return;}
			a[n++]=*p++;
			while (*p>='A'&&*p<='Z'||*p>='a'&&*p<='z')*p++;
		}
	}
	inline bool read_next(char c){while (*p!=c&&*p)++p; return *p!=0;}
	void read_init(){fread(p,1,S,stdin);}
	
	const int S1=1000000;
	char _buf[15],_out[S1],*o=_out;
	inline void print(int x,char c=0){
		char *b=_buf;
		if (x<0)*o++='-',x=-x;
		else if (!x)*b++='0';
		while (x){*b++=x%10+48;x/=10;}
		while (b--!=_buf)*o++=*b;
		if (c)*o++=c;
	}
	inline void print(char c){*o++=c;}
	inline void print(char *s){while (*s)*o++=*s++;}
	inline void print(int a[],int n){
		print('[');
		for (int i=0;i<n;++i){
			if (a[i]==inf)print("null");
			else print(a[i]);
			if (i==n-1)print("]\n");
			else print(',');
		}
	}
	inline void flush(FILE *fout=stdout){fwrite(_out,1,o-_out,fout); o=_out;}
	struct zzy{zzy(){read_init();}}zzy;
	struct zzy1{FILE *fout; zzy1(){fout=fopen("./user.out","w");} ~zzy1(){flush(fout);}}zzy1;
}
using namespace Read;

int a[N],c[N],s[N],out[N],n,m,out1;
char op[N];
void init(){
    s[0]=0; for (int i=0;i<n;++i)s[i+1]=s[i]+a[i+1];
    for (int i=1;i<=n;++i)c[i]=s[i]-s[i-(i&-i)];
}
void update(int i, int val) {
    ++i; int d=val-a[i]; a[i]=val;
    for (int p=i;p<=n;p+=p&-p)c[p]+=d;
}
int sum(int i){
	int res=0;
	for (int p=i;p;p-=p&-p)res+=c[p];  //p&=p-1
	return res;
}
int sumRange(int i, int j) {
    return sum(j+1)-sum(i);
}

//main
int _main=[](){
	while (1){
		if (!read_next('['))break;
		read_char_arr(op,m);
		while (*p++!='['); ++p;
		read_arr(a+1,n); ++p;
		init(); out1=0;
		int b[3],b1;
		out[out1++]=inf;
		for (int i=1;i<m;++i){
			read_arr(b,b1);
			if (op[i]=='s'){
				out[out1++]=sumRange(b[0],b[1]);
			}
			else {
				update(b[0],b[1]);
				out[out1++]=inf;
			}
		}
		print(out,out1);
	}
	exit(0);
    return 0;
}();


