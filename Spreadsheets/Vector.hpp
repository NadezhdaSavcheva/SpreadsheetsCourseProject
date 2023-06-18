#pragma once
#include <iostream>
#include <exception>

//GeorgiTerziev02FMI/Object Oriented Programming/Data Structures/Vector/Vector.hpp

const size_t DEFAULT_CAPACITY = 4;

template <typename T>
class Vector {
private:
	T* data;
	size_t size;
	size_t capacity;

	void copyFrom(const Vector& other);
	void free();
	void moveFrom(Vector&& other);

	size_t calculateCapacity(const size_t) const;
	void resize(const size_t);
public:
	Vector();
	Vector(size_t capacity);
	Vector(const Vector<T>& other);
	Vector(Vector<T>&& other);
	Vector<T>& operator=(const Vector<T>& other);
	Vector<T>& operator=(Vector<T>&& other);
	~Vector();

	size_t getSize() const;
	size_t getCapacity() const;

	void pushBack(const T&);
	void pushBack(T&& n);
	void pushAt(const T&, const size_t);
	void pushAt(T&&, const size_t);
	T& popBack();
	T& popAt(const size_t);
	T& operator[](const size_t);
	const T& operator[](const size_t) const;
	bool empty() const;
	void clear();
	void swap(const Vector<T>&);
};

template <typename T>
void Vector<T>::copyFrom(const Vector& other) {
	size = other.size;
	capacity = other.capacity;
	data = new T[capacity];

	for (size_t i = 0; i < size; i++)
		data[i] = other.data[i];
}

template <typename T>
void Vector<T>::free() {
	delete[] data;
	data = nullptr;
	size = capacity = 0;
}

template <typename T>
void Vector<T>::moveFrom(Vector&& other) {
	data = other.data;
	size = other.size;
	capacity = other.capacity;

	other.data = nullptr;
	other.size = other.capacity = 0;
}

template <typename T>
size_t Vector<T>::calculateCapacity(const size_t number) const {
	size_t result = DEFAULT_CAPACITY;
	while (number > result)
		result *= 2;

	return result;
}

template <typename T>
void Vector<T>::resize(const size_t expectedCapacityToFit) {
	capacity = calculateCapacity(expectedCapacityToFit);
	T* temp = new T[capacity];

	for (size_t i = 0; i < size; i++)
		temp[i] = data[i];

	delete[] data;
	data = temp;
}

template <typename T>
Vector<T>::Vector() {
	data = nullptr;
	size = 0;
	capacity = 8;
}

template <typename T>
Vector<T>::Vector(size_t capacity) : data(nullptr), size(0), capacity(capacity) {}

template <typename T>
Vector<T>::Vector(const Vector<T>& other) {
	copyFrom(other);
}

template <typename T>
Vector<T>::Vector(Vector<T>&& other) {
	moveFrom(std::move(other));
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template <typename T>
Vector<T>::~Vector() {
	free();
}

template <typename T>
size_t Vector<T>::getSize() const {
	return size;
}

template <typename T>
size_t Vector<T>::getCapacity() const {
	return capacity;
}

template <typename T>
void Vector<T>::pushBack(const T& element) {
	if (size + 1 > capacity)
		resize(size + 1);

	data[size++] = element;
}

template <typename T>
void Vector<T>::pushBack(T&& element) {
	if (size + 1 > capacity)
		resize(size + 1);

	data[size++] = element;
}

template <typename T>
void Vector<T>::pushAt(const T& element, const size_t index) {
	if (size + 1 > capacity)
		resize(size + 1);

	for (size_t i = size; i > index; i--)
		data[i] = data[i - 1];

	data[index] = element;
	size++;
}

template <typename T>
void Vector<T>::pushAt(T&& element, const size_t index) {
	if (size + 1 > capacity)
		resize(size + 1);

	for (size_t i = size; i > index; i--)
		data[i] = data[i - 1];

	data[index] = element;
	size++;
}

template <typename T>
T& Vector<T>::popBack() {
	if (empty())
		throw std::logic_error("Vector is empty!");

	return data[--size];
}

template <typename T>
T& Vector<T>::popAt(const size_t index) {
	if (index < 0 || index >= size)
		throw  std::out_of_range("Invalid index!");

	T temp = data[index];
	for (size_t i = index; i < size - 1; i++)
		data[i] = data[i + 1];

	size--;
	return temp;
}

template <typename T>
T& Vector<T>::operator[](const size_t index) {
	if (index >= size)
		throw  std::out_of_range("Invalid index!");

	return data[index];
}

template <typename T>
const T& Vector<T>::operator[](const size_t index) const {
	if (index >= size)
		throw  std::out_of_range("Invalid index!");

	return data[index];
}

template <typename T>
bool Vector<T>::empty() const {
	return size == 0;
}

template <typename T>
void Vector<T>::clear() {
	delete[] data;
	capacity = DEFAULT_CAPACITY;
	data = new T[capacity];
	size = 0;
}

template <typename T>
void Vector<T>::swap(const Vector<T>& other) {
	Vector<T> tempVector(std::move(*this));
	*this = std::move(other);
	other = std::move(tempVector);
}
