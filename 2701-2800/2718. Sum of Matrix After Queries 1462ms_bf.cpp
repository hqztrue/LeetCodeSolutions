typedef long long ll;
typedef unsigned int uint;
typedef unsigned short us;
const int N=10015;
uint a[N],a1[N];
us t[N],t1[N];
class Solution {
public:
    ll matrixSumQueries(int n, vector<vector<int>>& q) {
        int m=q.size(),n1=n; ll ans=0,ans1=0;
        for (int i=0;i<n+8;++i)a[i]=a1[i]=0,t[i]=t1[i]=0;
        for (int i=0;i<m;++i){
            int x=q[i][1],v=q[i][2];
            if (q[i][0]==0)a1[x]=v,t1[x]=i+1;
            else a[x]=v,t[x]=i+1;
        }
        while (n%4)t[n]=m+1,++n;
        for (int i=0;i<n;i+=4){
            uint x0=a[i],x1=a[i+1],x2=a[i+2],x3=a[i+3],ans2=0;
            us y0=t[i],y1=t[i+1],y2=t[i+2],y3=t[i+3];
            for (int j=0;j<n1;++j){
                uint a0=a1[j]; us t0=t1[j];
                ans2+=(t0>y0?a0:x0)+(t0>y1?a0:x1)
                     +(t0>y2?a0:x2)+(t0>y3?a0:x3);
            }
            ans+=ans2;
        }
        return ans;
    }
};

