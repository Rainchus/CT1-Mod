
typedef int s32;
typedef unsigned int u32;
typedef short s16;
typedef unsigned short u16;
typedef char s8;
typedef unsigned char u8;

typedef float f32;
typedef double f64;
#define NULL 0


typedef struct playerActor {
	/* 0x00 */ u32 flags; //a guess
	/* 0x04 */ f32 xPos;
	/* 0x08 */ f32 yPos;
	/* 0x0C */ f32 zPos;
    /* 0x10 */ char unk_10[0x14];
    /* 0x24 */ f32 xSpeed;
    /* 0x28 */ f32 ySpeed;
    /* 0x2C */ f32 zSpeed;
    /* 0x30 */ char unk_30[0x0C];
    /* 0x3C */ f32 yAngle;
    /* 0x40 */ char unk_40[0x88];
	/* 0xC8 */ s32 hp;
} playerActor;

typedef struct camera {
    /* 0x00 */ s32 flags;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 xPos;
    /* 0x10 */ f32 yPos;
    /* 0x14 */ f32 zPos;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ f32 unk_40;
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ f32 unk_48;
    /* 0x4C */ f32 unk_4C;
} camera; //sizeof 0x50 (?)


typedef struct mapRelatedStruct {
    /* 0x00 */ s32 isDuringRoomTransition;

    /* 0x0C */ s32 roomID;
} mapRelatedStruct;

typedef struct OSContStatus {
    u16 type;
    u8 status;
    u8 errno;
} OSContStatus;

typedef struct OSContPad {
    u16 button;
    s8 stick_x;
    s8 stick_y;
    u8 errno;
} OSContPad;

extern OSContStatus p1OSContStatus;
extern OSContPad p1OSContPad;


extern s32 p1PressedButtons;
extern s32 p1HeldButtons;

extern playerActor* p1ChameleonInstance;
extern camera* cameraInstance;
extern camera* cameraInstanceCopy;

extern s32 collisionJALOpcodeAddress;
extern s32 noClipBool;
extern s32 dpadTimer;
extern f32 p1ChameleonStoredX;
extern f32 p1ChameleonStoredY;
extern f32 p1ChameleonStoredZ;
extern s32 frameCount;

extern s32 gameMode;
extern s32 subGameMode;
extern s32 stepValue;
extern s32 gameModeCopy;

extern s16 controller1PreviousHeldButtons;
extern s16 controller1CurrentHeldButtons;
extern s16 controller1PressedButtons;

void ct_copyInputsToStruct(s32*, s32, s32, s32);
void osContStartReadData(s32*);
void osContGetReadData(void);
s32 func_800A06C0(void* romStart, void* ramStart, s32 size);
void dma_copy(void* ROMAddr, void* RamAddr, s32 size);
void printText(f32 xPos, f32 yPos, f32 zero, f32 scale, f32 zero2, f32 zero3, void* text, s32);
void printText2(f32 xPos, f32 yPos, f32 zero, f32 scale, f32 zero2, f32 zero3, void* text, s32);
s32 ct_strlen(void* string);
void ct_memcpy (void* destination, void* source, s32 size);
extern char* textBuffer;
extern void* textBuffer2;
extern u32 curRngSeedCopy;
extern u32 rngAdvanceTotal;
extern void _bzero(void* buffer, s32 size);

#define va_start(AP,LASTARG) (AP = ((__gnuc_va_list) __builtin_next_arg (LASTARG)))
typedef void *__gnuc_va_list;
void va_end (__gnuc_va_list);
typedef __gnuc_va_list va_list;

#define va_end(AP) ((void)0)

typedef __gnuc_va_list va_list;


extern s32 _Printf(void* functionCallback, void* arg, const char* fmt, va_list ap);
extern s32 g_p1HP; // 0x80174CF0