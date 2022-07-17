#include <iostream>
#include "SDL_template.h"

#include "HitableList.h"
#include "Sphere.h"
Vec3 color(const RAY& r, Hitable *world)
{
	hit_record rec;
	if(world->hit(r, 0.001, MAXFLOAT, rec))
	{
		return 0.5*Vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);		
	}
	else
	{
		Vec3 unit_dir = unit_vector(r.direction());
		float t = 0.5*(unit_dir.y() + 1.0);
		return (1.0-t) * Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
	}

}
int main() {
	int width = 800;
	int height = 400;
	std::cout << "P3\n" << width << " " << height << "\n255\n";
    sdltemplate::sdl("Ray Tracer", width, height);
	sdltemplate::loop();
	Vec3 lower_left_corner(-2.0, -1.0, -1.0);
	Vec3 horizontal(4.0, 0.0, 0.0);
	Vec3 vertical(0.0, 2.0, 0.0);
	Vec3 origin(0.0, 0.0, 0.0);
	Hitable *list[2];
	list[0] = new Sphere(Vec3(0,0,-1), 0.5);
	list[1] = new Sphere(Vec3(0,-100.5, -1), 100);
	Hitable *world = new Hitablelist(list, 2);
	for(int y=height-1; y>=00; y--) {
		for(int x=0; x<width; x++) {
			float u = float(x) / float(width);
			float v = float(y) / float(height);
			RAY r(origin, lower_left_corner + u*horizontal + v*vertical);
			Vec3 p = r.point_at_parameter(2.0);
			Vec3 col = color(r, world);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			std::cout << ir << " " << ig << " " << ib << "\n";
			sdltemplate::setDrawColor(sdltemplate::createColor(ir,ig,ib,255));
			sdltemplate::drawPoint(x,height-y);
		}
	}
	while(sdltemplate::running) {
		sdltemplate::loop();
	}
}