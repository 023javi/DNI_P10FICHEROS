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

const char nombres[8][10+1]={"jose","roberto","fernando","mario",
"sandra", "raquel", "isabel", "pilar"};
const char apellidos[8][10+1]={"garcia", "hernandez", "gutierrez",
"gomez", "fernandez", "lopez", "sanchez", "perez" };

void print_DATE(DATE );
void print_ALUMNO (struct ALUMNO);
void rand_DATE(DATE  *);
void rand_nom_comp(char [20+1]);
void rand_ALUMNO(struct ALUMNO  *);
unsigned es_fecha_valida(DATE);
void rand_str_DNI(char str_DNI[9+1]);

void all_swap(struct ALUMNO *, struct ALUMNO *);
void all_bubbleSort(struct ALUMNO  [A], unsigned);
void fprint_DATE(FILE *, DATE);
void fprint_ALUMNO (FILE *, struct ALUMNO);


void print_DATE(DATE fecha) {
    printf("%02d-%02d-%04d", fecha.dia, fecha.mes, fecha.anyo);
}

void print_ALUMNO(struct ALUMNO alumno) {
    printf("%-12s\t%-20s\t", alumno.DNI, alumno.nom_comp);
    print_DATE(alumno.nac);
    printf("\n");
}

unsigned is_fecha_valida(DATE fecha) {
    if (fecha.mes < 1 || fecha.mes > 12) {
        return 0;
    }

    int dias_en_mes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 ,31};
    if (fecha.mes == 2 && fecha.anyo % 400 && fecha.anyo % 100) {
        dias_en_mes[fecha.mes - 1]++;
    }

    if (fecha.dia > dias_en_mes[fecha.mes - 1] || fecha.dia < 1) {
        return 0;
    }

    if (fecha.anyo < 1999 && fecha.anyo > 2005) {
        return 0;
    }

    return 1;
}

void rand_DATE(DATE *fecha) {
    do {
        fecha->dia = (rand() % 31) + 1;
        fecha->mes = (rand() % 12) + 1;
        fecha->anyo = (rand() % 7) + 1999;
    }while(!is_fecha_valida(*fecha));
}

void rand_nom_comp(char nom_comp[20+1]) {
    int rand_name = rand() % 8;
    int rand_apell = rand() % 8;

    strcpy(nom_comp, apellidos[rand_apell]);
    strcat(nom_comp, ", ");
    strcat(nom_comp, nombres[rand_name]);
}

void rand_str_DNI(char str_DNI[9+1]) {
    int digit = 0, dni_number = 0, rest = 0;
    char letra[] = "TRWAGMYFPDXBNJZSQVHLCKE";
    for (int i = 0; i < 8; i++) {
        digit = rand() % 10;
        str_DNI[i] = '0' + digit;
    }
    dni_number = atoi(str_DNI);
    rest = dni_number % 23;
    str_DNI[8] = letra[rest];
    str_DNI[9] = '\0';
}


void rand_ALUMNO(struct ALUMNO *alumno) {
    rand_str_DNI(alumno->DNI);
    rand_nom_comp(alumno->nom_comp); // Generar el nombre completo aleatorio
    rand_DATE(&alumno->nac); // Generar la fecha de nacimiento aleatoria
}


int main(void)
{
    return 0;
}
