typedef long long ll;
const ll inf=~0ull>>2;
vector<int> A1,A2,B1,B2;
int nA1,nA2,nB1,nB2,n;
inline ll get(int i,int j){
	if (i<nA1)return j<nB2?-inf:(ll)A1[i]*B1[j-nB2];
	else if (i<nA1+nA2)return j<nB2?(ll)A2[i-nA1]*B2[j]:inf;
	else return inf;
}
struct row{
	int i;
	row(int _i=0):i(_i){}
	ll operator [](int j)const{return get(i,j);}
};
struct matrix{
	row operator [](int i)const{return row(i);}
}M;
class Solution {
public:
	pair<ll,ll> select(const vector<int> &id,ll *k){
		int n=id.size();
		if (n<=2){
			vector<ll> v;
			for (int i:id)
				for (int j:id)v.push_back(M[i][j]);
			sort(v.begin(),v.end());
			return {v[k[0]],v[k[1]]}; 
		}
		vector<int> _id;
		for (int i=0;i<n;i+=2)_id.push_back(id[i]);
		if (n%2==0)_id.push_back(id.back());
		ll _k[2]={k[0]/4,n%2==0?k[1]/4+n+1:(k[1]+n*2+1)/4};
		auto ans=select(_id,_k);
		ll _x[2]={ans.first,ans.second};
		ll less[2]={0,0},cols[2]={n,n};
		vector<ll> v;
		for (int i1=0;i1<n;++i1){
			int i=id[i1];
			for (int I=0;I<=1;++I){
				while (cols[I]&&M[i][id[cols[I]-1]]>=_x[I])--cols[I];
				less[I]+=cols[I];
			}
			for (int j=cols[0];j<cols[1];++j)v.push_back(M[i][id[j]]);
		}
		ll x[2];
		for (int I=0;I<=1;++I){
			ll k0=k[I];
			if (k0<less[0])x[I]=_x[0];
			else if (k0<less[1]){
				ll offset=k0-less[0];
				nth_element(v.begin(),v.begin()+offset,v.end());
				x[I]=v[offset];
			}
			else x[I]=_x[1];
		}
		return {x[0],x[1]};
	}
	void rev(vector<int> &a){reverse(a.begin(),a.end());}
	ll kthSmallestProduct(vector<int>& a1, vector<int>& a2, ll k) {
		int n=a1.size(),m=a2.size();
		vector<int> negA,negB,posA,posB;
		for (int i=0;i<n;++i)
			if (a1[i]>=0)posA.push_back(a1[i]);
			else negA.push_back(a1[i]);
		for (int i=0;i<m;++i)
			if (a2[i]>=0)posB.push_back(a2[i]);
			else negB.push_back(a2[i]);
		int nA=negA.size(),nB=negB.size(),pA=posA.size(),pB=posB.size();
		ll num_neg=(ll)nA*pB+(ll)pA*nB,num_pos=(ll)nA*nB+(ll)pA*pB;
		if (k<=num_neg){
			A1=negA,B1=posB,A2=posA,B2=negB;
			rev(B1); rev(A2);
		}
		else {
			k-=num_neg,A1=negA,B1=negB,A2=posA,B2=posB;
			rev(A1); rev(B1);
		}
		if (A1.size()+A2.size()>B1.size()+B2.size())swap(A1,B1),swap(A2,B2);
		nA1=A1.size(); nB1=B1.size(); nA2=A2.size(); nB2=B2.size(); n=nB1+nB2;
		vector<int> id(n);
		for (int i=0;i<n;++i)id[i]=i;
		k+=(ll)nA1*nB2; ll _k[2]={k-1,k-1};
		return select(id,_k).first;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

