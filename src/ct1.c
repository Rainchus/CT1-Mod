#include "../include/ct1.h"

char text[] = "test message";
char convertedText[sizeof(text)];
char testWithTextInFormat[] = "sound mode"; //TEST

char testDecimalText[] = "sound mode.";

f32 noClipMoveScalor = 25.0f;


//void printText(f32 xPos, f32 yPos, f32 zero, f32 scale, char* text, s32);

void convertAsciiToText(void* buffer, char* source) {
    u16* buf = (u16*)buffer;
    s32 strlength = ct_strlen(source);

    for (s32 i = 0; i < strlength; i++) {
        if ( (source[i] >= '0' && source[i] <= '9') ||
            (source[i] >= 'A' && source[i] <= 'Z')) { //is 0 - 9 or A - Z
            buf[i] = source[i] + 0xA380; //0x30 = 0 in ascii, 0xA3B0 = 0 in chameleon text
        } else if ( (source[i] > '0' && source[i] <= '9') ||
            (source[i] >= 'a' && source[i] <= 'z')) { //is 0 - 9 or A - Z
            buf[i] = source[i] + 0xA360; //0x30 = 0 in ascii, 0xA3B0 = 0 in chameleon text
        } else if(source[i] == '-') {
            buf[i] = 0xADA5; // '-' in chameleon text
        } else if (source[i] == '.') {
            buf[i] = 0xADA3; // '.' in chameleon text
        } else if (source[i] == ':') {
            buf[i] = 0xA1A7; // ':' in chameleon text
        } else if (source[i] == ' ') {
            buf[i] = 0xA1A1; // ' ' in chameleon text
        }
    }
}

void copyChameleonVariables(void) {
    p1ChameleonStoredX = p1ChameleonInstance->xPos;
    p1ChameleonStoredY = p1ChameleonInstance->yPos;
    p1ChameleonStoredZ = p1ChameleonInstance->zPos;
}

void loadChameleonVariables(void) {
    p1ChameleonInstance->xPos = p1ChameleonStoredX;
    p1ChameleonInstance->yPos = p1ChameleonStoredY;
    p1ChameleonInstance->zPos = p1ChameleonStoredZ;
}

void toggleNoClip (void) {
    //check double dpad up tap
    if (noClipBool == 1) {
        loadChameleonVariables();

        if (p1HeldButtons & 0x20000000) { //Z held
            if (p1HeldButtons & 0x08000000) { //dpad up
                p1ChameleonInstance->yPos += noClipMoveScalor;
                p1ChameleonStoredY = p1ChameleonInstance->yPos;
            } else if (p1HeldButtons & 0x04000000) { //dpad down
                p1ChameleonInstance->yPos -= noClipMoveScalor;
                p1ChameleonStoredY = p1ChameleonInstance->yPos;
            } else if (p1HeldButtons & 0x02000000) { //dpad right + Z
                collisionJALOpcodeAddress = 0x0C0309D7; //turn collision on
                noClipBool = !noClipBool; //flip bool
            } else if (p1HeldButtons & 0x01000000) { //dpad left + Z
                collisionJALOpcodeAddress = 0x0C0309D7; //turn collision on
                noClipBool = !noClipBool; //flip bool
            }
        } else {
            if (p1HeldButtons & 0x08000000) { //dpad up
                p1ChameleonInstance->zPos -= noClipMoveScalor;
                p1ChameleonStoredZ = p1ChameleonInstance->zPos;
            } else if (p1HeldButtons & 0x04000000) { //dpad down
                p1ChameleonInstance->zPos += noClipMoveScalor;
                p1ChameleonStoredZ = p1ChameleonInstance->zPos;
            } else if (p1HeldButtons & 0x02000000) { //dpad left
                p1ChameleonInstance->xPos -= noClipMoveScalor;
                p1ChameleonStoredX = p1ChameleonInstance->xPos;
            } else if (p1HeldButtons & 0x01000000) { //dpad right
                p1ChameleonInstance->xPos += noClipMoveScalor;
                p1ChameleonStoredX = p1ChameleonInstance->xPos;
            }
        }
    }

    if (dpadTimer == 0) {
        if (p1PressedButtons & 0x08000000) { //dpad up
            dpadTimer = 15; //15 frames, 1/2 second
        }
    } else { //dpad up was pressed once, check for second press
        if (p1PressedButtons & 0x08000000) { //dpad up
            dpadTimer = 0;
            if (noClipBool == 0) {
                collisionJALOpcodeAddress = 0; //turn collision off
                copyChameleonVariables();
                noClipBool = !noClipBool; //flip bool
            }
        }
    }

    if (dpadTimer != 0) {
        dpadTimer--;
    }

}

s32 returnTempFunction(void) {
    return 1;
}

void* crash_screen_copy_to_buf(void* dest, char* src, u32 size) {
    ct_memcpy(dest, src, size);
    return  (void*) ((s32)dest + (s32)size);
}

void formatText(s32 x, s32 y, char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    _Printf(crash_screen_copy_to_buf, &textBuffer, fmt, args);
    va_end(args);
}

void printTestMessage() {
    f32 xPos = 72.0f;
    f32 yPos = 72.0f;
    s32 arga2 = 0.0f;
    f32 scale = 0.5f;
    f32 arga4 = 0.0f;
    f32 arga5 = 0.0f;
    s32 style = 1;
    convertAsciiToText(&textBuffer2, (char*)textBuffer); //returns output to textBuffer at 0x807FE000
    printText(xPos, yPos, arga2, scale, arga4, arga5, &textBuffer2, style);
}

void testTextFormatWithPrintf(void) {
    f32 xPos = 20.0f;
    f32 yPos = 20.0f;
    s32 arga2 = 0.0f;
    f32 scale = 0.5f;
    f32 arga4 = 0.0f;
    f32 arga5 = 0.0f;
    s32 style = 3;

    if (p1ChameleonInstance != NULL) {
        formatText(0, 0, "XPos: %.4f\n", p1ChameleonInstance->xPos);
        convertAsciiToText(&textBuffer2, (char*)&textBuffer);
        printText(xPos, yPos, arga2, scale, arga4, arga5, &textBuffer2, style);

        yPos += 10.0f;

        formatText(0, 0, "YPos: %.4f\n", p1ChameleonInstance->yPos);
        convertAsciiToText(&textBuffer2, (char*)&textBuffer);
        printText(xPos, yPos, arga2, scale, arga4, arga5, &textBuffer2, style);

        yPos += 10.0f;

        formatText(0, 0, "ZPos: %.4f\n", p1ChameleonInstance->zPos);
        convertAsciiToText(&textBuffer2, (char*)&textBuffer);
        printText(xPos, yPos, arga2, scale, arga4, arga5, &textBuffer2, style);
    }
}

void mainCFunction(void) {
    //toggleNoClip();
    testTextFormatWithPrintf();
}