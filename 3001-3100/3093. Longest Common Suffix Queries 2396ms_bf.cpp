template<size_t SIZE>
inline int memcmp_fixed_(const unsigned char *s1, const unsigned char *s2){
    for(size_t i = 0; i < SIZE; ++i)
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
    return 0;
}

template<>
inline int memcmp_fixed_<1>(const unsigned char *s1, const unsigned char *s2){
    return *s1 - *s2;
}

inline int fast_memcmp(const void *a1, const void *a2, size_t const size){
	const unsigned char *s1 = (const unsigned char *)a1, *s2 = (const unsigned char *)a2;
    switch(size){
        case  0: return 0;
        case  1: return memcmp_fixed_< 1>(s1, s2);
        case  2: return memcmp_fixed_< 2>(s1, s2);
        case  3: return memcmp_fixed_< 3>(s1, s2);
        case  4: return memcmp_fixed_< 4>(s1, s2);
        case  5: return memcmp_fixed_< 5>(s1, s2);
        case  6: return memcmp_fixed_< 6>(s1, s2);
        case  7: return memcmp_fixed_< 7>(s1, s2);
        case  8: return memcmp_fixed_< 8>(s1, s2);
        case  9: return memcmp_fixed_< 9>(s1, s2);
        case 10: return memcmp_fixed_<10>(s1, s2);
        case 21: return memcmp_fixed_<21>(s1, s2);
        case 22: return memcmp_fixed_<22>(s1, s2);
        case 23: return memcmp_fixed_<23>(s1, s2);
        case 24: return memcmp_fixed_<24>(s1, s2);
        case 25: return memcmp_fixed_<25>(s1, s2);
        case 26: return memcmp_fixed_<26>(s1, s2);
        case 27: return memcmp_fixed_<27>(s1, s2);
        case 28: return memcmp_fixed_<28>(s1, s2);
        case 29: return memcmp_fixed_<29>(s1, s2);
        case 30: return memcmp_fixed_<30>(s1, s2);
        case 31: return memcmp_fixed_<31>(s1, s2);
        default: return memcmp(a1, a2, size);
    }
}

const int N=10005;
int wl[N];
char *wp[N];
class Solution {
public:
    __attribute__((no_sanitize_address,no_sanitize_memory))
    vector<int> stringIndices(vector<string> &w, vector<string> &q) {
        int n=w.size(),m=q.size();
        vector<int> ans(m);
        for (auto &s:w)reverse(s.begin(),s.end());
        for (auto &s:q)reverse(s.begin(),s.end());
        for (int i=0;i<n;++i)wl[i]=w[i].size();
        for (int i=0;i<n;++i)wp[i]=w[i].data();
        for (int i=0;i<m;++i){
        	int t=0,l=1e9;
        	char *q0=q[i].data();
        	int ql=q[i].size();
        	for (int j=0;j<n;++j){
        		char *w0=wp[j];
        		if (wl[j]<t||fast_memcmp(q0,w0,t))continue;
                int t1=t;
        		while (q0[t]==w0[t]&&t<ql&&t<wl[j])++t;
                if (t>t1||wl[j]<l)ans[i]=j,l=w[j].size();
        	}
        }
        return ans;
    }
};
