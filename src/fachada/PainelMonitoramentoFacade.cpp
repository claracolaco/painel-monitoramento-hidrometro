#include "PainelMonitoramentoFacade.hpp"
#include <iostream>

// -------- Usuários --------

void PainelMonitoramentoFacade::cadastrarUsuario(const std::string& nome,
                                                 const std::string& email,
                                                 const std::string& endereco,
                                                 const std::string& perfil) {
    std::cout << "[Fachada] cadastrarUsuario: " << nome
              << " | " << email
              << " | perfil=" << perfil << "\n";
}

void PainelMonitoramentoFacade::removerUsuario(int idUsuario) {
    std::cout << "[Fachada] removerUsuario: id=" << idUsuario << "\n";
}

// -------- Hidrômetros --------

void PainelMonitoramentoFacade::registrarHidrometro(int idUsuario,
                                                    const std::string& numeroSerie,
                                                    const std::string& localInstalacao) {
    std::cout << "[Fachada] registrarHidrometro: usuario=" << idUsuario
              << " | serie=" << numeroSerie
              << " | local=" << localInstalacao << "\n";
}

void PainelMonitoramentoFacade::removerHidrometro(int idHidrometro) {
    std::cout << "[Fachada] removerHidrometro: id=" << idHidrometro << "\n";
}

// -------- Consumo / Leituras --------

double PainelMonitoramentoFacade::lerConsumoHidrometro(int idHidrometro) {
    std::cout << "[Fachada] lerConsumoHidrometro: id=" << idHidrometro << "\n";
    return 0.0; // stub por enquanto
}

double PainelMonitoramentoFacade::consultarConsumoUsuario(int idUsuario) {
    std::cout << "[Fachada] consultarConsumoUsuario: usuario=" << idUsuario << "\n";
    return 0.0; // stub por enquanto
}

// -------- Alertas --------

void PainelMonitoramentoFacade::definirLimiteConsumoUsuario(int idUsuario, double limite) {
    std::cout << "[Fachada] definirLimiteConsumoUsuario: usuario=" << idUsuario
              << " | limite=" << limite << "\n";
}