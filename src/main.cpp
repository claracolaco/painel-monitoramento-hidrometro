#include <iostream>
#include "fachada/PainelMonitoramentoFacade.hpp"

int main() {
    std::cout << "Painel de Monitoramento de Hidrômetros - inicializado.\n\n";

    PainelMonitoramentoFacade painel;

    painel.cadastrarUsuario("Admin",
                            "admin@painel.com",
                            "Endereço de teste",
                            "ADMIN");

    painel.registrarHidrometro(1,
                               "HID-001",
                               "Apartamento 101");

    double consumo = painel.lerConsumoHidrometro(1);
    std::cout << "Consumo lido (stub): " << consumo << " m3\n";

    painel.definirLimiteConsumoUsuario(1, 10.0);

    return 0;
}