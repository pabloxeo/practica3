# include "ParchisGUI.h"

ParchisGUI::ParchisGUI(const Parchis &model)
    : game_window(VideoMode(1600, 800), "Parchís", Style::Titlebar | Style::Close)
{
    this->model = model;
}