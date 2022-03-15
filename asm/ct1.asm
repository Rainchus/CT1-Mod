.definelabel g_p1HP, 0x80174CF0
.definelabel func_800a06c0, 0x800a06c0
.definelabel dma_copy, 0x800809A0
.definelabel printText, 0x8007C8A4
.definelabel printText2, 0x8007C864
.definelabel ct_strlen, 0x800E503C
.definelabel ct_strchr, 0x800E5064
.definelabel ct_memcpy, 0x800E5010
.definelabel osContGetReadData, 0x800D4A24
.definelabel osContStartReadData, 0x800D4960
.definelabel gameMode, 0x800F68D8
.definelabel subGameMode, 0x800F68DC
.definelabel advanceRNG, 0x80052248
.definelabel frameCount, 0x800F6118

//data
.definelabel osCountCopy, 0x800F7044
.definelabel p1ChameleonInstance, 0x80182A98
.definelabel p1OSContStatus, 0x80254E50
.definelabel p1OSContPad, 0x80254E54
.definelabel cameraPtr, 0x801806E8
.definelabel p1PressedButtons, 0x80181484
.definelabel p1HeldButtons, 0x80181450
.definelabel collisionJALOpcodeAddress, 0x800C97CC
.definelabel collisionJALOpcodeHex, 0x0C0309D7
.definelabel _bzero, 0x800D94C0

//custom data
.definelabel textBuffer, 0x807FE000 //buffer size of 0x1000
.definelabel textBuffer2, 0x807FF000 //buffer size of 0x1000
//.definelabel cameraInstanceCopy, 0x807FDF90
.definelabel curRngSeedCopy, 0x807FDFD4
.definelabel rngAdvanceTotal, 0x807FDFD8
.definelabel controller1PreviousHeldButtons, 0x807FDFDC
.definelabel controller1CurrentHeldButtons, 0x807FDFDE
.definelabel controller1PressedButtons, 0x807FDFE0
.definelabel gameModeCopy, 0x807FDFE4
.definelabel stepValue, 0x807FDFE8
.definelabel p1ChameleonStoredX, 0x807FDFEC
.definelabel p1ChameleonStoredY, 0x807FDFF0
.definelabel p1ChameleonStoredZ, 0x807FDFF4
.definelabel dpadTimer, 0x807FDFF8
.definelabel noClipBool, 0x807FDFFC

//Payload related information
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

.org 0x8008AA20
LUI a0, 0x8012 //restore instruction from hook
JAL stepInvalidGameMode
ADDIU a0, a0, 0x81FC //restore instruction from hook

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

LI t0, 0x8005226C
LI t1, advanceRNGHookInstruction
LW t1, 0x0000 (t1) //load jump instruction
SW t1, 0x0000 (t0) //store hook
//clear custom variables
LUI at, hi(noClipBool)
SW r0, lo(noClipBool) (at)
LUI at, hi(dpadTimer)
SW r0, lo(dpadTimer) (at)
LUI at, hi(rngAdvanceTotal)
SW r0, lo(rngAdvanceTotal) (at)
LUI at, hi(curRngSeedCopy)
SW r0, lo(curRngSeedCopy) (at)
//
LUI at, 0x800F
J 0x8008A84C
SW r0, 0x68DC (at)

mainASMFunctionJump:
J mainASMFunction //instruction copied and used as a hook
NOP

advanceRNGTracker:
//v0 holds current rng seed
LI t0, rngAdvanceTotal
LW t1, 0x0000 (t0) //load total
ADDIU t1, t1, 1 //increment total
SW t1, 0x0000 (t0) //store new result
LI t0, curRngSeedCopy //load pointer to rng seed copy
SW v0, 0x0000 (t0) //store new rng seed (it's already in v0 due to location of our hook)
JR RA
NOP

advanceRNGHookInstruction:
J advanceRNGTracker
NOP

.org 0x804000C0
mainASMFunction:
JAL mainCFunction
NOP
LUI a1, 0x800F
LW a1, 0x68D8 (a1)
J 0x8008A8B0
NOP

.headersize CT_MOD_RAM - CT_MOD_ROM
.org CT_MOD_RAM
.include "asm/printf.asm" // Include ct1.asm to tell armips' linker where to find the game's function(s)
.align 4
.importobj "obj/ct1.o"



PAYLOAD_END:
