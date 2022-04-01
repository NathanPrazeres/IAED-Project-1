/*
Include das bibliotecas que podem ser usadas no projeto.
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define MAXAPS 40
#define MAXVOOS 30000
#define MAXID 4
#define MAXPAIS 31
#define MAXCIDADE 51
#define MAXCODIGO 7

/*
Estruturas
*/
#include "structs.c"


/*
Variáveis Globais.
*/
int n_aero = 0, n_voos = 0;
Data data = {1, 1, 2022};
AP aps[MAXAPS];
Voo voos[MAXVOOS];


/*
Funções auxiliares.
*/
#include "aux.c"


/*
FUNÇÕES PRINCIPAIS
*/
void a()
{
    AP aeroporto;
    int i, flag = 1;
    scanf("%s %s %[^\n]", aeroporto.id, aeroporto.pais, aeroporto.cidade);
    aeroporto.voos = 0;
 
    if (n_aero < MAXAPS) {
        if (isupper(aeroporto.id[0]) && isupper(aeroporto.id[1]) && 
        isupper(aeroporto.id[2])) {

            for (i = 0; i < n_aero; i++)
                if (!strcmp(aps[i].id, aeroporto.id))
                    flag = 0;

            if (flag) {
                printf("airport %s\n", aeroporto.id);
                aps[n_aero] = aeroporto;
                n_aero++;
            }
            else
                printf("duplicate airport\n");
        }
        else
            printf("invalid airport ID\n");
    }
    else
        printf("too many airports\n");
}


void l()
{
    int i, flag = 1, err = 1;
    char id[MAXID], c = getchar();

    sortAP();

    while (c != '\n' && c != '\0') {
        flag = err = 0;
        scanf("%s", id);

        for (i = 0; i < n_aero; i++) {
            if (!strcmp(aps[i].id, id)) {
                printAP(aps[i]);
                err = 1;
            }
        }
        if (!err)
            printf("%s: no such airport ID\n", id);

        c = getchar();
    }
    if (flag)
        for (i = 0; i < n_aero; i++)
            printAP(aps[i]);
}


void v()
{
    int i, flag = 0;
    char c = getchar();
    Voo voo;

    if (c != '\n') {
        voo = leVoo();

        flag = testeVoo(voo, flag);

        /* raiseError(flag); */
        switch (flag) {
            case 0:
                voos[n_voos] = voo;
                n_voos++;

                for (i = 0; i < n_aero; i++)
                    if (!strcmp(voo.idp, aps[i].id))
                        aps[i].voos++;
                break;
            case 1:
                printf("invalid flight code\n");
                break;
            case 2:
                printf("flight already exists\n");
                break;
            case 3:
                printf("%s: no such airport ID\n", voo.idp);
                break;
            case 4:
                printf("%s: no such airport ID\n", voo.idc);
                break;
            case 5:
                printf("too many flights\n");
                break;
            case 6:
                printf("invalid date\n");
                break;
            case 7:
                printf("invalid duration\n");
                break;
            case 8:
                printf("invalid capacity\n");
                break;
        }
    }
    else 
        for (i = 0; i < n_voos; i++)
            printVoo(voos[i]);
}


void p()
{
    int i, flag = 1, max = 0;
    char id[MAXID];
    Voo copiaVoos[MAXVOOS];

    scanf("%s", id);

    for (i = 0; i < n_voos; i++)
        if (!strcmp(voos[i].idp, id)) {
            copiaVoos[max] = voos[i];
            max++;
        }

    for (i = 0; i < n_aero; i++)
        if (!strcmp(aps[i].id, id))
            flag = 0;

    if (flag)
        printf("%s: no such airport ID\n", id);
    else {
        sortVoo(copiaVoos, max);

        for (i = 0; i < max; i++) {
            printf("%s %s %02d-%02d-%04d %02d:%02d\n", copiaVoos[i].codigo, 
            copiaVoos[i].idc, copiaVoos[i].datap.dia, 
            copiaVoos[i].datap.mes, copiaVoos[i].datap.ano, 
            copiaVoos[i].horap.horas, 
            copiaVoos[i].horap.minutos);
        }
    }
}


void c()
{
    int i, flag = 1, max = 0;
    char id[MAXID];
    Voo copiaVoos[MAXVOOS];

    scanf("%s", id);

    for (i = 0; i < n_voos; i++)
        if (!strcmp(voos[i].idc, id)) {
            copiaVoos[max] = voos[i];

            if (passaDia(copiaVoos[max].horap, copiaVoos[max].duracao))
                copiaVoos[max].datap = somaDia(copiaVoos[max].datap);

            copiaVoos[max].horap = horaChegada(voos[i].horap, voos[i].duracao);

            max++;
        }

    for (i = 0; i < n_aero; i++) 
        if (!strcmp(aps[i].id, id))
            flag = 0;

    if (flag)
        printf("%s: no such airport ID\n", id);
    else {
        sortVoo(copiaVoos, max);

        for (i = 0; i < max; i++) {
            printf("%s %s %02d-%02d-%04d %02d:%02d\n", copiaVoos[i].codigo, 
            copiaVoos[i].idp, copiaVoos[i].datap.dia, copiaVoos[i].datap.
            mes, copiaVoos[i].datap.ano, copiaVoos[i].horap.horas, 
            copiaVoos[i].horap.minutos);
        }
    }
}


void t()
{
    int dia, mes, ano, flag;
    scanf("%d-%d-%d", &dia, &mes, &ano);
    flag = testeData(dia, mes, ano);
    if (flag)
        printf("%02d-%02d-%04d\n", data.dia=dia, data.mes=mes, data.ano=ano);
    else
        printf("invalid date\n");
}


int main()
{
    char comando;

    while ((comando = getchar()) != 'q') {
        switch (comando) {
            case 'a':
                a();
                break;
            case 'l':
                l();
                break;
            case 'v':
                v();
                break;
            case 'p':
                p();
                break;
            case 'c':
                c();
                break;
            case 't':
                t();
                break;
        }
    }
    return 0;
}