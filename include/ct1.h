typedef int s32;
typedef unsigned int u32;
typedef short s16;
typedef unsigned short u16;
typedef char s8;
typedef unsigned char u8;



s32 func_800A06C0(void* romStart, void* ramStart, s32 size);
void dma_copy(void* ROMAddr, void* RamAddr, s32 size);
extern s32 g_p1HP; // 0x80174CF0