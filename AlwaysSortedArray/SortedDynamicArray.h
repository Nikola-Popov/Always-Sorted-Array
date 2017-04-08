#ifndef _SORTED_DYNAMIC_ARRAY_H_
#define _SORTED_DYNAMIC_ARRAY_H_

#include "DynamicArray.h"

#define START_INDEX 0

const size_t OFFSET_REQUIRED_FOR_SHIFT = 1;

template <typename TYPE>
class SortedDynamicArray : public DynamicArray<TYPE> {
public:
	SortedDynamicArray();
public:
	void add(const TYPE& element);
	void serialize(std::ostream& outputStream) const;
private:
	size_t findInsertIndexForElement(const TYPE& element) const;
	void shiftElementsRightIfNecessaryFrom(const size_t index);
	bool isResizeNecessary() const;
};

template <typename TYPE>
SortedDynamicArray<TYPE>::SortedDynamicArray() : DynamicArray() {
}

template <typename TYPE>
void SortedDynamicArray<TYPE>::add(const TYPE& element) {
	size_t insertIndex = isEmpty() ? START_INDEX : findInsertIndexForElement(element);
	if(isResizeNecessary()) {
		resize();
	}
	shiftElementsRightIfNecessaryFrom(insertIndex);
	data[insertIndex] = element;
	size++;
}

template <typename TYPE>
size_t SortedDynamicArray<TYPE>::findInsertIndexForElement(const TYPE& element) const {
	for(int index = 0; index < size; index++) {
		if(data[index] >= element) {
			return index;
		}
		return size;
	}
}

template <typename TYPE>
void SortedDynamicArray<TYPE>::shiftElementsRightIfNecessaryFrom(const size_t index) {
	if(index == size) {
		return;
	}
	for(int i = size - 1; i > index; i--) {
		std::cout << data[i] << std::endl;
		std::cout << data[i-1] << std::endl;

		data[i] = data[i - 1];
	}
}

template <typename TYPE>
bool SortedDynamicArray<TYPE>::isResizeNecessary() const {
	if(size + OFFSET_REQUIRED_FOR_SHIFT >= capacity) {
		return true;
	}
	return false;
}

template <typename TYPE>
void SortedDynamicArray<TYPE>::serialize(std::ostream& outputStream) const {
	DynamicArray::serialize(outputStream);
}

#endif //_SORTED_DYNAMIC_ARRAY_H_