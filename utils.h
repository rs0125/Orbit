// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <bits/stdc++.h>
using namespace std;

class vertex
{
public:
    double globalheight = 1000;
    double x = 0;
    double y = 0;
    double z = 0;
    vector<double> pt = {x, y, z};

    vertex(vector<double> i)
    {
        x = i[0];
        y = i[1];
        z = i[2];
        cout << "Vertex input successful" << endl;
    }

    vertex projected()
    {
        float fov = 30.0f;
        float scale = globalheight / 62.0f;
        vertex v = *this;

        // Perspective projection based on the Z value
        float invZ = 1.0f / (z + globalheight / 200); // Fix Z to account for the global height
        v.x = x * invZ * fov * scale + globalheight / 2.0f;
        v.y = -y * invZ * fov * scale + globalheight / 2.0f;

        // Prevent the cube from drifting
        return v;
    }

    void rotateX(float theta, vertex center)
    {
        x -= center.x;
        y -= center.y;
        z -= center.z;
        double y0 = y, z0 = z;
        y = y0 * cos(theta) - z0 * sin(theta);
        z = y0 * sin(theta) + z0 * cos(theta);
    }

    void rotateY(float theta, vertex center)
    {
        x -= center.x;
        y -= center.y;
        z -= center.z;
        double x0 = x, z0 = z;
        x = x0 * cos(theta) + z0 * sin(theta);
        z = -x0 * sin(theta) + z0 * cos(theta);
    }

    void rotateZ(float theta, vertex center)
    {
        x -= center.x;
        y -= center.y;
        z -= center.z;
        double x0 = x, y0 = y;
        x = x0 * cos(theta) - y0 * sin(theta);
        y = x0 * sin(theta) + y0 * cos(theta);
    }
};

vertex calculateCenter(const std::vector<vertex> &vertices);
bool isSafe(double x, double y);
void plot(vertex A, vertex B, SDL_Renderer *rend);
void plotTriangle(vertex A, vertex B, vertex C, SDL_Renderer *rend);

#endif
