#include "parque.h"

vector<Visitante> listaDeVisitantes;
vector<Atracao> listaDeAtracoes;

void interfaceCadastroAtracao();
void interfaceCadastroVisitante();
void interfacePortalVisitante();
void interfacePainelControle();

// ⚙️ Função principal (menu)
int main() {
    int opcao;

    do {
        system("clear"); // limpa a tela (Linux)
        cout << "==============================\n";
        cout << "🎢 SISTEMA - PARQUE TEMÁTICO 🎡\n";
        cout << "==============================\n";
        cout << "1. Cadastrar Atração\n";
        cout << "2. Cadastrar Visitante\n";
        cout << "3. Portal do Visitante (Entrar na Fila)\n";
        cout << "4. Painel de Controle\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1: interfaceCadastroAtracao(); break;
            case 2: interfaceCadastroVisitante(); break;
            case 3: interfacePortalVisitante(); break;
            case 4: interfacePainelControle(); break;
            case 0: cout << "Encerrando... 🎟️\n"; break;
            default: cout << "Opção inválida!\n"; break;
        }

        if (opcao != 0) {
            cout << "\nPressione Enter para continuar...";
            cin.ignore();
            cin.get();
        }

    } while (opcao != 0);

    return 0;
}

// 💡 Cadastro de atrações
void interfaceCadastroAtracao() {
    system("clear");
    cout << "--- 1. Cadastro de Nova Atração ---\n";

    Atracao nova;
    cout << "Nome da atração: ";
    cin.ignore();
    getline(cin, nova.nome);

    cout << "Tipo (montanha-russa, roda gigante, etc.): ";
    getline(cin, nova.tipo);

    cout << "Capacidade por horário: ";
    cin >> nova.capacidadePorHorario;

    char vip;
    cout << "Tem fila VIP? (s/n): ";
    cin >> vip;
    nova.prioridadeVIP = (vip == 's' || vip == 'S');

    listaDeAtracoes.push_back(nova);
    cout << "\n✅ Atração cadastrada com sucesso!\n";
}

// 💡 Cadastro de visitantes (Etapa 1)
void interfaceCadastroVisitante() {
    system("clear");
    cout << "--- 2. Cadastro de Novo Visitante ---\n";

    Visitante novo;
    cout << "Nome: ";
    cin.ignore();
    getline(cin, novo.nome);

    cout << "CPF: ";
    getline(cin, novo.cpf);

    cout << "Email: ";
    getline(cin, novo.email);

    cout << "Tipo de ingresso (Normal/VIP): ";
    getline(cin, novo.tipoIngresso);

    listaDeVisitantes.push_back(novo);

    cout << "\n✅ Visitante cadastrado com sucesso!\n";
}

// 💡 Portal do visitante (Etapa 3)
void interfacePortalVisitante() {
    system("clear");
    cout << "--- 3. Portal do Visitante ---\n";

    string cpf;
    cout << "Digite seu CPF: ";
    cin >> cpf;

    // Procurar visitante
    string tipoIngresso = "Normal";
    bool encontrado = false;

    for (auto &v : listaDeVisitantes) {
        if (v.cpf == cpf) {
            tipoIngresso = v.tipoIngresso;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "❌ Visitante não encontrado!\n";
        return;
    }

    cout << "\nAtrações disponíveis:\n";
    for (size_t i = 0; i < listaDeAtracoes.size(); i++) {
        cout << i + 1 << ". " << listaDeAtracoes[i].nome << endl;
    }

    int escolha;
    cout << "Escolha uma atração: ";
    cin >> escolha;
    escolha--;

    if (escolha >= 0 && escolha < (int)listaDeAtracoes.size()) {
        if (tipoIngresso == "VIP")
            listaDeAtracoes[escolha].filaPrioritaria.push_back(cpf);
        else
            listaDeAtracoes[escolha].filaNormal.push_back(cpf);

        cout << "\n✅ Você entrou na fila de " << listaDeAtracoes[escolha].nome << "!\n";
    } else {
        cout << "❌ Opção inválida!\n";
    }
}

// 💡 Painel de controle (Etapa 4)
void interfacePainelControle() {
    system("clear");
    cout << "--- 4. Painel de Controle ---\n";

    for (auto &a : listaDeAtracoes) {
        cout << "\n🎠 " << a.nome << " (" << a.tipo << ")\n";
        cout << "Fila VIP: " << a.filaPrioritaria.size() << " pessoas\n";
        cout << "Fila Normal: " << a.filaNormal.size() << " pessoas\n";
        cout << "Total: " << a.filaPrioritaria.size() + a.filaNormal.size() << "\n";
    }
}
