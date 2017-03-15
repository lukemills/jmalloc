#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mymalloc.h"

void double_check_memory(int **ptrs, int *dc, int nptrs, int fl_size, int tbytes)
{
  void *low, *l;
  void *high, *h;
  int *ip, i;
  int nbytes;
  int nfl;

  nbytes = 0;

  for (i = 0; i < nptrs; i++) {
    l = (void *) ptrs[i];
    l -= 8;
    ip = (int *) l;

    if (*ip != dc[i]) {
      printf("Error: pointer number %d the wrong size (%d instead of %d)\n", i, *ip, dc[i]);
      exit(1);
    }
    h = l + *ip;
    if (nbytes == 0 || l < low) low = l;
    if (nbytes == 0 || h > high) high = h;
    nbytes += *ip;
  }
    
  nfl = 0;
  for (l = free_list_begin(); l != NULL; l = free_list_next(l)) {
    ip = (int *) l;
    h = l + *ip;
    if (nbytes == 0 || l < low) low = l;
    if (nbytes == 0 || h > high) high = h;
    nbytes += *ip;
    nfl++;
  }

  if (nbytes != tbytes) {
    printf("Error: Total bytes allocated and on the free list = %d, not %d\n", nbytes, tbytes);
    exit(0);
  }
    
  if (high - low != tbytes) {
    printf("Error: Highest address (0x%x) minus lowest (0x%x) does not equal %d\n", (int) high, (int) low, tbytes);
    exit(0);
  }

  if (nfl != fl_size && fl_size != -1) {
    printf("Error: %d nodes on the free list -- should be %d\n", nfl, fl_size);
    exit(0);
  }
}


main()
{
  int *ptrs[27];
  int *free_ptrs[27];
  int dc[27];

  ptrs[22] = my_malloc(145); dc[22] = 160;
  free_ptrs[7] = my_malloc(73);
  free_ptrs[5] = my_malloc(85);
  ptrs[18] = my_malloc(148); dc[18] = 160;
  ptrs[0] = my_malloc(127); dc[0] = 136;
  free_ptrs[21] = my_malloc(82);
  ptrs[7] = my_malloc(143); dc[7] = 152;
  free_ptrs[20] = my_malloc(90);
  free_ptrs[16] = my_malloc(86);
  free_ptrs[0] = my_malloc(95);
  free_ptrs[12] = my_malloc(91);
  free_ptrs[22] = my_malloc(95);
  ptrs[21] = my_malloc(115); dc[21] = 128;
  free_ptrs[19] = my_malloc(76);
  free_ptrs[11] = my_malloc(82);
  free_ptrs[26] = my_malloc(88);
  free_ptrs[8] = my_malloc(86);
  free_ptrs[23] = my_malloc(88);
  free_ptrs[24] = my_malloc(75);
  free_ptrs[10] = my_malloc(76);
  ptrs[10] = my_malloc(147); dc[10] = 160;
  free_ptrs[14] = my_malloc(74);
  ptrs[26] = my_malloc(131); dc[26] = 144;
  free_ptrs[1] = my_malloc(80);
  free_ptrs[18] = my_malloc(83);
  free_ptrs[17] = my_malloc(92);
  ptrs[15] = my_malloc(132); dc[15] = 144;
  ptrs[17] = my_malloc(118); dc[17] = 128;
  ptrs[25] = my_malloc(150); dc[25] = 160;
  free_ptrs[6] = my_malloc(75);
  free_ptrs[4] = my_malloc(90);
  free_ptrs[9] = my_malloc(91);
  free_ptrs[15] = my_malloc(80);
  ptrs[14] = my_malloc(151); dc[14] = 160;
  free_ptrs[13] = my_malloc(80);
  free_ptrs[2] = my_malloc(73);
  ptrs[19] = my_malloc(145); dc[19] = 160;
  ptrs[1] = my_malloc(147); dc[1] = 160;
  free_ptrs[3] = my_malloc(83);
  free_ptrs[25] = my_malloc(91);
  ptrs[12] = my_malloc(144); dc[12] = 152;
  ptrs[24] = my_malloc(124); dc[24] = 136;
  my_free(free_ptrs[21]);
  my_free(free_ptrs[3]);
  ptrs[20] = my_malloc(150); dc[20] = 160;
  my_free(free_ptrs[22]);
  my_free(free_ptrs[14]);
  ptrs[8] = my_malloc(137); dc[8] = 152;
  ptrs[16] = my_malloc(132); dc[16] = 144;
  my_free(free_ptrs[9]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[8]);
  ptrs[3] = my_malloc(115); dc[3] = 128;
  my_free(free_ptrs[16]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[18]);
  ptrs[13] = my_malloc(120); dc[13] = 128;
  ptrs[5] = my_malloc(137); dc[5] = 152;
  my_free(free_ptrs[7]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[11]);
  ptrs[11] = my_malloc(121); dc[11] = 136;
  my_free(free_ptrs[5]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[4]);
  ptrs[6] = my_malloc(130); dc[6] = 144;
  ptrs[4] = my_malloc(151); dc[4] = 160;
  my_free(free_ptrs[6]);
  my_free(free_ptrs[17]);
  ptrs[23] = my_malloc(123); dc[23] = 136;
  ptrs[9] = my_malloc(135); dc[9] = 144;
  my_free(free_ptrs[23]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[25]);
  ptrs[2] = my_malloc(119); dc[2] = 128;
  my_free(free_ptrs[10]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 27, 10, 8192);
  printf("Correct\n");
}
