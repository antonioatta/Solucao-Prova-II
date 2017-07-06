#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LETRAS 26

int main(int argc, char *argv[]) {

    FILE *fd;
    int contMinusc[MAX_LETRAS];
    int contMaiusc[MAX_LETRAS];
    char c;
    int i;

    if (argc < 2) {
        printf("Use: %s nome_do_arquivo_texto. Tente novamente!\n", argv[0]);
        exit(1);
    }

    fd=fopen(argv[1],"r");
    if (fd==NULL) {
        printf("Arquivo %s inexistente. Tente novamente!\n", argv[1]);
        exit(2);
    }

    memset(contMinusc, 0, sizeof(contMinusc));
    memset(contMaiusc, 0, sizeof(contMinusc));

    c=fgetc(fd);
    while (!feof(fd)) {
        if (c>='a' && c <='z') contMinusc[c - 'a']++;
        if (c>='A' && c <='Z') contMaiusc[c - 'A']++;
        c=fgetc(fd);
    }

    fclose(fd);

    printf("Frequencia das letras minusculas e maiusculas encontrada em %s:\n", argv[1]);
    for (i=0; i<MAX_LETRAS; i++){
        printf("%c = %d\n", 'a' + i, contMinusc[i]);
    }
    for (i=0; i<MAX_LETRAS; i++){
        printf("%c = %d\n", 'A' + i, contMaiusc[i]);
    }
    return(0);
}
