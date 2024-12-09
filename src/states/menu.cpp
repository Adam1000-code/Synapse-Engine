#include "menu.hpp"
#include "play.hpp"
#include "../input/input.hpp"
#include "../core/engine.hpp"

using namespace std;

Menu::Menu()
{
}

bool Menu::Init()
{
    m_ctxt = Engine::GetInstance()->GetRenderer();
    cout << "Menu initialized" << endl;
    return true;
}

void Menu::Render()
{
    SDL_SetRenderDrawColor(m_ctxt, 16, 45, 70, 255);
    SDL_RenderClear(m_ctxt);

    SDL_RenderPresent(m_ctxt);
}

void Menu::Update()
{
}

bool Menu::Exit()
{
    cout << "Exited menu" << endl;
    return true;
}

void Menu::Quit()
{
}