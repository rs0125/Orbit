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

vertex calculateCenter(const vector<vertex> &vertices)
{
    double xSum = 0, ySum = 0, zSum = 0;
    int count = vertices.size();
    for (const auto &v : vertices)
    {
        xSum += v.x;
        ySum += v.y;
        zSum += v.z;
    }
    return vertex({xSum / count, ySum / count, zSum / count});
}

void plot(vertex A, vertex B, SDL_Renderer *rend)
{
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    SDL_RenderDrawLine(rend, A.x, A.y, B.x, B.y);
}

void plotTriangle(vertex A, vertex B, vertex C, SDL_Renderer *rend)
{
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    SDL_RenderDrawLine(rend, A.x, A.y, B.x, B.y);
    SDL_RenderDrawLine(rend, C.x, C.y, B.x, B.y);
    SDL_RenderDrawLine(rend, A.x, A.y, C.x, C.y);
}

int main(int argc, char *argv[])
{

    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    SDL_Window *win = SDL_CreateWindow("Renderer Kumar",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       1000, 1000, 0);
    if (!win)
    {
        cerr << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    // creates a renderer to render our images
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);

    int running = 1;
    SDL_Event event;
    float zOffset = 6.0f;

    vertex v0 = vertex({-1, -1, -1 + zOffset});
    vertex v1 = vertex({1, -1, -1 + zOffset});
    vertex v2 = vertex({1, 1, -1 + zOffset});
    vertex v3 = vertex({-1, 1, -1 + zOffset});
    vertex v4 = vertex({-1, -1, 1 + zOffset});
    vertex v5 = vertex({1, -1, 1 + zOffset});
    vertex v6 = vertex({1, 1, 1 + zOffset});
    vertex v7 = vertex({-1, 1, 1 + zOffset});

    float theta = 0;

    vector<vertex> VertexBuffer = {v0, v1, v2, v3, v4, v5, v6, v7};

    vector<vector<int>> EdgeBuffer = {
        {0, 1, 2},
        {0, 2, 3},
        // Front face
        {4, 5, 6},
        {4, 6, 7},
        // Left face
        {0, 4, 7},
        {0, 7, 3},
        // Right face
        {1, 5, 6},
        {1, 6, 2},
        // Top face
        {3, 2, 6},
        {3, 6, 7},
        // Bottom face
        {0, 1, 5},
        {0, 5, 4}};

    while (running)
    {
        vector<vertex> transformedVertices;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false; // Exit the loop if close button is clicked
            }
        }
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 0); // white

        // Clear the screen with the chosen color
        SDL_RenderClear(rend);

        vertex center = calculateCenter(VertexBuffer);

        for (auto &v : VertexBuffer)
        {
            vertex temp = v;
            temp.rotateY(theta, center);
            transformedVertices.push_back(temp.projected());
        }
        theta += 0.01;

        for (auto edges : EdgeBuffer)
        {
            plotTriangle(transformedVertices[edges[0]], transformedVertices[edges[1]], transformedVertices[edges[2]], rend);
        }

        // Update the screen (present the renderer contents)
        SDL_RenderPresent(rend);

        SDL_Delay(16); // Delay for ~60 FPS
    }
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}