#include "Graphics.h"

void(*Graphics::EventReaction[Engine::EVENTCOUNT])(std::vector<arg>);
std::vector<Graphics::graphicsObject> gObjects;
IrrlichtDevice* Graphics::device;
IVideoDriver* Graphics::driver;
ISceneManager* Graphics::smgr;
IGUIEnvironment* Graphics::guienv;
const IGeometryCreator* Graphics::geometryCreator;
ICameraSceneNode* cam;
int lastFPS = -1;
IAnimatedMesh* meshList[1024];
float prevCamRot;

Graphics::Graphics() : Subsystem()
{
}

Graphics::~Graphics()
{
}

//Receives the paths to the model files and loads them as meshes that irrlicht can use
void LoadModelPaths(std::vector<arg> args) {
	std::string path = args[0].s;
	int id = args[0].i;
	const char* pathChar = path.c_str();
	IAnimatedMesh* mesh = Graphics::smgr->getMesh(pathChar);
	if (meshList[id] == NULL) {
		meshList[id] = mesh;
	}
	else {
		std::cout << "ERROR::Multiple file paths assigned to ID " << id << std::endl;
	}
}

//These functions will create the graphics objects which will point to the relvent entity
void CreatePlayer(std::vector<arg> args) {
	Graphics::graphicsObject player;
	player.entity = args[0].e;
	IAnimatedMeshSceneNode* newNode = Graphics::smgr->addAnimatedMeshSceneNode(meshList[player.entity->meshNum]);
	player.object = newNode;
	newNode->setScale(vector3df(args[0].e->scale.x, args[0].e->scale.y, args[0].e->scale.z));
	gObjects.push_back(player);
}

void CreateObject(std::vector<arg> args) {
	Graphics::graphicsObject object;
	object.entity = args[0].e;
	IMeshSceneNode* newNode = Graphics::smgr->addMeshSceneNode(meshList[object.entity->meshNum]);
	newNode->setScale(vector3df(args[0].e->scale.x, args[0].e->scale.y, args[0].e->scale.z));
	object.object = newNode;
	gObjects.push_back(object);
}

void CreateLight(std::vector<arg> args) {
	ILightSceneNode* light = Graphics::device->getSceneManager()->addLightSceneNode();
	light->setPosition(vector3df(args[0].e->position.x, args[0].e->position.y, args[0].e->position.z));
}

void Graphics::InitSystem()
{
	auto start = std::chrono::system_clock::now();
	std::cout << "::::Initialising Graphics Subsystem::::" << std::endl;
	//Initialise irrlicht
	Graphics::device = createDevice(video::EDT_OPENGL, dimension2d<u32>(Engine::width, Engine::height), 16, false, false, false, 0);
	Graphics::device->setWindowCaption(L"301 Engine");

	Graphics::driver = Graphics::device->getVideoDriver();
	Graphics::smgr = Graphics::device->getSceneManager();
	Graphics::guienv = Graphics::device->getGUIEnvironment();
	Graphics::geometryCreator = Graphics::smgr->getGeometryCreator();

	smgr->setAmbientLight(video::SColorf(0.3f, 0.3f, 0.3f, 1.0f));

	//Initialise camera
	cam = Graphics::smgr->addCameraSceneNodeFPS();
	cam->setPosition(vector3df(0,0,0));
	cam->bindTargetAndRotation(true);
	cam->setRotation(vector3df(0, 180, 0));
	vector3df tempRot = cam->getRotation();
	prevCamRot = tempRot.Y;

	//Declare function pointers
	void (*fnpCreatePlayer)(std::vector<arg> args) = CreatePlayer;
	void (*fnpLoadModelPaths)(std::vector<arg> args) = LoadModelPaths;
	void (*fnpCreateObject)(std::vector<arg> args) = CreateObject;
	void (*fnpCreateLight)(std::vector<arg> args) = CreateLight;
	EventReaction[(int)EventType::EVENT_CREATE_PLAYER] = fnpCreatePlayer;
	EventReaction[(int)EventType::EVENT_SEND_MODEL_PATHS] = fnpLoadModelPaths;
	EventReaction[(int)EventType::EVENT_CREATE_OBJECT] = fnpCreateObject;
	EventReaction[(int)EventType::EVENT_CREATE_LIGHT] = fnpCreateLight;

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "System initialized - Time taken: " << elapsed_seconds.count() << std::endl << std::endl;
}

void Graphics::StartSystem()
{
	std::cout << "::Starting Graphics Subsystem::" << std::endl;
	Update();
	std::cout << std::endl;
}

void Graphics::MainLoop()
{
	Update();

	//Sends camera info to the entity system to rotate the player relative to the camera
	vector3df rot = cam->getRotation();
	float rotVal = prevCamRot - rot.Y;
	Event newEvent(EventType::EVENT_ROTATE_ENTITY);
	newEvent.addSubsystem(SubsystemEnum::ENTITYSUB);
	arg arg1, arg2;
	arg1.f = -rotVal;
	arg2.f = rot.Y;
	arg1.e = Engine::entities[Engine::pEntityNum];
	newEvent.addArg(arg1);
	newEvent.addArg(arg2);
	Engine::eventQ.push_back(newEvent);
	prevCamRot = rot.Y;

	UpdateObjects();
	UpdateCamera();
	

	if (device->run()) {
		driver->beginScene(true, true, video::SColor(255, 200, 200, 200));
		smgr->drawAll();
		driver->endScene();
	}
}

//Reads event queue for graphics specific events
void Graphics::Update()
{
	for (int i = 0; i < Engine::eventQ.size(); i++)
	{
		for (int j = 0; j < Engine::eventQ[i].eventSystems.size(); j++)
		{
		if (Engine::eventQ[i].eventSystems[j] == SubsystemEnum::GRAPHICS)
			{
				EventReaction[(int)Engine::eventQ[i].eType](Engine::eventQ[i].args);
				Engine::eventQ[i].eventSystems.erase(Engine::eventQ[i].eventSystems.begin() + j);
			}
		}
	}
}

//Move graphics objects to same position as the entity
void Graphics::UpdateObjects() {
	for (int i = 0; i < gObjects.size(); i++) {
		vector3df newPos(gObjects[i].entity->position.x, gObjects[i].entity->position.y, gObjects[i].entity->position.z);
		vector3df newRot(gObjects[i].entity->rotation.x, gObjects[i].entity->rotation.y, gObjects[i].entity->rotation.z);
		gObjects[i].object->setPosition(newPos);
		gObjects[i].object->setRotation(newRot);
	}
}

//Locks the camera to the player
void Graphics::UpdateCamera() {
	if (gObjects.size() > 0) {
		cam->setPosition(vector3df(gObjects[Engine::pEntityNum].object->getPosition().X, gObjects[Engine::pEntityNum].object->getPosition().Y, gObjects[Engine::pEntityNum].object->getPosition().Z));
	}
}