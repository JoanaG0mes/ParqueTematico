
#include <iostream>
#include <string>
#include <map>
#include "../include/Parque.hpp"
#include "util_cgi.hpp"

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
        cout << "<meta charset='UTF-8'>";  // Corrige problemas de acentos e emojis
        cout << "<title>Resultado do Cadastro</title>";
        cout << "<link rel='stylesheet' href='/parque/style.css'>";
        cout << "</head><body><div class='container'>";

        // Formulário vazio
        if (form.empty() || form.find("cpf") == form.end() || form["cpf"].empty()) {
            cout << "<h1 class='error'>Erro: Dados insuficientes.</h1>";
            cout << "<p>O formulário parece ter sido enviado vazio ou sem CPF.</p>";
            cout << "<hr>";
            cout << "<p><a href='/parque/cadastro.html'>⬅ Voltar à página de cadastro</a></p>";
            cout << "</div></body></html>";
            return 0;
        }

        // Pegar dados do formulário
        string nome = form["nome"];
        string cpf = form["cpf"];
        string tipo = form["tipo"];

        // Cadastrar visitante usando a classe Parque
        Parque parque;
        int resultado = parque.cadastrarVisitante(nome, cpf, tipo); // Captura o resultado

        // --- LÓGICA ATUALIZADA ---
        // Verifica o resultado
        if (resultado == 0) {
            // Mensagem de sucesso
            cout << "<h1 class='success'>✔ Cadastro realizado com sucesso!</h1>";
            cout << "<p><strong>Nome:</strong> " << nome << "</p>";
            cout << "<p><strong>CPF:</strong> " << cpf << "</p>";
            cout << "<p><strong>Tipo de ingresso:</strong> " << tipo << "</p>";
        } else {
            // Mensagem de erro (CPF duplicado)
            cout << "<h1 class='error'>Erro: CPF já cadastrado!</h1>";
            cout << "<p>O CPF <strong>" << cpf << "</strong> já existe no sistema.</p>";
            cout << "<p>Tente cadastrar outro visitante ou remova o existente.</p>";
        }
        // --- FIM DA LÓGICA ---

        cout << "<hr>";
        cout << "<p><a href='/parque/cadastro.html'>⬅ Voltar à página de cadastro</a></p>";
        cout << "<p><a href='/cgi-bin/painel.cgi'>Ver Painel</a></p>";


        // Fim do HTML
        cout << "</div></body></html>";

    } catch (const exception& e) {
        // Mensagem de erro
        cout << "<html><head><meta charset='UTF-8'><title>Erro</title>";
        cout << "<link rel='stylesheet' href='/parque/style.css'></head><body><div class='container'>";
        cout << "<h1 class='error'>Erro interno no CGI!</h1>";
        cout << "<p>" << e.what() << "</p>";
        cout << "<p><a href='/parque/cadastro.html'>⬅ Voltar à página de cadastro</a></p>";
        cout << "</div></body></html>";
    }

    return 0;
}