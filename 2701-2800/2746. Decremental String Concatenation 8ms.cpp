const int N=1005,CH=256,inf=1<<20;
int f[CH],f1[CH];
inline void upd(int &x,int y){if (y>x)x=y;}
class Solution {
public:
	int minimizeConcatenatedLength(vector<string>& a) {
		int n=a.size(),add=0,add1=0,ma=0,ma1=0;
		for (int i='a';i<='z';++i)f[i]=f1[i]=-inf;
		f[a[0][0]]=0; f1[a[0].back()]=0;
		for (int i=1;i<n;++i){
			char x=a[i-1][0],y=a[i-1].back(),x1=a[i][0],y1=a[i].back();
			int v=max(f[y1]+1+add,ma),v1=max(f1[x1]+1+add1,ma1);
			if (y==x1)++add,++ma;
			if (y1==x)++add1,++ma1;
			upd(ma1,v); upd(ma,v1);
			upd(f1[y],v-add1); upd(f[x],v1-add);
		}
		int ans=-max(ma,ma1);
		for (int i=0;i<n;++i)ans+=a[i].size();
		return ans;
	}
};
