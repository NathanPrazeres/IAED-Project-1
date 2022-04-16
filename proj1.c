/*
Nathaniel Prazeres
ist1 103145
1º Projeto de IAED
*/

/* Inclusoes */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Definicoes */

#define MAXAPS 40
#define MAXVOOS 30000
#define MAXID 4
#define MAXPAIS 31
#define MAXCIDADE 51
#define MAXCODIGO 7

/* Estruturas e tipos de dados */

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int horas;
    int minutos;
} Hora;

typedef struct {
    char id[MAXID];
    char pais[MAXPAIS];
    char cidade[MAXCIDADE];
    int voos;
} AP;

typedef struct {
    char codigo[MAXCODIGO];
    char idp[MAXID];
    char idc[MAXID];
    Data datap;
    Hora horap;
    Hora duracao;
    int capacidade;
} Voo;


/* Inicializacao de variaveis globais */

int n_aero = 0, n_voos = 0;
Data data = {1, 1, 2022};
AP aps[MAXAPS];
Voo voos[MAXVOOS];


/* Funcoes auxiliares */

/* SORT AEROPORTOS
    Funcao que ordena os aeroportos por ordem alfabetica de identificador.
*/
void sortAP()
{
    AP temp;
    int i, j, flag;

    for (i = 0; i < n_aero - 1; i++) {
        flag = 1;

        for (j = 0; j < n_aero - i - 1; j++) {
            if (strcmp(aps[j].id, aps[j + 1].id) > 0) {
                flag = 0;
                temp = aps[j];
                aps[j] = aps[j + 1];
                aps[j + 1] = temp;
            }
        }
        if (flag)
            break;
    }
}

/* SORT VOOS POR HORA
    Funcao que ordena os voos por ordem crescente de hora.
*/
void sortVooHora(Voo v[], int max)
{
    Voo temp;
    int i, j, flag;

    for (i = 0; i < max - 1; i++) {
        flag = 1;

        for (j = 0; j < max - i - 1; j++) {
            if (v[j].horap.horas > v[j + 1].horap.horas ||
            (v[j].horap.horas == v[j + 1].horap.horas && 
            v[j].horap.minutos > v[j + 1].horap.minutos)) {
                flag = 0;
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
        if (flag)
            break;
    }
}

/* SORT VOOS POR DATA
    Funcao que ordena os voos por ordem crescente de data.
*/
void sortVooData(Voo v[], int max)
{
    Voo temp;
    int i, j, flag;

    for (i = 0; i < max - 1; i++) {
        flag = 1;

        for (j = 0; j < max - i - 1; j++) {
            if (v[j].datap.ano > v[j + 1].datap.ano || 
            (v[j].datap.ano == v[j + 1].datap.ano && 
            v[j].datap.mes > v[j + 1].datap.mes) || 
            (v[j].datap.ano == v[j + 1].datap.ano && 
            v[j].datap.mes == v[j + 1].datap.mes && 
            v[j].datap.dia > v[j + 1].datap.dia)) {
                flag = 0;
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
        if (flag)
            break;
    }
}

/* SORT VOOS
    Funcao que ordena os voos por ordem crescente de data e hora.
*/
void sortVoo(Voo v[], int max)
{
    sortVooHora(v, max);
    sortVooData(v, max);
}

/* COMPARAR DATAS
    Funcao que verifica se duas datas sao iguais.
*/
int comparaDatas(Data d1, Data d2)
{
    return (d1.dia == d2.dia && d1.mes == d2.mes && d1.ano == d2.ano);
}

/* TESTAR MES
    Funcao que verifica se um mes tem os dias que devia ter.
*/
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

/* TESTAR DATA
    Funcao que verifica se uma data eh mais de um ano no futuro ou no passado.
*/
int testeData(int dia, int mes, int ano)
{
    int flag = 1;

    if (ano > data.ano) {
        if (mes > data.mes)
            flag = 0;
        else if (mes == data.mes && dia > data.dia)
            flag = 0;
    }

    if (ano < data.ano || (mes < data.mes && ano == data.ano) || 
            (dia < data.dia && mes == data.mes && ano == data.ano) || mes > 12)
        flag = 0;

    return flag;
}

/* PASSA DIA
    Funcao que verifica se a hora de partida de um voo mais a duracao do mesmo
    excede o limite de horas de um dia.
*/
int passaDia(Hora partida, Hora duracao)
{
    int somaMinutos = partida.minutos + duracao.minutos, 
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

/* ADICIONA DIA
    Funcao que adiciona 1 dia a uma data de modo a manter-se valida.
*/
Data adicionaDia(Data dataPartida)
{
    Data dataNova = {0};
    int flag = 1;

    flag = testeMes(dataPartida.dia + 1, dataPartida.mes, flag);

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

/* HORA DE CHEGADA
    Funcao que calcula a hora de chegada de um voo a partir da sua hora de 
    partida e a sua duracao.
*/
Hora horaChegada(Hora partida, Hora duracao)
{
    Hora chegada;
    int somaMinutos = partida.minutos + duracao.minutos, 
            somaHoras = partida.horas + duracao.horas;

    if (somaMinutos >= 60) {
        somaMinutos -= 60;
        somaHoras += 1;
    }
    
    if (somaHoras >= 24)
        somaHoras -= 24;

    chegada.minutos = somaMinutos;
    chegada.horas = somaHoras;
    
    return chegada;
}

/* LE VOO
    Funcao que le um voo a partir do Standard Input.
*/
Voo leVoo()
{
    Voo voo;
    scanf("%s %s %s %d-%d-%d %d:%d %d:%d %d", voo.codigo, voo.idp, voo.idc, 
            &voo.datap.dia, &voo.datap.mes, &voo.datap.ano, &voo.horap.horas, 
            &voo.horap.minutos, &voo.duracao.horas, &voo.duracao.minutos, 
            &voo.capacidade);
    return voo;
}

/* PRINT VOO
    Funcao que traduz um voo para o formato:
        "CODIGO IDP IDC DATAdePARTIDA HORAdePARTIDA DURACAO CAPACIDADE"
    e imprime-o no Standard Output.
*/
void printVoo(Voo voo) 
{
    printf("%s %s %s %02d-%02d-%04d %02d:%02d\n", voo.codigo, voo.idp, 
            voo.idc, voo.datap.dia, voo.datap.mes, voo.datap.ano, 
            voo.horap.horas, voo.horap.minutos);
}

/* DETETA ERROS NUM VOO
    Funcao que verifica se um voo tem erros, devolvendo o inteiro.
*/
int vooDetetaErros(Voo voo, int lencod)
{
    int i, flag = 0, temp_flag;

    if (voo.capacidade < 10 || voo.capacidade > 100)
        flag = 8;

    if (voo.duracao.horas > 12 || 
            (voo.duracao.horas == 12 && voo.duracao.minutos > 0))
        flag = 7;

    if (testeData(voo.datap.dia, voo.datap.mes, voo.datap.ano) == 0)
        flag = 6;

    if (n_voos >= MAXVOOS)
        flag = 5;

    temp_flag = flag;
    flag = 4;
    for (i = 0; i < n_aero; i++)
        if (!strcmp(voo.idc, aps[i].id))
            flag = temp_flag;
    
    temp_flag = flag;
    flag = 3;
    for (i = 0; i < n_aero; i++)
        if (!strcmp(voo.idp, aps[i].id))
            flag = temp_flag;

    for (i = 0; i < n_voos; i++)
        if (!strcmp(voos[i].codigo, voo.codigo) && 
                comparaDatas(voos[i].datap, voo.datap))
            flag = 2;
    
    for (i = 2; i < lencod; i++)
        if(!isdigit(voo.codigo[i]))
            flag = 1;
    
    if (lencod <= 2 || voo.codigo[2] == '0' ||
            !isupper(voo.codigo[0]) || !isupper(voo.codigo[1]))
        flag = 1;

    return flag;
}

/* TRATA ERROS NUM VOO
    Funcao que recebe um inteiro e imprime uma mensagem de erro correspondente.
*/
void vooTrataErros(Voo voo, int flag)
{
    int i;

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

/* PRINT AEROPORTOS
    Funcao que traduz um aeroporto para o formato:
        "ID NOME CAPACIDADE NUMEROdeVOOS"
    e imprime-o para o Standard Output.
*/
void printAP(AP a)
{
    printf("%s %s %s %d\n", a.id, a.cidade, a.pais, a.voos);
}



/* ADICIONAR AEROPORTO
    Esta funcao adiciona um aeroporto ao sistema.

    Quando recebe uma string contendo um id, pais e cidade de um aeroporto que
    ainda nao pertence ao sistema, adiciona-o ao sistema e imprime
    o id do aeroporto adicionado para o standard output.

    Erros:
        -> Quando o ID do aeroporto nao eh valido.
        -> Quando o aeroporto excede o limite de aeroportos do sistema.
        -> Quando o aeroporto ja existe.
*/
void criaAeroporto()
{
    AP aeroporto;
    int i, flag = 1;
    scanf("%s %s %[^\n]", aeroporto.id, aeroporto.pais, aeroporto.cidade);
    aeroporto.voos = 0;
 
    if (n_aero < 40) {
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

/* LISTAR AEROPORTOS
    Esta funcao lista todos os aeroportos do sistema.

    Se nao forem introduzidos argumentos, imprime todos os aeroportos do 
    sistema, um por linha, em ordem alfabetica do ID, com o seguinte formato:
        IDAEROPORTO CIDADE PAIS VOOS
    
    Se for introduzido um ou mais IDs de aeroportos, imprime os aeroportos 
    correspondentes, com o mesmo formato, na ordem em que foram introduzidos.

    Erros:
        -> Quando o id de um aeroporto introduzido nao existe.
*/
void lista()
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

/* VOOS
    Esta funcao imprime todos os voos do sistema ou adiciona um voo ao sistema.
    
    Quando recebe uma string contendo os atributos de um voo validos,
    adiciona-o ao sistema e imprime o codigo do voo adicionado para o standard
    output. Se nao recebe nenhum argumento, imprime todos os voos do sistema.

    Erros:
        -> Quando o codigo do voo nao eh valido.
        -> Quando o voo ja existe.
        -> Quando o aeroporto de partida ou chegada nao existe.
        -> Quando o voo excede o limite de voos do sistema.
        -> Quando a data de partida eh no passado ou mais de um ano no futuro.
        -> Quando a duracao eh superior a 12 horas.
        -> Quando a capacidade nao eh um inteiro entre 10 e 100.
*/
void v()
{
    int i, flag;
    char c = getchar();
    Voo voo;

    if (c != '\n') {
        voo = leVoo();
        flag = vooDetetaErros(voo, (int) strlen(voo.codigo));
        vooTrataErros(voo, flag);
    }
    else 
        for (i = 0; i < n_voos; i++)
            printVoo(voos[i]);
}

/* VOOS COM PARTIDA DE UM AEROPORTO
    Esta funcao eh usada para obter todos os voos que partem de um determinado
    aeroporto.

    Quando recebe uma string contendo um id de um aeroporto, imprime todos os
    voos que partem do aeroporto com o id recebido.

    Erros:
        -> Quando o aeroporto nao existe.
*/
void partidas()
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

/* VOOS COM CHEGADA A UM AEROPORTO
    Esta funcao eh usada para obter todos os voos que chegam a um determinado
    aeroporto.

    Quando recebe uma string contendo um id de um aeroporto, imprime todos os
    voos que chegam ao aeroporto com o id recebido.

    Erros:
        -> Quando o aeroporto nao existe.
*/
void chegadas()
{
    int i, flag = 1, max = 0;
    char id[MAXID];
    Voo copiaVoos[MAXVOOS];

    scanf("%s", id);

    for (i = 0; i < n_voos; i++)
        if (!strcmp(voos[i].idc, id)) {
            copiaVoos[max] = voos[i];

            if (passaDia(copiaVoos[max].horap, copiaVoos[max].duracao))
                copiaVoos[max].datap = adicionaDia(copiaVoos[max].datap);

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
                    copiaVoos[i].idp, copiaVoos[i].datap.dia, 
                    copiaVoos[i].datap.mes, copiaVoos[i].datap.ano, 
                    copiaVoos[i].horap.horas, copiaVoos[i].horap.minutos);
        }
    }
}

/* TEMPO
    Esta funcao eh usada para alterar a data atual do sistema.
    Quando recebe uma data valida, altera a data atual do sistema e devolve a 
    mesma para o standard output no formato DD-MM-AAAA.

    Erros:
        -> Quando a data recebida eh anterior a data atual.
        -> Quando a data recebida eh mais de um ano no futuro.
*/
void tempo()
{
    int dia, mes, ano, flag;
    scanf("%d-%d-%d", &dia, &mes, &ano);
    flag = testeData(dia, mes, ano);
    if (flag)
        printf("%02d-%02d-%04d\n", data.dia=dia, data.mes=mes, data.ano=ano);
    else
        printf("invalid date\n");
}

/* MAIN
    Esta funcao eh usada para controlar o funcionamento do programa.
    Comeca por ler um carater comando e chamar a funcao correspondente.
    So acaba a execucao do programa quando o utilizador escreve o carater 'q'.
*/
int main()
{
    char comando;

    while ((comando = getchar()) != 'q') {
        switch (comando) {
            case 'a':
                criaAeroporto();
                break;
            case 'l':
                lista();
                break;
            case 'v':
                v();
                break;
            case 'p':
                partidas();
                break;
            case 'c':
                chegadas();
                break;
            case 't':
                tempo();
                break;
        }
    }
    return 0;
}