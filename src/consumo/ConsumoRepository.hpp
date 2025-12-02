#pragma once
#include <vector>
#include "LeituraConsumo.hpp"

class ConsumoRepository {
public:
    ConsumoRepository();

    LeituraConsumo registrarLeitura(int idHidrometro,
                                    int idUsuario,
                                    double valor);

    std::vector<LeituraConsumo> listarPorUsuario(int idUsuario) const;

    std::vector<LeituraConsumo> listarPorHidrometro(int idHidrometro) const;

private:
    std::vector<LeituraConsumo> leituras_;
    int proximoId_;
};