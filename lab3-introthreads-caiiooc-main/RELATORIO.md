# Relatório - Laboratório de Threads

**Nome**: [Caio Henrique Santos Carvalho]  
**Data**: [16/09]  
**Sistema**: [Linux/WSL/Mac]  
**Processador**: [Intel(R) Core(TM) i7-4790 CPU @ 3.60GHz 3.60 GHz / 4 cores / 8 threads]

## Parte 1: Exercícios Básicos

### Exercício 1: Hello Thread

**Observações**:
- Comportamento observado ao executar múltiplas vezes:

R: A saída sempre aparecia na mesma ordem.


- Ordem das mensagens:

R: 
Hello da main!
Hello da thread!


- Explicação do comportamento:

R: Na minha máquina, a main é rápida o suficiente para imprimir primeiro, mas em sistemas diferentes a ordem poderia variar devido ao escalonamento de threads pelo SO.


### Exercício 2: Sincronização com pthread_join

**Comparação com Exercício 1**:
- Diferenças observadas:

R: Agora a main espera explicitamente a thread filha terminar antes de continuar.


- Importância do pthread_join:

R: Garante que a thread principal sincronize com a thread filha evitando que a main termine antes da thread.


- Consequências de não usar pthread_join:

R: A thread filha poderia não imprimir sua mensagem antes da main finalizar causando comportamento inesperado.


### Exercício 3: Múltiplas Threads

**Análise**:
- Ordem de execução observada:

R: Cada thread imprime seu ID, na minha máquina a ordem foi sempre 0, 1, 2, 3, 4.


- Determinismo (ou falta dele):

R: No meu caso a execução foi sempre na ordem crescente.


- Comportamento com 100 threads:

R: O escalonamento dependeria do SO; algumas threads poderiam executar fora de ordem, mas todas seriam executadas corretamente.


## Parte 2: Comunicação entre Threads

### Exercício 4: Passagem de Argumentos

**Análise**:
- Importância de ter argumentos separados para cada thread:

R: Cada thread precisa de seu próprio valor para não sobrescrever dados de outras threads.


- Como o array garante que cada thread recebe seu próprio valor:

R: Cada posição do array armazena o ID único da thread e o endereço é passado para cada thread.


- Processo de conversão de tipos (cast) observado:

R: O ponteiro void* recebido pela função da thread é convertido para int* e depois desreferenciado para obter o valor do ID.



### Exercício 5: Passando Estruturas

**Decisões de Design**:
- Por que alocação dinâmica:

R: Permite que cada thread acesse sua própria cópia da estrutura sem risco de sobrescrever dados de outras threads.


- Momento de liberação de memória:

R: Somente após todas as threads terminarem garantindo que nenhuma thread ainda está acessando os dados.


- Alternativas consideradas:

R: Usar variáveis locais, mas isso causaria problemas de escopo e threads poderiam acessar memória inválida.



### Exercício 6: Valores de Retorno

**Análise de Memória**:
- Necessidade de alocação no heap:

R: O valor retornado precisa permanecer válido mesmo após a função da thread terminar.


- Problemas com variáveis locais:

R: Se retornássemos o endereço de uma variável local, a memória seria liberada ao sair da função causando comportamento indefinido.


- Gerenciamento de memória:

R: Cada thread aloca seu resultado no heap, o main coleta com pthread_join e libera a memória após usar o valor.



## Parte 3: Análise e Reflexões

### Questões Respondidas

1. **Por que pthread_join é necessário?**
   
   [Para garantir que a thread principal espere as threads filhas terminarem antes de continuar ou encerrar, evitando problemas de sincronização e acesso a memória inválida.]

2. **Qual a diferença entre passar valores e ponteiros para threads?**
   
   [Passar valores cria cópias independentes para cada thread; passar ponteiros permite compartilhar dados, mas exige cuidado para evitar sobrescrita ou acessos concorrentes.]

3. **O que as threads compartilham e o que é privativo?**
   
   [Compartilham memória global, heap e recursos do processo; variáveis locais e argumentos passados por cópia são privativos de cada thread.]

4. **Por que a ordem de execução das threads é não-determinística?**
   
   [O escalonamento é feito pelo sistema operacional que decide qual thread executa em cada momento. Fatores como núcleos disponíveis e carga do sistema afetam a ordem.]

5. **Por que devemos alocar no heap para retornar valores de threads?**
   
   [Para garantir que os valores retornados permaneçam válidos após a função da thread terminar permitindo que o main ou outras threads acessem os resultados.]

6. **Quando vale a pena usar threads em vez de processos?**
   
   [Quando é necessário compartilhar memória facilmente, reduzir overhead de criação de processos e aproveitar múltiplos núcleos para tarefas paralelas.]

### Principais Aprendizados

1. [Entender a importância da sincronização com pthread_join.]
2. [Aprender a passar argumentos corretamente para threads usando arrays e estruturas.]
3. [Gerenciar memória dinamicamente para comunicação segura entre threads.]

### Dificuldades Encontradas

1. **Problema**: [Inicialmente threads não tinham argumentos separados e sobrescreviam valores.]
   **Solução**: [Usei arrays para cada thread armazenar seu ID ou dados exclusivos.]

2. **Problema**: [Tentativa de retornar variável local da thread.]
   **Solução**: [Alocar resultado no heap e liberar depois do pthread_join.]

### Possíveis Melhorias

- [Adicionar mutexes para proteger dados compartilhados se necessário.]
- [Criar funções auxiliares para inicialização de threads e argumentos.]
- [Medir tempo de execução das threads para análise de performance.]

## Conclusão

[O laboratório permitiu compreender conceitos essenciais de programação paralela usando threads em C. Aprendi a criar múltiplas threads, passar argumentos corretamente, sincronizar com pthread_join e gerenciar memória dinamicamente. Esses conhecimentos são aplicáveis em programas que exigem execução concorrente eficiente como processamento paralelo e servidores multithreaded.]

## Anexos

### Comandos de Compilação Utilizados
```bash
make all
./ex1_hello_thread
./ex2_hello_join
./ex3_multiple_threads
./ex4_thread_args
./ex5_struct_args
./ex6_return_value
```

### Ambiente de Testes
```bash
# Output de comandos como:
uname -a
gcc --version
nproc
```

---