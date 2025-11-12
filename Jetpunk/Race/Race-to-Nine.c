/*
    Programa inspirado no puzzle Race-to-Nine do Jetpunk
    @https://www.jetpunk.com/user-quizzes/97243/race-to-nine-word-puzzle-1

    A partir de uma string com as letras que o puzzle te dá, o programa passa por todos anagramas possíveis da palavra,
    o programa original printava todas as combinações, porém era muito cansativo ter que ir olhando por tantas palavras.
    Por isso, no arquivo "words_alpha.txt" do repositório @https://github.com/dwyl/english-words, é possível encontrar 
    mais de 460 mil palavras em inglês. A ideia é simplesmente fazer os anagramas e ir checando no arquivo do dicionário.
    Claramente isso toma muito custo computacional, sendo preferível parar em até palavras de 8 letras.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_WORD_SIZE 10

typedef struct {
    char **words;
    int size;
} Dicionario;

Dicionario carregaDicionario(const char *filename) {
    Dicionario dict = {NULL, 0};
    FILE *file = fopen(filename, "r");
    if(!file) {
        perror("Erro ao abir dicionário");
        return dict;
    }

    char buffer[MAX_WORD_SIZE];
    while(fscanf(file, "%s", buffer) !=EOF) {
        dict.size++;
    }

    rewind(file);
    dict.words = malloc(dict.size * sizeof(char *));
    for(int i=0; i<dict.size; i++) {
        fscanf(file, "%s", buffer);
        dict.words[i] = strdup(buffer);
    }

    fclose(file);
    return dict;
}

bool estaNoDicionario(Dicionario *dict, const char *word) {
    for(int i=0; i< dict->size; i++) {
        if(strcmp(dict->words[i], word)==0) {
            return true;
        }
    }
    return false;
}

void swap(char *x, char*y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

bool repeticao(const char *string, int comeco, int atual) {
    for(int i=comeco; i<atual; i++) {
        if(string[i]==string[atual]) {
            return false;
        }
    }
    return true;
}

void anagramas(Dicionario *dict,char *string, int comeco, int fim) {
    if(comeco==fim) {
        if(estaNoDicionario(dict, string)) {
            printf("%s\n", string);
        }
    } else {
        for(int i=comeco; i<=fim; i++) {
            if(repeticao(string, comeco, i)) {
                swap(&string[comeco], &string[i]);
                anagramas(dict, string, comeco+1, fim);
                swap(&string[comeco], &string[i]);
            }
        }
    }
}

int main () {
    int i, tamanho;
    char palavra[MAX_WORD_SIZE];

    scanf("%s", palavra);
    printf("\n");

    Dicionario dict = carregaDicionario("words_alpha.txt");
    if(dict.words==NULL) {
        printf("Dicionário não carregado");
        return 1;
    }

    tamanho = strlen(palavra)-1;
    
    anagramas(&dict, palavra, 0, tamanho);

    for(i=0; i<dict.size; i++) {
        free(dict.words[i]);
    }
    free(dict.words);

    return 0;
}