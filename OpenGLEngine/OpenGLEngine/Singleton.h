#ifndef Singleton_h__
#define Singleton_h__

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