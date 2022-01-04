vector<vector<int>> a;
inline int get(int i,int j){
	return a[i][j];
}
struct row{
	int i;
	row(int _i=0):i(_i){}
	int operator [](int j)const{return get(i,j);}
};
struct matrix{
	row operator [](int i)const{return row(i);}
}M;
class Solution {
public:
	pair<int,int> select(const vector<int> &id,int *k){
		int n=id.size();
		if (n<=2){
			vector<int> v;
			for (int i:id)
				for (int j:id)v.push_back(M[i][j]);
			sort(v.begin(),v.end());
			return {v[k[0]],v[k[1]]}; 
		}
		vector<int> _id;
		for (int i=0;i<n;i+=2)_id.push_back(id[i]);
		if (n%2==0)_id.push_back(id.back());
		int _k[2]={k[0]/4,n%2==0?k[1]/4+n+1:(k[1]+n*2+1)/4};
		auto ans=select(_id,_k);
		int _x[2]={ans.first,ans.second};
		int less[2]={0,0},cols[2]={n,n};
		vector<int> v;
		for (int i1=0;i1<n;++i1){
			int i=id[i1];
			for (int I=0;I<=1;++I){
				while (cols[I]&&M[i][id[cols[I]-1]]>=_x[I])--cols[I];
				less[I]+=cols[I];
			}
			for (int j=cols[0];j<cols[1];++j)v.push_back(M[i][id[j]]);
		}
		int x[2];
		for (int I=0;I<=1;++I){
			int k0=k[I];
			if (k0<less[0])x[I]=_x[0];
			else if (k0<less[1]){
				int offset=k0-less[0];
				nth_element(v.begin(),v.begin()+offset,v.end());
				x[I]=v[offset];
			}
			else x[I]=_x[1];
		}
		return {x[0],x[1]};
	}
	int kthSmallest(vector<vector<int>>& _a, int k) {
		int n=_a.size(); a=_a;
		vector<int> id(n);
		for (int i=0;i<n;++i)id[i]=i;
		int _k[2]={k-1,k-1};
		return select(id,_k).first;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

