#include<SDL_ttf.h>
#include<SDL.h>
#include<stdio.h>
void animatePopValueWithTempStack(Stack* stack, int valueToPop, Stack* tempStack, SDL_Renderer* renderer, TTF_Font* font) {
    // Move elements above the target value to the temporary stack
    moveAboveToTemp(stack, valueToPop, tempStack, renderer, font);

    // Animation: highlight elements in main stack before pop
    renderStack(renderer, font, stack, tempStack, -1, -1, "A", "B",valueToPop);

    // Introduce a delay to control the frame rate
    SDL_Delay(FRAME_DELAY);

    // Pop the specified value from the main stack
    int poppedValue = pop(stack);
    if (poppedValue == valueToPop) {
        // Animation: show the final state after popping from main stack
        renderStack(renderer, font, stack, tempStack, -1, poppedValue, "A", "B",valueToPop);

        // Introduce a delay to control the frame rate
        SDL_Delay(FRAME_DELAY);

        // Animation: highlight elements in temp stack before repush
        renderStack(renderer, font, stack, tempStack, poppedValue, -1, "A", "B",valueToPop);

        // Introduce a delay to control the frame rate
        SDL_Delay(FRAME_DELAY);

        // Move elements back to the original stack one by one
        while (tempStack->top >= 0) {
            int element = pop(tempStack);
            push(stack, element);

            // Animation: show the state after moving one element back
            renderStack(renderer, font, stack, tempStack, -1, -1, "A", "B",valueToPop);

            // Introduce a delay to control the frame rate
            SDL_Delay(FRAME_DELAY);
        }
    }
