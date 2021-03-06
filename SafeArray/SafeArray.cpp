#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

//Prototype, (things to come)
template <typename T> class Iterator;
template <typename T> class SafeArray;

//Five things are needed for a ranged-based for loop to work. 
//Container's begin() method (returns an iterator to the start of the container)
//Container's end() method (returns an iterator to the end of the container*)
//Iterator needs a prefix++ method
//Iterator needs a != method
//Iterator needs a * dereference method

template <typename T>
class Iterator {
	friend class SafeArray<T>;

public:
	Iterator<T> operator++();
	bool operator!=(const Iterator<T>& rhs) const;
	T operator*() const;
private:
	unsigned int index{ 0 };
	unsigned int capacity{ 0 };
	T* arr{ nullptr };
	bool rightCliffHanger{ false };

};

template <typename T>
Iterator<T> Iterator<T>::operator++() {
	if (index == capacity - 1) {
		rightCliffHanger = true;
	}
	else {
		index++;
	}
	return *this;
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator<T>& rhs) const {
	return !(this->arr == rhs.arr && this->index == rhs.index && this->rightCliffHanger == rhs.rightCliffHanger);
}

template <typename T>
T Iterator<T>::operator*() const {
	return arr[index];
}

template <typename T>
class SafeArray {
public:
	SafeArray(const unsigned int capacity);
	void set(const unsigned int index, const T& value); //& is awesome compiler work for you
	T get(const unsigned int index) const;  //This makes it immutable, the method is constant, you can't change data members
	unsigned int size() const;
	Iterator<T> begin() const;
	Iterator<T> end() const;
private:
	//data members
	unsigned int capacity{ 0 }; //Please please please avoid writing runnable code in a declaration
	T* arr{ nullptr };
};

//Definition of the members of the class
template <typename T>
SafeArray<T>::SafeArray(const unsigned int capacity) {
	this->capacity = capacity;
	arr = new T[capacity];
}

template <typename T>
void SafeArray<T>::set(const unsigned int index, const T& value) {
	if (index >= capacity) {
		cout << "No...just...ugh...no" << endl;
		return;
	}
	arr[index] = value;
}

template <typename T>
T SafeArray<T>::get(const unsigned int index) const {

	if (index >= capacity) {
		cout << "The index is out of bounds" << endl;
		throw 1; //Alternate bail out condition, or an ejection seat, or a backdoor...
	}
	return arr[index];
}

template <typename T>
unsigned int SafeArray<T>::size() const {
	return capacity;
}

template <typename T>
Iterator<T> SafeArray<T>::begin() const {
	Iterator<T> retVal;
	retVal.index = 0;
	retVal.capacity = this->capacity;
	if (retVal.capacity == 0) {
		//empty
		retVal.rightCliffHanger = true;
	}
	else {
		retVal.rightCliffHanger = false;
	}
	retVal.arr = this->arr;
	return retVal;
}

template <typename T>
Iterator<T> SafeArray<T>::end() const {
	Iterator<T> retVal;

	if (this->capacity == 0) {
		retVal.index = 0;
	}
	else {
		retVal.index = this->capacity - 1;
	}
	retVal.rightCliffHanger = true;
	retVal.capacity = this->capacity;
	retVal.arr = this->arr;
	return retVal;
}

int main() {

	//int* arr = new int[100];
	//for (int i = 0; i < 100; i++) {
	//  arr[i] = i*i;
	//}
	//cout << arr << endl;
	//cout << *arr << endl;
	//cout << arr[0] << endl;
	//
	//cout << *(arr + 42) << endl;
	//cout << arr[42] << endl;

	////There is no bounds checking here
	//cout << arr[-1] << endl;
	//cout << arr[666] << endl;

	//delete[] arr;

	SafeArray<int> myArray(10); //This puts the object on the stack.

	for (int i = 0; i < 10; i++) {
		//The equivalent of this: arr[i] = i*i;
		//.set(index, value)
		myArray.set(i, i*i);
	}

	for (int i = 0; i < myArray.size(); i++) {
		//The equivalent of this: cout << arr[i]
		cout << myArray.get(i) << " ";
	}
	cout << endl;

	//I can stop this from happening!
	myArray.set(666, 1234567);

	//I can now stop this from actually happening!
	try {
		cout << myArray.get(666) << endl;
	}
	catch (int err) {
		cout << "I caught a value " << err << endl;
	}
	cout << endl;

	for (auto item : myArray) {
		cout << item << endl;
	}

	cin.get();
	return 0;
}

/*template <typename T>
class Iterator {
  friend class SafeArray<T>;

public:
  Iterator<T> operator++();
  bool operator!=(const Iterator<T>& rhs) const;
  T operator*() const;
private:
  unsigned int index{ 0 };
  unsigned int capacity{ 0 };
  T* arr{ nullptr };
  bool rightCliffHanger{ false };

};

template <typename T>
Iterator<T> Iterator<T>::operator++() {
  if (index == capacity - 1) {
    rightCliffHanger = true;
  }
  else {
    index++;
  }
  return *this;
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator<T>& rhs) const {
  return !(this->arr == rhs.arr && this->index == rhs.index && this->rightCliffHanger == rhs.rightCliffHanger);
}

template <typename T>
T Iterator<T>::operator*() const {
  return arr[index];
}

template <typename T>
class SafeArray {
public:
  SafeArray(const unsigned int capacity);
  void set(const unsigned int index, const T& value); //& is awesome compiler work for you
  T get(const unsigned int index) const;  //This makes it immutable, the method is constant, you can't change data members
  unsigned int size() const;
  Iterator<T> begin() const;
  Iterator<T> end() const;
private:
  //data members
  unsigned int capacity{ 0 }; //Please please please avoid writing runnable code in a declaration
  T* arr{ nullptr };
};

//Definition of the members of the class
template <typename T>
SafeArray<T>::SafeArray(const unsigned int capacity) {
  this->capacity = capacity;
  arr = new T[capacity];
}

template <typename T>
void SafeArray<T>::set(const unsigned int index, const T& value) {
  if (index >= capacity) {
    cout << "No...just...ugh...no" << endl;
    return;
  }
  arr[index] = value;
}

template <typename T>
T SafeArray<T>::get(const unsigned int index) const {

  if (index >= capacity) {
    cout << "The index is out of bounds" << endl;
    throw 1; //Alternate bail out condition, or an ejection seat, or a backdoor...
  }
  return arr[index];
}

template <typename T>
unsigned int SafeArray<T>::size() const {
  return capacity;
}

template <typename T>
Iterator<T> SafeArray<T>::begin() const {
  Iterator<T> retVal;
  retVal.index = 0;
  retVal.capacity = this->capacity;
  if (retVal.capacity == 0) {
    //empty
    retVal.rightCliffHanger = true;
  }
  else {
    retVal.rightCliffHanger = false;
  }
  retVal.arr = this->arr;
  return retVal;
}

template <typename T>
Iterator<T> SafeArray<T>::end() const {
  Iterator<T> retVal;
  
  if (this->capacity == 0) {
    retVal.index = 0;
  } else {
    retVal.index = this->capacity - 1;
  }
  retVal.rightCliffHanger = true;
  retVal.capacity = this->capacity;
  retVal.arr = this->arr;
  return retVal;
}

int main() {

  //int* arr = new int[100];
  //for (int i = 0; i < 100; i++) {
  //  arr[i] = i*i;
  //}
  //cout << arr << endl;
  //cout << *arr << endl;
  //cout << arr[0] << endl;
  //
  //cout << *(arr + 42) << endl;
  //cout << arr[42] << endl;

  ////There is no bounds checking here
  //cout << arr[-1] << endl;
  //cout << arr[666] << endl;

  //delete[] arr;

  SafeArray<int> myArray(10); //This puts the object on the stack.

  for (int i = 0; i < 10; i++) {
    //The equivalent of this: arr[i] = i*i;
    //.set(index, value)
    myArray.set(i, i*i);
  }

  for (int i = 0; i < myArray.size(); i++) {
    //The equivalent of this: cout << arr[i]
    cout << myArray.get(i) << " ";
  }
  cout << endl;

  //I can stop this from happening!
  myArray.set(666, 1234567);

  //I can now stop this from actually happening!
  try {
    cout << myArray.get(666) << endl;
  }
  catch (int err) {
    cout << "I caught a value " << err << endl;
  }
  cout << endl;

  for (auto item : myArray) {
    cout << item << endl;
  }

  cin.get();
  return 0;
}*/