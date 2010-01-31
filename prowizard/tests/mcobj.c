#ifdef DOS
#include "..\include\globals.h"
#include "..\include\extern.h"
#endif

#ifdef UNIX
#include "../include/globals.h"
#include "../include/extern.h"
#endif

short testMegaCruncherObj ( void )
{
  PW_Start_Address = PW_i;

  if ( (in_data[PW_Start_Address+12] != 0x4C ) ||
       (in_data[PW_Start_Address+13] != 0xDD ) ||
       (in_data[PW_Start_Address+14] != 0x00 ) ||
       (in_data[PW_Start_Address+15] != 0x03 ) ||
       (in_data[PW_Start_Address+16] != 0x4E ) ||
       (in_data[PW_Start_Address+17] != 0xAE ) ||
       (in_data[PW_Start_Address+18] != 0xFF ) ||
       (in_data[PW_Start_Address+19] != 0x3A ) ||
       (in_data[PW_Start_Address+20] != 0x4A ) ||
       (in_data[PW_Start_Address+21] != 0x80 ) ||
       (in_data[PW_Start_Address+22] != 0x67 ) ||
       (in_data[PW_Start_Address+23] != 0x30 ) ||
       (in_data[PW_Start_Address+24] != 0x41 ) ||
       (in_data[PW_Start_Address+25] != 0xFA ) ||
       (in_data[PW_Start_Address+26] != 0x00 ) ||
       (in_data[PW_Start_Address+27] != 0x0E ) )
  {
    /* should be enough :))) */
/*printf ( "#2 Start:%ld\n" , PW_Start_Address );*/
    return BAD;
    
  }

  /* packed size */
  PW_l = ( (in_data[PW_Start_Address+466]*256*256*256) +
	   (in_data[PW_Start_Address+467]*256*256) +
	   (in_data[PW_Start_Address+468]*256) +
	   in_data[PW_Start_Address+469] );
      PW_l += 532;

  if ( PW_i >= 36 )
  {
    if ( (in_data[PW_Start_Address-36]  != 0x00 ) ||
         (in_data[PW_Start_Address-35]  != 0x00 ) ||
         (in_data[PW_Start_Address-34]  != 0x03 ) ||
         (in_data[PW_Start_Address-33]  != 0xF3 ) ||
         (in_data[PW_Start_Address-32]  != 0x00 ) ||
         (in_data[PW_Start_Address-31]  != 0x00 ) ||
         (in_data[PW_Start_Address-30]  != 0x00 ) ||
         (in_data[PW_Start_Address-29]  != 0x00 ) ||
         (in_data[PW_Start_Address-28]  != 0x00 ) ||
         (in_data[PW_Start_Address-27]  != 0x00 ) ||
         (in_data[PW_Start_Address-26]  != 0x00 ) ||
         (in_data[PW_Start_Address-25]  != 0x02 ) ||
         (in_data[PW_Start_Address-24]  != 0x00 ) ||
         (in_data[PW_Start_Address-23]  != 0x00 ) ||
         (in_data[PW_Start_Address-22]  != 0x00 ) ||
         (in_data[PW_Start_Address-21]  != 0x00 ) )
    {
      Amiga_EXE_Header = BAD;
    }
    else
      Amiga_EXE_Header = GOOD;
  }
  else
    Amiga_EXE_Header = BAD;
 
  return GOOD;
  /* PW_l is the size of the pack */
}

