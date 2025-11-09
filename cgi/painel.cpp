#include <iostream>
#include "../include/Parque.hpp"
using namespace std;

int main() {
    cout << "Content-type: text/html\n\n";
    cout << "<html><head>";
    cout << "<meta charset='UTF-8'>";
    cout << "<title>Painel do Parque</title>";
    cout << "<link rel='stylesheet' href='/parque/style.css'>";
    cout << "</head><body><div class='container'>";
    
    cout << "<h1>🎢 Painel do Parque</h1>";
    
    Parque parque; // Cria o parque (carrega os dados do arquivo)

    cout << "<h2>Visitantes Atuais:</h2><ul>";
    parque.listarVisitantesHtml(); // Lista os visitantes
    cout << "</ul>";

    // cout << "<hr>";
    cout << "<p><a href='/parque/cadastro.html'>Cadastrar Novo Visitante</a></p>";
    cout << "<p><a href='/parque/remover.html'>Remover Visitante</a></p>";

    cout << "</div></body></html>";

    return 0;
}