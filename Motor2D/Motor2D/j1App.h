#ifndef __j1APP_H__
#define __j1APP_H__

#include "p2List.h"
#include "j1Module.h"
#include "j1TimeNormal.h"
#include "PugiXml\src\pugixml.hpp"
#include "Brofiler\Brofiler.h"

// Modules
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1Audio;
class j1Scene;
class j1Map;
//class Player;
//class EnemyNormal;
//class EnemyFly;
class ManagerCriatures;
class ParticleManager;
class j1FadeToBlack;
class ModuleCollision;

class j1App
{
public:

	// Constructor
	j1App(int argc, char* args[]);

	// Destructor
	virtual ~j1App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(j1Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	// DT
	float GetDT()
	{
		return dt;
	}

	//Call to load and save function
	void Load();
	void Save() const;

private:

	// Load config file
	bool LoadConfig();

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	//Load and save functions on XML
	bool  DocLoad();
	bool  DocSave() const;

public:

	// Modules
	j1Window*			win;
	j1Input*			input;
	j1Render*			render;
	j1Textures*			tex;
	j1Audio*			audio;
	j1Map*              map;
	j1Scene*			scene;
	ManagerCriatures*	managerC;
	//Player*				player;
	//EnemyNormal*		enemy_normal;
	//EnemyFly*			enemy_fly;
	ParticleManager*    particles;
	j1FadeToBlack*		fade;
	ModuleCollision*	collision;

	uint64				frame_count = 0;
	j1TimeNormal		startup_time;
	j1TimeNormal		frame_time;
	j1TimeNormal	    last_sec_frame_time;
	uint32				last_sec_frame_count = 0;
	uint32				prev_last_sec_frame_count = 0;
	//float				dt = 0.0f;
	int					capped_ms = -1;

private:

	p2List<j1Module*>	modules;
	uint				frames;
	float				dt;
	pugi::xml_document	config_file;
	pugi::xml_node		config;
	pugi::xml_node		app_config;
	int					argc;
	char**				args;

	p2SString			title;
	p2SString			organization;

	mutable bool        need_save = false;
	bool                need_load = false;

};

extern j1App* App;

#endif