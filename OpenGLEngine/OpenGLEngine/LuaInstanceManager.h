#pragma once

#include <unordered_map>
#include <map>
#include "Singleton.h"
#include "LuaContext.h"
#include "LuaManager.h"

typedef int InstanceHandle;


template <class Type> 
class InstanceManager : public Singleton<InstanceManager<Type>>
{
private:
	static std::unordered_map<int, Type* > InstanceManager<Type>::m_instanceMap;
	//static int InstanceManager<Type>::m_lastIndex;

	//static std::vector <Type>m_instanceMap;
	static int m_lastIndx;



public:
	InstanceManager<Type>()
	{
		m_lastIndx = 0;
	}

	InstanceHandle InstanceManager<Type>::AddNewInstance()
	{

		Type * newInstance = new Type();
		m_instanceMap.emplace(m_lastIndx, newInstance);

		//m_instanceMap.push_back(newInstance);
		m_lastIndx += 1;

		return m_lastIndx - 1;
	}

	Type * InstanceManager<Type>::GetInst(int instanceHandle) // Probably has to use same instancehandle/params as in singleton! Same GetInstance() or don't interit at all!..
	{
		//return & m_instanceMap[instanceHandle];
	

		auto got = m_instanceMap.find(instanceHandle);

		if (got == m_instanceMap.end())
		{
			//printf("Instance with name %n not found.", instanceHandle); //this crashes
			printf("Instance not found\n");
			//getChar();
			Type * nullInst;
			return nullInst;
		}

		return got->second;
		//return new Type;

		
	}

	void InstanceManager<Type> ::Expose(LuaContextHandle contextHandle, string luaAPIName)
	{
		LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
		pContext->ExposeFunction(luaAPIName, "addNewInstance", AddNewInstance);
	}


};




// static member definition
//template<class T> std::vector <T> InstanceManager<T>::m_instanceMap;

template<class T>  std::unordered_map<int, T * >  InstanceManager<T>::m_instanceMap;


template<class T>  int InstanceManager <T> ::m_lastIndx;
