/* ku : binary sudoku solver by jankeromnes */

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

#define DEBUG

// for each digit, where it is placed
unsigned long long is_a[9] = {0}; unsigned long is_b[9] = {0};

// for each digit, where it can be
unsigned long long can_a[9] = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
unsigned long can_b[9] = {0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff};

// masks
unsigned long long lin_a[9] = {0x1ff, 0x3fe00, 0x7fc0000, 0xff8000000, 0x1ff000000000, 0x3fe00000000000, 0x7fc0000000000000, 0x8000000000000000, 0};
unsigned long lin_b[9] = {0,0,0,0,0,0,0,0xff,0x1ff00};
unsigned long long col_a[9] = {0x8040201008040201,0x80402010080402,0x100804020100804,0x201008040201008,0x402010080402010,0x804020100804020,0x1008040201008040,0x2010080402010080,0x4020100804020100};
unsigned long col_b[9] = {0x100,0x201,0x402,0x804,0x1008,0x2010,0x4020,0x8040,0x10080};
unsigned long long blc_a[9] = {0x1c0e07, 0xe07038, 0x70381c0, 0xe07038000000, 0x70381c0000000, 0x381c0e00000000,0x81c0000000000000,0xe00000000000000,0x7000000000000000};
unsigned long blc_b[9] = {0,0,0,0,0,0,0x703,0x381c,0x1c0e0};


// a buffer     some chars
char buffer[9]; char i, j, c; unsigned long long llbu = 1, llb; unsigned long lbu = 1, lb;


// main function
int main ( int argc, char * argv[] ) {

  // input
  for (i = 0 ; i < 81 ; i++) {
    c = getchar();
    while (c != '.' && (c <= '0' || c > '9')) c = getchar();

#ifdef DEBUG

    //printf("found %c at position %d\n", c, i);

#endif

    if (c != '.') {
      c -= '1';
      if (i < 64) {
        llb = llbu << i;
        is_a[c] |= llb;
        for (j = 0 ; j < 9 ; j++) can_a[j] &= ~llb;
      }
      else {
        lb = lbu << (i-64);
        is_b[c] |= (lb);
        for (j = 0 ; j < 9 ; j++) can_b[j] &= ~lb;
      }
      can_a[c] &= ~lin_a[i/9] & ~col_a[i%9] & ~blc_a[(i/3)%3+3*(i/27)];
      can_b[c] &= ~lin_b[i/9] & ~col_b[i%9] & ~blc_b[(i/3)%3+3*(i/27)];
    }

  }


#ifdef DEBUG

  // generate masks
  /*unsigned long long mask = 0x1ff;
  for (i = 0 ; i < 9 ; i++) {
    printf("0x%llx, ", (mask << i*9));
  }
  putchar('\n');
  mask = 0x1c0e07;
  for (i = 0 ; i < 3 ; i++) {
    for (j = 0 ; j < 3 ; j++) {
      printf("0x%llx, ", (mask << (j*3+(i*18))));
    }
  }
  putchar('\n');*/

  // test masks
  printf("\nmasks (lines):\n");
  for (i = 0 ; i < 9 ; i++) {
    putchar('1'+i); putchar(':');
    for (j = 0 ; j < 81 ; j++) {
      if ((j % 9) == 0) putchar('\n');
      if (j < 64) putchar(((lin_a[i] >> j) & 0x1) + '0');
      else putchar(((lin_b[i] >> (j-64)) & 0x1) + '0');
    }
    putchar('\n');
  }
  printf("\nmasks (cols):\n");
  for (i = 0 ; i < 9 ; i++) {
    putchar('1'+i); putchar(':');
    for (j = 0 ; j < 81 ; j++) {
      if ((j % 9) == 0) putchar('\n');
      if (j < 64) putchar(((col_a[i] >> j) & 0x1) + '0');
      else putchar(((col_b[i] >> (j-64)) & 0x1) + '0');
    }
    putchar('\n');
  }
  printf("\nmasks (blocks):\n");
  for (i = 0 ; i < 9 ; i++) {
    putchar('1'+i); putchar(':');
    for (j = 0 ; j < 81 ; j++) {
      if ((j % 9) == 0) putchar('\n');
      if (j < 64) putchar(((blc_a[i] >> j) & 0x1) + '0');
      else putchar(((blc_b[i] >> (j-64)) & 0x1) + '0');
    }
    putchar('\n');
  }

  // test bitmap can
  printf("\nbitmap can (hex):\n");
  for (i = 0 ; i < 9 ; i++) {
    printf("%d: %lx %llx\n", i, can_b[i], can_a[i]);
  }
  printf("\nbitmap can (bin):\n");
  for (i = 0 ; i < 9 ; i++) {
    putchar('1'+i); putchar(':');
    for (j = 0 ; j < 81 ; j++) {
      if ((j % 9) == 0) putchar('\n');
      if (j < 64) putchar(((can_a[i] >> j) & 0x1) + '0');
      else putchar(((can_b[i] >> (j-64)) & 0x1) + '0');
    }
    putchar('\n');
  }

  // test bitmap is
  printf("\nbitmap is (hex):\n");
  for (i = 0 ; i < 9 ; i++) {
    printf("%d: %lx %llx\n", i, is_b[i], is_a[i]);
  }
  printf("\nbitmap is (bin):\n");
  for (i = 0 ; i < 9 ; i++) {
    putchar('1'+i); putchar(':');
    for (j = 0 ; j < 81 ; j++) {
      if ((j % 9) == 0) putchar('\n');
      if (j < 64) putchar(((is_a[i] >> j) & 0x1) + '0');
      else putchar(((is_b[i] >> (j-64)) & 0x1) + '0');
    }
    putchar('\n');
  }

  // inform about DEBUG
  printf("\nThese are just debug logs, please do not be scared.\nSimply undefine DEBUG in ku.c to get rid of them.\n\n");

#endif

  return 0;
}

