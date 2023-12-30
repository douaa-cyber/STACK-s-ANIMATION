#include<SDL.h>

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


        printf("Commands: P (push), O (pop), Q (quit):\n");
        fflush(stdout);

        char input[10];
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Error or end of file
            break;
        }

        if (input[0] == 'q' || input[0] == 'Q') {
            running = 0;
        } else if (input[0] == 'p' || input[0] == 'P') {
            printf("Enter a number to push: ");
            fflush(stdout);
            int value;
            if (fgets(input, sizeof(input), stdin) != NULL) {
                value = atoi(input);

                // Check if the stack is full before pushing
                if (!isFull(&p)) {
                    push(&p, value);
                } else {
                    printf("Cannot push to a full stack.\n");
                }
            }
        } else if (input[0] == 'o' || input[0] == 'O') {
            printf("Enter a number to pop: ");
            fflush(stdout);
            int valueToPop;
            if (fgets(input, sizeof(input), stdin) != NULL) {
                valueToPop = atoi(input);

                // Check if the stack is empty before popping
                if (!isEmpty(&p)) {
                    animatePopValueWithTempStack(&p, valueToPop, &r, renderer, font);
                } else {
                    printf("Cannot pop from an empty stack.\n");
                }
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