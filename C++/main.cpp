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

//chapter1-6
template <class T, int array_size>
bool is_sorted(T (&array)[array_size]){
    if(array_size < 3){
        return true;
    }
    bool ascending_sequence;
    if(array[0]<array[1])
        ascending_sequence = true;
    else
        ascending_sequence = false;
    for(int i=1;i<array_size;i++){
        if(ascending_sequence==true &&(array[i-1]>array[i]))
            return false;
        if(ascending_sequence==false && array[i-1]<array[i])
            return false;
    }
    return true;
}

//chapter1-8
//不是。因为签名是由函数的形参类型与形参个数决定的。

//chapter1-9
//第三条。实参的类型不符合程序1-1和1-2中形参类型的任何一个。
//第四条。实参的类型是double，不符合1-1和1-2形参类型的任何一个。


//chapter1-10
int abc(int a, int b, int c){
    if(a<0&&b<0&&c<0){
        throw 1;
    }
    if(a==0&&b==0&&c==0){
        throw 2;
    }
    return 9;
}

//chapter1-11
template <class T>
int count(T a[], int n, const T& value)
{
   if (n < 1)
      throw "n must be >= 1";

   int theCount = 0;
   for (int i = 0; i < n; i++)
      if (a[i] == value)
         theCount++;
   return theCount;
}

template <class T>
bool make2dArray(T **&x, int numberOfRows, int numbeOfColumns){
    x = new T* [numberOfRows];
    for(int i=0;i<numberOfRows;i++){
        x[i] = new T [numbeOfColumns];
    }
    for(int i=0;i<numberOfRows;i++){
        for(int j=0;j<numbeOfColumns;j++){
            x[i][j] = 1;
        }
    }
    return true;
}

//chapter1-12
template <class T>
bool make2dArray2(T **&x, int numOfRows, int rowSize[]){
    x = new T* [numOfRows];
    for(int i=0;i<numOfRows;i++){
        x[i] = new T [rowSize[i]];;
    }
    for(int i=0;i<numOfRows;i++){
        for(int j=0;j<rowSize[i];j++){
            x[i][j] = 2;
        }
    }
    return true;
}

//chapter1-13
template <class T>
T*& changeLength1D(T *x, int oldLength, int newLength){
    T *newx = new T[newLength];
    int minLength = 0;
    if(oldLength<newLength)
        for(int i=0;i<oldLength;i++){
            newx[i] = x[i];
        }
    else
        for(int i=0;i<newLength;i++){
            newx[i] = x[i];
        }
    delete []x;
    x = NULL;
    return newx;
}

//chapter1-14
template <class T>
void changeLength2D(T** &x, int oldRows, int oldColumns, int newRows, int newColumns){
    T **newx;
    newx = new int* [newRows];
    for(int i=0;i<newColumns;i++){
        newx[i] = new int[newColumns];
    }
    int minRows = *min(&oldRows, &newRows);
    int minColumns = *min(&oldColumns, &newColumns);
    for(int i=0;i<minRows;i++){
        for(int j=0;j<minColumns;j++){
            newx[i][j] = x[i][j];
        }
    }
    for(int j=0;j<oldColumns;j++){
        delete [] x[j];
    }
    delete [] x;
    x = newx;
}

template <class T>
void permutation(T* list_, int start_, int end_){
    if(start_ == end_ ){
        for(int i=0;i<end_;i++){
            cout<<list_[i]<<" ";
        }
        cout<<endl;
    }
    else{
        for(int i=start_;i<end_;i++){
            swap(list_[start_], list_[i]);
            permutation(list_, i, end_);
            swap(list_[start_], list_[i]);
        }
    }
}


//chapter1-15
//1)
//max: 2^{32} - 1 dollars and 99 cents.
//min: - (2^{32} - 1) dollars and -99 cents.
//2)
//max: 2^{31} - 1 dollars and 99 cents.
//min: - (2^{31} - 1) dollars and -99 cents.
//3)
//dollar 应小于等于 2^30-1

int main(){
    try{
        abc(3,-1,-1);
    }
    catch(int result){
        if(result==2){
            cout<<"a b c都为0，非法"<<endl;
            return -1;
        }
        if(result==1){
            cout<<"a b c都小于0，非法"<<endl;
            return -1;
        }
    }
    int **x;
    int a = 2;
    int **b;
    b = new int*[3];
    for(int i=0;i<3;i++){
        b[i] = new int[5];
    }
    b[0][0]=b[1][1]=b[2][2]=5;
    changeLength2D(b, 3, 5, 4, 6);
    cout<<b[3][5]<<endl;
    int* list_ = new int[5];
    for(int i=0;i<5;i++){
        list_[i] = i;
    }
    permutation(list_, 0, 5);
    return 0;
}


