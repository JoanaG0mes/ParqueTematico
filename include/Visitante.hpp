#ifndef VISITANTE_HPP
#define VISITANTE_HPP

#include <string>
using namespace std;

class Visitante {
private:
    string nome;
    string cpf;
    string tipo;

public:
    Visitante() {}
    Visitante(const string& n, const string& c, const string& t) : nome(n), cpf(c), tipo(t) {}
    
    string getNome() { return nome; }
    string getCpf() { return cpf; }
    string getTipo() { return tipo; }
};

#endif
