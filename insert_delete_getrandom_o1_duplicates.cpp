https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed


// Approach i: https://zxi.mytechroad.com/blog/hashtable/leetcode-381-insert-delete-getrandom-o1-duplicates-allowed/
class RandomizedCollection {
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
        
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        if (!val2Indices.count(val)) {
            val2Indices[val].push_back(nums.size());
            nums.push_back({val, 0});
            return true;
        }
        val2Indices[val].push_back(nums.size());
        nums.push_back({val, val2Indices[val].size() - 1});
        return false;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if (!val2Indices.count(val)) return false;
        int index2Evict = val2Indices[val].back();
        auto& lastEntry = nums.back();
        
        // update index
        val2Indices[lastEntry.first][lastEntry.second] = index2Evict;
        
        // swap values
        swap(nums[index2Evict], nums.back());
        
        // clean-up
        nums.pop_back();
        val2Indices[val].pop_back();
        if (val2Indices[val].size() == 0) val2Indices.erase(val);
        return true;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        int index = rand() % nums.size();
        return nums[index].first;
    }
    
private:
    // key: val, value: [index]
    unordered_map<int, vector<int>> val2Indices;
    // first: val, second: index in val2Indices
    vector<pair<int, int>> nums;
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

// Approach ii: use map<int, set<int>>
class RandomizedCollection {
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
        
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        if (!val2Indices.count(val)) {
            val2Indices[val] = unordered_set<int>{static_cast<int>(nums.size())};
            nums.push_back(val);
           return true; 
        }
        val2Indices[val].insert(nums.size());
        nums.push_back(val);        
        return false;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if (!val2Indices.count(val)) return false;
        int index = *val2Indices[val].begin();
        // need to change nums.back()'s index to val's index
        val2Indices[val].erase(index); // must put ahead because it might be val == nums.back() and if we first insert(index), we actually did nothing because it's a set!
        val2Indices[nums.back()].insert(index);
        val2Indices[nums.back()].erase(nums.size() - 1);
        swap(nums[index], nums.back());
        nums.pop_back();
        if (val2Indices[val].empty()) val2Indices.erase(val);
        return true;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        int index = rand() % nums.size();
        return nums[index];
    }

private:
    // key: val, value: [index]
    unordered_map<int, unordered_set<int>> val2Indices;
    vector<int> nums;
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */