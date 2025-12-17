#pragma once
#include <string>
#include <unordered_map>
#include "../usuarios/UsuarioRepository.hpp"
#include "../hidrometros/HidrometroRepository.hpp"
#include "../consumo/ConsumoRepository.hpp"
#include "../alertas/AlertaRepository.hpp"

// Forward declaration da Strategy
class ImageReader;

class PainelMonitoramentoFacade {
public:
    PainelMonitoramentoFacade();
    ~PainelMonitoramentoFacade();

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
    void configurarDiretorioImagensHidrometro(int idHidrometro, const std::string& diretorio);

    // ---- Consumo / Leituras ----
    double lerConsumoHidrometro(int idHidrometro);
    double consultarConsumoUsuario(int idUsuario);

    // ---- Alertas ----
    void definirLimiteConsumoUsuario(int idUsuario, double limite);

    void consultarUsuario(int idUsuario);


    
    void atualizarUsuario(int idUsuario,
                        const std::string& nome,
                        const std::string& email,
                        const std::string& endereco,
                        const std::string& perfil);

    void listarHidrometrosUsuario(int idUsuario);

    double consultarConsumoHidrometro(int idHidrometro);

private:
    UsuarioRepository usuarioRepository_;
    HidrometroRepository hidrometroRepository_;
    ConsumoRepository consumoRepository_;
    AlertaRepository alertaRepository_;

    ImageReader* imageReader_; // Strategy para leitura de imagens

    std::unordered_map<int, double> limitesConsumoPorUsuario_;
};