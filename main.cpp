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
                SDL_RenderDrawPoint(renderer, (windowCenterPosX + windowWidth/2)+x,
                                              (windowCenterPosY + windowHeight/2)+y);
            }
        }
    }
};

void drawPhysicsSimulation(SDL_Renderer * renderer, PhysicsSimu * simulation)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for(size_t i = 0; i < simulation->objectsCount(); ++i)
    {
        PhysicalCircle & currObject = *simulation->getObject(i);
        // if((currObject.pos.x) < (windowCenterPosX + windowWidth /2) &&
        //    (currObject.pos.x) > (windowCenterPosX - windowWidth /2) &&
        //    (currObject.pos.y) < (windowCenterPosY + windowHeight/2) &&
        //    (currObject.pos.y) > (windowCenterPosY - windowHeight/2))
        // {
            DrawCircle(renderer, currObject.radius, currObject.pos, currObject.color);
            SDL_RenderDrawLine(renderer, (windowCenterPosX + windowWidth/2)+currObject.pos.x,
                                         (windowCenterPosY + windowHeight/2)+currObject.pos.y,
                                         (windowCenterPosX + windowWidth/2)+currObject.pos.x + currObject.speed.x,
                                         (windowCenterPosY + windowHeight/2)+currObject.pos.y + currObject.speed.y);
        // };
    };
    SDL_RenderPresent(renderer);
};


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


    PhysicsSimu simulation({9.8, 9.8}, 0.0001);
    PhysicalCircle circle;
    // circle = {1, __PHYSICSSIMU_MASS_MAX__, {0,0}, {0,0}, {(char)255,(char)255,(char)255}}
    // simulation.addObject(circle);
    for(size_t i = 10; i > 0; --i)
    {
        // srand(time(nullptr));
        circle = {10, (double)(rand()%1000), {(double)(rand()%windowWidth/2),(double)(rand()%windowHeight/2)},
        {1,1}, {(char)(rand()%255),(char)(rand()%255),(char)(rand()%255)}};
        simulation.addObject(circle);
    };
    
    char quit = 0;
    for(;quit == 0;)
    {
        drawPhysicsSimulation(mainWindowRenderer, &simulation);
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
                switch(e.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        PhysicalCircle * obj;
                        obj = simulation.getObject({(double)e.button.x-(windowCenterPosX+windowHeight/2),
                                                    (double)e.button.y-(windowCenterPosY+windowWidth/2)});
                        if(obj != nullptr)
                        {
                            for(;SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT);)
                            {
                                obj->pos = {(double)e.button.x-(windowCenterPosX+windowHeight/2),
                                            (double)e.button.y-(windowCenterPosY+windowWidth/2)};
                                drawPhysicsSimulation(mainWindowRenderer, &simulation);
                                SDL_PollEvent(&e);
                                SDL_Delay(10);
                            };
                        };
                    break;

                    case SDL_BUTTON_RIGHT:
                        PhysicalCircle * object;
                        object = simulation.getObject({(double)e.button.x-(windowCenterPosX+windowHeight/2),
                                                       (double)e.button.y-(windowCenterPosY+windowWidth/2)});
                        if(object != nullptr)
                        {
                            for(;SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT);)
                            {
                                object->speed = {(object->pos.x-((double)e.button.x-(windowCenterPosX+windowHeight/2))),
                                                 (object->pos.y-((double)e.button.y-(windowCenterPosY+windowWidth/2)))};

                                drawPhysicsSimulation(mainWindowRenderer, &simulation);
                                SDL_PollEvent(&e);
                                SDL_Delay(10);
                            };
                        };
                    break;
                };
            break;
        }
        simulation.simulateTimePeriod(0.01);
        // SDL_Delay(1000/60);
    };
    SDL_Quit();
    return 0;
};