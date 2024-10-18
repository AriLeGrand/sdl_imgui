#pragma once
#include <iostream>
#include <stdio.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <SDL.h>
#include <vector>

#define W_WIDTH 1200
#define W_HEIGHT 700

int SDLInit(SDL_Window** window, SDL_Renderer** renderer);
int SDLCleanUp(SDL_Window* window);