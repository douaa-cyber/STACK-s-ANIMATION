
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
