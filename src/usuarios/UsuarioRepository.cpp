#include "UsuarioRepository.hpp"

UsuarioRepository::UsuarioRepository()
    : proximoId_(1) {}

Usuario UsuarioRepository::criar(const std::string& nome,
                                 const std::string& email,
                                 const std::string& endereco,
                                 const std::string& perfil) {
    Usuario u(proximoId_, nome, email, endereco, perfil);
    usuarios_.push_back(u);
    ++proximoId_;
    return u;
}

bool UsuarioRepository::remover(int idUsuario) {
    for (auto it = usuarios_.begin(); it != usuarios_.end(); ++it) {
        if (it->id == idUsuario) {
            usuarios_.erase(it);
            return true;
        }
    }
    return false;
}

Usuario* UsuarioRepository::buscarPorId(int idUsuario) {
    for (auto& u : usuarios_) {
        if (u.id == idUsuario) {
            return &u;
        }
    }
    return nullptr;
}

std::vector<Usuario> UsuarioRepository::listarTodos() const {
    return usuarios_;
}