INSTALL
  This patch is for FE8U!

  Buildfile users: Install by using Event Assembler to apply "MinimugPalette.event" to your ROM, or include 
  "MinimugPalette.event" in your buildfile.
  
  FEBuilder users: "Advanced Editors"->"Insert EA"->"Select File". Pick "MinimugPalette.event" and press "Load 
  Script".


WHATITDO?
  When switching from one minimug to another, the new palette is buffered, but the new tiles are immediately flushed 
  to VRAM. This patch instead buffers the tiles, preventing that one frame where a minimug is using the wrong palette.
  
  Mind you, the patch uses 0x200 bytes of RAMspace as a buffer. By default it'll use 0x201F148, which is used by the Sound Room, Random mode song id and related things. This should be unoccupied when this patch runs, but you can change the address by changing the MMP_Buffer definition in "MinimugPalette.event".
  
9/2/2023. ~Huichelaar