<<<<<<< HEAD
void animatePopValueWithTempStack(pile* p, int valueToPop, pile* r, SDL_Renderer* renderer, TTF_Font* font) {
    // Move elements above the target value to the temporary stack
    moveAboveToTemp(p, valueToPop, r, renderer, font);

    // Animation: highlight elements in main stack before pop
    renderStack(renderer, font, p, r, -1, -1, "A", "B",valueToPop);

    // Introduce a delay to control the frame rate
    SDL_Delay(FRAME_DELAY);
     // Pop the specified value from the main stack
    int poppedValue = pop(p);
    if (poppedValue == valueToPop) {
        // Animation: show the final state after popping from main stack
        renderStack(renderer, font, p, r, -1, poppedValue, "A", "B",valueToPop);
=======
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
>>>>>>> e8ba6b216812147a665da1e6add9cf87ce4acf61

        // Introduce a delay to control the frame rate
        SDL_Delay(FRAME_DELAY);

        // Animation: highlight elements in temp stack before repush
<<<<<<< HEAD
        renderStack(renderer, font, p, r, poppedValue, -1, "A", "B",valueToPop);
=======
        renderStack(renderer, font, stack, tempStack, poppedValue, -1, "A", "B",valueToPop);
>>>>>>> e8ba6b216812147a665da1e6add9cf87ce4acf61

        // Introduce a delay to control the frame rate
        SDL_Delay(FRAME_DELAY);

        // Move elements back to the original stack one by one
<<<<<<< HEAD
        while (!isEmpty(r)) {
            int element = pop(r);
            push(p, element);

            // Animation: show the state after moving one element back

             renderStack(renderer, font, p, r, -1, -1, "A", "B",valueToPop);
            // Introduce a delay to control the frame rate
            SDL_Delay(FRAME_DELAY);
        }
    } else {
        // The value to pop is not on top, do not perform animation
        printf("Value %d not found in the stack. Restoring stack to its initial state.\n", valueToPop);


}}
=======
        while (tempStack->top >= 0) {
            int element = pop(tempStack);
            push(stack, element);

            // Animation: show the state after moving one element back
            renderStack(renderer, font, stack, tempStack, -1, -1, "A", "B",valueToPop);

            // Introduce a delay to control the frame rate
            SDL_Delay(FRAME_DELAY);
        }
    }
>>>>>>> e8ba6b216812147a665da1e6add9cf87ce4acf61
