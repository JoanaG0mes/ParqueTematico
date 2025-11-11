#ifndef VISITANTE_HPP
#define VISITANTE_HPP

#include <string>
#include <iostream>
using namespace std;

// --- ESTRUTURAS SECUNDÁRIAS DE LISTA ---

// 1. Estrutura para o histórico de visitas
struct RegistroVisita {
    string nomeAtracao;
    string horaEntrada;
    string horaSaida;
};

// 2. Nó da Lista de Histórico
struct NoHistorico {
    RegistroVisita registro;
    NoHistorico* proximo;

    NoHistorico(const RegistroVisita& r) : registro(r), proximo(nullptr) {}
};

// 3. Nó da Lista de Reservas Ativas
struct NoReserva {
    string nomeAtracao;
    NoReserva* proximo;

    NoReserva(const string& nome) : nomeAtracao(nome), proximo(nullptr) {}
};

// --- CLASSE VISITANTE COM LISTAS ENCAD. INTERNAS ---

class Visitante {
private:
    string nome;
    string cpf;
    string tipoIngresso;
    string dataNascimento;
    string email;
    string dadosCartao;

    // Ponteiros para o início das listas encadeadas internas
    NoReserva* reservasAtivasInicio;
    NoHistorico* historicoInicio;

public:
    // Construtor
    Visitante(const string& n, const string& c, const string& t, const string& dn, const string& e, const string& dc)
        : nome(n), cpf(c), tipoIngresso(t), dataNascimento(dn), email(e), dadosCartao(dc),
          reservasAtivasInicio(nullptr), historicoInicio(nullptr) {}

    // Destrutor (Libera a memória de todas as listas internas)
    ~Visitante() {
        // Liberação da lista de reservas
        NoReserva* atualR = reservasAtivasInicio;
        while (atualR != nullptr) {
            NoReserva* proximoR = atualR->proximo;
            delete atualR;
            atualR = proximoR;
        }

        // Liberação da lista de histórico
        NoHistorico* atualH = historicoInicio;
        while (atualH != nullptr) {
            NoHistorico* proximoH = atualH->proximo;
            delete atualH;
            atualH = proximoH;
        }
    }

    // --- GETTERS COMPLETOS ---
    string getNome() const { return nome; }
    string getCpf() const { return cpf; }
    string getTipoIngresso() const { return tipoIngresso; }
    string getDataNascimento() const { return dataNascimento; }
    string getEmail() const { return email; }
    string getDadosCartao() const { return dadosCartao; }
    
    // Getters para a interface (Retornam o ponteiro de início para travessia)
    NoReserva* getReservasAtivasInicio() const { return reservasAtivasInicio; }
    NoHistorico* getHistoricoInicio() const { return historicoInicio; }


    // --- MÉTODOS DE AÇÃO (Implementação Final da Lista Encadeada) ---

    // 1. Adicionar Reserva Ativa (Inserção no Fim da Lista)
    void adicionarReservaAtiva(const string& nomeAtracao) {
        NoReserva* novoNo = new NoReserva(nomeAtracao);
        if (reservasAtivasInicio == nullptr) {
            reservasAtivasInicio = novoNo;
        } else {
            NoReserva* atual = reservasAtivasInicio;
            while (atual->proximo != nullptr) {
                atual = atual->proximo;
            }
            atual->proximo = novoNo;
        }
    }
    
    // 2. Remover Reserva Ativa (Remoção por Valor)
    bool removerReservaAtiva(const string& nomeAtracao) {
        if (reservasAtivasInicio == nullptr) {
            return false;
        }

        // Caso 1: O nó a ser removido é o primeiro
        if (reservasAtivasInicio->nomeAtracao == nomeAtracao) {
            NoReserva* noParaRemover = reservasAtivasInicio;
            reservasAtivasInicio = reservasAtivasInicio->proximo;
            delete noParaRemover;
            return true;
        }

        // Caso 2: O nó está no meio ou no fim
        NoReserva* anterior = reservasAtivasInicio;
        NoReserva* atual = reservasAtivasInicio->proximo;

        while (atual != nullptr) {
            if (atual->nomeAtracao == nomeAtracao) {
                anterior->proximo = atual->proximo;
                delete atual;
                return true;
            }
            anterior = atual;
            atual = atual->proximo;
        }
        
        return false; // Não encontrado
    }
    
    // 3. Adicionar ao Histórico (Inserção no Fim da Lista)
    void adicionarAoHistorico(const RegistroVisita& registro) {
        NoHistorico* novoNo = new NoHistorico(registro);
        if (historicoInicio == nullptr) {
            historicoInicio = novoNo;
        } else {
            NoHistorico* atual = historicoInicio;
            while (atual->proximo != nullptr) {
                atual = atual->proximo;
            }
            atual->proximo = novoNo;
        }
    }
};

#endif