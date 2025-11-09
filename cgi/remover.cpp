#include <iostream>
#include <string>
#include <map>
#include "../include/Parque.hpp" // O caminho para seu header
#include "util_cgi.hpp"        // O caminho para seu utilitário

using namespace std;

int main() {
    // Cabeçalho CGI
    cout << "Content-type: text/html\n\n";

    try {
        // Ler dados enviados pelo formulário
        string body = readRequestBody();
        auto form = parseForm(body);

        // Início do HTML
        cout << "<html><head>";
        cout << "<meta charset='UTF-8'>";
        cout << "<title>Resultado da Remoção</title>";
        cout << "<link rel='stylesheet' href='/parque/style.css'>";
        cout << "</head><body><div class='container'>";

        string cpf;
        if (form.find("cpf") != form.end()) {
            cpf = form["cpf"];
        }

        // Se o CPF estiver vazio
        if (cpf.empty()) {
            cout << "<h1 class='error'>Erro: CPF não fornecido.</h1>";
        } else {
            // Cria o objeto Parque (que carrega os dados do arquivo)
            Parque parque;
            
            // Tenta remover o visitante (isso também salva o arquivo)
            if (parque.removerVisitante(cpf)) {
                cout << "<h1 class='success'>✔ Visitante Removido!</h1>";
                cout << "<p>O visitante com CPF <strong>" << cpf << "</strong> foi removido com sucesso.</p>";
            } else {
                cout << "<h1 class='error'>Erro: Visitante não encontrado.</h1>";
                cout << "<p>Nenhum visitante com CPF <strong>" << cpf << "</strong> foi encontrado no sistema.</p>";
            }
        }

        // Links de navegação
        cout << "<hr>";
        cout << "<p><a href='/parque/remover.html'>Remover outro visitante</a></p>";
        cout << "<p><a href='/cgi-bin/painel.cgi'>Ver Painel Atualizado</a></p>";
        cout << "<p><a href='/parque/cadastro.html'>Voltar ao Cadastro</a></p>";

        // Fim do HTML
        cout << "</div></body></html>";

    } catch (const exception& e) {
        // Mensagem de erro genérica
        cout << "<html><head><meta charset='UTF-8'><title>Erro</title>";
        cout << "<link rel='stylesheet' href='/parque/style.css'></head><body><div class='container'>";
        cout << "<h1 class='error'>Erro interno no CGI!</h1>";
        cout << "<p>" << e.what() << "</p>";
        cout << "<p><a href='/parque/cadastro.html'>Voltar ao Cadastro</a></p>";
        cout << "</div></body></html>";
    }

    return 0;
}