#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// TODO: Implemente a função que será executada pela thread
// Esta função deve:
// 1. Imprimir "Hello da thread!"
// 2. Retornar NULL
void* print_hello(void* arg) {
    // TODO: Implemente aqui
    printf("Hello da thread!\n");

    return NULL;
}

int main() {
    pthread_t thread;
    
    printf("Hello da main!\n");
    
    // TODO: Crie uma thread usando pthread_create
    // Parâmetros:
    // 1. &thread - endereço da variável pthread_t
    // 2. NULL - atributos padrão
    // 3. print_hello - função a ser executada
    // 4. NULL - argumento para a função

    if (pthread_create(&thread, NULL, print_hello, NULL) != 0) 
    {
        perror("Erro ao criar a thread");
        exit(1);
    }

    pthread_join(thread, NULL);
    
    // Nota: Sem sincronização, o programa pode terminar
    // antes da thread imprimir sua mensagem.
    // Execute várias vezes e observe o comportamento!
    
    return 0;
}