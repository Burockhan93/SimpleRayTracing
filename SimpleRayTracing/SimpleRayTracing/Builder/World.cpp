#include "..\Light\PointLight.h"
#include "..\Light\AmbientLight.h"
#include "..\Light\AreaLight.h"
#include "..\Material\Lambertian.h"
#include "..\Material\Glossy.h"
#include "World.h"
#include "..\Object\Rectangle.h"
#include "..\Object\Sphere.h"
#include "..\Object\Plane.h"
#include "..\Object\Grid.h"
#include "..\Object\Instance.h"
#include "..\Material\Material.h"
#include "..\Material\Emissive.h"
#include "..\Material\Matte.h"
#include "..\Material\Disney.h"
#include "..\ObjectHandler\OBJHandler.h"

#define PRIMITIVES
#define COMPOSITE
#define SHREK

void World::add_light(Light* light) {
	m_lights.push_back(light);
}
void World::add_object(Object* object) {
	m_objects.push_back(object);
}

void World::build_world() {


#ifndef PRIMITIVES
	Vec3 cam_pos{ 0,0,1 };
	Vec3 cam_lookat{ 0,0,0 };
	m_camera = Camera{ cam_pos,cam_lookat,90 };
	Rectangle* r = new Rectangle(Vec3(-2.5, 5, 0), Vec3(5, 0, 0), Vec3(0, 0, 5), new Emissive(10,Vec3{1}));
	r->set_shadowCast(false);
	Sphere* sphere = new Sphere(Vec3{ 3,0,0 }, 2.0f, new Emissive(10, Vec3{ 1 }));
	Sphere* sphere2 = new Sphere(Vec3{ 3,0,0 }, 0.5f, new Matte(Lambertian{ 0.5f, Vec3{0} }, new Lambertian{ 0.5f, Vec3{0} }));
	sphere->set_shadowCast(false);
	AreaLight* light = new AreaLight(r, Vec3(1), 10);

	PointLight* p_light = new PointLight(Vec3(0.5, 0.5, 0), Vec3(0, 5, 0), 1);
	m_ambientLight = new AmbientLight{ 0.5,Vec3{1},1 };
	add_light(light);
	add_light(p_light);
	//add_object(r);
	add_object(sphere);
	//add_object(sphere2);
	Matte* planem = new Matte(
		Lambertian(0.25, Vec3(1)),
		new Lambertian(0.5, Vec3(1)));
	Matte* planeb = new Matte(
		Lambertian(0.25, Vec3(1)),
		new Lambertian(0.5, Vec3(1)));

	Matte* planel = new Matte(
		Lambertian(0.25, Vec3(1, 0, 0)),
		new Lambertian(0.5, Vec3(1, 0, 0)));
	Matte* planer = new Matte(
		Lambertian(0.25, Vec3(0, 1, 0)),
		new Lambertian(0.5, Vec3(0, 1, 0)));

	Plane* planeback = new Plane(Vec3(0, 0, -5), Vec3(0, 0, 1), planem);
	Plane* planeleft = new Plane(Vec3(-5, 0, 0), Vec3(1, 0, 0), planel);
	Plane* planeright = new Plane(Vec3(5, 0, 0), Vec3(-1, 0, 0), planer);
	Plane* planebottom = new Plane(Vec3(0, -5, 0), Vec3(0, 1, 0), planeb);
	Plane* planetop = new Plane(Vec3(0, 5, 0), Vec3(0, -1, 0), planem);

	Disney* boxMat = new Disney();
	boxMat->m_baseColor = Vec3(0.17);
	boxMat->m_specular = 0;
	boxMat->m_roughness = 1;

	OBJHandler objhandler{};


	objhandler.load_mesh("Resources\\LibertStatue.obj");
	Mesh statue_mesh = objhandler.get_mesh();
	Grid* statue = new Grid(statue_mesh, boxMat);


	//add_object(r);
	add_object(planeback);
	add_object(planeleft);
	add_object(planeright);
	add_object(planebottom);
	add_object(planetop);
	//add_object(box);
	add_object(statue);

#endif // PRIIMTIVES

#ifdef COMPOSITE

	Vec3 lookfrom{ 0,2,3.5f };
	//Vec3 lookfrom{ 0,0.75,10.0f };
	Vec3 lookat{ 0,0.99,0 };

	m_camera = Camera{ lookfrom, lookat, 40 };
	
	Disney* boxMat = new Disney();
	boxMat->m_baseColor = Vec3(0.17);
    boxMat->m_specular = 0;
    boxMat->m_roughness =1;

	Disney* generic_mat = new Disney();
	generic_mat->m_baseColor = Vec3(1);
	generic_mat->m_specular = 1;
	generic_mat->m_roughness = 0;
	generic_mat->m_metallic = 0.4;


	OBJHandler objhandler{};
	/*objhandler.load_mesh("Resources\\box.obj");
	Mesh box_mesh = objhandler.get_mesh();
	Grid* box = new Grid(box_mesh, boxMat);*/
	
	/*objhandler.load_mesh("Resources\\LibertyStatue.obj");
	Mesh statue_mesh = objhandler.get_mesh();
	Grid* statue = new Grid(statue_mesh, helmetsMat);*/

	objhandler.load_mesh("Resources\\shrek.obj");
	std::vector<Mesh> shrek_meshes = objhandler.get_meshes();
	Grid* shrek;
	for (size_t i = 0; i < shrek_meshes.size(); i++)
	{
		shrek = new Grid(shrek_meshes[i], generic_mat);
		add_object(shrek);
	}


	/*objhandler.load_mesh("Resources\\lights.obj");
	Mesh mesh2 = objhandler.get_mesh();
	Grid* lights = new Grid(mesh2, new Emissive(10, Vec3(0.31, 0.55, 0.47)));*/


	Matte* planem = new Matte(
		Lambertian(0.25, Vec3(1)),
		new Lambertian(0.5, Vec3(1)));
	Matte* planeb = new Matte(
		Lambertian(0.25, Vec3(1)),
		new Lambertian(0.5, Vec3(1)));

	Matte* planel = new Matte(
		Lambertian(0.25, Vec3(1)),
		new Lambertian(0.5, Vec3(1)));
	Matte* planer = new Matte(
		Lambertian(0.25, Vec3(1)),
		new Lambertian(0.5, Vec3(1)));

	Plane* planeback = new Plane(Vec3(0, 0, -2), Vec3(0, 0, 1), planem);
	Plane* planeleft = new Plane(Vec3(-2, 0, 0), Vec3(1, 0, 0), planel);
	Plane* planeright = new Plane(Vec3(2, 0, 0), Vec3(-1, 0, 0), planer);
	Plane* planebottom = new Plane(Vec3(0, -2, 0), Vec3(0, 1, 0), planeb);
	Plane* planetop = new Plane(Vec3(0, 2, 0), Vec3(0, -1, 0), planem);

	//Sphere* sphere = new Sphere(Vec3{ 1.35,0.5f,0.5 }, 0.75f, new Emissive(5, Vec3{ 0.31, 0.55, 0.47 }));
	Sphere* sphere = new Sphere(Vec3{ 2.35,3.0f,0.5 }, 0.75f, new Emissive(22, Vec3{ 0.439, 0.678, 0 }));
	sphere->set_shadowCast(false);
	add_object(sphere);
	//Sphere* sphere_red = new Sphere(Vec3{ -1.35,0.5f,0.5 }, 0.75f, new Emissive(5, Vec3{ 0.31, 0.55, 0.47 }));
	Sphere* sphere_red = new Sphere(Vec3{ -2.35,3.0f,0.5 }, 0.75f, new Emissive(22, Vec3{ 0.439, 0.678, 0 }));
	sphere->set_shadowCast(false);
	add_object(sphere_red);
	/*objhandler.load_mesh("Resources\\helmets.obj");
	std::vector<Mesh> helm_mesh = objhandler.get_meshes();
	Grid* helmet;
	for (size_t i = 0; i < helm_mesh.size(); i++)
	{
		helmet = new Grid(helm_mesh[i], helmetsMat);
		add_object(helmet);
	}*/
	add_object(planeback);
	add_object(planeleft);
	add_object(planeright);
	add_object(planebottom);
	//add_object(planetop);
	//add_object(box);
	//add_object(statue);
	//add_object(lights);

#endif // COMPOSITE

}