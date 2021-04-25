const int L=10000;
class Solution {
public:
	int maxIceCream(vector<int>& _c, int C) {
		int *c=&_c[0],l=0,r=_c.size();
		while (l<r){
			int s=0,mid=(l+r)/2; nth_element(c+l,c+mid,c+r);
			for (int i=l;i<=mid&&s<=C;i+=L)s=accumulate(c+i,c+min(i+L,mid+1),s);
			if (s>C)r=mid; else l=mid+1,C-=s;
		}
		return l;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

