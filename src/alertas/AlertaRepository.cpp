#include "AlertaRepository.hpp"

AlertaRepository::AlertaRepository()
    : proximoId_(1) {}

Alerta AlertaRepository::registrar(int idUsuario,
                                   const std::string& mensagem,
                                   double valorReferencia,
                                   double consumoAtual) {
    Alerta a(proximoId_, idUsuario, mensagem, valorReferencia, consumoAtual);
    alertas_.push_back(a);
    ++proximoId_;
    return a;
}

std::vector<Alerta> AlertaRepository::listarPorUsuario(int idUsuario) const {
    std::vector<Alerta> resultado;
    for (const auto& a : alertas_) {
        if (a.idUsuario == idUsuario) {
            resultado.push_back(a);
        }
    }
    return resultado;
}

std::vector<Alerta> AlertaRepository::listarTodos() const {
    return alertas_;
}