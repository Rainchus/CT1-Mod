.definelabel g_p1HP, 0x80174CF0
.definelabel func_800a06c0, 0x800a06c0
.definelabel dma_copy, 0x800809A0
.definelabel printText, 0x8007C8A4
.definelabel strlen, 0x800E503C
.definelabel strchr, 0x800E5064

.definelabel PAYLOAD_START_ROM, 0xB92000
.definelabel PAYLOAD_START_RAM, 0x80400000
.definelabel CT_MOD_ROM, PAYLOAD_START_ROM + 0x1000
.definelabel CT_MOD_RAM, PAYLOAD_START_RAM + 0x1000

.definelabel PAYLOAD_SIZE, 0x0006E000 //end of rom - 0xB92000 to get this size

//func_800809A0 - ROM 0x5BD10
PAYLOAD_START:
.headersize 0x80024C90
.org 0x8008A824
LUI a0, hi(PAYLOAD_START_ROM)
ADDIU a0, a0, lo(PAYLOAD_START_ROM)
LUI a1, hi(PAYLOAD_START_RAM)
ADDIU a1, a1, lo(PAYLOAD_START_RAM)
LUI a2, hi(PAYLOAD_SIZE)
JAL dma_copy
ADDIU a2, a2, lo(PAYLOAD_SIZE)

J originalCode
NOP


//.headersize 0x7F86E000 // Set the displacement between ROM and RAM addresses (0xB92000)
.headersize (PAYLOAD_START_RAM - PAYLOAD_START_ROM)
.org 0x80400000 //ct1.asm max size of 0x1000, otherwise will overwrite ct1.o
originalCode:
//restore from hook and jump back
LUI v0, 0x800F
LW v0, 0xA0A8 (v0)
ADDIU at, r0, 0xFFFF
LUI a0, 0x8012
BEQ v0, at, label0
ADDIU a0, a0, 0x5190
LUI at, 0x800F
SW v0, 0x68D8 (at)
LUI at, 0x800F
SW r0, 0x68DC (at)
label0:
LI t0, 0x8008A8A8
LI t1, mainASMFunctionJump
LW t1, 0x0000 (t1) //load jump instruction
SW t1, 0x0000 (t0) //store hook
SW r0, 0x0004 (t0) //store NOP after hook
LUI at, 0x800F
J 0x8008A84C
SW r0, 0x68DC (at)

mainASMFunctionJump:
J mainASMFunction //instruction copied and used as a hook
NOP

.org 0x80400080
mainASMFunction:
JAL mainCFunction
NOP
LUI a1, 0x800F
LW a1, 0x68D8 (a1)
J 0x8008A8B0
NOP

.headersize CT_MOD_RAM - CT_MOD_ROM
.org CT_MOD_RAM
.importobj "obj/ct1.o"

PAYLOAD_END: