const int N=100005;
int x[N],y[N],d[N];
template<int N0>
int calc(vector<vector<int>>& a) {
    int n=a.size(),m=a[0].size(),h=0,t=1;
    x[0]=y[0]=0; d[0]=1;
    bitset<N/N0*10> row[n];
    bitset<N0> col[m];
    for (int i=0;i<n;++i)row[i].flip();
    for (int i=0;i<m;++i)col[i].flip();
    while (h<t){
        int x0=x[h],y0=y[h],d0=d[h++],l=a[x0][y0];
        if (x0==n-1&&y0==m-1)return d0;
        for (int i=row[x0]._Find_next(y0);i<m&&i<=y0+l;i=row[x0]._Find_next(i))
            row[x0].set(i,0),col[i].set(x0,0),x[t]=x0,y[t]=i,d[t]=d0+1,++t;
        for (int i=col[y0]._Find_next(x0);i<n&&i<=x0+l;i=col[y0]._Find_next(i))
            row[i].set(y0,0),col[y0].set(i,0),x[t]=i,y[t]=y0,d[t]=d0+1,++t;
    }
    return -1;
}
class Solution {
public:
    int minimumVisitedCells(vector<vector<int>>& a) {
        int n=a.size();
        if (n<=10)return calc<10>(a);
        if (n<=100)return calc<100>(a);
        if (n<=1000)return calc<1000>(a);
        if (n<=10000)return calc<10000>(a);
        return calc<100000>(a);
    }
};

