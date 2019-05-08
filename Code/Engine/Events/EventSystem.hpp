#pragma once
#include "Engine\Core\NamedProperties.hpp"
#include "Engine\Events\EventSubscription.hpp"
#include <map>
#include <vector>

class EventSystem
{
private:
	EventSystem() {}

public:
	~EventSystem() {}
	static EventSystem* CreateInstance();
	static EventSystem* GetInstance();

	static void Startup();
	static void Shutdown();

	static void Subscribe(const std::string& eventName, EventFunctionCallbackForPtrType callback);
	static void Unsubscribe(const std::string& eventName, EventFunctionCallbackForPtrType callback);

	template <class T, typename M>
	static void Subscribe(const std::string& eventName, T* object, M callback)
	{
		typedef bool (T::*EventObjectMethodCallbackPtr) (NamedProperties& args);
		EventObjectMethodCallbackPtr castedMethodPtr = static_cast<EventObjectMethodCallbackPtr>(callback);

		std::vector<EventSubscription*>& currentSubscribers = m_subscriptions[eventName];

		for (int subscriptionIndex = 0; subscriptionIndex < (int)currentSubscribers.size(); ++subscriptionIndex)
		{
			EventObjectMethodSubscription* functionSubscription = (EventObjectMethodSubscription*)currentSubscribers[subscriptionIndex];
			if (functionSubscription->m_functionPointer == callback)
				return;
		}

		currentSubscribers.push_back(new EventObjectMethodSubscription<T>(object, castedMethodPtr));
	}

	template <class T, typename M>
	static void Unsubscribe(const std::string& eventName, T* object, M callback)
	{
		typedef bool (T:: * EventObjectMethodCallbackPtr) (NamedProperties & args);

		//does it exist
		std::map<std::string, std::vector<EventSubscription*>>::iterator subscriptionIterator = g_theEventSystem->m_subscriptions.find(eventName);
		if (subscriptionIterator == g_theEventSystem->m_subscriptions.end())
			return;

		EventObjectMethodCallbackPtr castedMethodPtr = static_cast<EventObjectMethodCallbackPtr>(callback);

		std::vector<EventSubscription*>& currentSubscribers = m_subscriptions[eventName];

		for (int subscriptionIndex = 0; subscriptionIndex < (int)currentSubscribers.size(); ++subscriptionIndex)
		{
			EventObjectMethodSubscription* functionSubscription = (EventObjectMethodSubscription*)currentSubscribers[subscriptionIndex];
			if (functionSubscription->m_functionPointer == callback)
			{
				currentSubscribers.erase(currentSubscribers.begin() + subscriptionIndex);
				return;
			}				
		}
	}

	static void FireEvent(const std::string& name, NamedProperties& properties);
	static void FireEvent(const std::string& name);

private:
	std::map<std::string, std::vector<EventSubscription*>> m_subscriptions;
};

