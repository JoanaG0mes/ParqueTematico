
#ifndef PARQUE_HPP
#define PARQUE_HPP

#include <iostream>
#include <string>
#include <fstream>  // Para ler e escrever arquivos
#include <sstream>  // Para "parsear" as linhas do arquivo
#include "Visitante.hpp"
using namespace std;


struct No {
    Visitante visitante; 
    No* proximo;         
    No(const Visitante& v) : visitante(v), proximo(nullptr) {}
};


class Parque {
private:
    No* inicio;
    // Local do "banco de dados"
    const string ARQUIVO_DADOS = "/opt/lampp/database/visitantes.txt";

    /**
     * @brief Salva o estado atual da lista encadeada no arquivo.
     */
    void salvarDados() {
        ofstream arquivo(ARQUIVO_DADOS); 
        if (!arquivo.is_open()) {
            return; 
        }

        No* atual = inicio;
        while (atual != nullptr) {
            Visitante v = atual->visitante;
            arquivo << v.getCpf() << "," << v.getNome() << "," << v.getTipo() << "\n";
            atual = atual->proximo;
        }
        arquivo.close();
    }

    /**
     * @brief Carrega os dados do arquivo para a lista encadeada.
     */
    void carregarDados() {
        ifstream arquivo(ARQUIVO_DADOS); 
        if (!arquivo.is_open()) {
            return; 
        }

        string linha;
        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            string cpf, nome, tipo;

            getline(ss, cpf, ',');
            getline(ss, nome, ',');
            getline(ss, tipo);

            if (!cpf.empty()) {
                Visitante v(nome, cpf, tipo);
                No* novoNo = new No(v);
                if (inicio == nullptr) {
                    inicio = novoNo;
                } else {
                    No* atual = inicio;
                    while (atual->proximo != nullptr) {
                        atual = atual->proximo;
                    }
                    atual->proximo = novoNo;
                }
            }
        }
        arquivo.close();
    }


public:
    /**
     * @brief Construtor: Carrega os dados do arquivo ao criar o objeto.
     */
    Parque() : inicio(nullptr) {
        carregarDados(); 
    }

    /**
     * @brief Destrutor: Libera a memória da lista encadeada.
     */
    ~Parque() {
        No* atual = inicio;
        while (atual != nullptr) {
            No* proximo = atual->proximo; 
            delete atual;                 
            atual = proximo;              
        }
    }

    // --- OPERAÇÕES PÚBLICAS ---

    /**
     * @brief Adiciona um novo visitante e salva a lista.
     * @return 0 = Sucesso, 1 = Erro (CPF duplicado)
     */
    int cadastrarVisitante(const string& nome, const string& cpf, const string& tipo) {
        
        // --- NOVA VERIFICAÇÃO ---
        // Antes de cadastrar, verifica se o CPF já existe
        if (buscarVisitantePorCpf(cpf) != nullptr) {
            // Se o buscar NÃO retornar nulo, significa que já existe.
            return 1; // Retorna um código de erro (CPF duplicado)
        }
        // --- FIM DA VERIFICAÇÃO ---

        // Se chegou aqui, o CPF é novo. Prossiga com o cadastro:
        Visitante v(nome, cpf, tipo);
        No* novoNo = new No(v); 

        if (inicio == nullptr) {
            inicio = novoNo;
        } else {
            No* atual = inicio;
            while (atual->proximo != nullptr) {
                atual = atual->proximo; 
            }
            atual->proximo = novoNo;
        }
        
        salvarDados(); // Salva a lista no arquivo
        return 0; // Retorna sucesso
    }

    /**
     * @brief Remove um visitante por CPF e salva a lista.
     * @return true se removeu, false se não encontrou.
     */
    bool removerVisitante(const string& cpf) {
        if (inicio == nullptr) return false;

        bool removido = false;
        if (inicio->visitante.getCpf() == cpf) {
            No* noParaRemover = inicio;     
            inicio = inicio->proximo;       
            delete noParaRemover;           
            removido = true;
        } else {
            No* anterior = inicio;
            No* atual = inicio->proximo;
            while (atual != nullptr) {
                if (atual->visitante.getCpf() == cpf) {
                    anterior->proximo = atual->proximo; 
                    delete atual; 
                    removido = true;
                    break;
                }
                anterior = atual;
                atual = atual->proximo;
            }
        }
        
        if (removido) {
            salvarDados(); // Salva a lista no arquivo
        }
        return removido;
    }

    /**
     * @brief Lista todos os visitantes em formato HTML.
     */
    void listarVisitantesHtml() {
        No* atual = inicio;
        if (atual == nullptr) {
            cout << "<li>Nenhum visitante cadastrado.</li>";
            return;
        }
        while (atual != nullptr) {
            Visitante v = atual->visitante; 
            cout << "<li>" << v.getNome() << " | " << v.getCpf() << " | " << v.getTipo() << "</li>";
            atual = atual->proximo; 
        }
    }

    /**
     * @brief Busca um visitante por CPF.
     * @return Ponteiro para o Visitante se encontrar, ou nullptr.
     */
    Visitante* buscarVisitantePorCpf(const string& cpf) {
        No* atual = inicio; 
        while (atual != nullptr) {
            if (atual->visitante.getCpf() == cpf) {
                return &(atual->visitante);
            }
            atual = atual->proximo;
        }
        return nullptr;
    }
};

#endif