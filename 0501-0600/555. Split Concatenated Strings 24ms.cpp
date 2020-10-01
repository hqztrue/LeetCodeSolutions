#define N 3105
namespace SA{
	int sa[N],h[N],rk[N],c[N],l[N],p[N],s[N<<1],t[N<<1];
	#define pushS(x) sa[l[s[x]]--]=x
	#define pushL(x) sa[l[s[x]]++]=x
	#define _sort(v) fill(sa,sa+n,-1),fill(c,c+m,0); \
		for (int i=0;i<=n-1;++i)++c[s[i]]; for (int i=1;i<=m-1;++i)c[i]+=c[i-1]; \
		l[0]=0; for (int i=1;i<=m-1;++i)l[i]=c[i]-1; for (int i=n1-1;i>=0;--i)pushS(v[i]); \
		l[0]=0; for (int i=1;i<=m-1;++i)l[i]=c[i-1]; for (int i=0;i<=n-1;++i) if (sa[i]>0&&t[sa[i]-1])pushL(sa[i]-1); \
		for (int i=0;i<=m-1;++i)l[i]=c[i]-1; for (int i=n-1;i>=0;--i) if (sa[i]>0&&!t[sa[i]-1])pushS(sa[i]-1);
	void sais(int n,int m,int *s,int *t,int *p){
		int n1=t[n-1]=0,ch=rk[0]=-1,*s1=s+n;
		for (int i=n-2;i>=0;--i)t[i]=s[i]!=s[i+1]?s[i]>s[i+1]:t[i+1];
		for (int i=1;i<=n-1;++i)rk[i]=t[i-1]&&!t[i]?p[n1]=i,n1++:-1;
		_sort(p);
		for (int i=0,x,y;i<n;++i) if (sa[i]<0||~(x=rk[sa[i]])){
			if (ch<1||p[x+1]-p[x]!=p[y+1]-p[y])++ch;
			else for (int j=p[x],k=p[y];j<=p[x+1];++j,++k)
				if ((s[j]<<1|t[j])!=(s[k]<<1|t[k])){++ch; break;}
			s1[y=x]=ch;
		}
		if (ch+1<n1)sais(n1,ch+1,s1,t+n,p+n1);
		else for (int i=0;i<=n1-1;++i)sa[s1[i]]=i;
		for (int i=0;i<=n1-1;++i)s1[i]=p[sa[i]];
		_sort(s1);
	}
	template<class T>
	void SA(const T &_s,int n){
		for (int i=0;i<=n-1;++i)s[i]=_s[i]; s[n++]=0;
		sais(n,255,s,t,p);
		for (int i=0;i<=n-1;++i)rk[sa[i]]=i;
		for (int i=0,k=0;i<n-1;h[rk[i++]]=k)
			for (k&&k--;s[i+k]==s[sa[rk[i]-1]+k];++k);
	}
} using SA::sa; using SA::h; using SA::rk;

namespace RMQ{
	const int D_max=13,L=15,inf=1<<30;
	int f[N/L][D_max],M[N/L],a[N+L],stack[L+1],n,q,D;
	struct node{
		int state[L+1],*a;
		int Qmin(int x,int y){return a[x+__builtin_ctz(state[y]>>x)];}
		void init(int *_a){
			int top=0;a=_a;
			for (int i=1;i<=L;++i){
				state[i]=state[i-1];
				while (top&&a[i]<=a[stack[top]])state[i]-=1<<stack[top],--top;
				stack[++top]=i;state[i]+=1<<i;
			}
		}
	}c[N/L];
	void build(){
		int nn=n/L;M[0]=-1;
		for (int i=1;i<=nn;++i){
			f[i][0]=inf;for (int j=1;j<=L;++j)f[i][0]=min(f[i][0],a[(i-1)*L+j]);
		}
		for (int i=1;i<=nn;++i)M[i]=!(i&(i-1))?M[i-1]+1:M[i-1];
		for (int j=1;j<=D;++j)
			for (int i=1;i<=nn-(1<<j)+1;++i)f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
		for (int i=1;i<=nn+1;++i)c[i].init(a+(i-1)*L);
	}
	int Qmin_ST(int x,int y){
		int z=M[y-x+1];return min(f[x][z],f[y-(1<<z)+1][z]);
	}
	int Qmin(int x,int y){
		if (x>y)return 1<<30;
		int xx=(x-1)/L+1,yy=(y-1)/L+1,res;
		if (xx+1<=yy-1)res=Qmin_ST(xx+1,yy-1);else res=inf;
		if (xx==yy)res=min(res,c[xx].Qmin(x-(xx-1)*L,y-(yy-1)*L));
		else res=min(res,c[xx].Qmin(x-(xx-1)*L,L)),res=min(res,c[yy].Qmin(1,y-(yy-1)*L));
		return res;
	}
}; using RMQ::a; using RMQ::Qmin;

int rev[N],sta[N]; char s[N];
struct str{
	int p[3],l[3];
	bool operator <(const str &A)const{
		int i1=0,i2=0,j1=0,j2=0;
		while (i1<3&&i2<3){
			if (!l[i1]){++i1; continue;}
			if (!A.l[i2]){++i2; continue;}
			int r1=rk[p[i1]+j1],r2=rk[A.p[i2]+j2];
			if (r1>r2)swap(r1,r2);
			int len=Qmin(r1+1,r2),len1=min(l[i1]-j1,A.l[i2]-j2);
			if (len==0)return s[p[i1]+j1]<s[A.p[i2]+j2];
			j1+=min(len,len1); if (j1==l[i1])++i1,j1=0;
			j2+=min(len,len1); if (j2==A.l[i2])++i2,j2=0;
		}
		return 0;
	}
	string to_str()const{
		return string(s+p[0],l[0])+string(s+p[1],l[1])+string(s+p[2],l[2]);
	}
};
class Solution {
public:
	string splitLoopedString(vector<string>& strs) {
		int n=strs.size(),m=0,s1=0;
		for (int i=0;i<n;++i){
			sta[i]=s1; m+=strs[i].size();
			if (rev[i]=strs[i]<string(strs[i].rbegin(),strs[i].rend()))
				for (int j=strs[i].size()-1;j>=0;--j)s[s1++]=strs[i][j];
			else for (int j=0;j<strs[i].size();++j)s[s1++]=strs[i][j];
		}
		for (int i=0;i<m;++i)s[s1++]=s[i];
		s[s1++]='#';
		for (int i=0;i<n;++i){
			if (rev[i])for (int j=0;j<strs[i].size();++j)s[s1++]=strs[i][j];
			else for (int j=strs[i].size()-1;j>=0;--j)s[s1++]=strs[i][j];
		}
		SA::SA(s,s1);
		RMQ::n=s1; RMQ::D=int(log2(RMQ::n))+1;
		for (int i=1;i<=s1;++i)a[i]=h[i];
		RMQ::build();
		str ans,now; ans.p[0]=m*2; ans.l[0]=1;
		for (int i=0;i<n;++i){
			int m1=strs[i].size();
			now.p[1]=sta[(i+1)%n]; now.l[1]=m-m1;
			for (int j=0;j<m1;++j){
				now.l[0]=j; now.l[2]=m1-j;
				now.p[0]=sta[i]+m1-j; now.p[2]=sta[i];
				if (ans<now)ans=now;
				now.p[0]=sta[i]+m*2+1+m1-j; now.p[2]=sta[i]+m*2+1;
				if (ans<now)ans=now;
			}
		}
		return ans.to_str();
	}
};


