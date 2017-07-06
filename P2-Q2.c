#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef
struct  {
	char matricula[8];
	char cod_disciplina[4];
	float notas[3];
	float media;
	char resultado_final[3];
}  REG_ALUNO;


int main() {

    FILE *fd;
    REG_ALUNO ra;
    int salto_negativo;

    fd=fopen("resultados.dat","rb+");
    if (fd==NULL) {
        printf("Arquivo \"resultados.dat\" inexistente! Saindo...\n");
        exit(1);
    }

    salto_negativo=sizeof(REG_ALUNO);    // calcula o retrocesso em bytes do arquivo
    salto_negativo *= -1;                // correspondendo ao tamanho de um registro
    fread(&ra, sizeof(REG_ALUNO), 1, fd);
    while (!feof(fd)) {
       ra.media=(ra.notas[0]+ra.notas[1]+ra.notas[2])/3;   // calcula e atualiza o campo media do registro
       if (ra.media>=7.0) strcpy(ra.resultado_final, "AP");  // atualiza o campo resultado_final de acordo com a tabela
       else if (ra.media>=5.0) strcpy(ra.resultado_final, "AM");
       else if (ra.media>=3.0) strcpy(ra.resultado_final, "PF");
       else strcpy(ra.resultado_final, "RP");

       fseek(fd, salto_negativo, SEEK_CUR);   // retrocede para o inicio do registrto lido
       fwrite(&ra, sizeof(REG_ALUNO), 1, fd); // grava o registro atualizado e o ponteiro do arquivo ficara sobre o inicio do proximo registro a ser processado
       fread(&ra, sizeof(REG_ALUNO), 1, fd);  // le o proximo registro
    }

    fclose(fd);
    printf("Feito!\n");
    return(0);
}
