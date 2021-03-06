#include "display.h"

Display::Display(int width, int height, const std::string& title)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    glContext = SDL_GL_CreateContext(window);

    GLenum status = glewInit();

    if(status != GLEW_OK)
    {
        std::cerr << "Glew Failed to Initialize" << std::endl;
    }

    closed = false;

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

Display::~Display()
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Display::update(IApplicationEventHandler& eventHandler)
{
    SDL_GL_SwapWindow(window);

    SDL_Event e;

    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case SDL_KEYDOWN:
                eventHandler.onKeyDown(e.key.keysym.scancode, e.key.repeat != 0);
                break;
            case SDL_KEYUP:
                eventHandler.onKeyUp(e.key.keysym.scancode, e.key.repeat != 0);
                break;
            case SDL_MOUSEBUTTONDOWN:
                eventHandler.onMouseDown(e.button.button, e.button.clicks);
                break;
            case SDL_MOUSEBUTTONUP:
                eventHandler.onMouseUp(e.button.button, e.button.clicks);
                break;
            case SDL_MOUSEMOTION:
                eventHandler.onMouseMove(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
                break;
            case SDL_QUIT:
                closed = true;
                break;
            default:
                break;
        }
    }
}

void Display::clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
