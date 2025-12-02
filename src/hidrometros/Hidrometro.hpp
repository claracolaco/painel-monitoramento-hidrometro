#pragma once
#include <string>

class Hidrometro {
public:
    int id;
    int idUsuario;           // dono / responsável
    std::string numeroSerie;
    std::string localInstalacao;

    Hidrometro() = default;

    Hidrometro(int id,
               int idUsuario,
               const std::string& numeroSerie,
               const std::string& localInstalacao)
        : id(id),
          idUsuario(idUsuario),
          numeroSerie(numeroSerie),
          localInstalacao(localInstalacao) {}
};