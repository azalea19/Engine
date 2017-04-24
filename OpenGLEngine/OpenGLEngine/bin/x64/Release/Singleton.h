#ifndef Singleton_h__
#define Singleton_h__


/**
* @file Singleton.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief A template class for creating Classes of the singleton pattern.
*
*/

template <class DerivedClass>
class Singleton
{
public:
	static DerivedClass& GetInstance()
	{
		if (p == nullptr)
			p = new DerivedClass();
		return *p;
	}

protected:
	static DerivedClass* p;
	Singleton() {}
};
template <class T>
T* Singleton<T>::p = nullptr;

#endif