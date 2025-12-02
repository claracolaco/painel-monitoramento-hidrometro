#pragma once
#include <vector>
#include "Usuario.hpp"

class UsuarioRepository {
public:
    UsuarioRepository();

    Usuario criar(const std::string& nome,
                  const std::string& email,
                  const std::string& endereco,
                  const std::string& perfil);

    bool remover(int idUsuario);

    Usuario* buscarPorId(int idUsuario);

    std::vector<Usuario> listarTodos() const;

private:
    std::vector<Usuario> usuarios_;
    int proximoId_;
};