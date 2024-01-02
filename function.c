
void renderStack(SDL_Renderer* renderer, TTF_Font* font,  pile* p,  pile* r, int highlightIndex, int poppedValue, const char* stackName, const char* tempStackName, int foundValue) {
    SDL_SetRenderDrawColor(renderer, 240, 158, 190, 20);
    SDL_RenderClear(renderer);

    SDL_Rect baseRect = {100, 300, 200, 50};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    // Render main stack
    for (int i = 0; i <= p->sommet; i++) {
        SDL_Rect rect = {baseRect.x, baseRect.y - (i * (baseRect.h + 10)), baseRect.w, baseRect.h};

        // Change the background color if the value is found
        if (p->T[i] ==poppedValue) {
            SDL_SetRenderDrawColor(renderer, 55, 180, 200, 0.5); // Blue background for found value
        } else {
            SDL_SetRenderDrawColor(renderer, 220, 100, 150, 0.5);
        }

        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 0,0, 255, 255);

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