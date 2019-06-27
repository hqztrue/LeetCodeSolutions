class Solution {
public:
    vector<int> countBits(int num) {
        return vector<int>();
    }
};

//fastIO
namespace Read{
	const int S=3000000;
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
	inline bool read_next_digit(){while (*p&&(*p<'0'||*p>'9'))++p; return *p!=0;}
	void read_init(){fread(p,1,S,stdin);}
	
	const int S1=3000000;
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
			print(a[i]);
			if (i==n-1)print("]\n");
			else print(',');
		}
	}
	inline void flush(FILE *fout=stdout){fwrite(_out,1,o-_out,fout); o=_out;}
	struct zzy{zzy(){read_init();}}zzy;
	struct zzy1{FILE *fout; zzy1(){fout=fopen("./user.out","w");} ~zzy1(){flush(fout);}}zzy1;
}
using namespace Read;

const int N=100005;
int c[N];
//main
int _main=[](){
	//FILE *fout=fopen("./user.out","w");
	int cur=0; c[0]=0;
	while (1){
		if (!read_next_digit())break;
		int n; read(n);
		for (int i=cur+1;i<=n;++i)c[i]=c[i>>1]+(i&1);
		cur=max(cur,n);
		print(c,n+1);
	} 
	exit(0);
    return 0;
}();


