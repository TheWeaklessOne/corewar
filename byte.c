#include <stdio.h>
#include <stdint.h>

int main(void)
{
	  uint16_t x = 1; /* 0x0001 */
	    printf("%s\n", *((uint8_t *) &x) == 0 ? "big-endian" : "little-endian");
		  return 0;
}
