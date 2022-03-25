#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int n_aero=0, n_voos=0;

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

AP aps[40];

typedef struct {
    char codigo[7];
    char idp[4];
    char idc[4];
    Data datap;
    Hora horap;
    Hora duracao;
    int capacidade;
} Voo;

Voo voos[30000];

int comparaDatas(Data d1, Data d2)
{
    return (d1.dia == d2.dia && d1.mes == d2.mes && d1.ano == d2.ano)? 1:0;
}

int testeMes(int dia, int mes, int flag)
{
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
            if (dia > 28)
                flag = 0;
            break;
    }

    return flag;
}

int testeData(int dia, int mes, int ano)
{
    int flag = 1;

    if (ano > data.ano) {
        if (mes > data.mes)
            flag = 0;
        else if (mes == data.mes && dia > data.dia)
            flag = 0;
    }

    if (ano < data.ano || (mes < data.mes && ano == data.ano) || \
    (dia < data.dia && mes == data.mes && ano == data.mes) || mes > 12)
        flag = 0;

    flag = testeMes(dia, mes, flag);

    return flag;
}



void sortAP(AP aps[], int n_aero)
{
    AP temp;
    int i, j;
    for (i = 0; i < n_aero - 1; i++) {
        for (j = i + 1; j < n_aero; j++) {
            if (strcmp(aps[i].id, aps[j].id) > 0) {
                temp = aps[i];
                aps[i] = aps[j];
                aps[j] = temp;
            }
        }
    }
}


void sortVoo1()
{
    Voo temp;
    int i, j;
    for (i = 0; i < n_voos - 1; i++) {
        for (j = i + 1; j < n_voos; j++) {
            if (voos[i].horap.horas > voos[j].horap.horas || \
            (voos[i].horap.horas == voos[j].horap.horas && \
            voos[i].horap.minutos > voos[j].horap.minutos)) {
                temp = voos[i];
                voos[i] = voos[j];
                voos[j] = temp;
            }
        }
    }
}


void sortVoo2()
{
    Voo temp;
    int i, j;
    for (i = 0; i < n_voos - 1; i++) {
        for (j = i + 1; j < n_voos; j++) {
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


void sortVoo()
{
    sortVoo1();
    sortVoo2();
}



int dataChegada(Hora partida, Hora duracao)
{
    int somaMinutos = partida.minutos + duracao.minutos, \
    somaHoras = partida.horas + duracao.horas, day = 0;

    if (somaMinutos >= 60) {
        somaMinutos -= 60;
        somaHoras += 1;
    }
    
    if (somaHoras >= 24) {
        somaHoras -= 24;
        day = 1;
    }
    
    return day;
}



Data somaDia(Data dataPartida)
{
    Data dataNova = {0, 0, 0};
    int flag = 1;

    flag = testeMes(dataPartida.dia, dataPartida.mes, flag);

    if (dataPartida.mes == 12 && flag == 0)
        flag = 2;

    if (flag == 1) {
        dataNova.dia = dataPartida.dia + 1;
        dataNova.mes = dataPartida.mes;
        dataNova.ano = dataPartida.ano;
    }
    else if (flag == 0) {
        dataNova.dia = 1;
        dataNova.mes = dataPartida.mes + 1;
        dataNova.ano = dataPartida.ano;
    }
    else if (flag == 2) {
        dataNova.dia = 1;
        dataNova.mes = 1;
        dataNova.ano = dataPartida.ano + 1;
    }

    return dataNova;
}



Hora horaChegada(Hora partida, Hora duracao)
{
    Hora chegada;
    int somaMinutos = partida.minutos + duracao.minutos, \
    somaHoras = partida.horas + duracao.horas;

    if (somaMinutos >= 60) {
        somaMinutos -= 60;
        somaHoras += 1;
    }
    
    if (somaHoras >= 24) {
        somaHoras -= 24;
    }

    chegada.minutos = somaMinutos;
    chegada.horas = somaHoras;
    
    return chegada;
}



void a()
{
    AP aeroporto;
    int i, flag = 1;
 


    if (n_aero >= 40)
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
}


void printAP(AP a)
{
    printf("%s %s %s %d\n", a.id, a.cidade, a.pais, a.voos);
}


void l()
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
        printf("%s: no such airport ID\n", id);
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



void v()
{
    int i, flag = 0, temp_flag;
    char c = getchar();
    Voo voo;

    if (c != '\n') {
        voo = leVoo();

        if (voo.capacidade < 10 || voo.capacidade > 100)
            flag = 8;

        if (voo.duracao.horas > 12 || \
        (voo.duracao.horas == 12 && voo.duracao.minutos > 0))
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


void p()
{
    int i, flag = 1;
    char id[4];

    scanf("%s", id);
    sortVoo();

    for (i = 0; i < n_voos; i++) {
        if (!strcmp(voos[i].idp, id)) {
            flag = 0;

            printf("%s %s %02d-%02d-%04d %02d:%02d\n", voos[i].codigo, \
            voos[i].idp, voos[i].datap.dia, voos[i].datap.mes, \
            voos[i].datap.ano, voos[i].horap.horas, voos[i].horap.minutos);
        }
    }

    if (flag)
        printf("%s: no such airport ID\n", id);
}


void c()
{
    Hora horaNova;
    Data dataNova;
    int i, flag = 1;
    char id[4];

    scanf("%s", id);
    sortVoo();

    for (i = 0; i < n_voos; i++) {
        if (!strcmp(voos[i].idc, id)) {
            flag = 0;

            if (dataChegada(voos[i].horap, voos[i].duracao))
                dataNova = somaDia(voos[i].datap);

            horaNova = horaChegada(voos[i].horap, voos[i].duracao);

            printf("%s %s %02d-%02d-%04d %02d:%02d\n", voos[i].codigo, \
            voos[i].idc, dataNova.dia, dataNova.mes, dataNova.ano, \
            horaNova.minutos, horaNova.horas);
        }
    }

    if (flag)
        printf("%s: no such airport ID\n", id);
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