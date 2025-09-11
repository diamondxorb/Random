/*
    Código de uma lista dupla encadeada em C, feita a partir de um challenge do livro Crafting Interpreters
    (https://craftinginterpreters.com/introduction.html), o desafio pede para que fosse uma lista de strings
    com memória dinâmica, porém eu fiz utilizando a data como inteiro
*/

#include <stdio.h>
#include <stdlib.h>

#if _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

// Criação do node
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};


void insertFront(struct Node** head, int data), insertAfter(struct Node* prev_node, int data);
void insertEnd(struct Node** head, int data), deleteNode(struct Node** head, struct Node* del_node);
void displayList(struct Node* node), freeList(struct Node** head), displayMenu();
struct Node* findNode(struct Node* head, int data);

// Insere node no começo
void insertFront(struct Node** head, int data) {
    // Aloca memória para o newNode
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    // Assinala data para o newNode
    newNode->data = data;

    // Assinala o anterior como null
    newNode->prev = NULL;

    // Assinala o próximo do newNode como a cabeça
    newNode->next = *head;
    
    // Se já existe uma cabeça, coloca o anterior dela como o newNode
    if(*head != NULL) {
        (*head)->prev = newNode;
    }

    // Cabeça é o newNode
    *head = newNode;
}

// Insere node depois de um node específico
void insertAfter(struct Node* prev_node, int data) {
    // Checa se o node anterior existe
    if(prev_node == NULL ) {
        printf("O node anterior não existe!\n");
        return;
    }

    // Aloca memória para o newNode
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    // Assinala data para o newNode
    newNode->data = data;

    // Coloca o próximo de newNode como o próximo do prev_node
    newNode->next = prev_node->next;

    // Coloca o anterior do newNode como o prev_node
    newNode->prev = prev_node;

    // Coloca o próximo do prev_node como o newNode
    prev_node->next = newNode;

    // Coloca o anterior do próximo do newNode como o newNode
    if(newNode->next != NULL) {
        newNode->next->prev = newNode;
    }
}

// Insere um newNode no final da lista
void insertEnd(struct Node** head, int data) {
    // Aloca memória para o newNode
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    // Assinala data para o newNode
    newNode->data = data;

    // Coloca o próximo de newNode como null
    newNode->next = NULL;

    // Se a lista for vazia coloca o newNode como cabeça
    if(*head == NULL) {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }

    // Guarda o node cabeça temporariamente
    struct Node* temp = *head;

    // Se a lista não está vazia, atravessa até o final da list encadeada
    while(temp->next != NULL) {
        temp = temp->next;
    }

    // temp é o último node da lista

    // Coloca o próximo do último node (temp) como o newNode
    temp->next = newNode;

    // Coloca o anterior do newNode como o temp
    newNode->prev = temp;
}

// Deleta um node da lista
void deleteNode(struct Node** head, struct Node* del_node) {
    // Se a cabeça ou o del_node não existir, deletar não é possível
    if(*head == NULL || del_node == NULL) {
        return;
    }

    // Se o del_node é o node cabeça, aponta a cabeça para o próximo de del_node
    if(*head == del_node) {
        *head = del_node->next;
    }

    // Se o del_node não é o último node, aponta o anterior do node próximo para o anterior do del_node
    if(del_node->next != NULL) {
        del_node->next->prev = del_node->prev;
    }

    // Se o del_node não é o primeiro node, aponta o próximo do node anterior para o próximo do del_node
    if(del_node->prev != NULL) {
        del_node->prev->next = del_node->next;
    }

    // Libera a memória do del_node
    free(del_node);
}

// Encontra um node na lista
struct Node* findNode(struct Node* head, int data) {
    struct Node* current = head;

    while(current != NULL) {
        if(current->data == data) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

// Printa a lista
void displayList(struct Node* node) {
    while(node != NULL) {
        printf("%d", node->data);
        if(node->next != NULL) {
            printf(" <-> ");
        }
        node = node->next;
    }
    printf(" -> NULL\n");
}

// Libera a memória de toda a lista
void freeList(struct Node** head) {
    struct Node* current = *head;
    struct Node* next;

    while(current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

// Printa o menu com as opções
void displayMenu() {
    printf("\n");
    printf("Duply Linked List\n\n");
    printf("1. Inserir no início\n");
    printf("2. Inserir no final\n");
    printf("3. Inserir após um valor\n");
    printf("4. Deletar um valor\n");
    printf("5. Buscar um valor\n");
    printf("6. Mostrar lista\n");
    printf("7. Limpar toda a lista\n");
    printf("0. Sair\n");
}


int main () {
    struct Node* head = NULL;
    int choice, data, afterValue;
    struct Node* tempNode;

    do {
        system(CLEAR);
        displayMenu();
        printf("\nEscolha uma opção: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Digite o valor para inserir no início: ");
                scanf("%d", &data);
                insertFront(&head, data);
                printf("Valor %d inserido no início!\n", data);
                break;
            
            case 2:
                printf("Digite o valor para inserir no final: ");
                scanf("%d", &data);
                insertEnd(&head, data);
                printf("Valor %d inserido no final!\n", data);
                break;

            case 3:
                printf("Digite o valor após o qual deseja inserir: ");
                scanf("%d", &afterValue);
                tempNode = findNode(head, afterValue);

                if(tempNode != NULL) {
                    printf("Digite o valor para inserir após %d: ", afterValue);
                    scanf("%d", &data);
                    insertAfter(tempNode, data);
                    printf("Valor %d inserido após %d!\n", data, afterValue);
                } else {
                    printf("Valor %d não encontrado na lista!\n", afterValue);
                }
                break;

            case 4:
                printf("Digite o valor para deletar: ");
                scanf("%d", &data);
                tempNode = findNode(head, data);

                if(tempNode != NULL) {
                    deleteNode(&head, tempNode);
                    printf("Valor %d deletado da lista!\n", data);
                } else {
                    printf("Valor %d não encontrado na lista!\n", data);
                }
                break;
            
            case 5:
                printf("Digite o valor para buscar: ");
                scanf("%d", &data);
                tempNode = findNode(head, data);

                if(tempNode != NULL) {
                    printf("Valor %d encontrado na lista!\n", data);
                } else {
                    printf("Valor %d não encontrado na lista!\n", data);
                }
                break;

            case 6:
                printf("\nLista atual:\n");
                displayList(head);
                break;

            case 7:
                freeList(&head);
                printf("Lista limpa!\n");
                break;
            
            case 0:
                freeList(&head);
                break;
            
            default:
                printf("Opção inválida! Tente novamente\n");
        }

        if(choice != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
            getchar();
        }
    } while(choice != 0);

    return 0;
}
