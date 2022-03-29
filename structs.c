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