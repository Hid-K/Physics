#include <SDL.h>
#include <iostream>
#include "MathVectors.hpp"
#include "PhysicsSimu.hpp"

size_t windowCenterPosX = 0;
size_t windowCenterPosY = 0;

size_t windowWidth = 512;
size_t windowHeight = 512;

void DrawCircle(SDL_Renderer * renderer, signed long long int radius, Vec2 pos, RGB color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    for(int x=pos.x-radius; x<=pos.x+radius; x++)
    {
        for(int y=pos.y-radius; y<=pos.y+radius; y++)
        {
            if((pow(pos.y-y,2)+pow(pos.x-x,2)) <= 
                pow(radius,2))
            {
                SDL_RenderDrawPoint(renderer, (windowCenterPosX)+x,
                                              (windowCenterPosY)+y);
            }
        }
    }
}


int main()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout<<"Cant create a main window"<<std::endl;
        return -1;
    };


    SDL_Window * mainWindow = SDL_CreateWindow("HidPhysicsSimulation", 0, 0, windowWidth, windowHeight,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

    if(mainWindow == nullptr)
    {
        std::cout<<"Cant create a main window"<<std::endl;
        return -1;
    };


    SDL_Renderer * mainWindowRenderer = SDL_CreateRenderer(mainWindow, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(mainWindowRenderer == nullptr)
    {
        std::cout<<"Cant create a main window renderer"<<std::endl;
        return -1;
    };


    PhysicsSimu simulation(0.0001, 0.0001);
    PhysicalCircle circle;
    for(size_t i = rand()%100; i > 0; --i)
    {
        // srand(time(nullptr));
        circle = {10, 10, {(double)(rand()%windowWidth/2),(double)(rand()%windowHeight/2)},
        {0,0}, {(char)(rand()%255),(char)(rand()%255),(char)(rand()%255)}};
        simulation.addObject(circle);
    };
    
    char quit = 0;
    for(;quit == 0;)
    {
        SDL_SetRenderDrawColor(mainWindowRenderer, 0, 0, 0, 255);
        SDL_RenderClear(mainWindowRenderer);
        for(size_t i = 0; i < simulation.objectsCount(); ++i)
        {
            PhysicalCircle & currObject = *simulation.getObject(i);
            // if((currObject.pos.x) < (windowCenterPosX + windowWidth /2) &&
            //    (currObject.pos.x) > (windowCenterPosX - windowWidth /2) &&
            //    (currObject.pos.y) < (windowCenterPosY + windowHeight/2) &&
            //    (currObject.pos.y) > (windowCenterPosY - windowHeight/2))
            // {
                DrawCircle(mainWindowRenderer, currObject.radius, currObject.pos, currObject.color);
            // };
        };
        SDL_RenderPresent(mainWindowRenderer);
        SDL_Event e;
        for(;SDL_PollEvent(&e);)
        switch (e.type)
        {
            case SDL_QUIT:
                quit = 1;
                SDL_Quit();
                break;
            case SDL_MOUSEBUTTONDOWN:
                PhysicalCircle * obj;
                if(e.button.button == SDL_BUTTON_LEFT)
                {
                    obj = simulation.getObject({(double)e.button.x,(double)e.button.y});
                };
                if(obj != nullptr)
                {
                    for(;SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT);)
                    {
                        SDL_PollEvent(&e);
                        SDL_Delay(10);
                    };
                    obj->pos = {(double)e.button.x,(double)e.button.y};
                };
            break;
        }
        simulation.simulateTimePeriod(0.01);
        SDL_Delay(1000/60);
    };
    SDL_Quit();
    return 0;
};