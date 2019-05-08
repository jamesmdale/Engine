#pragma once
#include "Engine\Core\NamedProperties.hpp"

typedef bool(*EventFunctionCallbackForPtrType)(NamedProperties& args);

class EventSystem;

//  ----------------------------------------------
class EventSubscription
{
	friend EventSystem;

public:
	EventSubscription() {};
	~EventSubscription() {};

	virtual bool Execute(NamedProperties& args) = 0;
};

class EventFunctionSubscription : public EventSubscription
{
public:
	friend EventSystem;

	EventFunctionSubscription() {};
	EventFunctionSubscription(EventFunctionCallbackForPtrType callbackFunctionPointer)
	{
		m_functionPointer = callbackFunctionPointer;
	}

	virtual bool Execute(NamedProperties& args) override
	{
		return m_functionPointer(args);
	}

private:
	EventFunctionCallbackForPtrType m_functionPointer = nullptr; //callback is already a pointer
};


// Handle method callback subscriptions ----------------------------------------------
template <class T>
class EventObjectMethodSubscription : public EventSubscription
{
	friend EventSystem;

public:
	typedef bool (T::*EventObjectMethodCallbackForPtrType) (NamedProperties& eventArgs);

	EventObjectMethodSubscription(T* object, EventObjectMethodCallbackForPtrType method) : m_object(object), m_method(method) {};

	~EventObjectMethodSubscription<T>()
	{
		m_object = nullptr;
	}

	virtual bool Execute(NamedProperties& args) override
	{
		return (m_object->*m_method) (args);
	}

private:
	T* m_object = nullptr;
	EventObjectMethodCallbackForPtrType m_method;
};