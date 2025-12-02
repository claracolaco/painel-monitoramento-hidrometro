#include <iostream>
#include "fachada/PainelMonitoramentoFacade.hpp"

int main() {
    std::cout << "Painel de Monitoramento de Hidrometros - inicializado.\n\n";

    PainelMonitoramentoFacade painel;

    painel.cadastrarUsuario("Admin",
                            "admin@painel.com",
                            "Endereço de teste",
                            "ADMIN");

    painel.registrarHidrometro(1,
                               "HID-001",
                               "Apartamento 101");

    painel.definirLimiteConsumoUsuario(1, 200.0);

    double c1 = painel.lerConsumoHidrometro(1);
    double c2 = painel.lerConsumoHidrometro(1);

    std::cout << "Leituras individuais: " << c1 << " m3, " << c2 << " m3\n";

    double totalUsuario = painel.consultarConsumoUsuario(1);
    std::cout << "Consumo total do usuario 1: " << totalUsuario << " m3\n";

    return 0;
}