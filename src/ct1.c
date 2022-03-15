#include "../include/ct1.h"

char text[] = "test message";
char convertedText[sizeof(text)];
char testWithTextInFormat[] = "sound mode"; //TEST

char testDecimalText[] = "sound mode.";

f32 noClipMoveScalor = 25.0f;

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

void printPositionAngleSpd(void) {
    f32 xPos = 20.0f;
    f32 yPos = 35.0f;
    s32 arga2 = 0.0f;
    f32 scale = 0.5f;
    f32 arga4 = 0.0f;
    f32 arga5 = 0.0f;
    s32 style = 3;

    if (p1ChameleonInstance != NULL) {
        formatText(0, 0, "XPos: %.4f\n", p1ChameleonInstance->xPos);
        _bzero(&textBuffer2, 50); //clear 50 bytes of buffer
        convertAsciiToText(&textBuffer2, (char*)&textBuffer);
        printText(xPos, yPos, arga2, scale, arga4, arga5, &textBuffer2, style);

        yPos += 10.0f;

        formatText(0, 0, "YPos: %.4f\n", p1ChameleonInstance->yPos);
        _bzero(&textBuffer2, 50); //clear 50 bytes of buffer
        convertAsciiToText(&textBuffer2, (char*)&textBuffer);
        printText(xPos, yPos, arga2, scale, arga4, arga5, &textBuffer2, style);

        yPos += 10.0f;

        formatText(0, 0, "ZPos: %.4f\n", p1ChameleonInstance->zPos);
        _bzero(&textBuffer2, 50); //clear 50 bytes of buffer
        convertAsciiToText(&textBuffer2, (char*)&textBuffer);
        printText(xPos, yPos, arga2, scale, arga4, arga5, &textBuffer2, style);

        yPos += 10.0f;

        formatText(0, 0, "Angl: %.4f\n", p1ChameleonInstance->yAngle);
        _bzero(&textBuffer2, 50); //clear 50 bytes of buffer
        convertAsciiToText(&textBuffer2, (char*)&textBuffer);
        printText(xPos, yPos, arga2, scale, arga4, arga5, &textBuffer2, style);

        
        yPos = 200.0f;

        formatText(0, 0, "XSpd: %.4f\n", p1ChameleonInstance->xSpeed);
        _bzero(&textBuffer2, 50); //clear 50 bytes of buffer
        convertAsciiToText(&textBuffer2, (char*)&textBuffer);
        printText(xPos, yPos, arga2, scale, arga4, arga5, &textBuffer2, style);

        yPos += 10.0f;

        formatText(0, 0, "YSpd: %.4f\n", p1ChameleonInstance->ySpeed);
        _bzero(&textBuffer2, 50); //clear 50 bytes of buffer
        convertAsciiToText(&textBuffer2, (char*)&textBuffer);
        printText(xPos, yPos, arga2, scale, arga4, arga5, &textBuffer2, style);

        yPos += 10.0f;

        formatText(0, 0, "ZSpd: %.4f\n", p1ChameleonInstance->zSpeed);
        _bzero(&textBuffer2, 50); //clear 50 bytes of buffer
        convertAsciiToText(&textBuffer2, (char*)&textBuffer);
        printText(xPos, yPos, arga2, scale, arga4, arga5, &textBuffer2, style);
    }
}

void stepInvalidGameMode(void) { //any invalid game, however we will use 0x16 (0x8008AA24)
    s16 buttonsTemp;

    osContStartReadData((s32*)0x80181420); //copy controller data to osCont struct
    controller1PreviousHeldButtons = controller1CurrentHeldButtons;
    controller1CurrentHeldButtons = p1OSContPad.button;
    buttonsTemp = controller1CurrentHeldButtons & controller1PreviousHeldButtons;
    controller1PressedButtons = buttonsTemp ^ controller1CurrentHeldButtons;

    if (controller1PressedButtons & 0x0800) { //dpad up pressed
        stepValue = 1;
    } else if (controller1PressedButtons & 0x0400) { //dpad down pressed
        stepValue = 0;
        gameMode = gameModeCopy;
    }
}

void saveStateTest(void) {
    if (controller1CurrentHeldButtons & 0x02000000) { //dpad right
        ct_memcpy((void*)0x80410000, (void*)0x800E7230, 0x328DD0); //copy ram to expansion pak ram
    } else if (controller1CurrentHeldButtons & 0x01000000) { //dpad left
        ct_memcpy((void*)0x800E7230, (void*)0x80410000, 0x328DD0); //copy saved ram back to normal ram space
    }
}

void frameAdvanceMain(void) {
    if (p1PressedButtons & 0x01000000) { //dpad right to start
        p1PressedButtons = 0;
        gameModeCopy = gameMode;
        gameMode = 0x16; //set invalid gamemode
    } else if (stepValue == 2) { //waiting on frame advance mode
        gameMode = 0x16;
    } else if (stepValue == 1) { //advance a frame
        gameMode = gameModeCopy;
        stepValue = 2;
    }
}

void printRNGTracker(void) {
    //track current rng seed and rng seed calls
    f32 xPos = 165.0f;
    f32 yPos = 200.0f;
    s32 arga2 = 0.0f;
    f32 scale = 0.5f;
    f32 arga4 = 0.0f;
    f32 arga5 = 0.0f;
    s32 style = 3;
    formatText(0, 0, "Seed:  %08X\n", curRngSeedCopy);
    _bzero(&textBuffer2, 50); //clear 50 bytes of buffer
    convertAsciiToText(&textBuffer2, (char*)&textBuffer);
    printText(xPos, yPos, arga2, scale, arga4, arga5, &textBuffer2, style);

    yPos += 10.0f;

    formatText(0, 0, "Total: %d\n", rngAdvanceTotal);
    _bzero(&textBuffer2, 50); //clear 50 bytes of buffer
    convertAsciiToText(&textBuffer2, (char*)&textBuffer);
    printText(xPos, yPos, arga2, scale, arga4, arga5, &textBuffer2, style);
}

void mainCFunction(void) { //right before running current game mode
    //frameAdvanceMain();
    toggleNoClip();
    printPositionAngleSpd();
    printRNGTracker();
    //saveStateTest();
}