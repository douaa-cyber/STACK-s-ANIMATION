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
