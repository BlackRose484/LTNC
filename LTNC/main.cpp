#include<SDL.h>

SDL_Window* g_window;
SDL_Renderer* g_render;

struct input
{
	int r, l, u, d;
};

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
			g_render = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
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

class Base
{
private:
	int x_pos;
	int y_pos;

	int x_val;
	int y_val;
	SDL_Texture *O_Text;
	SDL_Rect O_Rect;

	input input_;
public:

	Base()
	{
		x_pos = 0;
		y_pos = 0;

		y_val = 0;
		x_val = 0;

		input_.l = 0;
		input_.r = 0;
		input_.u = 0;
		input_.d = 0;
	}
	~Base()
	{

	}

	void setRect(const SDL_Rect& _rect)
	{
		O_Rect = _rect;
	}
	void key_move(SDL_Event e_)
	{
			if (e_.type == SDL_KEYDOWN)
				{
				switch (e_.key.keysym.sym)
				{
				case SDLK_w:
					input_.l = 0;
					input_.r = 0;
					input_.u = 1;
					input_.d = 0;
					break;
				case SDLK_s:
					input_.l = 0;
					input_.r = 0;
					input_.u = 0;
					input_.d = 1;
					break;
				case SDLK_a:
					input_.l = 1;
					input_.r = 0;
					input_.u = 0;
					input_.d = 0;
					break;
				case SDLK_d:
					input_.l = 0;
					input_.r = 1;
					input_.u = 0;
					input_.d = 0;
					break;
				}
			}
			else if (e_.type == SDL_KEYUP)
			{
				input_.l = 0;
				input_.r = 0;
				input_.u = 0;
				input_.d = 0;
			}
		
	}

	void move()
	{
		x_val = 0;
		y_val = 0;
		if (input_.l == 1)
		{
			x_val -= 10;
		}
		else if (input_.r == 1)
		{
			x_val += 10;
		}
		else if (input_.u == 1)
		{
			y_val -= 10;
		}
		else if (input_.d == 1)
		{
			y_val += 10;
		}
		x_pos += x_val;
		y_pos += y_val;
	}

	bool LoadI(SDL_Renderer* render)
	{
		SDL_Surface* I_sur = SDL_LoadBMP("pw.bmp");
		if (I_sur != NULL)
		{
			O_Text = SDL_CreateTextureFromSurface(render, I_sur);
			if (O_Text != NULL)
			{
				O_Rect.w = I_sur->w;
				O_Rect.h = I_sur->h;
			}
		}
		SDL_FreeSurface(I_sur);
		return O_Text != NULL;
	}

	void Render(SDL_Renderer* render)
	{
		O_Rect.x = x_pos;
		O_Rect.y = y_pos;
		SDL_Rect RenderQ{O_Rect.x,O_Rect.y,O_Rect.w,O_Rect.h };
		SDL_RenderCopy(render, O_Text, NULL, &RenderQ);
	}
};

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
		int x = 0;
		int y = 0;

		Base nv;
		nv.LoadI(g_render);


		while (!q)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
					q = 1;
				nv.key_move(e);
				
			}
			//clear render
			SDL_SetRenderDrawColor(g_render, 255, 255, 255,255);
			SDL_RenderClear(g_render);
			/*SDL_Rect rect_{ x,y,100,100 };
			SDL_SetRenderDrawColor(g_render,0, 241, 126,255);			
			SDL_RenderFillRect(g_render, &rect_);*/

			/*SDL_Rect rect_1{ 400,0,100,100 };
			SDL_SetRenderDrawColor(g_render, 0, 124, 25, 255);
			SDL_RenderFillRect(g_render, &rect_1);*/
			nv.move();
			nv.Render(g_render);
			

			SDL_RenderPresent(g_render);
		}
	}
	return 0;
}