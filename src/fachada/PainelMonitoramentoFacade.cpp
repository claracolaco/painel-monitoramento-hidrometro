#include "PainelMonitoramentoFacade.hpp"
#include <iostream>
#include "../imagens/SimpleImageReader.hpp"
#include "../hidrometros/Hidrometro.hpp"
#include "../consumo/LeituraConsumo.hpp"

// -------- Construtor / Destrutor --------

PainelMonitoramentoFacade::PainelMonitoramentoFacade()
    : imageReader_(new SimpleImageReader()) {}

PainelMonitoramentoFacade::~PainelMonitoramentoFacade() {
    delete imageReader_;
}

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
    Hidrometro* h = hidrometroRepository_.buscarPorId(idHidrometro);
    if (!h) {
        std::cout << "[Fachada] lerConsumoHidrometro: hidrômetro não encontrado: id="
                  << idHidrometro << "\n";
        return 0.0;
    }

    // Caminho fictício de imagem
    std::string caminhoImagem = "data/hidrometro_" + std::to_string(idHidrometro) + ".png";

    double valor = imageReader_->lerConsumoDaImagem(caminhoImagem);

    consumoRepository_.registrarLeitura(h->id, h->idUsuario, valor);

    std::cout << "[Fachada] lerConsumoHidrometro: id=" << h->id
              << " | usuario=" << h->idUsuario
              << " | consumoLido=" << valor << "\n";

    return valor;
}

double PainelMonitoramentoFacade::consultarConsumoUsuario(int idUsuario) {
    auto leituras = consumoRepository_.listarPorUsuario(idUsuario);

    double soma = 0.0;
    for (const auto& leitura : leituras) {
        soma += leitura.valor;
    }

    std::cout << "[Fachada] consultarConsumoUsuario: usuario=" << idUsuario
              << " | leituras=" << leituras.size()
              << " | consumoTotal=" << soma << "\n";

    return soma;
}

// -------- Alertas --------

void PainelMonitoramentoFacade::definirLimiteConsumoUsuario(int idUsuario, double limite) {
    std::cout << "[Fachada] definirLimiteConsumoUsuario: usuario=" << idUsuario
              << " | limite=" << limite << "\n";
}