#pragma once
#include "EventTypeEnum.h"
#include "SubsystemEnum.h"
#include "EntityObject.h"
#include "vec3.h"

//Each event will have a vector of args which can each store data
struct arg {
public:
	int i;
	float f;
	bool b;
	vec3 v;
	EntityObject* e;
	std::string s;
};

class Event
{
public:
	EventType eType;
	std::vector<SubsystemEnum> eventSystems;
	std::vector<arg> args;
	std::vector<std::string> strings;

	Event(EventType newEvent) { eType = newEvent; };
	~Event() {};
	void addSubsystem(SubsystemEnum systemNum) { eventSystems.push_back(systemNum); };
	void addArg(arg argToAdd) { args.push_back(argToAdd); };
};

