class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> mp;
        for(int i=0; i<nums.size(); ++i){
            if (mp.count(target-nums[i])==1)
                return vector<int>{i,mp[target-nums[i]]};
            mp[nums[i]]=i;
        }
        return vector<int>{};
    }
};
#define main main(int argc, char *argv[]) { \
    char SEPARATOR[] = "\x1b" "\x09" "\x1d"; \
    setbuf(stdout, NULL); \
    ofstream fout("user.out"); \
    string line; \
    while (getline(cin, line)) { \
        vector<int> param_1 = _des_.deserialize<vector<int>>(line); \
        getline(cin, line); \
        int param_2 = _des_.deserialize<int>(line); \
        vector<int> ret = __DriverSolution__().__helper__( \
          param_1, param_2 \
        ); \
        string out = _ser_.serialize(ret); \
        fout << out << endl; \
        cout << SEPARATOR; \
    } \
    return 0; \
} \
int _main
