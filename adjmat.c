#define D_CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <malloc.h>
#include <stdbool.h>
#define MAX 20

#pragma warning (push)
#pragma warning (disable:6540)


int inarr[MAX] = { 0 };


int main(void) {
  
    char c;
    int mass[MAX][MAX];
    int size = 0, i = 0, j = 0, u = 0;

    ///////////   Ввод кол-ва эл-тов   //////////

    printf("Enter the num verticles: ");
    scanf("%i", &size);
    c = getchar();

    ///////////   Ввод эл-тов   //////////

    for (i; i < size; i++)
    {
      for (j; j < size; j++)
      {
        if ((i == j) && (size == 1))
        {
          printf("Connect between  %i and %i: ", i + 1, j + 1);
          while ((c = getchar()) != '\n')
          {
            if ('0' == c || c == '1')
            {
                mass[i][j] = c - '0';
                mass[j][i] = c - '0';
            }
          }
        }

        else if (i == j)
        {
          mass[i][j] = 0;
        }

        else
        {
           printf("Connect between  %i and %i ", i + 1, j + 1);
            while ((c = getchar()) != '\n')
            {
                if ('0' == c || c == '1')
                {
                    mass[i][j] = c - '0';
                    mass[j][i] = c - '0';
                }
            }
        }
      }
      u++;
      j = u;
    }

    FILE* file;
    file = fopen("graph.dot", "w");
    fprintf(file, "graph DG {\n");

    for (int e = 97; e < (97 + size); e++)
    {
        fprintf(file, "%c;\n", e);
    }


    u = 0;
    j = 0;
    i = 0;


    for (i; i < size; i++)
    {
        for (j; j < size; j++)
        {
            if (mass[i][j] == 1)
            {
                fprintf(file, "%c -- %c;\n", (i + 97), (j + 97));
            }
        }
      u++;
      j = u;
    }

    int y = 0;

    fprintf(file, "}");
    fclose(file);

    system("dot -Tpng graph.dot -o graph.png");
	system("graph.dot");
    system("graph.png");



    printf("\nEnter edge like:a-b\n");
    char x;
    c = getchar();
    getchar();
    x = getchar();
    getchar();

    printf("Delet %c and %c\n",c, x);
  
    char ar[1000];
    char buf[MAX];

    if ((c > 96) && (c - 97 < size) && (x > 96) && (x - 97 < size))
    {
        FILE* file;
        file = fopen("graph.dot", "r");

        char w;
        int r = 0;

        for (r; r < 11; r++)
        {
            w = getc(file);
            ar[r] = w;
        }

        int q = 0;
        bool checkc = false;

        for (y = 0; !feof(file); y++)
        {
            if ((w != '\n') && (checkc == false))
            {
                buf[q] = w;
                q++;

                if ((w == c) || (w == x))
                    checkc = true;
                    w = getc(file);
            }

            if ((w == '\n') && (checkc == false))
            {
                buf[q] = w;
                q++;
                int t = q;
                q = 0;
                int l = 0;
                
                for (r; l < t; r++, q++, l++)
                    ar[r] = buf[q];
                    q = 0;
                    w = getc(file);
            }
            if (checkc == true)
            {
                q = 0;
                while (w != '\n')
                    w = getc(file);
                    checkc = false;
            }

      }

      ar[r] = '\0';

      FILE* refile;
      refile = fopen("graph1.dot", "w");

      for (y = 0; ar[y] != '\0'; y++)
      {
        if ((ar[y - 1] == '\n') && (ar[y] == '\n'))
          ;
        else
          fprintf(refile, "%c", ar[y]);
      }

      fprintf(refile, "}");
      fclose(file);
      fclose(refile);

    }

    //////////////////Insertion Sort//////////////////////

    int* arrsort; 
    arrsort = (int*)malloc((size + 1) * sizeof(int)); 

    for (y = 0; y < size; y++)
    {
        arrsort[y] = 0;
    }

    FILE* refile;
    refile = fopen("graph1.dot", "r");
    char w = getc(file);

    for (y = 0; y < size - 2; y++)
    {
        while (w != '\n')
            w = getc(file);
            w = getc(file);
    }
    for (y = 0; !feof(file); y++)
    {
        w = getc(file);
        arrsort[w - 97]++;
    }

    arrsort[size] = '\0';
    fclose(refile);

    for (i = 0; i < size; i++)
    {
        inarr[i] = i + 1;
    }

    InsertionSort(arrsort, size); 
    printf("\nSorted mass \n");

    for (i = size - 2; i > 0; i--)
    {
        c = inarr[i] + 96;
        printf("| %c |", c);
    }

    printf("\n");
    printArray(arrsort, size);
    
    
    system("dot -Tpng graph1.dot -o graph1.png");
	system("graph1.dot");
    system("graph1.png");
  
    return 0;

}


void InsertionSort(int mass[], int n)
{
  int Element, location;

  for (int i = 1; i < n; i++)
  {
        Element = mass[i];
        location = i - 1;
        while (location >= 0 && mass[location] > Element)
        {

            mass[location + 1] = mass[location];
            inarr[location + 1] = inarr[location];
            location = location - 1;

        }
        mass[location + 1] = Element;
        inarr[location + 1] = inarr[i];
  }

}


void printArray(int arr[], int n) 
{
  for (int i = n - 1; i > 0; i--)
    printf("| %d |", arr[i]);
    printf("\n");
}
