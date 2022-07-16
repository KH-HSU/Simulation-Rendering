#include <iostream>
#include "SDL_template.h"
#include "Ray.h"

bool draw_sphere(const Vec3 center, float radius, const RAY& r)
{
	Vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b*b - 4*a*c;
	return (discriminant > 0);
}
Vec3 sphere;
float sphere_radius;
Vec3 color(const RAY& r)
{
	if(draw_sphere(sphere, sphere_radius, r)){return Vec3(1, 0, 0);}
	Vec3 unit_dir = unit_vector(r.direction());
	float t = 0.5*(unit_dir.y() + 1.0);
	return (1.0-t) * Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
}
int main() {
	sphere = Vec3(0, 0 , -1);
	sphere_radius = 0.5;
	int width = 800;
	int height = 400;
	std::cout << "P3\n" << width << " " << height << "\n255\n";
    sdltemplate::sdl("Ray Tracer", width, height);
	sdltemplate::loop();
	Vec3 lower_left_corner(-2.0, -1.0, -1.0);
	Vec3 horizontal(4.0, 0.0, 0.0);
	Vec3 vertical(0.0, 2.0, 0.0);
	Vec3 origin(0.0, 0.0, 0.0);
	for(int y=height-1; y>=00; y--) {
		for(int x=0; x<width; x++) {
			float u = float(x) / float(width);
			float v = float(y) / float(height);
			RAY r(origin, lower_left_corner + u*horizontal + v*vertical);
			Vec3 col = color(r);
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