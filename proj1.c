#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

Data data = {1, 1, 2022};

typedef struct {
    int horas;
    int minutos;
} Hora;

typedef struct {
    char id[4];
    char pais[31];
    char cidade[51];
    int voos;
} AP;

typedef struct {
    char codigo[7];
    char idp[4];
    char idc[4];
    Data datap;
    Hora horap;
    Hora duracao;
    int capacidade;
} Voo;



int comparaDatas(Data d1, Data d2)
{
    return (d1.dia == d2.dia && d1.mes == d2.mes && d1.ano == d2.ano)? 1:0;
}



int testeData(int dia, int mes, int ano)
{
    int flag = 1;

    if (ano < data.ano || (mes < data.mes && ano == data.ano) || \
    (dia < data.dia && mes == data.mes && ano == data.mes) || \
    ano > 2023 || mes > 12)
        flag = 0;
    switch (mes) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if (dia > 31)
                flag = 0;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            if (dia > 30)
                flag = 0;
            break;
        case 2:
            if (dia > 29)
                flag = 0;
            break;
    }

    return flag;
}



void sortAP(AP aps[], int n_aero)
{
    AP temp;
    int i, j;
    for (i = 0; i < n_aero-1; i++) {
        for (j = i+1; j < n_aero; j++) {
            if (strcmp(aps[i].id, aps[j].id) > 0) {
                temp = aps[i];
                aps[i] = aps[j];
                aps[j] = temp;
            }
        }
    }
}





void sortVoo(Voo voos[], int n_voos)
{
    Voo temp;
    int i, j;
    for (i = 0; i < n_voos-1; i++) {
        for (j = i+1; j < n_voos; j++) {
            if ((voos[i].datap.ano > voos[j].datap.ano) || \
            (voos[i].datap.ano == voos[j].datap.ano && \
            voos[i].datap.mes > voos[j].datap.mes) || \
            (voos[i].datap.ano == voos[j].datap.ano && \
            voos[i].datap.mes == voos[j].datap.mes && \
            voos[i].datap.dia > voos[j].datap.dia)) {
                temp = voos[i];
                voos[i] = voos[j];
                voos[j] = temp;
            }
        }
    }
}





int a(AP aps[], int n_aero)
{
    AP aeroporto;
    int i, flag = 1;
 


    if (n_aero > 40)
        printf("too many airports\n");
    else {
        scanf("%s %s %[^\n]", aeroporto.id, aeroporto.pais, aeroporto.cidade);
        aeroporto.voos = 0;
        if (isupper(aeroporto.id[0]) && isupper(aeroporto.id[1]) && \
        isupper(aeroporto.id[2])) {
            for (i = 0; i < n_aero; i++)
                if (strcmp(aps[i].id, aeroporto.id) == 0)
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
    return n_aero;
}


void printAP(AP a)
{
    printf("%s %s %s %d\n", a.id, a.cidade, a.pais, a.voos);
}


void l(AP aps[], int n_aero)
{
    int i, flag = 1, err = 1;
    char id[4], c = getchar();

    sortAP(aps, n_aero);
    while (c != '\n' && c != '\0') {
        flag = 0;
        scanf("%s", id);
        for (i = 0; i < n_aero; i++) {
            if (!strcmp(aps[i].id, id)) {
                printAP(aps[i]);
                err = 0;
            }
        }
        c = getchar();
    }
    if (flag)
        for (i = 0; i < n_aero; i++)
            printAP(aps[i]);
    else if (err)
        printf("<IDAeroporto>: no such airport ID\n");
}


Voo leVoo()
{
    Voo voo;
    scanf("%s%s%s%d-%d-%d%d:%d%d:%d%d", voo.codigo, voo.idp, voo.idc, \
            &voo.datap.dia, &voo.datap.mes, &voo.datap.ano, &voo.horap.horas, \
            &voo.horap.minutos, &voo.duracao.horas, &voo.duracao.minutos, \
            &voo.capacidade);
    return voo;
}



void printVoo(Voo voo) 
{
    printf("%s %s %s %02d-%02d-%04d %d:%d\n", voo.codigo, voo.idp, \
    voo.idc, voo.datap.dia, voo.datap.mes, voo.datap.ano, voo.horap.horas, \
    voo.horap.minutos);
}



int v(Voo voos[], int n_voos, AP aps[], int n_aero)
{
    int i, flag = 0, temp_flag;
    char c = getchar();
    Voo voo;

    if (c != '\n') {
        voo = leVoo();

        if (voo.capacidade < 10 || voo.capacidade > 100)
            flag = 8;

        if (voo.duracao.horas >= 12)
            flag = 7;

        if (testeData(voo.datap.dia, voo.datap.mes, voo.datap.ano) == 0)
            flag = 6;

        if (n_voos >= 30000)
            flag = 5;

        temp_flag = flag;
        flag = 4;
        for (i = 0; i < n_aero; i++)
            if (strcmp(voo.idc, aps[i].id) == 0)
                flag = temp_flag;
        
        temp_flag = flag;
        flag = 3;
        for (i = 0; i < n_aero; i++)
            if (strcmp(voo.idp, aps[i].id) == 0)
                flag = temp_flag;

        for (i = 0; i < n_voos; i++)
            if (strcmp(voos[i].codigo, voo.codigo) == 0 && \
            comparaDatas(voos[i].datap, voo.datap))
                flag = 2;
        
        for (i = 2; i < (int) strlen(voo.codigo); i++)
            if(!isdigit(voo.codigo[i]))
                flag = 1;
        if ((voo.codigo[2] == 0 && (int) strlen(voo.codigo) > 2) || \
        !isupper(voo.codigo[0]) || !isupper(voo.codigo[1]))
            flag = 1;


        if (flag == 0) {
            voos[n_voos] = voo;
            n_voos++;
        }
        else if (flag == 1)
            printf("invalid flight code\n");
        else if (flag == 2)
            printf("flight already exists\n");
        else if (flag == 3 || flag == 4)
            printf("%s: no such airport ID\n", flag == 3? voo.idp:voo.idc);
        else if (flag == 5)
            printf("too many flights\n");
        else if (flag == 6)
            printf("invalid date\n");
        else if (flag == 7)
            printf("invalid duration\n");
        else if (flag == 8)
            printf("invalid capacity\n");
    }
    else 
        for (i = 0; i < n_voos; i++)
            printVoo(voos[i]);

    return n_voos;
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
    AP aps[40];
    Voo voos[30000];
    int n_aero=0, n_voos=0;
    char c;

    while ((c = getchar()) != 'q') {
        switch (c) {
            case 'a':
                n_aero = a(aps, n_aero);
                break;
            case 'l':
                l(aps, n_aero);
                break;
            case 'v':
                n_voos = v(voos, n_voos, aps, n_aero);
                break;
            case 'p':
                printf("p");
                break;
            case 'c':
                printf("c");
                break;
            case 't':
                t();
                break;
        }
    }
    return 0;
}