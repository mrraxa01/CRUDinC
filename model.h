typedef struct {
  char tecnico[100];
  char data[15];
  char origem[40];
  char destino[40];
  float valor;
  char status; /* 'PG' - PAGA / 'AP' - A PAGAR / 'C' - CANCELADA */
} Nota;
