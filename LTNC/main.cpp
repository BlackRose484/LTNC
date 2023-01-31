#include<SDL.h>

SDL_Window* g_window;
SDL_Renderer* g_render;

bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return 0;
	}
	else
	{
		g_window = SDL_CreateWindow("hung", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
		if (g_window == NULL)
		{
			return 0;
		}
		else
		{
			g_render = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
			if (g_render == NULL)
			{
				return 0;
			}
			else
			{
				SDL_SetRenderDrawColor(g_render, 255,124, 255, 255);
			}
		}
	}
	return 1;
}

int main(int argc, char* argv[])
{
	if (!Init())
	{
		return 0;
	}
	else
	{
		bool q = 0;
		SDL_Event e;
		while (q == 0)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
					q = 1;
			}
			//clear render


			SDL_RenderClear(g_render);
			SDL_Rect rect_{ 0,0,400,400 };
			SDL_SetRenderDrawColor(g_render,0, 241, 126,255);
			SDL_RenderFillRect(g_render, &rect_);

			

			SDL_RenderPresent(g_render);
		}
	}
	return 0;
}