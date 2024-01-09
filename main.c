#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 670
#define HEIGHT 490
#define STACK_SIZE 5
#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 40
#define FRAME_DELAY 1000

int pushButtonClicked=0;
int popButtonClicked=0;
int peekButtonClicked=0;
int searchButtonClicked=0;
int sortButtonClicked=0;
typedef struct {
    int T[STACK_SIZE];
    int sommet;
} pile;



int isEmpty( pile* p) {
    return p->sommet < 0;
}

int isFull( pile* p) {
    return p->sommet == STACK_SIZE - 1;
}
int initpile( pile* p){
     return p->sommet= -1;
}

int getTop( pile* p) {
    if (!isEmpty(p)) {
        return p->T[p->sommet];
    }
    return -1; // Indicates an empty stack
}

void push(pile* p, int value) {
    if (!isFull(p)) {
        p->sommet++;
        p->T[p->sommet] = value;
    } else {
        printf("Stack is full. Cannot push element.\n");
    }
}

int pop(pile* p) {
    if (!isEmpty(p)) {
        int value = getTop(p);
        p->sommet--;
        return value;
    }
    return -1; // Indicates an empty stack
}
void sort(pile* P, SDL_Renderer* renderer, TTF_Font* font) {
    pile T, Q;
    int min, x;

    // Initialize temporary stacks
    initpile(&T);
    initpile(&Q);

    // Sorting algorithm without SDL2 animation
    while (!isEmpty(P)) {
        min = getTop(P);

        while (!isEmpty(P)) {
            x = pop(P);
            push(&T, x);
            if (min > x) min = x;
        }

        // Restore the minimum values to Q, and others to P
        while (!isEmpty(&T)) {
            x = pop(&T);
            if (min == x) {
                push(&Q, x);
            } else {
                push(P, x);
            }
        }
    }

    // Restore Q to P
    while (!isEmpty(&Q)) {
        x = pop(&Q);
        push(P, x);
    }
}




void renderStack(SDL_Renderer* renderer, TTF_Font* font,  pile* p,  pile* r, int highlightIndex, int poppedValue, const char* stackName, const char* tempStackName, int foundValue) {
    SDL_SetRenderDrawColor(renderer, 240, 158, 190, 20);
    SDL_RenderClear(renderer);

    SDL_Rect baseRect = {100, 300, 200, 50};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    for (int i = 0; i <= p->sommet; i++) {
    SDL_Rect rect = {baseRect.x, baseRect.y - (i * (baseRect.h + 10)), baseRect.w, baseRect.h};

    // Change the background color if the value is found
    if (p->T[i] == poppedValue) {
        SDL_SetRenderDrawColor(renderer, 55, 180, 200, 255); // Blue background for popped value
    } else if (p->T[i] == foundValue) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green background for found value
    } else {
        SDL_SetRenderDrawColor(renderer, 220, 100, 150, 0.5);
    }

    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    char text[10];
    sprintf(text, "%d", p->T[i]);

    SDL_Color textColor = {0, 0, 0}; // black text color
    if (i == highlightIndex) {
        textColor.r = 255;
    }
    if (p->T[i] == poppedValue) {
        textColor.g = 255;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect text_rect = {rect.x + rect.w / 2 - 10, rect.y + rect.h / 2 - 10, 20, 20};
    SDL_RenderCopy(renderer, texture, NULL, &text_rect);

    SDL_DestroyTexture(texture);
}


    // Render stack name
    SDL_Surface* stackNameSurface = TTF_RenderText_Solid(font, stackName, (SDL_Color){0, 0, 0, 255});
    SDL_Texture* stackNameTexture = SDL_CreateTextureFromSurface(renderer, stackNameSurface);
    SDL_Rect stackNameRect = {baseRect.x + baseRect.w / 2 - 10, baseRect.y + baseRect.h + 10, stackNameSurface->w, stackNameSurface->h};
    SDL_RenderCopy(renderer, stackNameTexture, NULL, &stackNameRect);
    SDL_DestroyTexture(stackNameTexture);
    SDL_FreeSurface(stackNameSurface);

    // Render temporary stack
    for (int i = 0; i <= r->sommet; i++) {
        SDL_Rect rect = {baseRect.x + 220, baseRect.y - (i * (baseRect.h + 10)), baseRect.w, baseRect.h};

        // Change the background color if the value is found
        if (r->T[i] == foundValue) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Blue background for found value
        } else {
            SDL_SetRenderDrawColor(renderer, 220, 100, 150, 0.5);
        }

        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        char text[10];
        sprintf(text, "%d", r->T[i]);

        SDL_Color textColor = {0, 0, 0}; // black text color
        if (i == highlightIndex) {
            textColor.r = 255;
        }

        SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        SDL_Rect text_rect = {rect.x + rect.w / 2 - 10, rect.y + rect.h / 2 - 10, 20, 20};
        SDL_RenderCopy(renderer, texture, NULL, &text_rect);

        SDL_DestroyTexture(texture);
    }

    // Render temp stack name
    SDL_Surface* tempStackNameSurface = TTF_RenderText_Solid(font, tempStackName, (SDL_Color){0, 0, 0, 255});
    SDL_Texture* tempStackNameTexture = SDL_CreateTextureFromSurface(renderer, tempStackNameSurface);
    SDL_Rect tempStackNameRect = {baseRect.x + 200 + baseRect.w / 2 - 20, baseRect.y + baseRect.h + 10, tempStackNameSurface->w, tempStackNameSurface->h};
    SDL_RenderCopy(renderer, tempStackNameTexture, NULL, &tempStackNameRect);
    SDL_DestroyTexture(tempStackNameTexture);
    SDL_FreeSurface(tempStackNameSurface);

    SDL_RenderPresent(renderer);
}
void search(pile* p, int valueToSearch, SDL_Renderer* renderer, TTF_Font* font) {
    pile temp;
    initpile(&temp);

    int found = 0;
    int index = 1;

    // Search for the value in the main stack
    while (!isEmpty(p)) {
        int current = pop(p);
        push(&temp, current);

        // Draw the stack with the current value highlighted
        renderStack(renderer, font, p, &temp, index, -1, "A", "B", (current == valueToSearch) ? valueToSearch : -1);

        // Introduce a delay to control the frame rate
        SDL_Delay(FRAME_DELAY / 2);

        if (current == valueToSearch) {
            found = 1;
            break;
        }

        index++;
    }

    // Restore the main stack
    while (!isEmpty(&temp)) {
        int current = pop(&temp);
        push(p, current);

        // Draw the stack with the current value highlighted
        renderStack(renderer, font, p, &temp, index, -1, "A", "B", (current == valueToSearch) ? valueToSearch : -1);

        // Introduce a delay to control the frame rate
        SDL_Delay(FRAME_DELAY / 2);

        index--;
    }

    // Display the search result
    if (found) {
        printf("Value %d found.\n", valueToSearch);
    } else {
        printf("Value %d not found in the stack.\n", valueToSearch);
    }
    renderStack(renderer, font, p, &temp, index, -1, "A", "B", valueToSearch);
    SDL_Delay(FRAME_DELAY * 2);
    renderStack(renderer, font, p, &temp, index, -1, "A", "B", -1);
}

void moveAboveToTemp(pile* p, int value, pile* r, SDL_Renderer* renderer, TTF_Font* font) {
    int found = 0;

    while (!isEmpty(p)) {
        int current = getTop(p);
        if (current == value) {
            found = 1;
            if (!isEmpty(p)) {
                if (isEmpty(r)) {
                    pop(p);
                    renderStack(renderer, font, p, r, -1, value, "A", "B", -1);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(FRAME_DELAY);
                    break;
                }
                renderStack(renderer, font, p, r, -1, current, "A", "B", -1);
                pop(p);
                while (!isEmpty(r)) {
                    // Draw the temp stack with the current moving value highlighted
                    renderStack(renderer, font, p, r, value, -1, "A", "B", -1);

                    // Introduce a delay to control the frame rate
                    SDL_Delay(FRAME_DELAY / 2);

                    // Pop the value and push it into the main stack
                    int poppedValue = pop(r);
                    push(p, poppedValue);

                    // Draw the temp stack with the final state
                    renderStack(renderer, font, p, r, -1, -1, "A", "B", -1);

                    // Introduce a delay to control the frame rate
                    SDL_Delay(FRAME_DELAY / 2);
                }
                break;
            }
        } else {
            push(r, current);
            p->sommet--;

            // Draw the main stack with the current moving value highlighted
            renderStack(renderer, font, p, r, current, -1, "A", "B", -1);

            // Introduce a delay between pushing elements into the temp stack
            SDL_Delay(FRAME_DELAY / 2);

            SDL_RenderPresent(renderer);
        }
    }

    // Draw the main stack with the value removed
    renderStack(renderer, font, p, r, -1, -1, "A", "B", -1);
    SDL_RenderPresent(renderer);

    // Introduce a delay before returning elements to the main stack
    SDL_Delay(FRAME_DELAY);

    // If the value was not found, return the elements to the main stack
    if (isEmpty(p)) {
        while (!isEmpty(r)) {
            // Draw the temp stack with the current moving value highlighted
            renderStack(renderer, font, p, r, value, -1, "A", "B", -1);

            // Introduce a delay to control the frame rate
            SDL_Delay(FRAME_DELAY / 2);

            // Pop the value and push it into the main stack
            int poppedValue = pop(r);
            push(p, poppedValue);

            // Draw the temp stack with the final state
            renderStack(renderer, font, p, r, -1, -1, "A", "B", -1);

            // Introduce a delay to control the frame rate
            SDL_Delay(FRAME_DELAY / 2);

            SDL_RenderPresent(renderer);
        }
        printf("value %d is not found in the stack\n", value);
    }
}



int isMouseInsidePushButton(int mouseX, int mouseY) {
    int x = 10;
    int y = 10;
    return mouseX >= x && mouseX <= x + BUTTON_WIDTH && mouseY >= y && mouseY <= y + BUTTON_HEIGHT;
}

int isMouseInsidePopButton(int mouseX, int mouseY) {
    int x = 10 + (BUTTON_WIDTH + 10);
    int y = 10;
    return mouseX >= x && mouseX <= x + BUTTON_WIDTH && mouseY >= y && mouseY <= y + BUTTON_HEIGHT;
}

int isMouseInsidePeekButton(int mouseX, int mouseY) {
    int x = 10 + 2 * (BUTTON_WIDTH + 10);
    int y = 10;
    return mouseX >= x && mouseX <= x + BUTTON_WIDTH && mouseY >= y && mouseY <= y + BUTTON_HEIGHT;
}

int isMouseInsideSortButton(int mouseX, int mouseY) {
    int x = 10 + 3 * (BUTTON_WIDTH + 10);
    int y = 10;
    return mouseX >= x && mouseX <= x + BUTTON_WIDTH && mouseY >= y && mouseY <= y + BUTTON_HEIGHT;
}

int isMouseInsideSearchButton(int mouseX, int mouseY) {
    int x = 10 + 4 * (BUTTON_WIDTH + 10);
    int y = 10;
    return mouseX >= x && mouseX <= x + BUTTON_WIDTH && mouseY >= y && mouseY <= y + BUTTON_HEIGHT;
}
int isMouseInsideCreateButton(int mouseX, int mouseY) {
    int x = 10 + 5 * (BUTTON_WIDTH + 10);
    int y = 10;
    return mouseX >= x && mouseX <= x + BUTTON_WIDTH && mouseY >= y && mouseY <= y + BUTTON_HEIGHT;
}

void renderButton(SDL_Renderer* renderer, TTF_Font* font, int index, int width, int height, const char* text) {
    int spacing = 10; // Ajustez l'espacement entre les boutons
    int x = 10 + (width + spacing) * index;
    int y = 10;

    SDL_SetRenderDrawColor(renderer, 90, 27, 0, 255);
    SDL_Rect buttonRect = {x, y, width, height};
    SDL_RenderFillRect(renderer, &buttonRect);

    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect = {x + width / 2 - textSurface->w / 2, y + height / 2 - textSurface->h / 2, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}


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


                    printf("Pop button clicked !\n");
                    popButtonClicked = 1;
                } else if (isMouseInsidePeekButton(mouseX, mouseY)) {
                    printf("Peek button clicked!\n");
                    peekButtonClicked = 1;
                } else if (isMouseInsideSortButton(mouseX, mouseY)) {
                    printf("Sort button clicked!\n");
                    sortButtonClicked = 1;
                } else if (isMouseInsideSearchButton(mouseX, mouseY)) {
                    printf("Search button clicked !\n");
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
            if(isEmpty(&p)){
                printf("cannot pop from an empty stack");
            }  else{
               printf("Enter a value to pop: ");
                scanf("%d", &popvalue);

                moveAboveToTemp(&p, popvalue ,&r,renderer,font);
               renderStack(renderer,font,&p,&r,-1,popvalue,"A","B",-1);}

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


