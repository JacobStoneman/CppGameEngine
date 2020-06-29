#include "GameData.h"

using namespace luabridge;

//Reads all of the player specific values and sends these to a player create event
void CreatePlayer(LuaRef t) {
	LuaRef posX = t["posX"];
	LuaRef posY = t["posY"];
	LuaRef posZ = t["posZ"];
	LuaRef headX = t["headX"];
	LuaRef headY = t["headY"];
	LuaRef headZ = t["headZ"];
	LuaRef scaleX = t["scaleX"];
	LuaRef scaleY = t["scaleY"];
	LuaRef scaleZ = t["scaleZ"];
	LuaRef meshNum = t["meshNum"];

	//Push creation event
	Event newEvent(EventType::EVENT_CREATE_PLAYER_ENTITY);
	newEvent.addSubsystem(SubsystemEnum::ENTITYSUB);
	arg arg1, arg2, arg3, arg4, arg5, arg6, arg7,arg8,arg9,arg10;
	arg1.f = posX.cast<float>();
	arg2.f = posY.cast<float>();
	arg3.f = posZ.cast<float>();
	arg4.f = headX.cast<float>();
	arg5.f = headY.cast<float>();
	arg6.f = headZ.cast<float>();
	arg7.f = scaleX.cast<float>();
	arg8.f = scaleY.cast<float>();
	arg9.f = scaleZ.cast<float>();
	arg10.i = meshNum.cast<int>();
	newEvent.addArg(arg1);
	newEvent.addArg(arg2);
	newEvent.addArg(arg3);
	newEvent.addArg(arg4);
	newEvent.addArg(arg5);
	newEvent.addArg(arg6);
	newEvent.addArg(arg7);
	newEvent.addArg(arg8);
	newEvent.addArg(arg9);
	newEvent.addArg(arg10);
	Engine::eventQ.push_back(newEvent);
}

//Reads all of the objects values and sends these to a generic object create event
void CreateObject(LuaRef t) {
	LuaRef posX = t["posX"];
	LuaRef posY = t["posY"];
	LuaRef posZ = t["posZ"];
	LuaRef headX = t["headX"];
	LuaRef headY = t["headY"];
	LuaRef headZ = t["headZ"];
	LuaRef scaleX = t["scaleX"];
	LuaRef scaleY = t["scaleY"];
	LuaRef scaleZ = t["scaleZ"];
	LuaRef meshNum = t["meshNum"];

	//Push creation event
	Event newEvent(EventType::EVENT_CREATE_OBJECT_ENTITY);
	newEvent.addSubsystem(SubsystemEnum::ENTITYSUB);
	arg arg1, arg2, arg3, arg4, arg5, arg6, arg7,arg8, arg9, arg10;
	arg1.f = posX.cast<float>();
	arg2.f = posY.cast<float>();
	arg3.f = posZ.cast<float>();
	arg4.f = headX.cast<float>();
	arg5.f = headY.cast<float>();
	arg6.f = headZ.cast<float>();
	arg7.f = scaleX.cast<float>();
	arg8.f = scaleY.cast<float>();
	arg9.f = scaleZ.cast<float>();
	arg10.i = meshNum.cast<int>();
	newEvent.addArg(arg1);
	newEvent.addArg(arg2);
	newEvent.addArg(arg3);
	newEvent.addArg(arg4);
	newEvent.addArg(arg5);
	newEvent.addArg(arg6);
	newEvent.addArg(arg7);
	newEvent.addArg(arg8);
	newEvent.addArg(arg9);
	newEvent.addArg(arg10);
	Engine::eventQ.push_back(newEvent);
}

//Reads position values for the light then sends these to the creation event
void CreateLight(LuaRef t) {
	LuaRef posX = t["posX"];
	LuaRef posY = t["posY"];
	LuaRef posZ = t["posZ"];
	Event newEvent(EventType::EVENT_CREATE_LIGHT_ENTITY);
	newEvent.addSubsystem(SubsystemEnum::ENTITYSUB);
	arg arg1, arg2, arg3;
	arg1.f = posX.cast<float>();
	arg2.f = posY.cast<float>();
	arg3.f = posZ.cast<float>();
	newEvent.addArg(arg1);
	newEvent.addArg(arg2);
	newEvent.addArg(arg3);
	Engine::eventQ.push_back(newEvent);
}

std::vector<std::string> getElements(const std::string& tab, lua_State* L) {

	std::string source =
		"function getElements(tab) "
		"s = \"\""
		"for k, v in pairs(_G[tab]) do "
		"    s = s..k..\"|\" "
		"    end "
		"return s "
		"end";

	luaL_loadstring(L, source.c_str());
	lua_pcall(L, 0, 0, 0);
	lua_getglobal(L, "getElements");
	lua_pushstring(L, tab.c_str());
	lua_pcall(L, 1, 1, 0);

	std::string ans = lua_tostring(L, -1);
	std::vector<std::string> elements;
	std::string temp = "";
	for (unsigned int i = 0; i < ans.size(); i++) {
		if (ans.at(i) != '|') {
			temp += ans.at(i);
		}
		else {
			elements.push_back(temp);
			temp = "";
		}
	}

	int n = lua_gettop(L);
	lua_pop(L, 1);

	return elements;
}

//Reads file paths and sends these to be loaded into memory
void sendModelPath(std::string path, int id) {
	Event newEvent(EventType::EVENT_SEND_MODEL_PATHS);
	newEvent.addSubsystem(SubsystemEnum::GRAPHICS);
	arg arg1;
	arg1.s = path;
	arg1.i = id;
	newEvent.addArg(arg1);
	Engine::eventQ.push_back(newEvent);
}

void sendAudioPath(std::string path, int id, int type) {
	Event newEvent(EventType::EVENT_SEND_AUDIO_PATHS);
	newEvent.addSubsystem(SubsystemEnum::AUDIO);
	arg arg1, arg2;
	arg1.s = path;
	arg1.i = id;
	arg2.i = type;
	newEvent.addArg(arg1);
	newEvent.addArg(arg2);
	Engine::eventQ.push_back(newEvent);
}

void GameData::InitSystem()
{
	auto start = std::chrono::system_clock::now();
	std::cout << "::::Reading Game Data::::" << std::endl;

	lua_State* F = luaL_newstate();
	luaL_dofile(F, "elements.lua");
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);

	std::vector<std::string> elementList;
	std::vector<std::string> gameObjects;

	//Reads each global in the lua script and sends the data where it is needed

	//Read gameobject global
	elementList = getElements("elementList", F);
	LuaRef elementsRef = getGlobal(F, "elementList");
	int checker;

	for (int i = 0; i < elementList.size(); i++) {
		LuaRef entityCheck = elementsRef[elementList.at(i)];
		checker = entityCheck["e_type"].cast<int>();
		switch (checker) {
		case 0:
			CreatePlayer(entityCheck);
			break;
		case 1:
			CreateObject(entityCheck);
			break;
		case 2:
			CreateLight(entityCheck);
		default:
			break;
		}
	}

	//Read config global
	LuaRef t = getGlobal(F, "config");
	std::cout << "Reading config" << std::endl;
	LuaRef w = t["width"];
	LuaRef h = t["height"];

	Engine::width = w.cast<int>();
	Engine::height = h.cast<int>();
	
	//Read model global
	std::vector<std::string> models;
	t = getGlobal(F, "models");
	models = getElements("models", F);

	for (int i = 0; i < models.size(); i++) {
		LuaRef modelCheck = t[models[i]];
		std::string path = modelCheck["path"].cast<std::string>();
		std::cout << "Loaded: " << path << std::endl;
		int id = modelCheck["id"].cast<int>();
		sendModelPath(path, id);
	}

	//Read audio global
	t = getGlobal(F, "audio");
	std::vector<std::string> audio;
	audio = getElements("audio", F);
	for (int i = 0; i < audio.size(); i++) {
		LuaRef audioCheck = t[audio[i]];
		std::string path = audioCheck["path"].cast<std::string>();
		std::cout << "Loaded: " << path << std::endl;
		int id = audioCheck["id"].cast<int>();
		int type = audioCheck["soundType"].cast<int>();
		sendAudioPath(path, id, type);
	}

	for (int i = 0; i < elementList.size(); i++)
	{
		std::cout << "Loaded: " << (std::string)elementList.at(i) << std::endl;
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "System initialized - Time taken: " << elapsed_seconds.count() << std::endl << std::endl;

}

void GameData::StartSystem()
{
}

//This subsystem has no update function as it should be done with once the lua has been read
