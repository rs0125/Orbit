#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <bits/stdc++.h>
#include "utils.h"
#include "ObjUtils.h"

using namespace std;

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

    bool running = true;

    SDL_Event event;
    float zOffset = 10.0f;

    Obj ImportedModel;
    vector<vertex> VertexBuffer;
    vector<vector<int>> EdgeBuffer;
    if (!ImportedModel.loadOBJ("plant.obj"))
    {
        cerr << "Failed to load model!" << endl;
        return 1;
    }

    float theta = 0;

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

        vertex center = calculateCenter(ImportedModel.VertexBuffer);

        for (auto &v : ImportedModel.VertexBuffer)
        {
            vertex temp = v;
            temp.rotateY(theta, center);
            transformedVertices.push_back(temp.projected());
        }
        theta += 0.01;

        for (auto edges : ImportedModel.EdgeBuffer)
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