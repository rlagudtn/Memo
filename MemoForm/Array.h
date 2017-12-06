//Array.h
#ifndef _ARRAY_H
#define _ARRAY_H
typedef signed long int Long;
template <typename T>
class Array {
public:
	Array(Long capacity = 256);
	Array(const Array& source);
	~Array();
	Long Store(Long index, T object);
	Long Insert(Long index, T object);
	Long AppendFromFront(T object);
	Long AppendFromRear(T object);
	Long Delete(Long index);
	Long DeleteFromFront();
	Long DeleteFromRear();
	void Clear();
	Long Modify(Long index, T object);
	Long LinearSearchUnique(void *key, int(*compare)(void *, void*));
	void LinearSearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void *, void *));
	Long BinarySearchUnique(void *key, int(*compare)(void *, void*));
	void BinarySearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void *, void *));
	void SelectionSort(int(*compare)(void *, void *));
	void BubbleSort(int(*compare)(void*, void *));
	void InsertionSort(int(*compare)(void *, void *));
	void MergeSort(const Array& one, const Array& other, int(*compare)(void *, void *));
	T& GetAt(Long index) const;
	Long GetCapacity() const;
	Long GetLength() const;
	Array<T>& operator=(const Array& source);
	T& operator[](Long index);
	T* operator+(Long index);
private:
	T(*front);
	Long capacity;
	Long length;
};

template <typename T>
inline Long Array<T>::GetCapacity()const {
	return this->capacity;

}
template <typename T>
inline Long Array<T>::GetLength()const {
	return this->length;
}
template<typename T>
Array<T>::Array(Long capacity) {
	this->front = new T[capacity];
	this->capacity = capacity;
	this->length = 0;
}


template<typename T>
Array<T>::Array(const Array& source) {
	Long i = 0;
	this->front = new T[source.capacity];
	this->capacity = source.capacity;
	while (i < source.length) {
		this->front[i] = source.front[i];
		i++;
	}
	this->length = source.length;
}

template<typename T>
Long Array<T>::Store(Long index, T object) {
	this->front[index] = object;
	this->length++;
	return index;
}


template <typename T>
Long Array<T>::Insert(Long index, T object) {
	T(*temp);
	Long i = 0;

	temp = new T[this->capacity + 1];
	while (i < index) {
		temp[i] = this->front[i];
		i++;
	}
	while (i < this->length) {
		temp[i + 1] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = temp;
	this->capacity++;
	this->front[index] = object;
	this->length++;

	return index;
}

template<typename T>
Long Array<T>::AppendFromFront(T object) {
	Long index = 0;
	T(*temp);
	Long i = 0;

	temp = new T[this->capacity + 1];
	while (i < this->length) {
		temp[i + 1] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = temp;
	this->capacity++;
	this->front[index] = object;
	this->length++;

	return index;
}

template<typename T>
Long Array<T>::AppendFromRear(T object) {
	Long index;
	T(*temp);
	Long i = 0;
	temp = new T[this->capacity + 1];
	while (i < this->length) {
		temp[i] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[]this->front;
	}
	this->front = temp;
	this->capacity++;
	index = this->capacity - 1;
	this->front[index] = object;
	this->length++;

	return index;
}

template<typename T>
Long Array<T>::Delete(Long index) {
	Long i = 0;
	T(*temp)=0;

	if (this->capacity > 1) {
		temp = new T[this->capacity - 1];
	}
	while (i < index) {
		temp[i] = this->front[i];
		i++;
	}
	while (i < this->length - 1) {
		temp[i] = this->front[i + 1];
		i++;
	}
	if (this->front != 0) {
		delete[]this->front;
		this->front = 0;
	}
	if (this->capacity > 1) {
		this->front = temp;
	}
	this->capacity--;
	this->length--;
	index = -1;

	return index;
}

template<typename T>
Long Array<T>::DeleteFromFront() {
	Long index;
	T(*temp)=0;
	Long i = 1;

	if (this->capacity > 1) {
		temp = new T[this->capacity - 1];
	}
	while (i < this->length) {
		temp[i - 1] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[]this->front;
		this->front = 0;
	}
	if (this->capacity > 1) {
		this->front = temp;
	}
	this->capacity--;
	this->length--;
	index = -1;

	return index;
}
//*****************DeleteFromRear
template<typename T>
Long Array<T> ::DeleteFromRear() {
	Long index;
	T(*temp) = 0;// =0없으면 초기화되지 않을 수 있는 변수 사용 오류 뜸
	Long i = 0;
	if (this->capacity > 1) {
		temp = new T[this->capacity - 1];
	}
	while (i < this->capacity - 1) {
		temp[i] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[]this->front;
		this->front = 0;
	}
	if (this->capacity > 1) {
		this->front = temp;
	}
	this->capacity--;
	this->length--;
	index = -1;

	return index;
}
template <typename T>
void Array<T>::Clear() {
	if (this->front != 0) {
		delete[]this->front;
		this->front = 0;
	}
	this->capacity = 0;
	this->length = 0;
}
template <typename T>
Array<T>& Array<T>::operator=(const Array& source) {
	Long i = 0;
	if (this->front != 0) {
		delete[]this->front;
	}
	this->front = new T[source.capacity];
	this->capacity = source.capacity;
	while (i < source.length) {
		this->front[i] = source.front[i];
		i++;
	}
	this->length = source.length;
	return *this;
}

template <typename T>
T& Array<T>::operator[](Long index) {
	return this->front[index];
}

template <typename T>
T* Array<T>::operator+(Long index) {
	return this->front + index;
}

//***********Modify

template <typename T>
Long Array<T>::Modify(Long index, T object) {
	this->front[index] = object;
	return index;
}

template <typename T>
Long Array<T>::LinearSearchUnique(void *key, int(*compare)(void*, void*)) {
	Long index = -1;
	Long i = 0;

	while (i < this->length && compare(this->front + i, key) != 0) {
		i++;
	}
	if (i < this->length) {
		index = i;
	}
	return index;
}

template <typename T>
void Array<T>::LinearSearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void *, void *)) {
	Long i = 0;
	Long j = 0;

	*count = 0;
	*indexes = new Long[this->length];

	while (i < this->length) {
		if (compare(this->front + i, key) == 0) {
			(*count)++;
			(*indexes)[j] = i;
			j++;
		}
		i++;
	}
}

template <typename T>
Long Array<T>::BinarySearchUnique(void *key, int(*compare)(void *, void*)) {
	Long index = -1;
	Long start = 0;
	Long mid;
	Long end;

	end = this->length - 1;
	mid = (start + end) / 2;

	while (start <= end && compare(this->front + mid, key) != 0) {
		if (compare(this->front + mid, key) < 0) {
			start = mid + 1;
		}
		else {
			end = mid - 1;
		}
		mid = (start + end) / 2;
	}
	if (start <= end) {
		index = mid;
	}
	return index;
}

template <typename T>
void Array<T>::BinarySearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void *, void *)) {
	Long start = 0;
	Long mid;
	Long end;
	Long i = 0;
	Long j;

	*count = 0;
	*indexes = new Long[this->length];
	end = this->length - 1;
	mid = (start + end) / 2;

	while (start <= end && compare(this->front + mid, key) != 0) {
		if (compare(this->front + mid, key) < 0) {
			start = mid + 1;
		}
		else {
			end = mid - 1;
		}
		mid = (start + end) / 2;
	}
	j = mid - 1;

	while (j >= 0 && compare(this->front + j, key) == 0) {
		j--;
	}
	start = j + 1;
	while (start < this->length && compare(this->front + start, key) == 0) {
		(*indexes)[i] = start;
		i++;
		(*count)++;
		start++;
	}
}

template <typename T>
void Array<T>::SelectionSort(int(*compare)(void *, void *)) {

	T temp;
	Long i = 0;
	Long j;

	while (i < this->length - 1) {
		j = i + 1;
		while (j < this->length) {
			if (compare(this->front + i, this->front + j) > 0) {
				temp = this->front[i];
				this->front[i] = this->front[j];
				this->front[j] = temp;
			}
			j++;
		}
		i++;
	}
}

template <typename T>
void Array<T>::BubbleSort(int(*compare)(void*, void *)) {
	T temp;
	Long i = 0;
	Long j;

	while (i < this->length - 1) {
		j = 0;
		while (j < this->length - i - 1) {
			if (compare(this->front + j, this->front + j + 1) > 0) {
				temp = this->front[j + 1];
				this->front[j + 1] = this->front[j];
				this->front[j] = temp;
			}
			j++;
		}
		i++;
	}
}





//********************Insertionsort
template <typename T>
void Array<T>::InsertionSort(int(*compare)(void *, void *)) {
	T temp;
	Long i = 1;
	Long j;
	Long k;
	while (i < this->length) {
		temp = this->front[i];
		j = 0;
		while (j < i&& compare(this->front + j, &temp) < 0) {//**********temp의 주소를 넣어야댐

			j++;
		}
		k = i - 1;
		while (k >= j) {
			this->front[k + 1] = this->front[k];
			k--;
		}
		this->front[j] = temp;
		i++;
	}
}

template <typename T>
void Array<T>::MergeSort(const Array& one, const Array& other, int(*compare)(void *, void *)) {
	Long i = 0;
	Long j = 0;
	Long k = 0;
	if (this->front != 0) {
		delete[]this->front;
	}
	this->front = new T[(one.capacity + other.capacity)];
	this->capacity = one.capacity + other.capacity;
	this->length = 0;
	while (i < one.length&&j < other.length) {
		if (compare(one.front + i, other.front + j) < 0) {
			this->front[k] = one.front[i];
			k++;
			i++;
		}
		else {
			this->front[k] = other.front[j];
			k++;
			j++;
		}
	}
	while (i < one.length) {
		this->front[k] = one.front[i];
		k++;
		i++;
	}
	while (j < other.length) {
		this->front[k] = other.front[j];
		k++;
		j++;
	}
	this->length = one.length + other.length;

}
template<typename T>
T& Array<T>::GetAt(Long index)const {
	return this->front[index];
}
template<typename T>
Array<T>::~Array() {
	if (this->front != 0) {
		delete[]this->front;
		this->front = 0;
	}
}

#endif // _ARRAY_H