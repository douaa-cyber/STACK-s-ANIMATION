#include<SDL.h>
#include<SDL_ttf.h>
#include<stdio.h>
#include<stdlib.h>
#define WIDTH 640
#define HEIGHT 480
#define STACK_SIZE 5
#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 40
#define FRAME_DELAY 1000
int pushButtonClicked=0;
int popButtonClicked=0;
int peekButtonClicked=0;
int searchButtonClicked=0;
int sortButtonClicked=0;

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
    int popvalue= -1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                if (isMouseInsidePushButton(mouseX, mouseY)) {
                    printf("Push button clicked!\n");
                    pushButtonClicked = 1;
                } else if (isMouseInsidePopButton(mouseX, mouseY)) {
                    // Demander à l'utilisateur quelle valeur "popper"
                    printf("Enter a value to pop: ");
                    scanf("%d", &popvalue);
                    printf("Pop button clicked for value %d!\n", popvalue);
                    popButtonClicked = 1;
                } else if (isMouseInsidePeekButton(mouseX, mouseY)) {
                    printf("Peek button clicked!\n");
                    peekButtonClicked = 1;
                } else if (isMouseInsideSortButton(mouseX, mouseY)) {
                    printf("Sort button clicked!\n");
                    sortButtonClicked = 1;
                } else if (isMouseInsideSearchButton(mouseX, mouseY)) {
                    printf("Enter a value to search: ");
                    int searchValue;
                    scanf("%d", &searchValue);
                    printf("Search button clicked for value %d!\n", searchValue);
                    searchButtonClicked = 1;
                }
            }
        }
        if (pushButtonClicked) {
            printf("Enter a number to push: ");
            int pushValue;
            scanf("%d", &pushValue);
            push(&p, pushValue);
            pushButtonClicked = 0;
        }

            if (popButtonClicked) {
            if (popvalue != -1) {
                moveAboveToTemp(&p, popvalue ,&r,renderer,font);
                popvalue = -1; // Réinitialiser la valeur après l'opération "pop"
            } else {
                printf("Please enter a value to pop.\n");
            }
            popButtonClicked = 0;
        }
        if (peekButtonClicked) {
            if (isEmpty(&p)) {
                printf("Cannot peek an empty stack.\n");
            } else {
                printf("Top of the stack: %d\n", getTop(&p));
            }
            peekButtonClicked = 0;
        }
        if (sortButtonClicked) {
            if (isEmpty(&p)) {
                printf("Cannot sort an empty stack.\n");
            } else {
                printf("Sort button clicked!\n");
                sort(&p, renderer, font);
            }
            sortButtonClicked = 0;
        }

        if (searchButtonClicked) {
            printf("Enter a value to search: ");
            int searchValue;
            scanf("%d", &searchValue);
            search(&p, searchValue, renderer, font);
            searchButtonClicked = 0;
        }
        renderStack(renderer, font, &p, &r, -1, -1, "A", "B", -1);

    renderButton(renderer, font, 0, BUTTON_WIDTH, BUTTON_HEIGHT, "Push");
    renderButton(renderer, font, 1, BUTTON_WIDTH, BUTTON_HEIGHT, "Pop");
    renderButton(renderer, font, 2, BUTTON_WIDTH, BUTTON_HEIGHT, "Peek");
    renderButton(renderer, font, 3, BUTTON_WIDTH, BUTTON_HEIGHT, "Sort");
    renderButton(renderer, font, 4, BUTTON_WIDTH, BUTTON_HEIGHT, "Search");

        SDL_RenderPresent(renderer);
        SDL_Delay(FRAME_DELAY);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}