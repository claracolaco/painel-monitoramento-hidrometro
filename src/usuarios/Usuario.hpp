#pragma once
#include <string>

class Usuario {
public:
    int id;
    std::string nome;
    std::string email;
    std::string endereco;
    std::string perfil; // "ADMIN" ou "COMUM"

    Usuario() = default;

    Usuario(int id,
            const std::string& nome,
            const std::string& email,
            const std::string& endereco,
            const std::string& perfil)
        : id(id),
          nome(nome),
          email(email),
          endereco(endereco),
          perfil(perfil) {}
};