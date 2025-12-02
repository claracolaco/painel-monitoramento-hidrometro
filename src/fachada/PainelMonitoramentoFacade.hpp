#pragma once
#include <string>
#include "../usuarios/UsuarioRepository.hpp"

class PainelMonitoramentoFacade {
public:
    // ---- Usuários ----
    void cadastrarUsuario(const std::string& nome,
                          const std::string& email,
                          const std::string& endereco,
                          const std::string& perfil);

    void removerUsuario(int idUsuario);

    // ---- Hidrômetros ----
    void registrarHidrometro(int idUsuario,
                             const std::string& numeroSerie,
                             const std::string& localInstalacao);

    void removerHidrometro(int idHidrometro);

    // ---- Consumo / Leituras ----
    double lerConsumoHidrometro(int idHidrometro);
    double consultarConsumoUsuario(int idUsuario);

    // ---- Alertas ----
    void definirLimiteConsumoUsuario(int idUsuario, double limite);

private:
    UsuarioRepository usuarioRepository_; 
};