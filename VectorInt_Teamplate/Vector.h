#pragma once
#include<string>
#include <memory>
#include <utility>

using namespace std;
template<typename T>
class Vector
{
private:
	T* mArr = nullptr;
	int mSize = 0;
	int mCapacity = 0;

public:
	Vector();// Конструктор по умолчанию.
	Vector(int size, T value); // Конструктор
	Vector(const T* arr, int size);//Дополнительный конструктор принимающий указатель на T* ptr и размер динамического массива.
	T& operator[](int index);// Перегрузка оператора []
	
	
	void Check_Mem();
	void Reserve(int newSize); // увеличивает внутренний размер массива (увеличивает Capacity)
	
	const Vector& operator=(std::vector<T>&& v);
	Vector(std::vector<T>&& v);
	
	const Vector(Vector&& v) // Конструктор перемещения
	{
		mArr = v.mArr;
		mSize = v.mSize;
		mCapacity = v.mCapacity;

		v.mArr = nullptr;
		v.mSize = 0;
		v.mCapacity = 0;
	}
	
	const Vector& operator = (Vector&& v) // Оператор присваивания
	{ 
		if (this != &v)
		{ 
		delete[] mArr;

		mArr = v.mArr;
		mSize = v.mSize;
		mCapacity = v.mCapacity;

		v.mArr = nullptr;
		v.mSize = 0;
		v.mCapacity = 0;
		}
		return *this; 
	}
	
	Vector(const Vector& v) : Vector() // Конструктор копирования
	{
		for (int i = 0; i < v.Size(); ++i)
			Push_Back(v.At(i));
	}
	
	const Vector& operator= (const Vector& copy)  // Конструктор присваивания 
	{
		Clear();
		for (int i = 0; i < copy.Size(); ++i)
			Push_Back(copy.At(i));
		return *this;
	}
	
	int Size() const
	{
		return mSize;
	}

	void Push_Back(T p)
	{
		Check_Mem();
		mArr[mSize] = p;
		++mSize;
	}

	int Capacity() const
	{
		return mCapacity;
	}

	T At(int index) const
	{
		return mArr[index];
	}

	void Set(int index, T value)
	{
		mArr[index] = value;
	}

	T& Front() const
	{
		return mArr[0];
	}

	T& Back() const
	{
		return mArr[mSize - 1];
	}

	bool Empty() const
	{
		return (mSize == 0);
	}

	void Clear()
	{
		mSize = 0;
	}

	T& At(int index)
	{
		return mArr[index];
	}

	~Vector()
	{
		delete[] mArr;
	}
};

template<typename T>
Vector<T>::Vector()
{
	mCapacity = 20;
	mArr = new T[mCapacity]{};
}

template<typename T>
Vector<T>::Vector(int size, T value)
{

	for (int i = 0; i < size; i++)
	{
		Push_Back(value);
	}
}

template<typename T>
Vector<T>::Vector(const T* arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		Push_Back(arr[i]);
	}
}

template<typename T>
T& Vector<T>::operator[](int index)
{
	return mArr[index];
}

template<typename T>
void Vector<T>:: Check_Mem()
{
	if (mSize == mCapacity)
	{
		mCapacity = (mCapacity <= 0) ? 10 : mCapacity * 2;
		T* arr = new T[mCapacity];
		for (int i = 0; i < mSize; i++)
		{
			arr[i] = mArr[i];
		}
		delete[] mArr;
		mArr = arr;
	}
}

template<typename T>
void Vector<T>::Reserve(int newSize)
{
	if (newSize > mCapacity)
	{
		T* newArr = new T[newSize]{};
		for (int i = 0; i < mSize; ++i)
			newArr[i] = std::move(mArr[i]);
		delete mArr;
		mArr = newArr;
		mCapacity = newSize;
	}
}

template<typename T, int SZ>	// объявление
Vector<T> Make_Vector(const T(&)[SZ]);

template<typename T, int SZ>	//	реализация Make_Vector
Vector<T> Make_Vector(const T(&arr)[SZ])
{
	Vector<T> ans;
	ans.Reserve(SZ);					
	for (auto& val : arr)
		ans.Push_Back(val);
	return ans;
}

