#pragma once
#include <vector>
#include "..\Object\Object.h"
#include "..\Utils\Camera.h"
class AmbientLight;
class Object;
class Light;



class World {
public:

	//members
	std::vector<Object*> m_objects{};
	std::vector<Light*> m_lights{};
	Camera m_camera{};
	AmbientLight* m_ambientLight{};

	//construtors
	World() = default;
	~World() = default;
	
	//methods
	void add_object(Object* object);
	void add_light(Light* light);

	//virtual methods
	void virtual build_world();



};


