#include "SimpleImageReader.hpp"
#include <iostream>
#include <fstream>
#include <cstdint>

static uint64_t fnv1a_hash_64(std::istream& in) {
    const uint64_t FNV_OFFSET = 1469598103934665603ULL;
    const uint64_t FNV_PRIME  = 1099511628211ULL;

    uint64_t hash = FNV_OFFSET;
    char buffer[4096];

    while (in.good()) {
        in.read(buffer, sizeof(buffer));
        std::streamsize n = in.gcount();
        for (std::streamsize i = 0; i < n; ++i) {
            hash ^= static_cast<unsigned char>(buffer[i]);
            hash *= FNV_PRIME;
        }
    }
    return hash;
}

double SimpleImageReader::lerConsumoDaImagem(const std::string& caminhoImagem) {
    std::cout << "    [IMAGEM] Lendo arquivo: " << caminhoImagem << "\n";

    std::ifstream file(caminhoImagem, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "    [IMAGEM] Nao foi possivel abrir o arquivo.\n";
        return 0.0;
    }

    uint64_t h = fnv1a_hash_64(file);

    // “Consumo” simulado, mas vindo do conteúdo da imagem
    double valor = static_cast<double>(h % 1000000ULL) / 100.0;

    std::cout << "    [IMAGEM] Consumo estimado (simulado): " << valor << " m³\n";
    return valor;
}