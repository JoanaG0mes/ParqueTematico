#ifndef RESERVA_HPP
#define RESERVA_HPP

#include <string>
#include "Visitante.hpp" // Para acessar o objeto Visitante
#include "Atracao.hpp"   // Para acessar o objeto Atracao
using namespace std;

class Reserva {
private:
    // Identificadores de quem está reservando e onde
    string idReserva;
    
    // Ponteiros para os objetos reais. Isso evita copiar dados e mantém o link
    Visitante* visitante;
    Atracao* atracao;
    
    // Detalhes da reserva
    string horarioSessao;
    string dataCriacao;
    bool confirmada; // Indica se a reserva foi atendida

public:
    // Construtor
    Reserva(const string& id, Visitante* v, Atracao* a, const string& horario)
        : idReserva(id), visitante(v), atracao(a), horarioSessao(horario), confirmada(false) 
    {
        // Aqui você definiria a data/hora atual da criação da reserva, se necessário.
    }

    // --- Getters ---
    Visitante* getVisitante() const { return visitante; }
    Atracao* getAtracao() const { return atracao; }
    string getHorarioSessao() const { return horarioSessao; }
    bool isConfirmada() const { return confirmada; }
    string getIdReserva() const { return idReserva; }
    
    // --- Setters/Ações ---
    void setConfirmada(bool status) {
        confirmada = status;
    }
};

#endif
