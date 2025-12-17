#include "PainelMonitoramentoFacade.hpp"
#include <iostream>
#include "../imagens/SimpleImageReader.hpp"
#include "../hidrometros/Hidrometro.hpp"
#include "../consumo/LeituraConsumo.hpp"
#include "../alertas/Alerta.hpp"
#include <filesystem>
#include <optional>

static std::optional<std::string> encontrarImagemMaisRecente(const std::string& diretorio) {
    namespace fs = std::filesystem;

    if (diretorio.empty()) return std::nullopt;
    if (!fs::exists(diretorio) || !fs::is_directory(diretorio)) return std::nullopt;

    fs::path maisRecente;
    fs::file_time_type tempoMaisRecente;
    bool achou = false;

    for (const auto& entry : fs::directory_iterator(diretorio)) {
        if (!entry.is_regular_file()) continue;

        fs::path p = entry.path();
        auto ext = p.extension().string();

        // aceita bmp/png/jpg/jpeg
        if (ext != ".bmp" && ext != ".png" && ext != ".jpg" && ext != ".jpeg") continue;

        auto t = fs::last_write_time(p);
        if (!achou || t > tempoMaisRecente) {
            achou = true;
            tempoMaisRecente = t;
            maisRecente = p;
        }
    }

    if (!achou) return std::nullopt;
    return maisRecente.string();
}


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

    std::cout << "  [USUARIO] Cadastrado: id=" << novo.id
              << " | nome=" << novo.nome
              << " | email=" << novo.email
              << " | perfil=" << novo.perfil << "\n";
}

void PainelMonitoramentoFacade::removerUsuario(int idUsuario) {
    bool removido = usuarioRepository_.remover(idUsuario);

    std::cout << "  [USUARIO] Remocao: id=" << idUsuario
              << (removido ? " (removido)\n" : " (nao encontrado)\n");
}

// -------- Hidrômetros --------

void PainelMonitoramentoFacade::registrarHidrometro(int idUsuario,
                                                    const std::string& numeroSerie,
                                                    const std::string& localInstalacao) {
    Hidrometro h = hidrometroRepository_.registrar(idUsuario, numeroSerie, localInstalacao);

    std::cout << "  [HIDROMETRO] Registrado: id=" << h.id
              << " | usuario=" << h.idUsuario
              << " | serie=" << h.numeroSerie
              << " | local=" << h.localInstalacao << "\n";
}

void PainelMonitoramentoFacade::removerHidrometro(int idHidrometro) {
    bool removido = hidrometroRepository_.remover(idHidrometro);

    std::cout << "  [HIDROMETRO] Remocao: id=" << idHidrometro
              << (removido ? " (removido)\n" : " (nao encontrado)\n");
}

void PainelMonitoramentoFacade::configurarDiretorioImagensHidrometro(int idHidrometro,
                                                                     const std::string& diretorio) {
    bool ok = hidrometroRepository_.definirDiretorioImagens(idHidrometro, diretorio);

    if (ok) {
        std::cout << "  [HIDRÔMETRO] Diretorio de imagens configurado: id=" << idHidrometro
                  << " | dir=" << diretorio << "\n";
    } else {
        std::cout << "  [HIDRÔMETRO] Falha ao configurar diretorio (nao encontrado): id="
                  << idHidrometro << "\n";
    }
}

// -------- Consumo / Leituras --------

double PainelMonitoramentoFacade::lerConsumoHidrometro(int idHidrometro) {
    Hidrometro* h = hidrometroRepository_.buscarPorId(idHidrometro);
    if (!h) {
        std::cout << "  [LEITURA] Hidrometro nao encontrado: id="
                  << idHidrometro << "\n";
        return 0.0;
    }

    // pega o caminho da imagem mais recente do diretório do SHA
    auto img = encontrarImagemMaisRecente(h->diretorioImagens);

    if (!img.has_value()) {
        std::cout << "  [LEITURA] Nenhuma imagem disponivel para o hidrometro " << h->id
                << " (dir=" << h->diretorioImagens << ")\n";
        return 0.0;
    }

    // evita processar a mesma imagem repetidamente
    if (*img == h->ultimoArquivoProcessado) {
        std::cout << "  [LEITURA] Sem nova imagem para o hidrometro " << h->id << "\n";
        return 0.0;
    }

    double valor = imageReader_->lerConsumoDaImagem(*img);
    consumoRepository_.registrarLeitura(h->id, h->idUsuario, valor);
    h->ultimoArquivoProcessado = *img;

    auto leiturasUsuario = consumoRepository_.listarPorUsuario(h->idUsuario);
    double totalUsuario = 0.0;
    for (const auto& leitura : leiturasUsuario) {
        totalUsuario += leitura.valor;
    }

    std::cout << "  [LEITURA] Hidrometro " << h->id
              << " (usuario=" << h->idUsuario << "): "
              << "consumoLido=" << valor
              << " | consumoTotalUsuario=" << totalUsuario << "\n";

    // Verifica limite e gera alerta, se necessário
    auto it = limitesConsumoPorUsuario_.find(h->idUsuario);
    if (it != limitesConsumoPorUsuario_.end()) {
        double limite = it->second;
        if (totalUsuario > limite) {
            std::string mensagem = "Limite de consumo excedido para o usuario " +
                                   std::to_string(h->idUsuario);

            Alerta alerta = alertaRepository_.registrar(
                h->idUsuario,
                mensagem,
                limite,
                totalUsuario
            );

            std::cout << "    [ALERTA] id=" << alerta.id
                      << " | usuario=" << alerta.idUsuario
                      << " | limite=" << alerta.valorReferencia
                      << " | consumoAtual=" << alerta.consumoAtual
                      << " | mensagem=" << alerta.mensagem << "\n";
        }
    }

    return valor;
}

double PainelMonitoramentoFacade::consultarConsumoUsuario(int idUsuario) {
    auto leituras = consumoRepository_.listarPorUsuario(idUsuario);

    double soma = 0.0;
    for (const auto& leitura : leituras) {
        soma += leitura.valor;
    }

    std::cout << "  [CONSULTA] Consumo do usuario " << idUsuario
              << ": leituras=" << leituras.size()
              << " | consumoTotal=" << soma << "\n";

    return soma;
}

// -------- Alertas --------

void PainelMonitoramentoFacade::definirLimiteConsumoUsuario(int idUsuario, double limite) {
    limitesConsumoPorUsuario_[idUsuario] = limite;

    std::cout << "  [ALERTA] Limite configurado para o usuario " << idUsuario
              << ": " << limite << " m3\n";
}
