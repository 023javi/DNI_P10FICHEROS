#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define A 80

typedef struct {
    unsigned dia, mes, anyo;
} DATE;

struct ALUMNO {
    char DNI[9+1];
    char nom_comp[20+1];
    DATE nac;
};

void all_swap(struct ALUMNO *, struct ALUMNO *);
void all_bubbleSort(struct ALUMNO  [A], unsigned);
void fprint_DATE(FILE *, DATE);
void fprint_ALUMNO (FILE *, struct ALUMNO);


int main(void)
{
    return 0;
}
