typedef long long ll;
const int inf=~0u>>1;
int *a1,*a2,n,m;
inline int get(int i,int j){
	return a1[i]==inf||a2[j]==inf?inf:a1[i]+a2[j];
}
class Solution {
public:
	pair<int,int> select(const vector<int> &id,int *k){
		int n=id.size();
		if (n<=2){
			vector<int> v;
			for (int i:id)
				for (int j:id)v.push_back(get(i,j));
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
				while (cols[I]&&get(i,id[cols[I]-1])>=_x[I])--cols[I];
				less[I]+=cols[I];
			}
			for (int j=cols[0];j<cols[1];++j)v.push_back(get(i,id[j]));
		}
		int x[2];
		for (int I=0;I<=1;++I){
			int k0=k[I];
			if (k0<less[0])x[I]=_x[0];
			else if (k0<less[1]){
				int offset=k0-less[0];
				nth_element(&v[0],&v[0]+offset,&v[0]+v.size());
				x[I]=v[offset];
			}
			else x[I]=_x[1];
		}
		return {x[0],x[1]};
	}
	vector<vector<int>> kSmallestPairs(vector<int>& _a1, vector<int>& _a2, int k) {
		n=_a1.size(); m=_a2.size(); k=min((ll)k,(ll)n*m);
		n=min(n,k); m=min(m,k);
		if (n<m){for (int i=n;i<m;++i)_a1.push_back(inf); n=m;}
		else {for (int i=m;i<n;++i)_a2.push_back(inf); m=n;}
		a1=&_a1[0]; a2=&_a2[0];
		vector<int> id(n);
		for (int i=0;i<n;++i)id[i]=i;
		int _k[2]={k-1,k-1},v=select(id,_k).first;
		vector<vector<int>> ans,ans1;
		for (int i=0;i<n;++i){
			int j=0;
			while (j<m&&get(i,j)<v)ans.push_back({a1[i],a2[j]}),++j;
			while (j<m&&get(i,j)==v&&ans.size()+ans1.size()<k)ans1.push_back({a1[i],a2[j]}),++j;
		}
		for (int i=0;i<ans1.size();++i)
			if (ans.size()<k)ans.push_back(ans1[i]);
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

