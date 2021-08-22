#define N 10005
#define eps 1e-6
struct node{double x,y;}p[N],O;
int n; double r;
inline double dist2(const node &x,const node &y){return (x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y);}
inline void calc(double a,double b,double c,double d,double e,double f){
	O.y=(c*d-f*a)/(b*d-e*a); O.x=(c*e-f*b)/(a*e-b*d);
}
class Solution {
public:
	vector<double> outerTrees(vector<vector<int>>& a) {
		n=a.size();
		for (int i=1;i<=n;++i)p[i].x=a[i-1][0],p[i].y=a[i-1][1];
		random_shuffle(p+1,p+1+n);
		O=p[1];r=0;
		for (int i=2;i<=n;++i)if (dist2(O,p[i])-r*r>eps){
			O=p[i];r=0;
			for (int j=1;j<i;++j)if (dist2(O,p[j])-r*r>eps){
				O.x=(p[i].x+p[j].x)/2; O.y=(p[i].y+p[j].y)/2; r=sqrt(dist2(O,p[j]));
				for (int k=1;k<j;++k)if (dist2(O,p[k])-r*r>eps){
					calc(p[j].x-p[i].x,p[j].y-p[i].y,
					(p[j].x*p[j].x+p[j].y*p[j].y-p[i].x*p[i].x-p[i].y*p[i].y)/2,
					p[k].x-p[i].x,p[k].y-p[i].y,
					(p[k].x*p[k].x+p[k].y*p[k].y-p[i].x*p[i].x-p[i].y*p[i].y)/2);
					r=sqrt(dist2(O,p[k]));
				}
			}
		}
		return {O.x,O.y,r};
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

