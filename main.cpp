#include <SDL.h>
#include <iostream>
#include "MathVectors.hpp"
#include "PhysicsSimu.hpp"
#include <thread>

size_t windowCenterPosX = 0;
size_t windowCenterPosY = 0;

size_t windowWidth = 1024;
size_t windowHeight = 512;

#define SIMULATION_RENDER_STATUS_EXECUTING 1
#define SIMULATION_RENDER_STATUS_PAUSED    0

char simulationRenderStatus = SIMULATION_RENDER_STATUS_PAUSED;

void DrawCircle(SDL_Renderer * renderer, signed long long int radius, Vec2 pos, RGB & color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    for(int x=pos.x-radius; x<=pos.x+radius; x++)
    {
        for(int y=pos.y-radius; y<=pos.y+radius; y++)
        {
            if((pow(pos.y-y,2)+pow(pos.x-x,2)) <= pow(radius,2))
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
        if(
            (currObject.pos.x) < (windowCenterPosX + windowWidth /2) &&
            (currObject.pos.y) < (windowCenterPosY + windowHeight/2)
          )
        {
            DrawCircle(renderer, currObject.radius, currObject.pos, currObject.color);
            SDL_RenderDrawLine(renderer, (windowCenterPosX + windowWidth/2)+currObject.pos.x,
                                         (windowCenterPosY + windowHeight/2)+currObject.pos.y,
                                         (windowCenterPosX + windowWidth/2)+currObject.pos.x + currObject.speed.x,
                                         (windowCenterPosY + windowHeight/2)+currObject.pos.y + currObject.speed.y);
        };
    };
    SDL_RenderPresent(renderer);
};

void SDL_WINDOW_UPDATER(char * quit, PhysicsSimu * simulation, SDL_Renderer * mainWindowRenderer)
{
    for(;*quit == 0;)
    {
        drawPhysicsSimulation(mainWindowRenderer, simulation);
        if(simulationRenderStatus == SIMULATION_RENDER_STATUS_EXECUTING)
        {
            simulation->simulateTimePeriod(0.01);
        };
        SDL_Delay(1000/60);
    };
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


    PhysicsSimu * simulation = new PhysicsSimu({9.8, 9.8}, 0.0001);
    PhysicalCircle circle;
    // circle = {1, __PHYSICSSIMU_MASS_MAX__, {0,0}, {0,0}, {(char)255,(char)255,(char)255}}
    // simulation.addObject(circle);
    
    circle = {10, 10, {-250,0},
    {200,0}, {(char)(255),(char)(255),(char)(255)}};
    simulation->addObject(circle);




    circle = {10, 10, {-17,0},
    {0,0}, {(char)(rand()%255),(char)(rand()%255),(char)(rand()%255)}};
    simulation->addObject(circle);



    
    circle = {10, 10, {1,10},
    {0,0}, {(char)(rand()%255),(char)(rand()%255),(char)(rand()%255)}};
    simulation->addObject(circle);

    circle = {10, 10, {1,-10},
    {0,0}, {(char)(rand()%255),(char)(rand()%255),(char)(rand()%255)}};
    simulation->addObject(circle);




    circle = {10, 10, {19,-20},
    {0,0}, {(char)(rand()%255),(char)(rand()%255),(char)(rand()%255)}};
    simulation->addObject(circle);

    circle = {10, 10, {19,0},
    {0,0}, {(char)(rand()%255),(char)(rand()%255),(char)(rand()%255)}};
    simulation->addObject(circle);

    circle = {10, 10, {19,20},
    {0,0}, {(char)(rand()%255),(char)(rand()%255),(char)(rand()%255)}};
    simulation->addObject(circle);




    circle = {10, 10, {37,30},
    {0,0}, {(char)(rand()%255),(char)(rand()%255),(char)(rand()%255)}};
    simulation->addObject(circle);

    circle = {10, 10, {37,10},
    {0,0}, {(char)(rand()%255),(char)(rand()%255),(char)(rand()%255)}};
    simulation->addObject(circle);

    circle = {10, 10, {37,-10},
    {0,0}, {(char)(rand()%255),(char)(rand()%255),(char)(rand()%255)}};
    simulation->addObject(circle);

    circle = {10, 10, {37,-30},
    {0,0}, {(char)(rand()%255),(char)(rand()%255),(char)(rand()%255)}};
    simulation->addObject(circle);




    circle = {10, 10, {55,40},
    {0,0}, {(char)(rand()%255),(char)(rand()%255),(char)(rand()%255)}};
    simulation->addObject(circle);

    circle = {10, 10, {55,20},
    {0,0}, {(char)(rand()%255),(char)(rand()%255),(char)(rand()%255)}};
    simulation->addObject(circle);

    circle = {10, 10, {55,0},
    {0,0}, {(char)(rand()%255),(char)(rand()%255),(char)(rand()%255)}};
    simulation->addObject(circle);

    circle = {10, 10, {55,-20},
    {0,0}, {(char)(rand()%255),(char)(rand()%255),(char)(rand()%255)}};
    simulation->addObject(circle);

    circle = {10, 10, {55,-40},
    {0,0}, {(char)(rand()%255),(char)(rand()%255),(char)(rand()%255)}};
    simulation->addObject(circle);
    
    char quit = 0;
    
    std::thread(SDL_WINDOW_UPDATER, &quit, simulation, mainWindowRenderer).detach();

    for(;quit == 0;)
    {
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
                        obj = simulation->getObject({( (double)e.button.x - windowWidth/2)+(windowCenterPosX),
                                                     ( (double)e.button.y - windowHeight/2)+(windowCenterPosY)});
                        if(obj != nullptr)
                        {
                            // simulationRenderStatus = SIMULATION_RENDER_STATUS_PAUSED;
                            for(;SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT);)
                            {
                                obj->pos = {( (double)e.button.x - windowWidth/2)+(windowCenterPosX),
                                            ( (double)e.button.y - windowHeight/2)+(windowCenterPosY)};
                                // drawPhysicsSimulation(mainWindowRenderer, simulation);
                                SDL_PollEvent(&e);
                                SDL_Delay(10);
                            };
                            // simulationRenderStatus = SIMULATION_RENDER_STATUS_EXECUTING;
                        };
                    break;

                    case SDL_BUTTON_RIGHT:
                        PhysicalCircle * object;
                        object = simulation->getObject({( (double)e.button.x - windowWidth/2)+(windowCenterPosX),
                                                        ( (double)e.button.y - windowHeight/2)+(windowCenterPosY)});
                        if(object != nullptr)
                        {
                            // simulationRenderStatus = SIMULATION_RENDER_STATUS_PAUSED;
                            for(;SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT);)
                            {
                                object->speed = {( object->pos.x - ((double)e.button.x - windowWidth/2)+(windowCenterPosX)),
                                                   object->pos.y - (((double)e.button.y - windowHeight/2)+(windowCenterPosY))};

                                // drawPhysicsSimulation(mainWindowRenderer, simulation);
                                SDL_PollEvent(&e);
                                SDL_Delay(10);
                            };
                            // simulationRenderStatus = SIMULATION_RENDER_STATUS_EXECUTING;
                        };
                    break;
                };
            break;
            case SDL_KEYDOWN:
                // std::cout<<(char)e.key.keysym.scancode<<std::endl;
                if(e.key.keysym.scancode == SDL_SCANCODE_P)
                {
                    if(simulationRenderStatus == SIMULATION_RENDER_STATUS_PAUSED)
                    {
                        simulationRenderStatus = SIMULATION_RENDER_STATUS_EXECUTING;
                    } else
                    {
                        simulationRenderStatus = SIMULATION_RENDER_STATUS_PAUSED;
                    };
                    for(;e.key.keysym.scancode == 19;)SDL_PollEvent(&e);
                };

                if(e.key.keysym.scancode == SDL_SCANCODE_UP) //UP
                {
                    windowCenterPosY++;
                };

                if(e.key.keysym.scancode == SDL_SCANCODE_DOWN) //DOWN
                {
                    windowCenterPosY--;
                };
                if(e.key.keysym.scancode == SDL_SCANCODE_LEFT) //LEFT
                {
                    windowCenterPosX++;
                };
                if(e.key.keysym.scancode == SDL_SCANCODE_RIGHT) //RIGHT
                {
                    windowCenterPosX--;
                };

                default:
                break;
            break;
        };
        SDL_Delay(10);
    };
    SDL_Quit();
    return 0;
};