#pragma once
#include <string>

class Hidrometro {
public:
    int id;
    int idUsuario;
    std::string numeroSerie;
    std::string localInstalacao;

    std::string diretorioImagens;

    std::string ultimoArquivoProcessado;

    Hidrometro() = default;

    Hidrometro(int id,
               int idUsuario,
               const std::string& numeroSerie,
               const std::string& localInstalacao)
        : id(id),
          idUsuario(idUsuario),
          numeroSerie(numeroSerie),
          localInstalacao(localInstalacao),
          diretorioImagens(""),
          ultimoArquivoProcessado("") {}
};