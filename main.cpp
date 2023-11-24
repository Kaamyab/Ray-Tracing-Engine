#include "utility.h"

#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"

int main()
{
	hittable_list world;

	// add objects to the world
	world.add(make_shared<sphere>(point3(-0.5, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0.5, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	// Camera Instance
	camera cam;

	// Render the world
	cam.render(world);

}