#include "EventSystem.hpp"

static EventSystem* g_theEventSystem = nullptr;

//  =========================================================================================
EventSystem::EventSystem()
{
}

//  =========================================================================================
EventSystem::~EventSystem()
{
}

//  =========================================================================================
EventSystem* EventSystem::GetInstance()
{
	return g_theEventSystem;
}

//  =========================================================================================
EventSystem* EventSystem::CreateInstance()
{
	if (g_theEventSystem == nullptr)
	{
		g_theEventSystem = new EventSystem();
	}
	return g_theEventSystem;
}

//  =========================================================================================
void EventSystem::Subscribe(EventCallback callback)
{
}

//  =========================================================================================
void EventSystem::FireEvent(std::string name, NamedProperties & properties)
{

}
