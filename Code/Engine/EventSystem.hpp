#pragma once
#include "Engine\Core\NamedProperties.hpp"

typedef void (*EventCallback)(NamedProperties& properties);

class EventSystem
{
private:
	EventSystem() {}

public:
	~EventSystem() {}
	static EventSystem* GetInstance();
	static EventSystem* CreateInstance();

	static void Subscribe(EventCallback callback);
	static void FireEvent(std::string name, NamedProperties& properties);
};

