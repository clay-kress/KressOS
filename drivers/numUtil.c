#include "AH.h"


/**********************************************************************/
float pwr(float base, float exponent) {
      
      float result;
      
      __asm__(
            "fld %1 \n\t"                                               // Loads the exp into st0
            "fld %2 \n\t"                                               // Loads the bas into st0
            // Now the exp is in st1 and the base is in st0
            
            "fyl2x \n\t"                                                // st0= st1 * log2(st0)
            "f2xm1 \n\t"                                                // st0= 2^st0-1
            "fld1 \n\t"                                                 // Loads 1 into st0, moves st0 to st1
            "faddp \n\t"                                                // Adds st0= st0 + st1
            
            "fst %0 \n\t"
            
            : "=m" (result)
            : "m" (exponent), "m" (base)
      );
      
      return result;
}
/**********************************************************************/
float log2(float x) {
      
      float result;
      
      __asm__(
            "fld1 \n\t"                                                 // Loads 1 into st0
            "fld %1 \n\t"                                               // Loads x into st0
            // Now st1= 1 and st0= x
            
            "fyl2x \n\t"                                                // st0= 1 * log2(x)
            
            "fst %0 \n\t"
            
            : "=m" (result)
            : "m" (x)
      );
      
      return result;
}
/**********************************************************************/
float absVal(float number) {
      
      float result;
      
      __asm__(
            "fld %1 \n\t"                                               // Loads the number into st0
            "fabs \n\t"                                                 // Processes absolute value of st0
            
            "fst %0"
            
            : "=m" (result)
            : "m" (number)
      );
      
      return result;
}
/**********************************************************************/
// Finds the sign of a number (+/-)
int sign(float number) {
      
      return number/absVal(number);
      
}
/**********************************************************************/
int numDigits(int number, int base) {
      
      int storedNumber= number;
      int length= 0;
      
      while (storedNumber != 0x00) {
            
            storedNumber /= base;
            length++;
      }
      
      return length;
}
/**********************************************************************/
