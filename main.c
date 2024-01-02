#include<SDL.h>
#include<SDL_ttf.h>
#include<stdio.h>
#include<stdlib.h>


int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Stack Animation",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WIDTH, HEIGHT,
                                          SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    TTF_Font* font = TTF_OpenFont("Roboto-Black.ttf", 24);
    int n;
    int nbr;
    pile p;
    initpile(&p);

    pile r;
    initpile(&r);

    SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Render the stacks
        renderStack(renderer, font, &p, &r, -1, -1, "A", "B", -1);

        printf("Commands: P (push), O (pop), Q (quit), S (sort):\n");
        char input[10];
        scanf("%s", &input);

        if (input[0] == 'q' || input[0] == 'Q') {
            running = 0;
        } else if (input[0] == 'p' || input[0] == 'P') {
            printf("Enter a number to push: ");
            scanf("%d", &nbr);

            // Check if the stack is full before pushing
            if (!isFull(&p)) {
                push(&p, nbr);
            } else {
                printf("Cannot push to a full stack.\n");
            }
        } else if (input[0] == 'o' || input[0] == 'O') {
            if (isEmpty(&p)) {
                printf("Cannot pop from an empty stack.\n");
            } else {
                printf("Enter a number to pop: ");
                scanf("%d", &n);

                // Check if the stack is empty before popping
                if (!isEmpty(&p)) {
                    moveAboveToTemp(&p, n, &r, renderer, font);
                }
            }
        } else if (input[0] == 's' || input[0] == 'S') {
            if (isEmpty(&p)) {
                printf("Cannot sort an empty stack.\n");
            } else {
                sort(&p, renderer, font);
            }
        }

        // Introduce a delay to control the frame rate
        SDL_Delay(FRAME_DELAY);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}