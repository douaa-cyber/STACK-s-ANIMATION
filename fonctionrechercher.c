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
}
