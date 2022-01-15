.n64 // Let armips know we're coding for the N64 architecture
.open "rom/ct1.z64", "rom/ct1.mod.z64", 0 // Open the ROM file
.include "asm/ct1.asm" // Include ct1.asm to tell armips' linker where to find the game's function(s)
.close // Close the ROM file