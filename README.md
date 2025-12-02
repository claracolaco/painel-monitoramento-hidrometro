# Painel de Monitoramento de Hidrômetros

Projeto de painel para consolidar e monitorar o consumo de água a partir das
leituras geradas pelos Simuladores de Hidrômetro Analógico (SHA), usando uma
**Fachada** para centralizar o acesso aos subsistemas internos.

---

## 📊 Progresso Geral do Projeto

`███████████░░░░░` **60%**

---

## 🧩 Padrões de Projeto Utilizados

### Padrões já implementados

| Padrão        | Onde ver no código                                                                 |
|---------------|-------------------------------------------------------------------------------------|
| **Facade**    | `src/fachada/PainelMonitoramentoFacade.hpp` e `src/fachada/PainelMonitoramentoFacade.cpp` |
| **Repository** | `src/usuarios/UsuarioRepository.*` (usuários) e `src/hidrometros/HidrometroRepository.*` (hidrômetros) |

### Padrões planejados (a implementar)

| Padrão          | Uso planejado                                                                  |
|-----------------|-------------------------------------------------------------------------------|
| **Repository**  | Repositórios para hidrômetros, leituras e consumo                            |
| **Strategy**    | Estratégias para leitura/processamento de imagens de hidrômetros             |
| **Template Method** | Fluxo padrão de monitoramento/atualização periódica de consumo           |
| **Observer**    | Disparo de alertas quando limites de consumo forem excedidos                 |
| **Singleton**   | Logger centralizado para o sistema                                           |
| **Adapter**     | Integração com biblioteca de OCR / serviço de envio de e-mails               |


- **Facade**: a classe `PainelMonitoramentoFacade` concentra o acesso aos subsistemas internos (usuários, hidrômetros, e futuramente consumo, alertas etc.), evitando que o código cliente (`main.cpp`) acesse diretamente os repositórios.
- **Repository**: os repositórios `UsuarioRepository` e `HidrometroRepository` encapsulam o armazenamento em memória das entidades de domínio, oferecendo operações de criação, remoção, busca e listagem sem expor detalhes de implementação (como `std::vector`).
