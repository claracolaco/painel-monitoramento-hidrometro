# Painel de Monitoramento de Hidrômetros

Projeto de painel para consolidar e monitorar o consumo de água a partir das
leituras geradas pelos Simuladores de Hidrômetro Analógico (SHA), usando uma
**Fachada** para centralizar o acesso aos subsistemas internos.

---

## 📊 Progresso Geral do Projeto

`██████████░░░░░░` **50%**

---

## 🧩 Padrões de Projeto Utilizados

### Padrões já implementados

| Padrão       | Onde ver no código                                                                 |
|--------------|-------------------------------------------------------------------------------------|
| **Facade**   | `src/fachada/PainelMonitoramentoFacade.hpp` e `src/fachada/PainelMonitoramentoFacade.cpp` |
| **Repository** | `src/usuarios/UsuarioRepository.hpp` e `src/usuarios/UsuarioRepository.cpp` (armazenamento em memória de usuários) |

### Padrões planejados (a implementar)

| Padrão          | Uso planejado                                                                  |
|-----------------|-------------------------------------------------------------------------------|
| **Repository**  | Repositórios para hidrômetros, leituras e consumo                            |
| **Strategy**    | Estratégias para leitura/processamento de imagens de hidrômetros             |
| **Template Method** | Fluxo padrão de monitoramento/atualização periódica de consumo           |
| **Observer**    | Disparo de alertas quando limites de consumo forem excedidos                 |
| **Singleton**   | Logger centralizado para o sistema                                           |
| **Adapter**     | Integração com biblioteca de OCR / serviço de envio de e-mails               |