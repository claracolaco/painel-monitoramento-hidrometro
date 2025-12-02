#include "PainelMonitoramentoFacade.hpp"
#include <iostream>

// -------- Usuários --------

void PainelMonitoramentoFacade::cadastrarUsuario(const std::string& nome,
                                                 const std::string& email,
                                                 const std::string& endereco,
                                                 const std::string& perfil) {
    Usuario novo = usuarioRepository_.criar(nome, email, endereco, perfil);

    std::cout << "[Fachada] cadastrarUsuario: id=" << novo.id
              << " | " << novo.nome
              << " | " << novo.email
              << " | perfil=" << novo.perfil << "\n";
}

void PainelMonitoramentoFacade::removerUsuario(int idUsuario) {
    bool removido = usuarioRepository_.remover(idUsuario);

    std::cout << "[Fachada] removerUsuario: id=" << idUsuario
              << (removido ? " (removido)\n" : " (não encontrado)\n");
}

// -------- Hidrômetros --------

void PainelMonitoramentoFacade::registrarHidrometro(int idUsuario,
                                                    const std::string& numeroSerie,
                                                    const std::string& localInstalacao) {
    Hidrometro h = hidrometroRepository_.registrar(idUsuario, numeroSerie, localInstalacao);

    std::cout << "[Fachada] registrarHidrometro: id=" << h.id
              << " | usuario=" << h.idUsuario
              << " | serie=" << h.numeroSerie
              << " | local=" << h.localInstalacao << "\n";
}

void PainelMonitoramentoFacade::removerHidrometro(int idHidrometro) {
    bool removido = hidrometroRepository_.remover(idHidrometro);

    std::cout << "[Fachada] removerHidrometro: id=" << idHidrometro
              << (removido ? " (removido)\n" : " (não encontrado)\n");
}

// -------- Consumo / Leituras --------

double PainelMonitoramentoFacade::lerConsumoHidrometro(int idHidrometro) {
    std::cout << "[Fachada] lerConsumoHidrometro: id=" << idHidrometro << "\n";
    return 0.0; 
}

double PainelMonitoramentoFacade::consultarConsumoUsuario(int idUsuario) {
    std::cout << "[Fachada] consultarConsumoUsuario: usuario=" << idUsuario << "\n";
    return 0.0; 
}

// -------- Alertas --------

void PainelMonitoramentoFacade::definirLimiteConsumoUsuario(int idUsuario, double limite) {
    std::cout << "[Fachada] definirLimiteConsumoUsuario: usuario=" << idUsuario
              << " | limite=" << limite << "\n";
}