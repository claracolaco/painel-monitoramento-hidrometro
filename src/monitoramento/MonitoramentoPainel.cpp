#include "MonitoramentoPainel.hpp"
#include "../fachada/PainelMonitoramentoFacade.hpp"
#include <iostream>

MonitoramentoPainel::MonitoramentoPainel(PainelMonitoramentoFacade& painel, std::vector<int> idsHidrometros)
    : painel_(painel), ids_(std::move(idsHidrometros)) {}

void MonitoramentoPainel::antesCiclo(int ciclo) {
    std::cout << "\n--- CICLO " << ciclo << " ---\n";
}

void MonitoramentoPainel::processarItens() {
    for (int id : ids_) {
        painel_.lerConsumoHidrometro(id);
    }
}

void MonitoramentoPainel::depoisCiclo(int /*ciclo*/) {

}