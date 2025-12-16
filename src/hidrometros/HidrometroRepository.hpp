#pragma once
#include <vector>
#include "Hidrometro.hpp"

class HidrometroRepository {
public:
    HidrometroRepository();

    Hidrometro registrar(int idUsuario,
                         const std::string& numeroSerie,
                         const std::string& localInstalacao);

    bool remover(int idHidrometro);

    Hidrometro* buscarPorId(int idHidrometro);

    std::vector<Hidrometro> listarPorUsuario(int idUsuario) const;

    std::vector<Hidrometro> listarTodos() const;

    bool definirDiretorioImagens(int idHidrometro, const std::string& diretorio);

private:
    std::vector<Hidrometro> hidrometros_;
    int proximoId_;
};