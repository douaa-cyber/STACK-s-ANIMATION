
void renderStack(SDL_Renderer* renderer, TTF_Font* font,  pile* p,  pile* r, int highlightIndex, int poppedValue, const char* stackName, const char* tempStackName, int foundValue) {
    SDL_SetRenderDrawColor(renderer, 240, 158, 190, 20);
    SDL_RenderClear(renderer);

    SDL_Rect baseRect = {100, 300, 200, 50};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    // Render main stack
    for (int i = 0; i <= p->sommet; i++) {
        SDL_Rect rect = {baseRect.x, baseRect.y - (i * (baseRect.h + 10)), baseRect.w, baseRect.h};

        if (p->T[i] == poppedValue) {
        SDL_SetRenderDrawColor(renderer, 55, 180, 200, 255); // Blue background for popped value
    } else if (p->T[i] == foundValue) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green background for found value
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
