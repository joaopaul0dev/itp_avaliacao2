# Reserva de Assentos de uma Sessão

## Identificação

**Aluno:** João Paulo de Medeiros Neto  
**Projeto:** Opção 3 — Reserva de Assentos de uma Sessão  
**Disciplina:** Introdução às Técnicas de Programação (ITP)  
**Instituição:** Universidade Federal do Rio Grande do Norte (UFRN)

## Descrição

Este projeto consiste em um programa desenvolvido em linguagem C para controlar a disponibilidade de assentos em uma pequena sala de cinema. O sistema permite cadastrar o título de uma sessão, definir a quantidade de filas e gerenciar as reservas por meio de uma interface interativa no terminal, implementada com a biblioteca ncurses.

A sala pode ter de 1 a 6 filas, cada uma com 8 assentos. Os assentos são representados por uma matriz de inteiros, na qual o valor `0` indica um assento livre e o valor `1` indica um assento reservado.

O projeto utiliza matrizes, strings, funções, ponteiros e alocação dinâmica de memória, aplicando os conceitos estudados na disciplina.

## Funcionalidades

- Cadastro do título da sessão.
- Definição da quantidade de filas, entre 1 e 6.
- Exibição do mapa de assentos com identificação visual dos lugares livres e reservados.
- Reserva de assentos disponíveis.
- Cancelamento de reservas existentes.
- Validação das posições informadas pelo usuário.
- Impedimento de reservas duplicadas e cancelamentos de assentos livres.
- Cálculo da quantidade de assentos livres em cada fila por meio de um vetor alocado dinamicamente.
- Exibição do total de assentos, assentos livres, assentos reservados e porcentagem de ocupação.
- Navegação pelo menu utilizando as setas do teclado e a tecla Enter.

## Tecnologias e conceitos utilizados

- **Linguagem:** C.
- **Biblioteca:** ncurses, para interface interativa no terminal.
- **Matriz:** representação dos assentos da sala.
- **Strings:** armazenamento do título da sessão.
- **Funções:** organização das operações do programa.
- **Ponteiros:** preenchimento do vetor de assentos livres.
- **Alocação dinâmica:** utilização de `malloc()` para reservar memória para o vetor de resultados.
- **Gerenciamento de memória:** liberação da memória alocada com `free()`.

## Requisitos

Para compilar e executar o programa, são necessários:

- Compilador GCC.
- Biblioteca ncurses.
- Terminal compatível com ncurses.

### Instalação no Arch Linux

```bash
sudo pacman -S gcc ncurses
```

## Compilação e execução

Com o arquivo `main.c` no diretório do projeto, execute:

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o reserva -lncurses
```

Para iniciar o programa:

```bash
./reserva
```

## Exemplos de testes

### Teste 1 — Reserva e cancelamento

**Procedimento:**

1. Iniciar o programa e informar o título `Vingadores: Ultimato`.
2. Definir a quantidade de filas como `3`.
3. Selecionar a opção de reservar assento.
4. Informar a fila `1` e o assento `2`.
5. Tentar reservar novamente a fila `1`, assento `2`.
6. Cancelar a reserva na mesma posição.
7. Exibir o mapa de assentos.

**Resultados esperados:**

- A primeira reserva é realizada com sucesso.
- A segunda tentativa é rejeitada porque o assento já está reservado.
- O cancelamento é realizado com sucesso.
- O assento volta a aparecer como livre no mapa.

### Teste 2 — Entrada inválida

**Procedimento:**

1. Iniciar o programa.
2. Tentar informar uma quantidade de filas igual a `0` ou `7`.
3. Informar um valor válido, como `3`.
4. Tentar reservar um assento na fila `0` ou no assento `9`.

**Resultados esperados:**

- As quantidades de filas inválidas são rejeitadas.
- O programa solicita novamente uma entrada válida.
- As posições fora dos limites da sala são rejeitadas sem acessar posições inválidas da matriz.

### Teste 3 — Resumo da ocupação

**Procedimento:**

1. Configurar uma sala com `2` filas.
2. Reservar três assentos.
3. Selecionar a opção de exibir resumo.

**Resultados esperados:**

- Total de assentos: `16`.
- Assentos reservados: `3`.
- Assentos livres: `13`.
- Ocupação: `18,75%`.

## Vídeo de apresentação

**Link do YouTube:** A preencher após a publicação do vídeo.

O vídeo apresentará o programa em execução, suas principais funcionalidades, a representação dos assentos na matriz, o uso do vetor dinâmico, os conceitos de ponteiros e gerenciamento de memória e os testes realizados.

## Referências

- Material didático da disciplina Introdução às Técnicas de Programação (ITP), UFRN.
- Documentação da biblioteca ncurses: https://invisible-island.net/ncurses/
- Documentação da linguagem C e da biblioteca padrão: https://en.cppreference.com/w/c

