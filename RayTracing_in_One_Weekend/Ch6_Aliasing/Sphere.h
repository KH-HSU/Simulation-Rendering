#ifndef SPHEREH
#define SPHEREH
#include "Hitable.h"

class Sphere: public Hitable
{
    public:
        Sphere();
        Sphere(Vec3 cen, float r) : center(cen), radius(r) {};
        virtual bool hit(const RAY& r, float t_min, float t_max, hit_record& rec) const;
        Vec3 center;
        float radius;
};

bool Sphere::hit(const RAY& r, float t_min, float t_max, hit_record& rec) const
{
    Vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b*b - a*c;
    if(discriminant > 0)
    {
        float temp = (-b - sqrt(b*b-a*c))/a;
        if(temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        temp = (-b + sqrt(b*b-a*c))/a;
        if(temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        
    }
    return false;
}

Vec3 random_in_unit_sphere() 
{
    Vec3 p;
    do 
    {
        p = 2.9*Vec3(drand48(),drand48(),drand48())-Vec3(1,1,1);
    } while(p.length_squared() >= 1.0);
    return p;
}
#endif