#include <SDL3/SDL.h>
#include <SDL3/SDL_oldnames.h>
#include <iostream>

#include "ppm.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Incorrect Usage: [program] [ppm image name]" << std::endl;
    return 1;
  }

  ppm image(256);

  image.read(argv[1]);

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL_Init failed: %s", SDL_GetError());
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("ppm-image-viewer", image.get_Ncol(),
                                        image.get_Nrow(), 0);

  if (window == nullptr) {
    SDL_Log("Window creation failed: %s", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
  if (renderer == nullptr) {
    SDL_Log("Renderer creation failed: %s", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  bool running = true;
  SDL_Event event{};

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT ||
          (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)) {
        running = false;
      }
    }
    for (int i = 0; i < image.get_Nrow(); i++) {
      for (int j = 0; j < image.get_Ncol(); j++) {
        SDL_SetRenderDrawColor(renderer, image[i][j].R, image[i][j].G,
                               image[i][j].B, 255);
        SDL_RenderPoint(renderer, (float)j, (float)i);
      }
    }

    // SDL_SetRenderDrawColor(renderer, 25, 30, 45, 255);
    // SDL_RenderClear(renderer);

    // SDL_FRect square{350, 250, 100, 100};
    // SDL_SetRenderDrawColor(renderer, 80, 190, 120, 255);
    // SDL_RenderFillRect(renderer, &square);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
