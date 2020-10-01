typedef unsigned long long ull;
inline int count_bits2(ull x){  //O(log^* W)
	x-=(x&0xaaaaaaaaaaaaaaaaull)>>1;
	x=(x&0x3333333333333333ull)+((x&0xccccccccccccccccull)>>2);
	x=((x*0x11)&0xf0f0f0f0f0f0f0f0ull)>>4;
	return (x*0x0101010101010101ull)>>56;
}
class Solution {
public:
	int hammingWeight(uint32_t n) {
		return count_bits2(n);
	}
};

