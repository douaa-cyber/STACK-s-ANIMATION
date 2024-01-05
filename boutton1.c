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
