typedef unsigned int uint;
const int N=100005;
int a[N],q[N]; uint even[N],odd[N];
inline void add(uint *a,int i,uint t=1){a[i/32]+=t*(1<<(i%32));}
class Solution {
public:
    vector<int> minReverseOperations(int n, int p, vector<int>& b, int k) {
    	for (int i=0;i<n;++i)a[i]=-1,even[i]=odd[i]=0;
        for (auto &x:b)a[x]=0;
        int h=0,t=1; q[0]=p; a[p]=0;
        for (int i=0;i<n;++i)
        	if (a[i]==-1)
        		if (i%2)add(odd,i/2);
        		else add(even,i/2);
        while (h<t){
        	int x=q[h++],d=a[x],l1=max(0,x-k+1),r1=min(n-k,x),
        		l=l1*2+k-1-x,r=r1*2+k-1-x;
        	if (l>r)swap(l,r);
        	//for (int i=l;i<=r;i+=2)
        	//	if (a[i]==-1)a[i]=d+1,q[t++]=i;
        	uint *c=l%2?odd:even;
        	for (;l%64>1&&l<=r;l+=2)
        		if (a[l]==-1)a[l]=d+1,add(c,l/2,-1),q[t++]=l;
        	for (;r%64<62&&r>=0&&r>=l;r-=2)
        		if (a[r]==-1)a[r]=d+1,add(c,r/2,-1),q[t++]=r;
        	if (l>r)continue;
        	for (int j=l/64,d0=l%2;j<=r/64;++j)
        		while (c[j]){
        			int k=__builtin_ctz(c[j]),i=(j*32+k)*2+d0;
        			add(c,j*32+k,-1);
        			a[i]=d+1,q[t++]=i;
        		}
        }
        for (auto &x:b)a[x]=-1;
        vector<int> ans(a,a+n);
        return ans;
    }
};

