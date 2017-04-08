#ifndef _DYNAMIC_ARRAY_H_
#define _DYNAMIC_ARRAY_H_

#include <ostream>

#define INVALID_VALUE (-1)
const size_t INITIAL_DATA_CAPACITY = 8;

template <typename TYPE>
class DynamicArray {
public:
	DynamicArray();
	virtual ~DynamicArray();
	DynamicArray(const DynamicArray& otherDynamicArray);
	DynamicArray& operator=(const DynamicArray& otherDynamicArray);
public:
	TYPE operator[](const size_t index);
	const TYPE operator[](const size_t index) const;
	void remove(const TYPE& element);
	void removeAtIndex(const size_t index);
	int search(const TYPE& element) const;
	size_t getSize() const;
	size_t getCapacity() const;
private:
	void releaseMemory();
	void copy(const DynamicArray& otherDynamicArray);
	bool isSpecifiedIndexValid(const size_t index) const;
	bool isIndexValid(const size_t index) const;
protected:
	virtual void add(const TYPE& element);
	virtual void serialize(std::ostream& outputStream) const;
	virtual bool isResizeNecessary() const;
	void resize();
	bool isEmpty() const;
protected:
	TYPE* data;
	size_t size;
	size_t capacity;
};

template <typename TYPE>
DynamicArray<TYPE>::DynamicArray() : size(NULL), capacity(INITIAL_DATA_CAPACITY) {
	data = new TYPE[capacity];
}

template <typename TYPE>
DynamicArray<TYPE>::~DynamicArray() {
	releaseMemory();
}

template <typename TYPE>
DynamicArray<TYPE>::DynamicArray(const DynamicArray& otherDynamicArray) {
	copy(otherDynamicArray);
}

template <typename TYPE>
DynamicArray<TYPE>& DynamicArray<TYPE>::operator=(const DynamicArray<TYPE>& otherDynamicArray) {
	if(this != &otherDynamicArray) {
		releaseMemory();
		copy(otherDynamicArray);
	}
	return *this;
}

template <typename TYPE>
void DynamicArray<TYPE>::releaseMemory() {
	delete[] data;
	data = nullptr;
}

template <typename TYPE>
void DynamicArray<TYPE>::copy(const DynamicArray<TYPE>& otherDynamicArray) {
	releaseMemory();
	data = new TYPE[otherDynamicArray.capacity];
	for(int i = 0; i < otherDynamicArray.size; i++) {
		data[i] = otherDynamicArray.data[i];
	}
	capacity = otherDynamicArray.capacity;
	size = otherDynamicArray.size;
}

template <typename TYPE>
TYPE DynamicArray<TYPE>::operator[](const size_t index) {
	if(!isSpecifiedIndexValid(index)) {
		throw "Index out of bounds!";
	}
	return data[index];
}

template <typename TYPE>
const TYPE DynamicArray<TYPE>::operator[](const size_t index) const {
	if(isSpecifiedIndexValid(index)) {
		throw "Index out of bounds!";
	}
	return data[index];
}

template <typename TYPE>
bool DynamicArray<TYPE>::isSpecifiedIndexValid(const size_t index) const {
	if(index > size) {
		return false;
	}
	return true;
}

template <typename TYPE>
void DynamicArray<TYPE>::add(const TYPE& element) {
	if(isResizeNecessary()) {
		resize();
	}
	data[size++] = element;
}

template <typename TYPE>
bool DynamicArray<TYPE>::isResizeNecessary() const {
	if(size == capacity) {
		return true;
	}
	return false;
}

template <typename TYPE>
void DynamicArray<TYPE>::resize() {
	const size_t NEW_CAPACITY = capacity * 2;
	TYPE* tmpData = new TYPE[NEW_CAPACITY];
	for(int i = 0; i < size; i++) {
		tmpData[i] = data[i];
	}
	capacity = NEW_CAPACITY;
	data = tmpData;
	delete tmpData;
}

template <typename TYPE>
void DynamicArray<TYPE>::remove(const TYPE& element) {
	int foundAtIndex = search(element);
	if(foundAtIndex != INVALID_VALUE) {
		removeAtIndex(foundAtIndex);
	}
}

template <typename TYPE>
void DynamicArray<TYPE>::removeAtIndex(const size_t index) {
	if(!isEmpty() && isIndexValid(index)) {
		for(int i = index; i < size; i++) {
			data[i] = data[i + 1];
		}
		size--;
	}
}

template <typename TYPE>
bool DynamicArray<TYPE>::isIndexValid(const size_t index) const {
	if(index <= size) {
		return true;
	}
	return false;
}

/*
 If the element is present in the array then the method returns the index in it. Otherwise -1 is returned.
 */
template <typename TYPE>
int DynamicArray<TYPE>::search(const TYPE& element) const {
	for(int index = 0; index < size; index++) {
		if(data[i] == element) {
			return index;
		}
	}
	return INVALID_VALUE;
}

template <typename TYPE>
void DynamicArray<TYPE>::serialize(std::ostream& outputStream) const {
	for(int i = 0; i < size; i++) {
		outputStream << data[i] << " ";
	}
}

template <typename TYPE>
bool DynamicArray<TYPE>::isEmpty() const {
	return size == 0;
}
template <typename TYPE>
size_t DynamicArray<TYPE>::getSize() const {
	return size;
}

template <typename TYPE>
size_t DynamicArray<TYPE>::getCapacity() const {
	return capacity;
}


#endif //_DYNAMIC_ARRAY_H_