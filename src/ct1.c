#include "../include/ct1.h"

//printText(s32 10, s32 0xFF, f32 a2, f32 1.0, f32 0, f32 0, char* text, s32 1);



char text[] = "test message";
char convertedText[sizeof(text)];
char testWithTextInFormat[] = "\xA3\xD4\xA3\xC5\xA3\xD3\xA3\xD4"; //TEST

//void printText(f32 xPos, f32 yPos, f32 zero, f32 scale, char* text, s32);

void printTestMessage() {
    f32 xPos = 72.0f;
    f32 yPos = 72.0f;
    s32 arga2 = 0.0f;
    f32 scale = 0.5f;
    f32 arga4 = 0.0f;
    f32 arga5 = 0.0f;
    char* messageText = testWithTextInFormat;
    s32 style = 1;
    printText(xPos, yPos, arga2, scale, arga4, arga5, messageText, style);
}

void mainCFunction(void) {
    printTestMessage();
}