
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
    /* 0x10 */ char unk_10[0xB8];
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

s32 func_800A06C0(void* romStart, void* ramStart, s32 size);
void dma_copy(void* ROMAddr, void* RamAddr, s32 size);
void printText(f32 xPos, f32 yPos, f32 zero, f32 scale, f32 zero2, f32 zero3, void* text, s32);
void printText2(f32 xPos, f32 yPos, f32 zero, f32 scale, f32 zero2, f32 zero3, void* text, s32);
s32 ct_strlen(void* string);
void ct_memcpy (void* destination, void* source, s32 size);
extern char* textBuffer;
extern void* textBuffer2;

#define va_start(AP,LASTARG) (AP = ((__gnuc_va_list) __builtin_next_arg (LASTARG)))
typedef void *__gnuc_va_list;
void va_end (__gnuc_va_list);
typedef __gnuc_va_list va_list;

#define va_end(AP) ((void)0)

typedef __gnuc_va_list va_list;


extern s32 _Printf(void* functionCallback, void* arg, const char* fmt, va_list ap);
extern s32 g_p1HP; // 0x80174CF0