namespace wTrie{
	typedef unsigned int uint;
	const int N=100005,W=32;  //[0,2^20)
	uint a1[N/W+5],a2[N/W/W+5],a3[N/W/W/W+5],a4;
	#define max_bit(x) 31-__builtin_clz(x)
	#define min_bit(x) __builtin_ctz(x)
	#define get_bit(x) (1u<<((x)&31u))
	#define get_bit1(x) (1u<<(x))
	void init(int n=N){
		memset(a1,0xFF,sizeof(uint)*(n/W+1));
		memset(a2,0xFF,sizeof(uint)*(n/W/W+1));
		memset(a3,0xFF,sizeof(uint)*(n/W/W/W+1));
		a4=0xFFFFFFFF;
	}
	inline bool find(uint x){
		return (a1[x>>5]>>(x&31))&1;
	}
	inline void add(uint x){
		a1[x>>5]|=get_bit(x);
		a2[x>>10]|=get_bit(x>>5);
		a3[x>>15]|=get_bit(x>>10);
		a4|=get_bit1(x>>15);
	}
	inline void del(uint x){
		if (a1[x>>5]&get_bit(x))
			if (!(a1[x>>5]-=get_bit(x)))
				if (!(a2[x>>10]-=get_bit(x>>5)))
					if (!(a3[x>>15]-=get_bit(x>>10)))
						a4-=get_bit1(x>>15);
	}
	inline int get_min(){
		//if (!a4)return -1;
		uint x=min_bit(a4);
		x=(x<<5)+min_bit(a3[x]);
		x=(x<<5)+min_bit(a2[x]);
		return (x<<5)+min_bit(a1[x]);
	}
} using namespace wTrie;
class SeatManager {
public:
	SeatManager(int n) {
		init(n); del(0);
	}
	int reserve() {
		int x=get_min(); del(x);
		return x;
	}
	void unreserve(int x) {
		add(x);
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();

