#pragma once
#include <string>

class Alerta {
public:
    int id;
    int idUsuario;
    std::string mensagem;
    double valorReferencia; // limite
    double consumoAtual;    // consumo no momento do alerta

    Alerta() = default;

    Alerta(int id,
           int idUsuario,
           const std::string& mensagem,
           double valorReferencia,
           double consumoAtual)
        : id(id),
          idUsuario(idUsuario),
          mensagem(mensagem),
          valorReferencia(valorReferencia),
          consumoAtual(consumoAtual) {}
};