#include "HidrometroRepository.hpp"

HidrometroRepository::HidrometroRepository()
    : proximoId_(1) {}

Hidrometro HidrometroRepository::registrar(int idUsuario,
                                           const std::string& numeroSerie,
                                           const std::string& localInstalacao) {
    Hidrometro h(proximoId_, idUsuario, numeroSerie, localInstalacao);
    hidrometros_.push_back(h);
    ++proximoId_;
    return h;
}

bool HidrometroRepository::remover(int idHidrometro) {
    for (auto it = hidrometros_.begin(); it != hidrometros_.end(); ++it) {
        if (it->id == idHidrometro) {
            hidrometros_.erase(it);
            return true;
        }
    }
    return false;
}

Hidrometro* HidrometroRepository::buscarPorId(int idHidrometro) {
    for (auto& h : hidrometros_) {
        if (h.id == idHidrometro) {
            return &h;
        }
    }
    return nullptr;
}

std::vector<Hidrometro> HidrometroRepository::listarPorUsuario(int idUsuario) const {
    std::vector<Hidrometro> resultado;
    for (const auto& h : hidrometros_) {
        if (h.idUsuario == idUsuario) {
            resultado.push_back(h);
        }
    }
    return resultado;
}

std::vector<Hidrometro> HidrometroRepository::listarTodos() const {
    return hidrometros_;
}