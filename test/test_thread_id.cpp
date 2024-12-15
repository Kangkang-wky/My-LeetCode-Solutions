#include "../include/help.h"

#define WARP_SIZE_IN_BITS 5

int main() {

  for (int threadIdx = 0; threadIdx < 128; threadIdx++) {

    uint tid = threadIdx;

    uint local_tid = tid & 0x1f;

    uint warp_idx = (tid >> WARP_SIZE_IN_BITS) & (2 - 1);
    uint warp_idy = tid >> (WARP_SIZE_IN_BITS + 1);

    uint ldg_idx = tid % 8;
    uint ldg_idy = tid / 8;

    uint sts_idx = ((tid & 0x1) ^ ((tid & 0xf) >> 3));
    uint sts_idy = tid >> 1;
    printf("%d %d %d %d %d %d %d %d\n", tid, local_tid, warp_idx, warp_idy,
           ldg_idx, ldg_idy, sts_idx, sts_idy);
  }

  return 0;
}
