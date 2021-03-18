typedef unsigned int uint;
inline bool cmp(vector<int> *a, vector<int> *b){return (*a)[0]<(*b)[0]||(*a)[0]==(*b)[0]&&(*a)[1]>(*b)[1];}
class Solution {
public:
	vector<int> *A[1005];
	vector<vector<int>> reconstructQueue(vector<vector<int>>& a) {
		uint c[36],n=a.size(),m=n?(n-1)/32+1:0;
		for (int i=0;i<n;++i)A[i]=&a[i];
		sort(A,A+n,cmp);
		vector<vector<int> > res(n);
		for (int i=0;i<m;++i)c[i]=~0u;
		int m1=m/2+1,sum1=m1*32;
		for (int I=0;I<n;++I){
			vector<int> *it=A[I];
			int s=(*it)[1]+1,i0=0;
			if (s>sum1)i0=m1,s-=sum1;
			for (int i=i0;i<m;++i){
				int s1=__builtin_popcount(c[i]);
				if (s<=s1){
					int j=0; uint &c1=c[i];
					if (__builtin_popcount(c1<<(j+16))>=s)j+=16;
					if (__builtin_popcount(c1<<(j+8))>=s)j+=8;
					if (__builtin_popcount(c1<<(j+4))>=s)j+=4;
					if (__builtin_popcount(c1<<(j+2))>=s)j+=2;
					if (__builtin_popcount(c1<<(j+1))>=s)j+=1;
					j=31-j; c1-=1u<<j;
					res[i*32+j]=*it;
					if (i0==0)--sum1;
					break;
				}
				s-=s1;
			}
		}
		return res;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

