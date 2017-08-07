#include <iostream>

using namespace std;

// chapter1-2
template <class T, int array_size>
int count(T (&array)[array_size], const T& target){
    int real_count = 0;
    for(int i=0;i<array_size;i++){
        if(target == (array)[i]){
            real_count ++;
        }
    }
    return real_count;
}

//chapter1-3
template <class T, int array_size>
void fill(T (&array)[array_size], const T& value, int start_, int end_){
    for(int i=start_; i<end_; i++)
        array[i] = value;
}

//chapter1-4
template <class T, int array_size, int array_size2>
T inner_product(T (&array1)[array_size], T (&array2)[array_size2]){
    T result=0;
    for(int i=0;i<array_size;i++){
        for(int j=0;j<array_size2;j++){
            result += array1[i]*array2[j];
        }
    }
    return result;
}

//chapter1-5
template <class T, int array_size>
void iota(T (&array)[array_size]){
    for(int i=0;i<array_size;i++){
        array[i]+=i;
    }
}

int main(){
    double A[3]={1.2,2.9,3};
    int B[4]={1,1,1,1};
    iota(A);
    for(int i=0;i<3;i++){
        cout<<A[i]<<endl;
    }
    return 0;
}


