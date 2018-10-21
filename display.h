#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <string>

class Display
{
private:
    bool m_isClosed;

    SDL_Window* m_window;
    SDL_GLContext m_glContext;

public:
    Display(int width, int height, const std::string& title);
    virtual ~Display();

    void update();
    void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f);

    bool isClosed() const { return m_isClosed; }
};

#endif // DISPLAY_H