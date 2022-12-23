#ifndef AOVECTORHEADER_H_INCLUDED
#define AOVECTORHEADER_H_INCLUDED
#include <iostream>
#include <algorithm>
using namespace std;
// vector CLASS

template <typename AO>
class AOVector {
private:
    AO* Vector = new AO[1];
    int size = 0;
    int Capacity = 1;

public:
    typedef AO* iterator;

    // constructors and bigFour
    // Constructors
    // intializing a vector with a specific size with zeros elements
    AOVector(int sz);
    // intializing a vector with zero size
    AOVector() : size(0) {}
    // intializing a vector with specific elements
    AOVector(AO*, int);
    // copy constructor
    AOVector(const AOVector& other);
    // Copy Assignment
    AOVector& operator=(const AOVector& other);
    // move assignment
    AOVector(AOVector&& rhs)
        :size(move(rhs.size)),
        Capacity(move(rhs.Capacity))
        {
            Vector = new AO[size];
            Vector = rhs.Vector;
            rhs.Vector = nullptr;
            rhs.size = 0;
        }

    iterator begin(){
        return Vector;
    }
    iterator end(){
        return Vector + size;
    }

    ////////   Comparison Operator   ///////
    bool operator==(const AOVector& other);
    // operator smaller than
    bool operator<(const AOVector& other);
    // destructor
    ~AOVector() {
        delete[] Vector;
    }

    // Access operations
    AO& operator[](int i){
        return Vector[i];
    }

    // Modifying operations
    void push_back(AO element);
    // poping back
    void pop_back();
    // erasing
    void erase(iterator a);
    // erase with an interval
    void erase(iterator a, iterator b);
    // inserting an element
    void insert(int index, AO val);
    void insert(iterator a, AO item);

    ////////   Capacity operations   ///////
    void clear();
    int Size() ;
    int capacity();

    friend ostream& operator<<(ostream& out, AOVector <AO>& vector){
        for (int i = 0; i < vector.Size(); i++){
            out << vector[i] << " ";
        }
        cout << endl;
        return out;
    }


};

template<typename AO> using iterator = AO*;
// constructor with a size parameter
template <typename AO> AOVector<AO>::AOVector(int sz){
    size = (sz);
    Vector = new AO[sz];
    for (int i = 0; i < sz; i++) {
        Vector[i] = 0;
    }
}
// copying data from an array
template <typename AO> AOVector<AO>::AOVector(AO* element, int n) {

    size = n;
    Vector = new AO[size]; // creating a new vector with the size of the given array
    Capacity = n;
    for (int i = 0; i < size; i++) {
        Vector[i] = *(element++); // increasing the pointer to the array
    }
}
// copy constructor
template <typename AO> AOVector<AO>::AOVector(const AOVector& other) {
    // copying each data member to the other vector
    // may lead to deep copying
    Vector = other.Vector;
    size = other.size;
    Capacity = other.Capacity;

}
// copy assignment
template <typename AO> AOVector<AO>&  AOVector<AO>::operator=(const AOVector& other) {

    if (this != &other){ // making sure its not pointing to itself
        delete[] Vector;
        size = other.size;
        Capacity = other.Capacity;
        Vector = new AO[size];
        for (int i = 0; i < size; i++){
            Vector[i] = other.Vector[i];
        }
    }
    else {
        cout << "Cannot delete self" << endl;
    }
}
// equality operation
template <typename AO> bool AOVector<AO>::operator==(const AOVector& other) {
        if (other.size != size) return false;
        for (int i = 0; i < other.size; i++) {
            if (other.Vector[i] != Vector[i]) {
                return false;
            }
        }
        return true;
}
// operator smaller than
template <typename AO> bool AOVector<AO>::operator<(const AOVector& other) {
    if (other.size > size) return true; // first comparing the two sizes
    else if (other.size < size) return false;
    else if (other.size == size) { // if the two sizes are equal then the first different element will decide
        for (int i = 0; i < other.size; i++) {
            if (other.Vector[i] > Vector[i]) return false;
        }
    }
    // if no difference is found then the operation is true
    return true;
}
// Modifying operations
template <typename AO> void AOVector<AO>::push_back(AO element){
    if (size == Capacity) {
        // increasing the capacity to the double
        AO* temp = new AO[2 * Capacity];
        for (int i = 0; i < Capacity; i++) {
            temp[i] = Vector[i];
        }
        delete[] Vector;
        Capacity *= 2;
        Vector = temp;
    }
    // if the capacity is bigger than the size
    Vector[size] = element;
    size++;
}
// popping back
template <typename AO> void AOVector<AO>::pop_back(){
    if (size == 0)
    {
        cout << "no element in vector" << endl;
    }
    else
    {
        size--;
    }
}
// erasing for an iterator to the end of the vector
template <typename AO> void AOVector<AO>::erase(iterator a){
    // this function is to erase from the given iterator to the end of the vector
    if (size > 0)
    {
        AO* newdata = new AO[Capacity];
        for (auto i = begin(); i != a; i++)
        {
            newdata[i - begin()] = Vector[i - begin()];
        }
        delete[] Vector;
        Vector = newdata;
        newdata = nullptr;
        size--;
    }
    // if the vector is empty
    else {
        cout << "Can't remove item vector is empty" << endl;
    }
}
// erase with an interval
template <typename AO>void AOVector<AO>::erase(iterator a, iterator b){
    if (size > 0)
		{
			AO* newdata = new AO[Capacity];
			for (auto i = begin(); i != a; i++)
			{
				newdata[i - begin()] = Vector[i - begin()];
			}
			for (auto i = b; i != end(); i++)
			{
				newdata[i - begin() - (b - a)] = Vector[i - begin()];
			}
			delete[] Vector;
			Vector = newdata;
			newdata = nullptr;
			size -= (b - a);
		}
		else {
			cout << "Can't remove item		vector is empty" << endl;
		}
}
// inserting an element
template <typename AO>void AOVector<AO>::insert(int index, AO val){

    if (index < 0 || index >= size)
    {
        cout << "the index out the range!";
    }
    else if (size != Capacity)
    {
        for (int i = size - 1; i >= index; i--)
            {
            Vector[i + 1] = Vector[i];
        }
            Vector[index] = val;
            ++size;
        }
    else
    {
        Capacity *= 2;
        AO* newar = new AO[Capacity];
        for (int i = 0; i < size; i++)
        {
            newar[i] = Vector[i];
        }
        delete[]Vector;
        Vector = newar;
    }
}
template <typename AO>void AOVector<AO>::insert(iterator a, AO item){
    if (size < Capacity) {
        AO* newdata = new AO[Capacity];
        for (auto i = begin(); i != a; i++)
        {
            newdata[i - begin()] = Vector[i - begin()];
        }
        newdata[a - begin()] = item;
        for (auto i = a; i != end(); i++)
        {
            newdata[i - begin() + 1] = Vector[i - begin()];
        }
        delete[] Vector;
        Vector = newdata;
        newdata = nullptr;
        size++;
    }
    else {
        cout << "Resizing to " << Capacity * 2 << endl;
        AO* newdata = new AO[Capacity * 2];
        Capacity *= 2;
        for (auto i = begin(); i != a; i++)
        {
            newdata[i - begin()] = Vector[i - begin()];
        }
        newdata[a - begin()] = item;
        for (auto i = a; i != end(); i++)
        {
            newdata[i - begin() + 1] = Vector[i - begin()];
        }
        delete[] Vector;
        Vector = newdata;
        newdata = nullptr;
        size++;
    }
}
////////   Capacity operations   ///////
template<typename AO> int AOVector<AO>::Size() {
    return size;
}
template<typename AO> int AOVector<AO>::capacity() {
    return Capacity;
}
template<typename AO> void AOVector<AO>::clear(){
    size = 0;
}
#endif // AOVECTORHEADER_H_INCLUDED
