#include<iostream>
#include<vector>
using namespace std;

class segment {
    public:
        vector<int> seg;
        vector<int> lazy;
        int n;

    segment(vector<int>& nums){
        if(nums.size() > 0) {
            n = nums.size();
            seg.resize(4*n, 0);
            lazy.resize(4*n, 0);
            build(0, 0, n - 1, nums);
        }
    }

    void build(int index, int left, int right, vector<int>& nums){
        if(left == right){
            seg[index] = nums[left];
            return;
        }
        int mid = (left + right)/2;
        build(2*index + 1, left, mid, nums);
        build(2*index + 2, mid + 1, right, nums);
        seg[index] = seg[2*index + 1] + seg[2*index + 2];
    }

    int queryUtil(int index, int left, int right, int qMin, int qMax){
        propogate(index, left, right);
        if(left > qMax || right < qMin) return 0;
        if(qMin <= left && right <= qMax) return seg[index];
        int mid = (left + right)/2;
        return queryUtil(2*index + 1, left, mid, qMin, qMax) + queryUtil(2*index + 2, mid + 1, right, qMin, qMax);
    }

    int query(int left, int right){ 
        if(n==0)return 0;
        return queryUtil(0, 0, n-1, left, right);
    }

    void updateUtil(int index, int left, int right, int pos, int diff){ 
        if(pos < left || pos > right) return;
        if(left == pos && left == right){
            seg[index] += diff;
            return;
        }
        int mid = (left + right)/2;
        updateUtil(2*index + 1, left, mid, pos, diff);
        updateUtil(2*index + 2, mid + 1, right, pos, diff);
        seg[index] = seg[2*index + 1] + seg[2*index + 2];
    }

    void update(int pos, int diff){ 
        if(n==0)return;
        return updateUtil(0, 0, n-1, pos, diff);
    }

    void updateRangeUtil(int index, int left, int right, int qMin, int qMax, int diff){
        propogate(index, left, right);
        if(right < qMin || left > qMax) return;
        if(left == right) {
            seg[index] += diff;
        }
        else if(qMin <= left && right <= qMax){
            lazy[index] += diff;
            propogate(index, left, right);
        } else {
            int mid = (left + right)/2;
            updateRangeUtil(2*index + 1, left, mid, qMin, qMax, diff);
            updateRangeUtil(2*index + 2, mid + 1, right, qMin, qMax, diff);
            seg[index] = seg[2*index + 1] + seg[2*index + 2];
        }
    }

    void updateRange(int left, int right, int diff){ 
        if(n==0)return;
        return updateRangeUtil(0, 0, n-1, left, right, diff);
    }

    void propogate(int index, int left, int right){
        if(left == right){
            seg[index] += lazy[index];
            lazy[index] = 0;
        } else {
            seg[index] += (right - left + 1)*lazy[index];
            lazy[2*index + 1] += lazy[index];
            lazy[2*index + 2] += lazy[index];
            lazy[index] = 0;
        }
    }

    void print(){
        for(int i = 0; i < (2*n - 1); i++){
            cout << seg[i] << " ";
        }
        cout << "\n";
        for(int i = 0; i < (2*n - 1); i++){
            cout << lazy[i] << " ";
        }
        cout << "\n";
    }
};

int main() {
    vector<int> nums = {1,2,3,4,5,6,7,8};
    segment* seg = new segment(nums);
    seg->print();
    cout << seg->query(0, 2) << "\n";
    seg->updateRange(1, 4, 2);
    seg->print();
    cout << seg->query(0, 2) << "\n";
    return 0;
}