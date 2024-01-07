#include <iostream>
#include <cmath>
#include <ctime>
#include <random>

using namespace std;

int random(){
    random_device rd;
    default_random_engine dfe(rd());
    uniform_int_distribution<int> number(1, 100);
    return number(dfe);
}

template <typename T>
class DynamicArray{
public:
    T* array;
    int size;
    int capacity;

    DynamicArray() :  size(0), capacity(1) ,array(nullptr) {}
    ~DynamicArray() {
        delete[] array;
    }

    void add(T data) {
        if (capacity == 0) {
            capacity++;
            array = new T[capacity];
        }
        else if (size == capacity) {
            capacity *= 2;
            T* temp = new T[capacity];
            for (int i = 0; i < size; i++) {
                temp[i] = array[i];
            }
            delete[] array;
            array = temp;
        }else if(size == 0){
            array = new T[capacity];
        }
        array[size] = data;
        size++;
    }

    void showTable(){
        if (array){
            cout << "========== Table ==========" << endl;
            for (int i = 0; i < size; i++){
                cout << i+1 << ". " << array[i] << endl;
            }
            cout << "===========================" << endl;
        }
        else {
            cout << "Your table is cleared" << endl;
        }

    }

    void showByIndex(int index){
        --index;
        if (index >= 0 && index < size) {
            cout << "Your element is: " << array[index] << endl;
        }
        else {
            cout << "Invalid index" << endl;
        }
    }

    void changeByIndex(int index, T data){
        --index;
        if (index >= 0 && index < size) {
            array[index] = data;
            cout << "Index " << index << " was changed" << endl;
        } else {
            cout << "Invalid index" << endl;
        }
    }

    void bubleSort(){
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (array[j] > array[j + 1]) {
                    T temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }

    T* begin() {
        return array;
    }

    T* end() const {
        return array + size;
    }

    void clearTable(){
        delete[] array;
        array = nullptr;
        size = 0;
        cout << "Table has been cleared" << endl;
    }
};