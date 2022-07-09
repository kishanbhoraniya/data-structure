#include<iostream>
#include<vector>
using namespace std;

class heap {
    public:
        int arr[100];
        int size;

    heap(vector<int> arr1) {
        arr[0] = -1;
        for(int i = 1; i <= arr1.size(); i++){
            arr[i] = arr1[i - 1];
        }
        size = arr1.size();
        build_heap();
    }

    void heapify(int index) {
        int left = 2 * index;
        int right = (2 * index) + 1;
        int largest = index;
        if(left <= size && arr[index] < arr[left]){
            swap(arr[index], arr[left]);
            largest = left;
        }
        if(right <= size && arr[index] < arr[right]){
            swap(arr[index], arr[right]);
            largest = right;
        }
        if(largest != index){
            heapify(largest);
        }
    }

    void build_heap(){
        for(int i = size/2; i >= 1; i--){
            heapify(i);
        }
    }

    void insert(int value) {
        arr[++size] = value;
        int index = size;
        while(index > 1){
            int parent = (index/2);
            if (arr[parent] < arr[index]) {
                swap(arr[parent], arr[index]);
                index = parent;
            } else {
                return;
            }
        }
    }

    void deleteElement() {
        if(size == 0) {
            cout << "No element to delete" << "\n";
            return; 
        }
        arr[1] = arr[size];
        size--;
        heapify(1);
    }

    void print() {
        for(int i = 1; i <= size; i++){
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
};

int main() {
    vector<int> arr = {10, 15, 20, 14};
    heap h(arr);
    h.deleteElement();
    h.deleteElement();
    h.deleteElement();
    h.deleteElement();
    h.deleteElement();
    h.print();
    h.insert(50);
    h.print();
    return 0;
}