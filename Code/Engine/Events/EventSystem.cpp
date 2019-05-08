#include "Engine\Events\EventSystem.hpp"

static EventSystem* g_theEventSystem = nullptr;

//  =========================================================================================
EventSystem* EventSystem::CreateInstance()
{
	if (g_theEventSystem == nullptr)
		g_theEventSystem = new EventSystem();

	return g_theEventSystem;
}

//  =========================================================================================
EventSystem* EventSystem::GetInstance()
{
	return g_theEventSystem;
}

//  =========================================================================================
void EventSystem::Startup()
{
	UNIMPLEMENTED();
}

//  =========================================================================================
void EventSystem::Shutdown()
{
	std::map<std::string, std::vector<EventSubscription*>>::iterator subscriptionIterator = g_theEventSystem->m_subscriptions.begin();
	for (subscriptionIterator; subscriptionIterator != g_theEventSystem->m_subscriptions.end(); ++subscriptionIterator)
	{
		std::vector<EventSubscription*>& subscriptions = subscriptionIterator->second;
		subscriptions.clear();
	}	
}

//  =========================================================================================
void EventSystem::Subscribe(const std::string& eventName, EventFunctionCallbackForPtrType callback)
{
	//find subscription (or add event if it doesn't exist)
	std::vector<EventSubscription*>& subscriptions = g_theEventSystem->m_subscriptions[eventName];

	//check every subscription to make sure we aren't adding subscriptions that already exist
	for (int subscriptionIndex = 0; subscriptionIndex < (int)subscriptions.size(); ++subscriptionIndex)
	{
		EventFunctionSubscription* functionSubscription = (EventFunctionSubscription*)subscriptions[subscriptionIndex];
		if (functionSubscription->m_functionPointer == callback)
			return;
	}

	subscriptions.push_back(new EventFunctionSubscription(callback));	
}

//  =========================================================================================
void EventSystem::Unsubscribe(const std::string& eventName, EventFunctionCallbackForPtrType callback)
{
	//does it exist
	std::map<std::string, std::vector<EventSubscription*>>::iterator subscriptionIterator = g_theEventSystem->m_subscriptions.find(eventName);
	if (subscriptionIterator == g_theEventSystem->m_subscriptions.end())
		return;

	std::vector<EventSubscription*>& subscriptions = g_theEventSystem->m_subscriptions[eventName];

	//check every subscription to make sure we aren't adding subscriptions that already exist
	for (int subscriptionIndex = 0; subscriptionIndex < (int)subscriptions.size(); ++subscriptionIndex)
	{
		EventFunctionSubscription* functionSubscription = (EventFunctionSubscription*)subscriptions[subscriptionIndex];
		if (functionSubscription->m_functionPointer == callback)
		{
			subscriptions.erase(subscriptions.begin() + subscriptionIndex);
			return;
		}			
	}
}

//  =========================================================================================
void EventSystem::FireEvent(const std::string& eventName, NamedProperties& properties)
{
	std::map<std::string, std::vector<EventSubscription*>>::iterator subIterator = g_theEventSystem->m_subscriptions.find(eventName);
	if (subIterator == g_theEventSystem->m_subscriptions.end())
		return;

	std::vector<EventSubscription*>& subscriptions = subIterator->second;

	//check every subscription to make sure we aren't adding subscriptions that already exist
	for (int subscriptionIndex = 0; subscriptionIndex < (int)subscriptions.size(); ++subscriptionIndex)
	{
		if (subscriptions[subscriptionIndex]->Execute(properties))
			return; //if the subscription consumed the call, return
	}
}

//  =========================================================================================
void EventSystem::FireEvent(const std::string& eventName)
{
	std::map<std::string, std::vector<EventSubscription*>>::iterator subIterator = g_theEventSystem->m_subscriptions.find(eventName);

	if (subIterator == g_theEventSystem->m_subscriptions.end())
		return;

	std::vector<EventSubscription*> & subscriptions = subIterator->second;

	//check every subscription to make sure we aren't adding subscriptions that already exist
	for (int subscriptionIndex = 0; subscriptionIndex < (int)subscriptions.size(); ++subscriptionIndex)
	{
		NamedProperties properties;
		if (subscriptions[subscriptionIndex]->Execute(properties))
			return; //if the subscription consumed the call, return
	}
}