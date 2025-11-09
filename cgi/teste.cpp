#include <iostream>

using namespace std;

int main() {
    // 1. Imprime o cabeçalho
    cout << "Content-type: text/html\n\n";

    // 2. Imprime um HTML simples
    cout << "<html><body>";
    cout << "<h1 style='color: green;'>Teste OK!</h1>";
    cout << "<p>Se voce esta vendo isto, o seu ambiente C++ CGI esta funcionando!</p>";
    cout << "</body></html>";
    
    return 0; // Termina com sucesso
}