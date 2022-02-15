#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX2 400000 // numero maximo de numeros aleatorios

typedef enum boleano
{
    falso,
    verdadeiro
} Boleano;

void InsertionSort(int *arr, int size)
{
    int x, y, value;

    for (x = 1; x < size; x++)
    {
        value = arr[x];

        for (y = x - 1; y >= 0 && arr[y] > value; y--)
        {
            arr[y + 1] = arr[y];
        }

        arr[y + 1] = value;
    }
}

void Imprime_Valores_Array(int *Ptr, int Dim, FILE *f)
{
    for (int i = 0; i < Dim; i++)
    {
        printf("\n[%d] = %d ", i, *(Ptr + i));

        fprintf(f, "\n[%d] = %d ", i, *(Ptr + i));
    }
}

//essa funcao pega os numeros de arquivo txt, converte o texto em numeros inteiros e devolve uma array 
//com os numero e a dimensai desta array
void GetTextArr(int *Ptr, int *Pptr, int *Pdim)
{
    FILE *file;

    char frase[100];

    file = fopen("numeros.txt", "r");

    if (file == NULL)
    {
        printf("nao foi possivel abrir o arquivo");
        getchar();
        return falso;
    }

    while (fgets(frase, 100, file) != NULL)
    {
        printf("\n%s\n", frase);
    }
    fclose(file);

    char *str = frase, *p = str;
    long val;
    int i = 0;

    while (*p) // enquanto ainda tiver caracteres para percorrer...
    {
        if (isdigit(*p) || ((*p == '-' || *p == '+') && isdigit(*(p))))
        {
            // encontra um numero
            val = strtol(p, &p, 10); // Le o numero
            Ptr[i] = val;
        }
        else
        {
            // caso contrario vá para o próximo caractere.
            p++;
            i++;
        }
    }
    int Dim = i + 1;

    *Pptr = *Ptr;
    *Pdim = Dim;
}

int main(void)
{
    int n1,           // tamanho real do array vetor1
        vetor1[MAX2]; // array vetor1 para armazenar os elementos

    FILE *file;

    GetTextArr(vetor1, &vetor1, &n1);
    
    file = fopen("numerosModf.txt", "w"); //o resultado sera devolvido no documento numerosModf.txt
    fprintf(file, "array original: ");
    printf("\narray original: \n");
    Imprime_Valores_Array(vetor1, n1, file);
    puts("\n");

    InsertionSort(vetor1, n1);
    puts("Array ordenado:");
    fprintf(file, "\n\narray ordenado: ");

    Imprime_Valores_Array(vetor1, n1, file);
    printf("\n\nAcabei!!!!\n");

    fclose(file);

    printf("Pressione enter/return para finalizar ...");
    fflush(stdin); // esvaziando o buffer de entrada
    getchar();
    return (0);
}