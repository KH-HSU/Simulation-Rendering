#include <iostream>
#include "SDL_template.h"

using namespace std;
int main()
{
    int u32Width = 800;
    int u32Height = 400;
    cout << "P3\n" << u32Width << " " << u32Height << "\n255\n";

    sdltemplate::sdl("Ray Tracer", u32Width, u32Height);
    sdltemplate::loop();
    for(int y = u32Height - 1; y >= 0; y--)
    {
        for(int x = 0; x < u32Width; x++)
        {
            float r = float(x) / float(u32Width);
            float g = float(y) / float(u32Height);
            float b = 0.2;
            int ir = int(255.99*r);
            int ig = int(255.99*g);
            int ib = int(255.99*b);
            cout << ir << " " << ig << " " << ib << "\n";
            sdltemplate::setDrawColor(sdltemplate::createColor(ir, ig, ib, 255));
            sdltemplate::drawPoint(x, u32Height - y);
        }
     }
    while(sdltemplate::running)
    {
        sdltemplate::loop();
    }
}

// print the image in ppm format ./a.out > one.ppm
// build the exe file g++ name.cpp -lSDL2 -std=c++11
