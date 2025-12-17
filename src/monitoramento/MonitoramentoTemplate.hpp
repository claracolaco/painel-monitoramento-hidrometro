#pragma once
#include <chrono>
#include <thread>

class MonitoramentoTemplate {
public:
    virtual ~MonitoramentoTemplate() = default;

    // Template Method (fluxo fixo)
    void executar(int ciclos, int intervaloMs);

protected:
    // “ganchos” (subclasses personalizam)
    virtual void antesCiclo(int ciclo) {}
    virtual void processarItens() = 0;
    virtual void depoisCiclo(int ciclo) {}
};