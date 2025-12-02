#pragma once

class LeituraConsumo {
public:
    int id;
    int idHidrometro;
    int idUsuario;
    double valor;

    LeituraConsumo() = default;

    LeituraConsumo(int id,
                   int idHidrometro,
                   int idUsuario,
                   double valor)
        : id(id),
          idHidrometro(idHidrometro),
          idUsuario(idUsuario),
          valor(valor) {}
};