/*#include <iostream>
#include "fachada/PainelMonitoramentoFacade.hpp"
#include <thread>
#include <chrono>
#include "notificacao/ConsoleAlertaObserver.hpp"
#include "notificacao/EmailAlertaObserver.hpp"


int main() {
    std::cout << "=============================================\n";
    std::cout << "  Painel de Monitoramento de Hidrometros\n";
    std::cout << "=============================================\n\n";

    PainelMonitoramentoFacade painel;

    ConsoleAlertaObserver obsConsole;
    EmailAlertaObserver obsEmail;

    painel.adicionarObserver(&obsConsole);
    painel.adicionarObserver(&obsEmail);


    std::cout << "[ETAPA 1] Cadastro de usuario administrador\n";
    painel.cadastrarUsuario("Admin",
                            "admin@painel.com",
                            "Endereco de teste",
                            "ADMIN");

    std::cout << "\n[ETAPA 2] Registro de dois hidrometros (SHA 1 e SHA 2)\n";
    painel.registrarHidrometro(1,
                               "HID-001",
                               "Apartamento 101 (SHA 1");
    painel.registrarHidrometro(1,
                               "HID-002",
                               "Apartamento 102 (SHA 2)");

    std::cout << "\n[ETAPA 3] Configuracao de limite de consumo para o usuario\n";
    painel.definirLimiteConsumoUsuario(1, 200.0);

    std::cout << "\n[ETAPA 4] Leituras de consumo por hidrometro\n";
    painel.configurarDiretorioImagensHidrometro(1, "../sha_sophia/Medicoes_sophia"); // SHA 1 - sophia
    painel.configurarDiretorioImagensHidrometro(2, "../sha_anna/medicoes_hidrometros");    // SHA 2 - anna

    std::cout << "\n[ETAPA 4B] Coleta de leituras (3 ciclos)\n";
for (int i = 1; i <= 3; i++) {
    std::cout << "\n--- Ciclo " << i << " ---\n";
    double l1 = painel.lerConsumoHidrometro(1);
    double l2 = painel.lerConsumoHidrometro(2);

    std::cout << "SHA 1: " << l1 << " m3\n";
    std::cout << "SHA 2:   " << l2 << " m3\n";

    std::this_thread::sleep_for(std::chrono::seconds(2));
}

    std::cout << "\n[ETAPA 5] Consolidacao por usuario\n";
    double totalUsuario = painel.consultarConsumoUsuario(1);
    std::cout << "  Consumo total do usuario 1: " << totalUsuario << " m3\n";

    std::cout << "\n[ETAPA 6] Monitoramento periodico (Template Method)\n";
    painel.executarMonitoramentoPeriodico(3, 2000);

    std::cout << "\n[ETAPA 7] Teste de remocao em cascata\n";
    painel.removerHidrometro(1);
    painel.consultarConsumoHidrometro(1);

    painel.removerUsuario(1);
    painel.consultarConsumoUsuario(1);

    std::cout << "\n[ETAPA 8] Consulta de logs\n";
    painel.consultarLogs(15);

    std::cout << "\n[ETAPA 9] Monitoramento periodico (Template Method)\n";
    painel.executarMonitoramentoPeriodico(3, 2000);


    std::cout << "\n=== Fim da demonstracao do painel ===\n";
    return 0;
}*/

#include "fachada/PainelMonitoramentoFacade.hpp"
#include "cli/PainelCLI.hpp"
#include "notificacao/ConsoleAlertaObserver.hpp"
#include "notificacao/EmailAlertaObserver.hpp"

int main() {
    PainelMonitoramentoFacade painel;

    // Observers (Observer pattern)
    ConsoleAlertaObserver obsConsole;
    EmailAlertaObserver obsEmail;
    painel.adicionarObserver(&obsConsole);
    painel.adicionarObserver(&obsEmail);

    PainelCLI cli(painel);
    cli.executar();
    return 0;
}
