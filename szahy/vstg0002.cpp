#include "SDL.h"
#include <time.h>
#include <iostream>
#include <SDL_image.h>


#define width 555
#define height 980
bool running, fullscreen;
SDL_Renderer* renderer;
SDL_Window* window;

SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}
int frameCount, timerFPS, lastFrame, fps, lastTime;   
void input() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) running = false;
	}
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	if (keystates[SDL_SCANCODE_ESCAPE]) running = false;
	if (keystates[SDL_SCANCODE_F11])  fullscreen =!fullscreen;
}
void update(){
	if (fullscreen) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	if (!fullscreen) SDL_SetWindowFullscreen(window, 0);

}
void drawboard() {
	int w, m;
	int g = 1;
	int f = 0;
	SDL_GetRendererOutputSize(renderer, &w, &m);


	if (m > w) {
		w = w + m;
		m = w - m;
		w = w - m;
		g = 0;
		f = 1;
	}
	int z = (w - m) / 2;
	int i = 0;
	int j = 0;
	SDL_Rect rect;
	for (j = 0; j < 8; j++) {
		for (i = 0; i < 8; i++) {
			rect.x = z * g + (m / 8) * i;
			rect.y = z * f + (m / 8) * j;
			rect.w = m / 8;
			rect.h = m / 8;
			if ((i + j) % 2 == 1) SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			if ((i + j) % 2 == 0)SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderFillRect(renderer, &rect);
		}
	}
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);


}
void drawpieces() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}
	loadTexture("assets/Knight.png");
}
void draw() {
	drawboard();
	drawpieces();

}
void renderboard() {
	SDL_Rect drawRect;
	for (int j = 0; j++; j < 8) {
		for (int i = 0; i++; i < 8) {
			if (i + j % 2 == 0) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
			}
			else {
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);

			}
				drawRect.x = 32 * i;
				drawRect.y = 32 * j;
				drawRect.w = 32;
				drawRect.h = 32;
				SDL_RenderFillRect(renderer, &drawRect);
			
		}
		
	}
	SDL_RenderPresent(renderer);
}


int main(int z, char*argv[]) {
	running = 1;
	fullscreen=0;
	if (SDL_Init(SDL_INIT_EVERYTHING < 0)) std::cout << "failed at sdl init" << std::endl;
	if (SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer) < 0) std::cout << "Failed at SDL_CreateWindowAndRenderer" << std::endl;
	SDL_SetWindowTitle(window, "SDL2 Window");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

	while (running) {
		lastFrame = SDL_GetTicks();
		if (lastFrame >= (lastFrame + 1000)) {
			lastTime = lastFrame;
			fps = frameCount;
			frameCount = 0;
		}

		update();
		input();
		draw();
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}