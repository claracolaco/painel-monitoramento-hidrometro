#pragma once
#include "../fachada/PainelMonitoramentoFacade.hpp"

class PainelCLI {
public:
    explicit PainelCLI(PainelMonitoramentoFacade& painel);
    void executar();

private:
    PainelMonitoramentoFacade& painel_;

    void menuUsuarios();
    void menuHidrometros();
    void menuConsumo();
    void menuAlertas();
    void menuMonitoramento();
    void menuLogs();
};