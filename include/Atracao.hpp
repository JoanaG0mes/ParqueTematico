#ifndef ATRACAO_HPP
#define ATRACAO_HPP

#include <string>
#include "Reserva.hpp"
using std::string;

// Nó para a fila de reservas
class NoFila {
public:
    Reserva* reserva;
    NoFila* proximo;

    NoFila(Reserva* r) : reserva(r), proximo(0) {}
};

class Atracao {
private:
    int id;
    string nome;
    string tipo;  // montanha-russa, simulador, etc.
    int capacidadePorSessao;
    string horariosDisponiveis[10]; // exemplo de até 10 horários
    int qtdHorarios;
    int faixaEtariaMinima;
    string passesComPrioridade[5]; // ex.: "VIP", "ANUAL"
    int qtdPasses;

    // Fila virtual
    NoFila* inicioPrioritaria;
    NoFila* inicioNormal;

public:
    Atracao() : inicioPrioritaria(0), inicioNormal(0), qtdHorarios(0), qtdPasses(0) {}

    Atracao(int i, const string& n, const string& t, int capacidade, int idadeMin)
        : id(i), nome(n), tipo(t), capacidadePorSessao(capacidade), faixaEtariaMinima(idadeMin),
          inicioPrioritaria(0), inicioNormal(0), qtdHorarios(0), qtdPasses(0) {}

    int getId() { return id; }
    string getNome() { return nome; }
    string getTipo() { return tipo; }

    // Adiciona horário disponível
    bool adicionarHorario(const string& h) {
        if (qtdHorarios >= 10) return false;
        horariosDisponiveis[qtdHorarios++] = h;
        return true;
    }

    // Adiciona pass de prioridade
    bool adicionarPassPrioridade(const string& pass) {
        if (qtdPasses >= 5) return false;
        passesComPrioridade[qtdPasses++] = pass;
        return true;
    }

    // Adiciona reserva na fila virtual
    bool adicionarReserva(Reserva* r, const string& tipoIngressoVisitante) {
        // verifica se é prioridade
        bool ehPrioridade = false;
        for (int i = 0; i < qtdPasses; i++) {
            if (passesComPrioridade[i] == tipoIngressoVisitante) {
                ehPrioridade = true;
                break;
            }
        }

        NoFila* novo = new NoFila(r);
        if (ehPrioridade) {
            if (!inicioPrioritaria) inicioPrioritaria = novo;
            else {
                NoFila* aux = inicioPrioritaria;
                while (aux->proximo) aux = aux->proximo;
                aux->proximo = novo;
            }
        } else {
            if (!inicioNormal) inicioNormal = novo;
            else {
                NoFila* aux = inicioNormal;
                while (aux->proximo) aux = aux->proximo;
                aux->proximo = novo;
            }
        }
        return true;
    }

    // Avança a fila para uma sessão, retorna quantas reservas foram confirmadas
    int avancarFila(int capacidade) {
        int confirmadas = 0;

        // Processa fila prioritária
        while (inicioPrioritaria && confirmadas < capacidade) {
            NoFila* aux = inicioPrioritaria;
            inicioPrioritaria = inicioPrioritaria->proximo;
            aux->reserva->getAtracao(); // aqui você poderia marcar como confirmada
            delete aux;
            confirmadas++;
        }

        // Processa fila normal
        while (inicioNormal && confirmadas < capacidade) {
            NoFila* aux = inicioNormal;
            inicioNormal = inicioNormal->proximo;
            aux->reserva->getAtracao();
            delete aux;
            confirmadas++;
        }

        return confirmadas;
    }

    // Posição na fila de uma reserva
    int posicaoFila(Reserva* r) {
        int pos = 1;
        NoFila* aux = inicioPrioritaria;
        while (aux) {
            if (aux->reserva == r) return pos;
            aux = aux->proximo;
            pos++;
        }
        aux = inicioNormal;
        while (aux) {
            if (aux->reserva == r) return pos;
            aux = aux->proximo;
            pos++;
        }
        return -1; // não encontrada
    }
};

#endif

