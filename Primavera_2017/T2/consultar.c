#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* eliminar_espacios(char* s, char* res){
    int len = strlen(s)-1;
    int i = 0;
    while(i<len){
        if(*s == ' '){
            res[i]='\0';
            break;
        }
        res[i]=*s;
        s++;
        i++;
    }
    return res;
}
void buscar(FILE *in, char* palabra) {
    char izqbuff[10];
    char derbuff[10];
    char word[20];
    char meaning[59];

    fread(izqbuff, 1, 10, in);
    fread(derbuff, 1, 10, in);
    fread(word, 1, 20, in);
    fread(meaning, 1, 59, in);

    int izq = atoi(izqbuff);
    int der = atoi(derbuff);
    
    char aux[20];
    int comp = strcmp(palabra, eliminar_espacios(word,aux));

    if(comp == 0){
        printf("%s\n", meaning);
    }
    else if(comp < 0){
        if(izq == -1)
            printf("palabra no encontrada\n");
        else{
            fseek(in, 100*izq, SEEK_SET);
            buscar(in, palabra);
        }
    }
    else{
        if(der == -1)
            printf("palabra no encontrada\n");
        else{
            fseek(in, 100*der, SEEK_SET);
            buscar(in, palabra);
        }
    }
    if (ferror(in)) {
        fprintf(stderr, "Error de lectura\n");
        exit(1);
    }
  }

int main(int argc, char *argv[]) {
    FILE *in;

    if(argc!=3) {
        fprintf(stderr, "uso: %s <arch. fuente> <palabra>\n", argv[0]);
        exit(1);
    }
    else {

        if ((in= fopen(argv[1], "r"))==NULL) {
            fprintf(stderr, "No se puede leer '%s'\n", argv[1]);
            exit(1);
        }
        buscar(in, argv[2]);
        fclose(in);
    }
    return 0;
  }
