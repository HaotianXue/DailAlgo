// https://leetcode.com/problems/my-calendar-iii/
class MyCalendarThree {
public:
    MyCalendarThree() {
        timeMap.clear();
    }
    
    int book(int start, int end) {
        ++timeMap[start];
        --timeMap[end];
        
        int res = 0, cnt = 0;
        for (auto kv: timeMap) {
            int time = kv.first, values = kv.second;
            cnt += values;
            res = max(res, cnt);
        }
        return res;
    }
    
private:
    map<int, int> timeMap;
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(start,end);
 */