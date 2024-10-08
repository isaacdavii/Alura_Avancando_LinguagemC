#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> // Função rand()
#include "Forca.h" // Incluindo o arquivo de cabeçalho

/* 12. Coloco a assinatura das funções que existem neste arquivo. Assim, o arquivo roda independente da ordem das funções
void aberura();
void chuta();
int jaChutou(char letra);
void desenhaForca();
void escolhePalavra();
int enforcou();
int acertou();
*/

// Variáveis globais porque todas as funções manipulam essas variáveis
char palavraSecreta[TAMANHO_PALAVRA];
char chutes[26]; // Array para guardar os chutes
int chutesDados = 0; // Contador de tentativas (tentativas == chutesDados)

void abertura() {
    printf("*********************\n");
    printf("*   Jogo de Forca   *\n");
    printf("*********************\n");
}

void chuta() { // Colocamos a estrela para receber o endereço de tentativas
    char chute;

    printf("Qual letra? ");
    scanf(" %c", &chute);

    if(letraExiste(chute)) {
        printf("Voce acertou: a palavra tem a letra %c\n\n", chute);
    } else {
        printf("Voce errou: a palavra NAO tem a letra %c\n\n", chute);
    }
    
    chutes[chutesDados] = chute;
    chutesDados++;
}

int jaChutou (char letra) {
    int achou = 0;

    for (int j = 0; j < chutesDados; j++) {
        if (chutes[j] == letra) {
            achou = 1; 
            break;
        }
    }

    return achou;
}

void desenhaForca() {

    int erros = chutesErrados();

    printf("  _______      \n");
    printf(" |/      |     \n");
    printf(" |      %c%c%c    \n", (erros >= 1 ? '(' : ' '),
                                   (erros >= 1 ? '_' : ' '),
                                   (erros >= 1 ? ')' : ' '));
    printf(" |      %c%c%c   \n",  (erros >= 3 ? '\\' : ' '), 
                                   (erros >= 2 ? '|' : ' '),
                                   (erros >= 3 ?  '/' : ' '));
    printf(" |       %c     \n",   (erros >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n",   (erros >= 4 ? '/' : ' '), 
                                   (erros >= 4 ? '\\' : ' '));
    printf(" |             \n");
    printf("_|___          \n");
    printf("\n\n");

    for (int i = 0; i < strlen(palavraSecreta); i++) {

        if (jaChutou(palavraSecreta[i])) {
            printf("%c ", palavraSecreta[i]);
        } else {
            printf("_ ");
        }
    }
    
    printf("\n");
}

void escolhePalavra() {
    //sprintf(palavraSecreta, "MELANCIA");

    FILE* f = fopen("palavras.txt", "r");
    if (!f)
        return printf("Erro ao abrir o arquivo!\n");
    
    int quantidadePalavras;
    fscanf(f, "%d", &quantidadePalavras); // Lê a primeira linha automaticamente

    srand(time(0));
    int randomico = rand() % quantidadePalavras; // Seleciona um número entre 0 e a quantidade de palavras

    for (int k = 0; k <= randomico; k++) {
        fscanf(f, "%s", palavraSecreta);
    }

    fclose(f);
}

int letraExiste(char letra) {

    for (int j = 0; j < strlen(palavraSecreta); j++) {
        if (letra == palavraSecreta[j]) {
            return 1;
        }
    }

    return 0;
}

int chutesErrados() {
    int erros = 0;

    for (int i = 0; i < chutesDados; i++) {
        if (!letraExiste(chutes[i])) {
            erros++;
        }
    }

    /* 13. Substituo o loop abaixo pelo 'int letraExiste(char letra)'
        for (int j = 0; j < strlen(palavraSecreta); j++) {
            if (chutes[i] == palavraSecreta[j]) {
                achou = 1;
                break;
            }
        }

        if (!achou) {
            erros++; //return 1;
        }
    }
    */

    return erros;
}

int enforcou() { // Se eu enforquei ou não
    return chutesErrados() >= 5;
}

int acertou() { // Se eu acertar o chute ou não
    for (int i = 0; i < strlen(palavraSecreta); i++) {
        if (!jaChutou(palavraSecreta[i])) {
            return 0;
        }
    }
    return 1;
}

int ganhou() {

    for(int i = 0; i < strlen(palavraSecreta); i++) {
        if (!jaChutou(palavraSecreta[i])) {
            return 0;
        }
    }

    return 1;
}

void adicionaPalavra() {

    char resposta;

    /* 14. Jogando na função ganhou()

    printf("Fim de jogo! Obrigado por jogar!\n");
    
    if (acertou()) {
        printf("Parabens! Voce ganhou!\n");
    } else {
        printf("Voce perdeu! Tente novamente!\n");
    }
    */
    
    printf("Voce deseja adicionar uma nova palavra no jogo? (S/N) \n");
    scanf(" %c", &resposta);

    if (resposta == 'S') {

        char novaPalavra[TAMANHO_PALAVRA];

        printf("Digite a nova palavra, em letras maiusculas: ");
        scanf("%s", novaPalavra);

        FILE* f = fopen("palavras.txt", "r+");
        if (!f)
            return printf("Erro ao abrir o arquivo!\n");

        int quantidade;
        fscanf(f, "%d", &quantidade);
        quantidade++;

        fseek(f, 0, SEEK_SET); // "SEEK_SET" é orientado para o início do arquivo
        fprintf(f, "%d", quantidade);

        fseek(f, 0, SEEK_END); // "SEEK_END" é orientado para o final do arquivo
        fprintf(f, "\n%s", novaPalavra);

        fclose(f);
    }

}

int main() {
    /* 1. Inicialiando uma palavra
    char letra1 = 'M';    char letra2 = 'E';    char letra3 = 'L';    char letra4 = 'A';    char letra5 = 'O';
    printf("%c%c%c%c%c", letra1, letra2, letra3, letra4, letra5);
    A fim de não fazer assim todas as vezes, usaremos de um Array para guardar a palavra.
    */

    /* 2. Criando um Array
    int notas[10]; e declarando as váriaveis: notas[0] = 10; notas[2] = 9; notas[9] = 4;
    printf("Notas %d - %d - %d", notas[0], notas[2], notas[9]);
    */

    /* 3. Entendendo o Array com CHARACTER
    char palavraSecreta[5];
    palavraSecreta[0] = 'M';
    palavraSecreta[1] = 'E';
    palavraSecreta[2] = 'L';
    palavraSecreta[3] = 'A';
    palavraSecreta[4] = 'O';
    palavraSecreta[5] = '\0'; // Caractere de fim de string
    for (int i = 0; i < 5; i++) {
        printf("%c ", palavraSecreta[i]);
    }
    */

    /* 9. Escolhendo a palavra secreta
        sprintf(palavraSecreta, "MELANCIA");
        printf("%s", palavraSecreta); // %s para string
    */
   
   /* 11. Crio uma função 'int acertou()' para dizer se ele acertou ou não
   int acertou = 0;
   */

    /* 10. Criei uma função 'int enforcou()' para usar
    int enforcou = 0;
    */
    
    /* 5. Fazendo um cabeçalho - ABERTURA
    printf("*********************\n");
    printf("*   Jogo de Forca   *\n");
    printf("*********************\n");
    */
    
    abertura();
    escolhePalavra();

    do {

        /* 8. Imprime a palavra secreta
        for (int i = 0; i < strlen(palavraSecreta); i++) {

            // 7. Verificando se a letra já foi chutada ou não
            //for (int j = 0; j < tentativas; j++) { // Percorre todas as tentativas feitas até o momento
            //    if (chutes[j] == palavraSecreta[i]) { // Percorre todas as letras da palavra secreta
            //        achou = 1; 
            //       break;
            //    }
            //}
            
            int achou = jaChutou(palavraSecreta[i], chutes, tentativas);

            if (achou) {
                printf("%c ", palavraSecreta[i]);
            } else {
                printf("_ ");
            }
            
        }
        printf("\n");
        */

        desenhaForca();

        /* 4. Verificando se o chute está na palavra
        for (int i = 0; i < strlen(palavraSecreta); i++) { // Loop para varrer o Array verificando compatibilidade
            if (palavraSecreta[i] == chute ) {
                printf("A posicao %d tem a letra %c\n", i, chute);
            } else {
                printf("A palavra nao tem a letra %c\n", chute);
            }
        }
        */
        
        /* 6. Recebe um novo chute
        char chute;
        scanf(" %c", &chute); // Eu tenho que colocar o espaço para que ignore o ENTER para não ser contado como CHAR
        chutes[tentativas] = chute;
        tentativas++;
        */
        
        chuta(); // Passamos o endereço em tentativas para se ler na função

    } while(!acertou() && enforcou() == NULL); // Usar a exclamação para negar a condição é igual o '== 0'. Usamos isso porque as variáveis são boolenas.

    if(ganhou()) {
        printf("Parabens! Voce ganhou!\n");
    } else {
        printf("Voce perdeu! Tente novamente!\n");
        printf("A palavra secreta era: **%s**\n", palavraSecreta);
    }

    adicionaPalavra();

}