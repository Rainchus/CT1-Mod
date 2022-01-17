typedef int s32;
typedef unsigned int u32;
typedef short s16;
typedef unsigned short u16;
typedef char s8;
typedef unsigned char u8;

typedef float f32;
typedef double f64;



s32 func_800A06C0(void* romStart, void* ramStart, s32 size);
void dma_copy(void* ROMAddr, void* RamAddr, s32 size);
void printText(f32 xPos, f32 yPos, f32 zero, f32 scale, f32 zero2, f32 zero3, char* text, s32);
extern s32 g_p1HP; // 0x80174CF0