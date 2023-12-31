void animatePopValueWithTempStack(pile* p, int valueToPop, pile* r, SDL_Renderer* renderer, TTF_Font* font) {
    // Move elements above the target value to the temporary stack
    moveAboveToTemp(p, valueToPop, r, renderer, font);

    // Animation: highlight elements in main stack before pop
    renderStack(renderer, font, p, r, -1, -1, "A", "B",valueToPop);

    // Introduce a delay to control the frame rate
    SDL_Delay(FRAME_DELAY);
     // Pop the specified value from the main stack


