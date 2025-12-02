#pragma once
#include "ImageReader.hpp"
#include <string>

class SimpleImageReader : public ImageReader {
public:
    double lerConsumoDaImagem(const std::string& caminhoImagem) override;
};