// mingw: 
//   gcc -mconsole playsound.c -lwinmm -o playsound.exe
//

#include <windows.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf ("%s <soundfile>\n", argv[0]);
    exit(0);
  }

  if (!PlaySound(argv[1],0,SND_FILENAME|SND_SYNC)) {
    printf ("error playing file\n");
  }
  return 0;
}
