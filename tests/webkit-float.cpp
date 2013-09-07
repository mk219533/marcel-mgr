#include <stdio.h>
#include <stdint.h>
#include <limits.h>  
#include <fenv.h>
typedef union {
    double d;
    uint32_t L[2];
} U;

//#define word0(x) ((uint32_t*)&x)[1]
//#define word1(x) ((uint32_t*)&x)[0]
#define word0(x) (x)->L[1]
#define word1(x) (x)->L[0]
#define NAN_WORD0 0x7ff80000
#define NAN_WORD1 0
#define Exp_mask  0x7ff00000


static void hexnan(U* rvp, const char** sp)
{
    uint32_t c, x[2];
    const char* s;
    int havedig, udx0, xshift;

    x[0] = x[1] = 0;
    havedig = xshift = 0;
    udx0 = 1;
    s = *sp;
    while ((c = *(const unsigned char*)++s)) {
        if (c >= '0' && c <= '9')
            c -= '0';
        else if (c >= 'a' && c <= 'f')
            c += 10 - 'a';
        else if (c >= 'A' && c <= 'F')
            c += 10 - 'A';
        else if (c <= ' ') {
            if (udx0 && havedig) {
                udx0 = 0;
                xshift = 1;
            }
            continue;
        } else if (/*(*/ c == ')' && havedig) {
            *sp = s + 1;
            break;
        } else
            return;    /* invalid form: don't change *sp */
        havedig = 1;
        if (xshift) {
            xshift = 0;
            x[0] = x[1];
            x[1] = 0;
        }
        if (udx0)
            x[0] = (x[0] << 4) | (x[1] >> 28);
        x[1] = (x[1] << 4) | c;
    }
    if ((x[0] &= 0xfffff) || x[1]) {
        word0(rvp) = Exp_mask | x[0];
        word1(rvp) = x[1];
    }
}

int main() {
  U rv;
//feenableexcept(FE_INVALID | FE_OVERFLOW);
  const char *s = "(fe00572c60)";
  //const char *s = "(1)";

  U z;
  //z.d = 0.0 / 0.0;
//  z.d = std::numeric_limits<double>::signaling_NaN();
  //printf("%08x %08x\n", word0(&z), word1(&z));
    
  word0(&rv) = NAN_WORD0;
  word1(&rv) = NAN_WORD1;
  printf("%s\n", s);
  printf("%08x %08x\n", word0(&rv), word1(&rv));
  hexnan(&rv, &s);
  printf("%f\n", rv.d);
  printf("%f\n", -rv.d);
  printf("%08x %08x\n", word0(&rv), word1(&rv));


}
