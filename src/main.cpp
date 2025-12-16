#include <iostream>
#include "fachada/PainelMonitoramentoFacade.hpp"

int main() {
    std::cout << "=============================================\n";
    std::cout << "  Painel de Monitoramento de Hidrometros\n";
    std::cout << "=============================================\n\n";

    PainelMonitoramentoFacade painel;

    std::cout << "[ETAPA 1] Cadastro de usuario administrador\n";
    painel.cadastrarUsuario("Admin",
                            "admin@painel.com",
                            "Endereco de teste",
                            "ADMIN");

    std::cout << "\n[ETAPA 2] Registro de dois hidrometros (SHA 1 e SHA 2)\n";
    painel.registrarHidrometro(1,
                               "HID-001",
                               "Apartamento 101 (SHA Pedro)");
    painel.registrarHidrometro(1,
                               "HID-002",
                               "Apartamento 102 (SHA Sophia)");

    std::cout << "\n[ETAPA 3] Configuracao de limite de consumo para o usuario\n";
    painel.definirLimiteConsumoUsuario(1, 200.0);

    std::cout << "\n[ETAPA 4] Leituras de consumo por hidrometro\n";
    double c1 = painel.lerConsumoHidrometro(1); // SHA 1
    double c2 = painel.lerConsumoHidrometro(2); // SHA 2

    std::cout << "\n  Resumo das leituras:\n";
    std::cout << "    SHA Pedro  (hidrometro 1): " << c1 << " m3\n";
    std::cout << "    SHA Sophia (hidrometro 2): " << c2 << " m3\n";

    std::cout << "\n[ETAPA 5] Consolidacao por usuario\n";
    double totalUsuario = painel.consultarConsumoUsuario(1);
    std::cout << "  Consumo total do usuario 1: " << totalUsuario << " m3\n";

    std::cout << "\n=== Fim da demonstracao do painel ===\n";
    return 0;
}