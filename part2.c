#include <stdio.h>
#include <time.h>
#include "nascimento.h"

int eh_bissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int dias_no_mes(int mes, int ano) {
    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return eh_bissexto(ano) ? 29 : 28;
        default:
            return 0;
    }
}

int dias_de_vida(data_t nasc) {
    // Obter a data atual
    time_t agora = time(NULL);
    struct tm *data_atual = localtime(&agora);
 
    data_t atual;
    atual.dia = data_atual->tm_mday;
    atual.mes = data_atual->tm_mon + 1; 
    atual.ano = data_atual->tm_year + 1900;
    int dias = 0;
  
    for (int ano = nasc.ano; ano < atual.ano; ano++) {
        dias += eh_bissexto(ano) ? 366 : 365;
    }

    for (int mes = nasc.mes; mes <= 12; mes++) {
        if (mes == nasc.mes) {
            dias -= nasc.dia - 1;
        } else {
            dias -= dias_no_mes(mes, nasc.ano);
        }
    }
 
    for (int mes = 1; mes < atual.mes; mes++) {
        dias += dias_no_mes(mes, atual.ano);
    }
    dias += atual.dia;
    
    return dias;
}
