#pragma once
#include "Engine\Core\EngineCommon.hpp"
#include <string>
#include <map>

//  ----------------------------------------------
class NamedPropertyBase
{
public:
	NamedPropertyBase(const std::string& name)
	{
		propertyName = name;
	}

	virtual ~NamedPropertyBase() {};

	std::string GetName() const
	{
		return propertyName;
	}

public:
	std::string propertyName = "";
};

//  ----------------------------------------------
template <class T>
class NamedPropertyType : public NamedPropertyBase
{
public:
	NamedPropertyType(const std::string& name, const T& prop) : NamedPropertyBase(name)
	{
		typeProperty = prop;
	}

	~NamedPropertyType() override {};

	T GetTypeProperty() const
	{
		return typeProperty;
	}

	void SetTypeProperty(const T& type)
	{
		typeProperty = type;
	}

public:
	T typeProperty;
};

//  ----------------------------------------------
class NamedProperties
{
public:

	template <typename T>
	void Set(const std::string& name, const T& prop)
	{
		//does property exist
		auto namedPropertyIterator = namedProperties.find(name);

		if (namedPropertyIterator != namedProperties.end())
		{
			NamedPropertyType<T>* propertyPointer = (NamedPropertyType<T>*)namedPropertyIterator->second;

			GUARANTEE_OR_DIE(typeid(propertyPointer->GetTypeProperty()).hash_code() == typeid(prop).hash_code(), "ATTEMPTED TO SET TYPED PROPERTY NAME OF DIFFERENT TYPE!!!!");

			propertyPointer->SetTypeProperty(prop);
		}			
		else
			namedProperties.insert(std::make_pair(name, new NamedPropertyType<T>(name, prop)));
	}

	template <typename T>
	T Get(const std::string& name, const T& defaultValue) const
	{
		auto namedPropertyIterator = namedProperties.find(name);
		if (namedPropertyIterator != namedProperties.end())
		{
			NamedPropertyType<T>* propertyPointer = (NamedPropertyType<T>*)namedPropertyIterator->second;

			//value exists and is different type than requested via default value
			if (typeid(propertyPointer->GetTypeProperty()).hash_code() != typeid(defaultValue).hash_code())
				return defaultValue;
			else //value is correct
				return propertyPointer->GetTypeProperty();
		}
		
		//value doesn't exist
		return defaultValue;
	}

	//edge case for const char*
	void NamedProperties::Set(const char* name, const char* defaultValue)
	{
		Set<std::string>(name, std::string(defaultValue));
	}

	std::string NamedProperties::Get(const char* name, const char* defaultValue)
	{
		return Get<std::string>(name, std::string(defaultValue));
	}

private:
	std::map<const std::string, NamedPropertyBase*> namedProperties;
};
