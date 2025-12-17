#pragma once
#include <vector>
#include <string>
#include "Alerta.hpp"

class AlertaRepository {
public:
    AlertaRepository();

    Alerta registrar(int idUsuario,
                     const std::string& mensagem,
                     double valorReferencia,
                     double consumoAtual);

    std::vector<Alerta> listarPorUsuario(int idUsuario) const;
    std::vector<Alerta> listarTodos() const;

    int removerPorUsuario(int idUsuario);

private:
    std::vector<Alerta> alertas_;
    int proximoId_;
};