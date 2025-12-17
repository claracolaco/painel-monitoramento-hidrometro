# Painel de Monitoramento de Hidrômetros

Projeto de painel para consolidar e monitorar o consumo de água a partir das
leituras geradas pelos Simuladores de Hidrômetro Analógico (SHA), usando uma
**Fachada** para centralizar o acesso aos subsistemas internos.

---

## 📊 Progresso Geral do Projeto
`████████████████████` **100%**

---

## 🧩 Padrões de Projeto Utilizados (Implementados)

| Padrão | Onde ver no código |
|---|---|
| **Facade** | `src/fachada/PainelMonitoramentoFacade.hpp` / `src/fachada/PainelMonitoramentoFacade.cpp` |
| **Repository** | `src/usuarios/UsuarioRepository.*`, `src/hidrometros/HidrometroRepository.*`, `src/consumo/ConsumoRepository.*`, `src/alertas/AlertaRepository.*` |
| **Strategy** | `src/imagens/ImageReader.*` e `src/imagens/SimpleImageReader.*` (usado em `PainelMonitoramentoFacade::lerConsumoHidrometro`) |
| **Template Method** | `src/monitoramento/MonitoramentoTemplate.*` e `src/monitoramento/MonitoramentoPainel.*` |
| **Observer** | `src/notificacao/IAlertaObserver.hpp`, `ConsoleAlertaObserver.hpp`, `EmailAlertaObserver.hpp` + `PainelMonitoramentoFacade::adicionarObserver/notificarAlerta` |
| **Singleton** | `src/log/Logger.*` (`Logger::instance()`) |

---

## ▶️ Como compilar e executar (Windows / PowerShell)

```powershell
g++ src\main.cpp `
    src\cli\PainelCLI.cpp `
    src\fachada\PainelMonitoramentoFacade.cpp `
    src\usuarios\UsuarioRepository.cpp `
    src\hidrometros\HidrometroRepository.cpp `
    src\consumo\ConsumoRepository.cpp `
    src\imagens\SimpleImageReader.cpp `
    src\alertas\AlertaRepository.cpp `
    src\log\Logger.cpp `
    src\monitoramento\MonitoramentoTemplate.cpp `
    src\monitoramento\MonitoramentoPainel.cpp `
    -std=c++17 -Wall -o painel.exe

.\painel.exe
```
---

📚 Projeto desenvolvido na disciplina **Padrões de Projeto** do curso de **Engenharia de Computação**.  
Autoria: **Maria Clara Colaço da Costa**.
