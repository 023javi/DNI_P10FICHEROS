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

void fprint_ALUMNO (FILE *file, struct ALUMNO alumno) {
    fprintf(file, "%-10s\t%-20s\t", alumno.DNI, alumno.nom_comp);
    fprint_DATE(file, alumno.nac);
}

void fprint_DATE(FILE *file, DATE fecha) {
    fprintf(file, "%d-%d-%d\n", fecha.dia, fecha.mes, fecha.anyo);
}

void all_swap(struct ALUMNO *alumno1, struct ALUMNO *alumno2) {
    struct ALUMNO temp = *alumno1;
    *alumno1 = *alumno2;
    *alumno2 = temp;
}

void vaciarbuffer(struct ALUMNO *alumno) {
        alumno->nom_comp[0] = '\0';
        alumno->DNI[0] = '\0';
        alumno->nac.dia = 0;
        alumno->nac.mes = 0;
        alumno->nac.anyo = 0;
}



int main(void)
{
    struct ALUMNO alumno[A];
    for (int i = 0; i < A; i++) {
        vaciarbuffer(&alumno[i]);

    }
    printf("Generandose datos aleatorios...\n");
    for (int i = 0; i < A; i++) {
        rand_ALUMNO(&alumno[i]);
        print_ALUMNO(alumno[i]);
    }

    printf("Generandose fichero de texto...\n\n");
    FILE *file = fopen("alum.txt", "a");
    if (file == NULL) {
        printf("Error al abrir el archivo\n");
        return 0;
    }

    for (int i = 0; i < A; i++) {
        fprint_ALUMNO(file, alumno[i]);
    }
    fclose(file);


    printf("Generandose fichero binario...\n\n");
    FILE *filebinary = fopen("alum.bin", "wb");
    if (filebinary == NULL) {
        printf("Error al abrir el archivo binario\n");
        return 0;
    }
    fwrite(alumno, sizeof(struct ALUMNO), A, filebinary);
    fclose(filebinary);

    filebinary = fopen("alum.bin", "rb");
    if (filebinary == NULL) {
        printf("Error al abrir el archivo binario\n");
        return 0;
    }
    struct ALUMNO alumnobin[A];
    fread(alumnobin, sizeof(struct ALUMNO), A, filebinary);
    fclose(filebinary);

    printf("anyo a buscar en los datos del ficero binario?\n");
    char anyo_buscar[10];
    gets(anyo_buscar);
    unsigned anyo = atoi(anyo_buscar);

    for (int i = 0; i < A; i++) {
        if (alumnobin[i].nac.anyo == anyo) {
            print_ALUMNO(alumnobin[i]);
        }
    }

    return 0;
}
