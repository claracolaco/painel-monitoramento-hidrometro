# Painel de Monitoramento de Hidrômetros

Projeto de painel para consolidar e monitorar o consumo de água a partir das
leituras geradas pelos Simuladores de Hidrômetro Analógico (SHA), usando uma
**Fachada** para centralizar o acesso aos subsistemas internos.

---

## 📊 Progresso Geral do Projeto

`████████████░░░░` **70%**

---

## 🧩 Padrões de Projeto Utilizados

### Padrões já implementados

| Padrão        | Onde ver no código                                                                 |
|---------------|-------------------------------------------------------------------------------------|
| **Facade**    | `src/fachada/PainelMonitoramentoFacade.hpp` e `src/fachada/PainelMonitoramentoFacade.cpp` |
| **Repository** | `src/usuarios/UsuarioRepository.*` (usuários), `src/hidrometros/HidrometroRepository.*` (hidrômetros) e `src/consumo/ConsumoRepository.*` (leituras de consumo) |
| **Strategy**  | Interface `ImageReader` (`src/imagens/ImageReader.hpp`) e implementação `SimpleImageReader.*` usada para ler o consumo a partir de imagens de hidrômetros |

### Padrões planejados (a implementar)

| Padrão          | Uso planejado                                                                  |
|-----------------|-------------------------------------------------------------------------------|
| **Template Method** | Fluxo padrão de monitoramento/atualização periódica de consumo           |
| **Observer**    | Disparo de alertas quando limites de consumo forem excedidos                 |
| **Singleton**   | Logger centralizado para o sistema                                           |
| **Adapter**     | Integração com biblioteca de OCR / serviço de envio de e-mails               |


- **Facade**: a classe `PainelMonitoramentoFacade` concentra o acesso aos subsistemas internos (usuários, hidrômetros, consumo, e futuramente alertas etc.), evitando que o código cliente (`main.cpp`) acesse diretamente os repositórios.

- **Repository**: os repositórios `UsuarioRepository`, `HidrometroRepository` e `ConsumoRepository` encapsulam o armazenamento em memória das entidades de domínio, oferecendo operações de criação, remoção, busca e listagem sem expor detalhes de implementação (como `std::vector`).

- **Strategy**: a interface `ImageReader` define o contrato para leitura do consumo a partir de uma imagem de hidrômetro. A implementação `SimpleImageReader` é uma estratégia concreta usada neste protótipo, que simula a leitura. No futuro, outras estratégias (por exemplo, usando OCR real) podem ser utilizadas sem alterar a Fachada.