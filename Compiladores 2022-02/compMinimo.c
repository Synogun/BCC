#include <stdio.h>
#include <ctype.h>
#include <string.h>

// -----------------------------------------------------------------------------------

int lin = 1;
int col = 0;

// -----------------------------------------------------------------------------------

int obter_numero(FILE *f, char car);
void obter_id(FILE *f, char buffer[]){
    int i = 1;
    char car;

    car = fgetc(f);
    col++;

    while(isalnum(car) || car == '_'){
        buffer[i++] = car;
        car = fgetc(f);
        col++;
    }
    buffer[i] = '\0';
    ungetc(car, f);
    col--;
}

int main(int argc, char *argv[]){
    FILE *f;
    char car;
    int linha, coluna;

    if(argc != 2){
        printf("Arquivo de entrada não informado.\n");
        return 2;
    }

    f = fopen(argv[1], "r");
    if(f == NULL){
        printf("Falha ao abrir o arquivo: %s.\n", argv[1]);
        return 1;
    }


    while((car = fgetc(f)) != EOF){
        col++;
        if(car == '\n'){
            lin++;
            col = 0;
            continue;
        }

        // Atualizando a posição de linha e coluna do token
        linha = lin;
        coluna = col;

        //obter um identificador
        if(isalpha(car) || car == '_'){
            char buffer[100];
            buffer[0] = car;
            obter_id(f, buffer);

            // Reconhece o token MAIN
            if(!strcmp(buffer, "main")){
                printf("(%i, %i): <MAIN, %s>\n", linha, coluna, buffer);

            }

            // Reconhece o token INT
            if(!strcmp(buffer, "int")){
                printf("(%i, %i): <INT, %s>\n", linha, coluna, buffer);
            }

            // Reconhece o token RETURN
            if(!strcmp(buffer, "return")){
                printf("(%i, %i): <RETURN, %s>\n", linha, coluna, buffer);
            }

        }

        // Obter um Numero
        if(isdigit(car)){
            int num = obter_numero(f, car);
            printf("(%i, %i): <NUM, %i>\n", linha, coluna, num);
        }
    }

    return 0;
}

// -----------------------------------------------------------------------------------

int obter_numero(FILE *f, char car){
    int num = car - '0';
    car = fgetc(f);
    col++;
    while(isdigit(car)){
        num = (num * 10) + (car - '0');
        car = fgetc(f);
        col++;
    }
    ungetc(car, f);
    col--;
    
    return num;
}