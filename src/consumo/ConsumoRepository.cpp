#include "ConsumoRepository.hpp"
#include <algorithm>


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

int ConsumoRepository::removerPorUsuario(int idUsuario) {
    auto antes = leituras_.size();
    leituras_.erase(
        std::remove_if(leituras_.begin(), leituras_.end(),
            [&](const LeituraConsumo& l){ return l.idUsuario == idUsuario; }),
        leituras_.end()
    );
    return static_cast<int>(antes - leituras_.size());
}

int ConsumoRepository::removerPorHidrometro(int idHidrometro) {
    auto antes = leituras_.size();
    leituras_.erase(
        std::remove_if(leituras_.begin(), leituras_.end(),
            [&](const LeituraConsumo& l){ return l.idHidrometro == idHidrometro; }),
        leituras_.end()
    );
    return static_cast<int>(antes - leituras_.size());
}