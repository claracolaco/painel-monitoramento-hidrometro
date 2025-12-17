#pragma once
#include "MonitoramentoTemplate.hpp"
#include <vector>

class PainelMonitoramentoFacade;

class MonitoramentoPainel : public MonitoramentoTemplate {
public:
    MonitoramentoPainel(PainelMonitoramentoFacade& painel, std::vector<int> idsHidrometros);

protected:
    void antesCiclo(int ciclo) override;
    void processarItens() override;
    void depoisCiclo(int ciclo) override;

private:
    PainelMonitoramentoFacade& painel_;
    std::vector<int> ids_;
};