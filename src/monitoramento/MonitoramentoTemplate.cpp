#include "MonitoramentoTemplate.hpp"

void MonitoramentoTemplate::executar(int ciclos, int intervaloMs) {
    for (int c = 1; c <= ciclos; ++c) {
        antesCiclo(c);
        processarItens();
        depoisCiclo(c);

        if (c < ciclos) {
            std::this_thread::sleep_for(std::chrono::milliseconds(intervaloMs));
        }
    }
}