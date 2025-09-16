#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 3

// TODO: Defina a estrutura thread_data
// A estrutura deve conter:
// - int id: identificador da thread
// - char name[50]: nome da thread
// - double value: valor a ser processado
typedef struct {
    // TODO: Adicione os campos aqui
    int id;
    char name[50];
    double value;
    
} thread_data;

// TODO: Implemente a função que processa os dados da estrutura
void* process_data(void* arg) {
    // TODO: Converta o argumento para thread_data*

    thread_data* data = (thread_data*) arg;

    // TODO: Processe e imprima os dados
    // Exemplo: "Thread 0 (Worker-A): Processing value 3.14"

    printf("Thread %d (%s): Processing value %.2f\n", data->id, data->name, data->value);
    
    // TODO: Calcule algo com o valor (ex: quadrado)
    // double result = data->value ...

    double result = data->value * data->value;
    
    // TODO: Imprima o resultado

    printf("Thread %d (%s): Result = %.2f\n", data->id, data->name, result);
    
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    
    // TODO: Aloque memória para as estruturas
    // Use malloc para um array de thread_data
    thread_data* thread_args = (thread_data*) malloc(NUM_THREADS * sizeof(thread_data));
    
    // TODO: Verifique se a alocação foi bem-sucedida
    if (thread_args == NULL) 
    {
        fprintf(stderr, "Erro ao alocar memória\n");
        return 1;
    }
    
    
    printf("Main: Criando threads com dados estruturados\n\n");
    
    // TODO: Inicialize os dados e crie as threads
    for (int i = 0; i < NUM_THREADS; i++) {
        // Preenchendo os campos da estrutura
        thread_args[i].id = i; // IDs únicos
        snprintf(thread_args[i].name, 50, "Worker-%c", 'A' + i); // Nomes únicos
        thread_args[i].value = (i + 1) * 3.14; // Valores diferentes
        
        // TODO: Crie a thread passando &thread_args[i]
        if (pthread_create(&threads[i], NULL, process_data, &thread_args[i]) != 0) 
        {
            fprintf(stderr, "Erro ao criar a thread %d\n", i);
            free(thread_args);
            return 1;
        }
    }
    
    // TODO: Aguarde todas as threads terminarem
    for (int i = 0; i < NUM_THREADS; i++)
    {
        // TODO: pthread_join aqui
        pthread_join(threads[i], NULL);
    }
    
    // TODO: Libere a memória alocada
    free(thread_args);
   
    printf("\nMain: Todas as threads completaram o processamento\n");
    
    return 0;
}