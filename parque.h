#ifndef PARQUE_H
#define PARQUE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Visitante {
    string nome;
    string cpf;
    string email;
    string tipoIngresso; // Normal ou VIP
};

struct Atracao {
    string nome;
    string tipo;
    int capacidadePorHorario;
    bool prioridadeVIP;

    vector<string> filaPrioritaria; // CPFs dos visitantes VIP
    vector<string> filaNormal;      // CPFs dos visitantes normais
};

#endif