void moveAboveToTemp(pile* p, int value, pile* r, SDL_Renderer* renderer, TTF_Font* font) {
    int found = 0;

    while (!isEmpty(p)) {
        int current = getTop(p);
        if (current == value) {
            found = 1;
            if (!isEmpty(p)) {
             if(isEmpty(r)){
                  pop(p);
                  renderStack(renderer, font, p, r,-1, value, "A", "B");
                  break;
             }
             renderStack(renderer, font, p, r, -1, current, "A", "B");
             pop(p);
           while (!isEmpty(r)) {
            // Draw the temp stack with the current moving value highlighted
            renderStack(renderer, font, p, r, value, -1, "A", "B");

            // Introduce a delay to control the frame rate
            SDL_Delay(FRAME_DELAY / 2);

            // Pop the value and push it into the main stack
            int poppedValue = pop(r);
            push(p, poppedValue);

            // Draw the temp stack with the final state
            renderStack(renderer, font, p, r, -1, -1, "A", "B");

            // Introduce a delay to control the frame rate
            SDL_Delay(FRAME_DELAY / 2);
        }
        break;
        }
        }else {
            push(r, current);
            p->sommet--;

            // Draw the main stack with the current moving value highlighted
            renderStack(renderer, font, p, r, current, -1, "A", "B");

            // Introduce a delay between pushing elements into the temp stack
            SDL_Delay(FRAME_DELAY / 2);
        }
    }

    // Draw the main stack with the value removed
    renderStack(renderer, font, p, r, -1, -1, "A", "B");

    // If the value was not found, return the elements to the main stack
    if (isEmpty(p)) {
        while (!isEmpty(r)) {
            // Draw the temp stack with the current moving value highlighted
            renderStack(renderer, font, p, r, value, -1, "A", "B");

            // Introduce a delay to control the frame rate
            SDL_Delay(FRAME_DELAY / 2);

            // Pop the value and push it into the main stack
            int poppedValue = pop(r);
            push(p, poppedValue);

            // Draw the temp stack with the final state
            renderStack(renderer, font, p, r, -1, -1, "A", "B");

            // Introduce a delay to control the frame rate
            SDL_Delay(FRAME_DELAY / 2);
        }
        printf("value %d is not found in the stack\n",value);


}}