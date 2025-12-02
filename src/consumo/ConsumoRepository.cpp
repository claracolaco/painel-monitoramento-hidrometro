#include "ConsumoRepository.hpp"

ConsumoRepository::ConsumoRepository()
    : proximoId_(1) {}

LeituraConsumo ConsumoRepository::registrarLeitura(int idHidrometro,
                                                   int idUsuario,
                                                   double valor) {
    LeituraConsumo l(proximoId_, idHidrometro, idUsuario, valor);
    leituras_.push_back(l);
    ++proximoId_;
    return l;
}

std::vector<LeituraConsumo> ConsumoRepository::listarPorUsuario(int idUsuario) const {
    std::vector<LeituraConsumo> resultado;
    for (const auto& l : leituras_) {
        if (l.idUsuario == idUsuario) {
            resultado.push_back(l);
        }
    }
    return resultado;
}

std::vector<LeituraConsumo> ConsumoRepository::listarPorHidrometro(int idHidrometro) const {
    std::vector<LeituraConsumo> resultado;
    for (const auto& l : leituras_) {
        if (l.idHidrometro == idHidrometro) {
            resultado.push_back(l);
        }
    }
    return resultado;
}