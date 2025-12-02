#pragma once
#include <string>

class ImageReader {
public:
    virtual ~ImageReader() = default;

    virtual double lerConsumoDaImagem(const std::string& caminhoImagem) = 0;
};