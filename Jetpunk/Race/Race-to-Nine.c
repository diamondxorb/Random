/*
    Programa inspirado no puzzle Race-to-Nine do Jetpunk
    @https://www.jetpunk.com/user-quizzes/97243/race-to-nine-word-puzzle-1

    A partir de uma string com as letras que o puzzle te dá, o programa passa por todos anagramas possíveis da palavra,
    o programa original printava todas as combinações, porém era muito cansativo ter que ir olhando por tantas palavras.
    Por isso, no arquivo "dictionary.csv" do repositório @https://github.com/zeisler/scrabble, é possível encontrar
    todas palavras em inglês válidas para o Scrabble, o que poupa o nosso tempo de palavras muito obscuras, além de que
    o arquivo já foi filtrado, tirando todas palavras com menos de 3 letras e mais de 10. A ideia é simplesmente fazer
    os anagramas e ir checando no arquivo do dicionário.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_WORD_SIZE 10
#define HASH_SIZE 100000

typedef struct HashNode {
    char *word;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode **buckets;
    int size;
} Dicionario;

unsigned int hash(const char *str) {
    unsigned int hash = 5381;
    int c;
    while((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % HASH_SIZE;
}

Dicionario carregaDicionario(const char *filename) {
    Dicionario dict = {NULL, 0};
    dict.buckets = calloc(HASH_SIZE, sizeof(HashNode*));
    
    FILE *file = fopen(filename, "r");
    if(!file) {
        perror("Erro ao abir dicionário");
        return dict;
    }

    char buffer[MAX_WORD_SIZE];
    while(fscanf(file, "%9s", buffer) != EOF) {
        if(strlen(buffer) == 0) {
            continue;
        }

        unsigned int index = hash(buffer);

        HashNode *newNode = malloc(sizeof(HashNode));
        newNode->word = strdup(buffer);
        newNode->next = dict.buckets[index];
        dict.buckets[index] = newNode;

        dict.size++;
    }

    fclose(file);
    return dict;
}

bool estaNoDicionario(Dicionario *dict, const char *word) {
    unsigned int index = hash(word);
    HashNode *current = dict->buckets[index];

    while(current != NULL) {
        if(strcmp(current->word, word) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void liberaDicionario(Dicionario *dict) {
    for(int i=0; i<HASH_SIZE; i++) {
        HashNode *current = dict->buckets[i];
        
        while(current != NULL) {
            HashNode *temp = current;
            current = current->next;
            free(temp->word);
            free(temp);
        }
    }
    free(dict->buckets);
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

    scanf("%9s", palavra);
    printf("\n");

    Dicionario dict = carregaDicionario("words.txt");
    if(dict.buckets == NULL) {
        printf("Dicionário não carregado");
        return 1;
    }

    tamanho = strlen(palavra);
    
    if(tamanho>0) {
        anagramas(&dict, palavra, 0, tamanho-1);
    }

    liberaDicionario(&dict);
    return 0;
}