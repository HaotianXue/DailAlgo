https://leetcode.com/problems/insert-delete-getrandom-o1/

class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (val2Index.count(val)) return false;
        val2Index[val] = nums.size();
        nums.push_back(val);
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) { // swap last number and element needs to be removed
        if (!val2Index.count(val)) return false;
        int index = val2Index[val];
        val2Index[nums.back()] = index;
        val2Index.erase(val);
        swap(nums[index], nums.back());
        nums.pop_back();
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        int index = rand() % nums.size();
        return nums[index];
    }
    
private:
    unordered_map<int, int> val2Index;
    vector<int> nums;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */