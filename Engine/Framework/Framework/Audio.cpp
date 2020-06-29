#include "Audio.h"

void(*Audio::EventReaction[Engine::EVENTCOUNT])(std::vector<arg>);
//Array of music files loaded into memory during initialisation
Mix_Music* musicList[1024];
Mix_Chunk* fxList[1024];

const float VOLMAX = 128;
float volume = VOLMAX;
int volumePercentage;

Audio::Audio()
{
}

Audio::~Audio()
{
}

//Loads audio files into memory from paths passed in by the game data subsystem
void LoadAudioPath(std::vector<arg> args) {
	std::string path = args[0].s;
	int id = args[0].i;
	int type = args[1].i;
	const char* pathChar = path.c_str();

	if (type == 0) {
		Mix_Music* newTrack = Mix_LoadMUS(pathChar);
		if (musicList[id] == NULL) {
			musicList[id] = newTrack;
		}
		else {
			std::cout << "ERROR::Multiple file paths assigned to ID " << id << std::endl;
		}
	}
	else if (type == 1) {
		Mix_Chunk* newFX = Mix_LoadWAV(pathChar);
		if (fxList[id] == NULL) {
			fxList[id] = newFX;
		}
		else {
			std::cout << "ERROR::Multiple file paths assigned to ID " << id << std::endl;
		}
	}
	else {
		std::cout << "ERROR::File path given incorrect type" << id << std::endl;
	}
	
}

//Play a specific sound when the player moves
void MoveFX(std::vector<arg> args) {
	Mix_VolumeChunk(fxList[args[0].i],volume);
	Mix_PlayChannel(-1, fxList[args[0].i], 0);
}

//Start, pause or unpause music
void PlayMusic(std::vector<arg> args) {
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(musicList[args[0].i], -1);
	}
	else
	{
		if (Mix_PausedMusic() == 1)
		{
			Mix_ResumeMusic();
		}
		else
		{
			Mix_PauseMusic();
		}
	}
}

//Increase or decrease volume
void Volume(std::vector<arg> args) {
	if (args[0].i == 1) {
		volume = volume + (VOLMAX/100);
	}
	else if (args[0].i == 0) {
		volume = volume - (VOLMAX/100);
	}
	if (volume > 128) {
		volume = 128;
	}
	else if (volume < 0) {
		volume = 0;
	}
	Mix_VolumeMusic(volume);
	volumePercentage = (volume / VOLMAX) * 100;
	std::cout << "volume: " << volumePercentage << "%"<< std::endl;
}

void Audio::InitSystem()
{
	auto start = std::chrono::system_clock::now();
	std::cout << "::::Initialising Audio Subsystem::::" << std::endl;

	Mix_VolumeMusic(volume);

	//Initialise function pointers
	void (*fnpPlayMusic)(std::vector<arg> args) = PlayMusic;
	void (*fnpVolume)(std::vector<arg> args) = Volume;
	void (*fnpLoadAudioPath)(std::vector<arg> args) = LoadAudioPath;
	void (*fnpMoveFX)(std::vector<arg> args) = MoveFX;
	EventReaction[(int)EventType::EVENT_PLAY_MUSIC] = fnpPlayMusic;
	EventReaction[(int)EventType::EVENT_MUSIC_VOLUME] = fnpVolume;
	EventReaction[(int)EventType::EVENT_SEND_AUDIO_PATHS] = fnpLoadAudioPath;
	EventReaction[(int)EventType::EVENT_MOVE_ENTITY] = fnpMoveFX;

	//Initialise SDL
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "System initialized - Time taken: " << elapsed_seconds.count() << std::endl << std::endl;
}

void Audio::StartSystem()
{
	Update();
}

void Audio::MainLoop()
{
	Update();
}

//Check for audio specific events in the event queue
void Audio::Update()
{
	for (int i = 0; i < Engine::eventQ.size(); i++)
	{
		for (int j = 0; j < Engine::eventQ[i].eventSystems.size(); j++)
		{
			if (Engine::eventQ[i].eventSystems[j] == SubsystemEnum::AUDIO)
			{
				EventReaction[(int)Engine::eventQ[i].eType](Engine::eventQ[i].args);
				Engine::eventQ[i].eventSystems.erase(Engine::eventQ[i].eventSystems.begin() + j);
			}
		}
	}
}
