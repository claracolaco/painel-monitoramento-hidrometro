#include "PainelCLI.hpp"
#include "InputUtils.hpp"
#include <iostream>

PainelCLI::PainelCLI(PainelMonitoramentoFacade& painel) : painel_(painel) {}

void PainelCLI::executar() {
    while (true) {
        std::cout << "\n=== PAINEL (CLI) ===\n"
                  << "1) Usuarios (CRUD)\n"
                  << "2) Hidrometros\n"
                  << "3) Consumo\n"
                  << "4) Alertas (limite)\n"
                  << "5) Monitoramento periodico\n"
                  << "6) Consultar logs\n"
                  << "0) Sair\n";

        int op = lerInt("Opcao: ");
        switch (op) {
            case 1: menuUsuarios(); break;
            case 2: menuHidrometros(); break;
            case 3: menuConsumo(); break;
            case 4: menuAlertas(); break;
            case 5: menuMonitoramento(); break;
            case 6: menuLogs(); break;
            case 0: std::cout << "Saindo...\n"; return;
            default: std::cout << "Opcao invalida.\n"; break;
        }
    }
}

void PainelCLI::menuUsuarios() {
    while (true) {
        std::cout << "\n--- USUARIOS ---\n"
                  << "1) Cadastrar\n"
                  << "2) Consultar\n"
                  << "3) Atualizar\n"
                  << "4) Remover (cascata)\n"
                  << "0) Voltar\n";
        int op = lerInt("Opcao: ");

        if (op == 0) return;

        if (op == 1) {
            auto nome = lerLinha("Nome: ");
            auto email = lerLinha("Email: ");
            auto endereco = lerLinha("Endereco: ");
            auto perfil = lerLinha("Perfil (ADMIN/COMUM): ");
            painel_.cadastrarUsuario(nome, email, endereco, perfil);
        } else if (op == 2) {
            int id = lerInt("ID usuario: ");
            painel_.consultarUsuario(id);
        } else if (op == 3) {
            int id = lerInt("ID usuario: ");
            auto nome = lerLinha("Novo nome: ");
            auto email = lerLinha("Novo email: ");
            auto endereco = lerLinha("Novo endereco: ");
            auto perfil = lerLinha("Novo perfil (ADMIN/COMUM): ");
            painel_.atualizarUsuario(id, nome, email, endereco, perfil);
        } else if (op == 4) {
            int id = lerInt("ID usuario: ");
            painel_.removerUsuario(id);
        } else {
            std::cout << "Opcao invalida.\n";
        }
    }
}

void PainelCLI::menuHidrometros() {
    while (true) {
        std::cout << "\n--- HIDROMETROS ---\n"
                  << "1) Registrar (associar a usuario)\n"
                  << "2) Listar do usuario\n"
                  << "3) Configurar diretorio de imagens\n"
                  << "4) Remover\n"
                  << "0) Voltar\n";
        int op = lerInt("Opcao: ");
        if (op == 0) return;

        if (op == 1) {
            int idUsuario = lerInt("ID usuario: ");
            auto serie = lerLinha("Numero de serie: ");
            auto local = lerLinha("Local instalacao: ");
            painel_.registrarHidrometro(idUsuario, serie, local);
        } else if (op == 2) {
            int idUsuario = lerInt("ID usuario: ");
            painel_.listarHidrometrosUsuario(idUsuario);
        } else if (op == 3) {
            int idH = lerInt("ID hidrometro: ");
            auto dir = lerLinha("Diretorio (ex: ../sha_sophia/Medicoes_sophia): ");
            painel_.configurarDiretorioImagensHidrometro(idH, dir);
        } else if (op == 4) {
            int idH = lerInt("ID hidrometro: ");
            painel_.removerHidrometro(idH);
        } else {
            std::cout << "Opcao invalida.\n";
        }
    }
}

void PainelCLI::menuConsumo() {
    while (true) {
        std::cout << "\n--- CONSUMO ---\n"
                  << "1) Ler consumo (1 hidrometro)\n"
                  << "2) Consultar consumo por usuario\n"
                  << "3) Consultar consumo por hidrometro\n"
                  << "0) Voltar\n";
        int op = lerInt("Opcao: ");
        if (op == 0) return;

        if (op == 1) {
            int idH = lerInt("ID hidrometro: ");
            painel_.lerConsumoHidrometro(idH);
        } else if (op == 2) {
            int idU = lerInt("ID usuario: ");
            painel_.consultarConsumoUsuario(idU);
        } else if (op == 3) {
            int idH = lerInt("ID hidrometro: ");
            painel_.consultarConsumoHidrometro(idH);
        } else {
            std::cout << "Opcao invalida.\n";
        }
    }
}

void PainelCLI::menuAlertas() {
    while (true) {
        std::cout << "\n--- ALERTAS ---\n"
                  << "1) Definir limite de consumo do usuario\n"
                  << "0) Voltar\n";
        int op = lerInt("Opcao: ");
        if (op == 0) return;

        if (op == 1) {
            int idU = lerInt("ID usuario: ");
            double limite = lerDouble("Limite (m3): ");
            painel_.definirLimiteConsumoUsuario(idU, limite);
        } else {
            std::cout << "Opcao invalida.\n";
        }
    }
}

void PainelCLI::menuMonitoramento() {
    int ciclos = lerInt("Ciclos: ");
    int intervalo = lerInt("Intervalo (ms): ");
    painel_.executarMonitoramentoPeriodico(ciclos, intervalo);
}

void PainelCLI::menuLogs() {
    int n = lerInt("Ultimas N linhas: ");
    painel_.consultarLogs(n);
}