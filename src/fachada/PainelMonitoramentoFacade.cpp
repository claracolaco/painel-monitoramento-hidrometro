#include "PainelMonitoramentoFacade.hpp"
#include <iostream>
#include "../imagens/SimpleImageReader.hpp"
#include "../hidrometros/Hidrometro.hpp"
#include "../consumo/LeituraConsumo.hpp"
#include "../alertas/Alerta.hpp"
#include <filesystem>
#include <optional>
#include "../log/Logger.hpp"
#include <fstream>
#include <deque>
#include "../monitoramento/MonitoramentoPainel.hpp"


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

    Logger::instance().info("Usuario cadastrado: nome=" + nome + " email=" + email + " perfil=" + perfil);
}

void PainelMonitoramentoFacade::removerUsuario(int idUsuario) {
    Usuario* u = usuarioRepository_.buscarPorId(idUsuario);
    if (!u) {
        std::cout << "  [USUARIO] Remocao: id=" << idUsuario << " (nao encontrado)\n";
        Logger::instance().warn("Tentativa de remover usuario inexistente: id=" + std::to_string(idUsuario));
        return;
    }

    // 1) Remover hidrômetros do usuário (e leituras de cada hidrômetro)
    auto hs = hidrometroRepository_.listarPorUsuario(idUsuario);
    int totalLeiturasRem = 0;

    for (const auto& h : hs) {
        totalLeiturasRem += consumoRepository_.removerPorHidrometro(h.id);
        hidrometroRepository_.remover(h.id);
    }

    // 2) Remover possíveis leituras órfãs por usuário (segurança)
    totalLeiturasRem += consumoRepository_.removerPorUsuario(idUsuario);

    // 3) Remover alertas
    int alertasRem = alertaRepository_.removerPorUsuario(idUsuario);

    // 4) Remover limite configurado
    limitesConsumoPorUsuario_.erase(idUsuario);

    // 5) Remover usuário
    bool removido = usuarioRepository_.remover(idUsuario);

    std::cout << "  [USUARIO] Remocao: id=" << idUsuario
              << (removido ? " (removido)" : " (falhou)")
              << " | hidrometrosRemovidos=" << hs.size()
              << " | leiturasRemovidas=" << totalLeiturasRem
              << " | alertasRemovidos=" << alertasRem << "\n";

    Logger::instance().info("Usuario removido (cascata): id=" + std::to_string(idUsuario));
}

void PainelMonitoramentoFacade::consultarUsuario(int idUsuario) {
    Usuario* u = usuarioRepository_.buscarPorId(idUsuario);
    if (!u) {
        std::cout << "  [USUARIO] Consulta: id=" << idUsuario << " (nao encontrado)\n";
        return;
    }

    std::cout << "  [USUARIO] Consulta: id=" << u->id
              << " | nome=" << u->nome
              << " | email=" << u->email
              << " | endereco=" << u->endereco
              << " | perfil=" << u->perfil << "\n";

    auto hs = hidrometroRepository_.listarPorUsuario(idUsuario);
    std::cout << "    [USUARIO] Hidrometros (" << hs.size() << "):\n";
    for (const auto& h : hs) {
        std::cout << "      - id=" << h.id
                  << " | serie=" << h.numeroSerie
                  << " | local=" << h.localInstalacao
                  << " | dir=" << (h.diretorioImagens.empty() ? "<nao definido>" : h.diretorioImagens)
                  << "\n";
    }

    auto leituras = consumoRepository_.listarPorUsuario(idUsuario);
    double total = 0.0;
    for (const auto& l : leituras) total += l.valor;

    std::cout << "    [USUARIO] Leituras (" << leituras.size()
              << ") | consumoTotal=" << total << " m3\n";

    auto alertas = alertaRepository_.listarPorUsuario(idUsuario);
    std::cout << "    [USUARIO] Alertas (" << alertas.size() << "):\n";
    for (const auto& a : alertas) {
        std::cout << "      - id=" << a.id
                  << " | limite=" << a.valorReferencia
                  << " | consumoAtual=" << a.consumoAtual
                  << " | msg=" << a.mensagem << "\n";
    }
}

void PainelMonitoramentoFacade::atualizarUsuario(int idUsuario,
                                                 const std::string& nome,
                                                 const std::string& email,
                                                 const std::string& endereco,
                                                 const std::string& perfil) {
    bool ok = usuarioRepository_.atualizar(idUsuario, nome, email, endereco, perfil);

    std::cout << "  [USUARIO] Atualizacao: id=" << idUsuario
              << (ok ? " (ok)\n" : " (nao encontrado)\n");
}

void PainelMonitoramentoFacade::listarHidrometrosUsuario(int idUsuario) {
    auto hs = hidrometroRepository_.listarPorUsuario(idUsuario);
    std::cout << "  [HIDROMETRO] Lista do usuario " << idUsuario
              << " (" << hs.size() << "):\n";
    for (const auto& h : hs) {
        std::cout << "    - id=" << h.id
                  << " | serie=" << h.numeroSerie
                  << " | local=" << h.localInstalacao << "\n";
    }
}

double PainelMonitoramentoFacade::consultarConsumoHidrometro(int idHidrometro) {
    auto leituras = consumoRepository_.listarPorHidrometro(idHidrometro);

    double soma = 0.0;
    for (const auto& l : leituras) soma += l.valor;

    std::cout << "  [CONSULTA] Consumo do hidrometro " << idHidrometro
              << ": leituras=" << leituras.size()
              << " | consumoTotal=" << soma << " m3\n";
    return soma;
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

    Logger::instance().info("Hidrometro registrado: usuario=" + std::to_string(idUsuario) +
                        " serie=" + numeroSerie + " local=" + localInstalacao);
}

void PainelMonitoramentoFacade::removerHidrometro(int idHidrometro) {
    Hidrometro* h = hidrometroRepository_.buscarPorId(idHidrometro);
    if (!h) {
        std::cout << "  [HIDROMETRO] Remocao: id=" << idHidrometro << " (nao encontrado)\n";
        return;
    }

    int leiturasRem = consumoRepository_.removerPorHidrometro(idHidrometro);
    bool removido = hidrometroRepository_.remover(idHidrometro);

    std::cout << "  [HIDROMETRO] Remocao: id=" << idHidrometro
              << (removido ? " (removido)" : " (falhou)")
              << " | leiturasRemovidas=" << leiturasRem << "\n";
    
    Logger::instance().info("Hidrometro removido: id=" + std::to_string(idHidrometro));
}

void PainelMonitoramentoFacade::configurarDiretorioImagensHidrometro(int idHidrometro,
                                                                     const std::string& diretorio) {
    bool ok = hidrometroRepository_.definirDiretorioImagens(idHidrometro, diretorio);

    if (ok) {
        std::cout << "  [HIDRÔMETRO] Diretorio de imagens configurado: id=" << idHidrometro
                  << " | dir=" << diretorio << "\n";
        Logger::instance().info("Diretorio de imagens definido: hidrometro=" + std::to_string(idHidrometro) +
                        " dir=" + diretorio);

    } else {
        std::cout << "  [HIDRÔMETRO] Falha ao configurar diretorio (nao encontrado): id="
                  << idHidrometro << "\n";
        Logger::instance().warn("Falha ao configurar diretorio: hidrometro=" + std::to_string(idHidrometro));
    }
}

// -------- Consumo / Leituras --------

double PainelMonitoramentoFacade::lerConsumoHidrometro(int idHidrometro) {
    Hidrometro* h = hidrometroRepository_.buscarPorId(idHidrometro);
    if (!h) {
        std::cout << "  [LEITURA] Hidrometro nao encontrado: id="
                  << idHidrometro << "\n";
        Logger::instance().warn("Leitura falhou: hidrometro inexistente id=" + std::to_string(idHidrometro));
        return 0.0;
    }

    // pega o caminho da imagem mais recente do diretório do SHA
    auto img = encontrarImagemMaisRecente(h->diretorioImagens);

    if (!img.has_value()) {
        std::cout << "  [LEITURA] Nenhuma imagem disponivel para o hidrometro " << h->id
                << " (dir=" << h->diretorioImagens << ")\n";
        Logger::instance().info("Nenhuma imagem disponivel: hidrometro=" + std::to_string(h->id) +
                        " dir=" + h->diretorioImagens);
        return 0.0;
    }

    // evita processar a mesma imagem repetidamente
    if (*img == h->ultimoArquivoProcessado) {
        std::cout << "  [LEITURA] Sem nova imagem para o hidrometro " << h->id << "\n";
        Logger::instance().info("Sem nova imagem: hidrometro=" + std::to_string(idHidrometro));
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
    
    Logger::instance().info("Leitura realizada: hidrometro=" + std::to_string(h->id) +
                        " valor=" + std::to_string(valor) +
                        " arquivo=" + *img);

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

            Logger::instance().warn("ALERTA: usuario=" + std::to_string(h->idUsuario) +
                        " limite=" + std::to_string(limite) +
                        " consumoAtual=" + std::to_string(totalUsuario));

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

    Logger::instance().info("Limite definido: usuario=" + std::to_string(idUsuario) +
                            " limite=" + std::to_string(limite));

    std::cout << "  [ALERTA] Limite configurado para o usuario " << idUsuario
              << ": " << limite << " m3\n";
}



void PainelMonitoramentoFacade::consultarLogs(int ultimasN) {
    std::ifstream in("data/log.txt");
    if (!in.is_open()) {
        std::cout << "  [LOG] Nao foi possivel abrir data/log.txt\n";
        Logger::instance().warn("Consulta de logs falhou: arquivo data/log.txt nao encontrado");
        return;
    }

    std::deque<std::string> ultimas;
    std::string linha;

    while (std::getline(in, linha)) {
        ultimas.push_back(linha);
        if ((int)ultimas.size() > ultimasN) ultimas.pop_front();
    }

    std::cout << "  [LOG] Ultimas " << ultimas.size() << " linhas:\n";
    for (const auto& l : ultimas) {
        std::cout << "    " << l << "\n";
    }

    Logger::instance().info("Logs consultados: ultimasN=" + std::to_string(ultimasN));
}


void PainelMonitoramentoFacade::executarMonitoramentoPeriodico(int ciclos, int intervaloMs) {
    auto hs = hidrometroRepository_.listarTodos();
    std::vector<int> ids;
    ids.reserve(hs.size());

    for (const auto& h : hs) ids.push_back(h.id);

    std::cout << "\n[MONITORAMENTO] Iniciando: ciclos=" << ciclos
              << " intervaloMs=" << intervaloMs
              << " hidrometros=" << ids.size() << "\n";

    Logger::instance().info("Monitoramento iniciado: ciclos=" + std::to_string(ciclos) +
                            " intervaloMs=" + std::to_string(intervaloMs) +
                            " hidrometros=" + std::to_string(ids.size()));

    MonitoramentoPainel m(*this, ids);
    m.executar(ciclos, intervaloMs);

    Logger::instance().info("Monitoramento finalizado");
}
