#include <iostream>
#include <ctime>
#include <cstdio>
#include <vector>

using namespace std;

//chapter5-2
template <class T>
void changeLength2D(T**& old2DList, int oldRows, int oldColumns, int newRows, int* newColumns_list){
    T** temp = new T* [newRows];
    for(int i=0;i<newRows;i++){
        temp[i] = new T[newColumns_list[i]];
    }
    int minRows = min(oldRows, newRows);
    for(int i=0;i<minRows;i++){
        int minColumns = min(oldColumns, newColumns_list[i]);
        for(int j=0;j<minColumns;j++){
            temp[i][j] = old2DList[i][j];
        }
    }
    for(int i=0;i<oldRows;i++){
        delete [] old2DList[i];
    }
    delete [] old2DList;
    old2DList = temp;

//  ---------TEST-----------
//    int oldRows = 3;
//    int oldColumns = 4;
//    int ** old2DList = new int* [oldRows];
//    for(int i=0;i<oldRows;i++){
//        old2DList[i] = new int [oldColumns];
//    }
//    int newRows = 4;
//    int *newColumns_list = new int[5];
//    for(int i=0;i<5;i++){
//        newColumns_list[i] = i+1;
//    }
//    changeLength2D(old2DList, oldRows, oldColumns, newRows, newColumns_list);
//    cout<<old2DList[2][2]<<endl;

}


//chapter5-3/5-4/5-5
template <class T>
void changeLength1D(T* &a, int oldLength, int newLength){
    if(newLength<0){
        throw "length can not < 0";
    }
    T* temp = new T[newLength];
    int number = min(oldLength, newLength);
    copy(a, a+number, temp);
    delete [] a;
    a = temp;
}

template <class T>
class linearList
{
    public:
        virtual  ~linearList() {};
        virtual  bool empty() const = 0;
        virtual  int size() const = 0;
        virtual  T& get(int theIndex) const = 0;
        virtual  int indexOf(const T& theElement) const = 0;
        virtual  void erase(int theIndex) = 0;
        virtual  void insert(int theIndex, const T& theElement) = 0;
        virtual  void trimToSize() = 0;
        virtual  void reverse() = 0;
        virtual  void circularShift(int i) = 0;
        virtual  void half() = 0;
      //  virtual  void output(ostream &out) const = 0;
};

template <class T>
class arrayList: public linearList<T>
{
    public:
    arrayList(int initialCapacity = 10, int riseLengthWhenFull = 2);
        arrayList(int initialCapacity = 10);
        arrayList(const arrayList<T>&);

        ~arrayList() {delete [] element;};

        bool empty() const {return listSize==0;};
        int size() const {return listSize;};
        T& get(int theIndex) const;
        int indexOf(const T& theElement) const;
        void erase(int theIndex);
        void insert(int theIndex, const T& theElement);
        void trimToSize();
        void reverse();
        void circularShift(int i);
        void half();
      //  void output(ostream& out) const;

        int capacity() const {return arrayLength;};
  //  protected:
        void checkIndex(int theIndex) const;
        T* element;
        int arrayLength;
        int listSize;
    protected:
        int riseLengthWhenFull=2;
};

template <class T>
arrayList<T>::arrayList(int initialCapacity, int myRiseLengthWhenFull) {
    if(initialCapacity < 1)
        throw "illegal initialCapacity";
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;
    riseLengthWhenFull = myRiseLengthWhenFull;
}

template <class T>
arrayList<T>::arrayList(int initialCapacity) {
    if(initialCapacity < 1)
        throw "illegal initialCapacity";
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;
}



template <class T>
arrayList<T>::arrayList(const arrayList<T> & theList) {
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T[arrayLength];
    copy(theList.element, theList.element+listSize, element);
}

template <class T>
void arrayList<T>::checkIndex(int theIndex) const {
    if(theIndex<0 || theIndex>=listSize){
        throw "the index is illegal";
    }
}

template <class T>
T& arrayList<T>::get(int theIndex) const {
    checkIndex(theIndex);
    return element[theIndex];
}

template <class T>
int arrayList<T>::indexOf(const T &theElement) const {

    int theIndex;
    for(int i=0;i<listSize;i++){
        if(element[i]==theElement){
            theIndex = i;
            break;
        }
        if(i==listSize-1){
            theIndex = -1;
        }
    }
    return theIndex;
}

template <class T>
void arrayList<T>::erase(int theIndex) {
    checkIndex(theIndex);
    copy(element+theIndex+1, element+listSize, element+theIndex);
    element[-- listSize].~T();
}

template <class T>
void arrayList<T>::insert(int theIndex, const T &theElement) {
    if(theIndex<0 || theIndex>listSize){
        throw "error";
    }
    if(listSize==arrayLength){
        changeLength1D(element, arrayLength, riseLengthWhenFull*arrayLength);
        arrayLength*=riseLengthWhenFull;
    }
    copy_backward(element+theIndex, element+listSize, element+listSize+1);
    element[theIndex] = theElement;
    listSize ++;
}

template <class T>
void arrayList<T>::trimToSize(){
    T* temp = new T[listSize];
    copy(element, element+listSize, temp);
    delete [] element;
    element = temp;
    arrayLength = listSize;
}

//chapter5-22
template <class T>
void arrayList<T>::reverse() {
    for(int i=0;i<listSize/2;i++){
        swap(element[i], element[listSize-i-1]);
    }
}

template <class T>
void reflect_reverse(arrayList<T>& x){
    x.reverse();
}

//chapter5-24
int gcb(int x, int y){
    if(x<y)
        swap(x, y);
    if(x==1||y==1)
        return 1;
    else if(x%y==0){
        cout<<"the gcb result is "<<y<<endl;
        return y;
    }
    else{
        return gcb(y, x%y ) ;
    }
}

int loop_i(int listSize, int i){
    if(i<0){
        return listSize+i;
    }
    return i;
}

template <class T>
void arrayList<T>::circularShift(int q) {
    int count_ = gcb(listSize, q);
    int temp;
    for(int i=0;i<count_;i++){
        temp = element[i];
        for(int j=1;j<listSize/count_+1;j++){
            int t2 = element[loop_i(listSize, i-j*count_)];
            element[loop_i(listSize, i-j*count_)] = temp;
            temp = t2;
        }
    }
}
//template <class T>
//void arrayList<T>::circularShift(int q) {
//    int count_ = gcb(listSize, q);
//    int temp;
//    for(int i=0;i<count_;i++){
//        temp = element[i];
//        for(int j=1;j<listSize/count_+1;j++){
//            int t2 = element[(i+j*count_)%listSize];
//            element[(i+j*count_)%listSize] = temp;
//            temp = t2;
//        }
//    }
//}


//chapter5-26
template <class T>
void arrayList<T>::half() {
//    int newSize = listSize/2;
    cout<<listSize/2<<endl;
    T* temp = new T[listSize/2+1];
    for(int i=0;i<listSize+1;i+=2){
        temp[i/2] = element[i];
    }
    delete [] element;
    element = temp;
    listSize = listSize/2 + 1;
    arrayLength=listSize;
}



//template <class T>
//void arrayList<T>::output(ostream &out) const {
//    copy(element, element+listSize, ostreambuf_iterator<T>(cout));
//}

//template <class T>
//ostream operator<<(ostream out, const arrayList<T>& x){
//    x.output(out);
//    return out;
//}





int main() {
    std::cout << "Hello, World!" << std::endl;
    int a = 18;
    arrayList<int> z(a,3);
    cout<<z.size()<<endl;
    cout<<z.capacity()<<endl;
    for(int i=0;i<9;i++){
        z.insert(i, i+100);
    }
    cout<<z.size()<<endl;
    cout<<z.capacity()<<endl;
    z.trimToSize();
    cout<<z.size()<<endl;
    cout<<z.capacity()<<endl;
//    clock_t s1, s2, e1, e2;
//    double duration;
//    int i=10000000;
//    s1 = clock();
//    while(i--){
//        z.reverse();
//    }
    for(int i=0;i<z.listSize;i++){
        cout<<" "<<z.element[i];
    }
    cout<<endl;
    z.circularShift(4);
    cout<<"23"<<endl;
    for(int i=0;i<z.listSize;i++){
        cout<<" "<<z.element[i];
    }
    cout<<endl;
    z.half();
    for(int i=0;i<z.listSize;i++){
        cout<<" "<<z.element[i];
    }
    cout<<endl;
//    arrayList<int>&r = z;
//    e1 = clock();
//    duration = (double)(e1-s1)/CLOCKS_PER_SEC;
//    cout<<" "<<duration<<endl;
//    s2 = clock();
//    while(i<10000000){
//        i++;
//        reflect_reverse(r);
//    }
//    e2 = clock();
//    duration = (double)(e2-s2)/CLOCKS_PER_SEC;
//    cout<<" "<<duration<<endl;
//    z.reverse();
    return 0;
}

