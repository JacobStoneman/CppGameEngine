#pragma once

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include "Subsystem.h"
#include "Event.h"
#include "Engine.h"

#include <irrlicht/irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Graphics : public Subsystem
{
private:
	static void(*EventReaction[0])(std::vector<arg>);
public:
	//Graphics objects hold an irrlicht scene node and a pointer to another entity
	//Allows for easy manipulation of entity position without including the entity system
	struct graphicsObject {
		ISceneNode* object;
		EntityObject* entity;
	};
	static IrrlichtDevice* device;
	static IVideoDriver* driver;
	static ISceneManager* smgr;
	static IGUIEnvironment* guienv;
	const static IGeometryCreator* geometryCreator;

	Graphics();
	~Graphics();
	static void Graphics::InitSystem();
	static void Graphics::StartSystem();
	static void Graphics::MainLoop();
	static void Update();
	static void UpdateObjects();
	static void UpdateCamera();
};
