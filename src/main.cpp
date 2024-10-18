#include "win.h"
#include "ballManager.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int quit = 0;
using namespace std;
int x;
int y;
bool pause = false;


// execute the command : vcvarsall x64 
// undefines the main function to avoid conflict with SDL's main function
#undef main

int main(int argc, char* argv[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	Uint32 startTicks = SDL_GetTicks64();
	Ball ball;

	int quit = 0;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	std::vector<Ball> ballArray = {};
	
	if (SDLInit(&window, &renderer) !=0) {return -1;}

	std::srand(static_cast<unsigned int>(std::time(0)));

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);


	while (!quit) 
	{
		quit = SDLCleanUp(window);

		Uint32 timeElapsed = SDL_GetTicks64() - startTicks;
		SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Game Information And Controls", nullptr, ImGuiWindowFlags_NoResize);
        ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
        ImGui::ColorEdit3("clear color", (float*)&clear_color, ImGuiColorEditFlags_NoInputs);
        if (ImGui::Button("Pause"))                            
                pause =!pause;
            ImGui::SameLine();
            ImGui::Text("pause = %d", pause);
        ImGui::End();

        ImGui::Begin("Ball Information", nullptr, ImGuiWindowFlags_NoResize);
        ImGui::Text("Amount of balls: %d / %d", ballArray.size(), MAX_BALL_AMOUNT - 1);
        if (ImGui::Button("Delete all balls")){ballArray.clear();}
        if (ImGui::Button("Create new ball")){ball.Init(ballArray, ball);}
        ImGui::End();

        if (timeElapsed >= 1000){
			ball.Init(ballArray, ball);
			startTicks = SDL_GetTicks64();
            }
            if (ballArray.size() >= MAX_BALL_AMOUNT)
            {
                ball.Delete(ballArray);
            }


        for (int i = 0; i < ballArray.size(); i++)
        {
            if (!pause) {
                ballArray[i].Update(ballArray, renderer);
            }
            ballArray[i].Display(renderer);
        }

		
		//ball.Game(timeElapsed, startTicks, ballArray, ball, renderer);

        

		ImGui::Render();
        SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_UpdateWindowSurface(window);
        SDL_RenderPresent(renderer);
	}

    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}