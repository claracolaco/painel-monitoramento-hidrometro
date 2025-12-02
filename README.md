# Painel de Monitoramento de Hidrômetros

Projeto de painel para consolidar e monitorar o consumo de água a partir das
leituras geradas pelos Simuladores de Hidrômetro Analógico (SHA), usando uma
**Fachada** para centralizar o acesso aos subsistemas internos.

---

## 📊 Progresso Geral do Projeto

`████████░░░░░░░░` **40%**

---

## 🧩 Padrões de Projeto Utilizados

> Nesta versão, é uma **lista planejada**. Depois vamos ligar cada padrão a arquivos específicos do código.

| Padrão          | Uso planejado no projeto                                             |
|-----------------|----------------------------------------------------------------------|
| **Facade**      | Classe de fachada do painel agregando todos os subsistemas           |
| **Repository**  | Acesso e gerenciamento de usuários, hidrômetros e leituras           |
| **Strategy**    | Estratégias para leitura/processamento de imagens de hidrômetros     |
| **Template Method** | Fluxo padrão de monitoramento/atualização de consumo             |
| **Observer**    | Disparo de alertas quando limites de consumo forem excedidos         |
| **Singleton**   | Logger centralizado para o sistema                                   |
| **Adapter**     | Integração com biblioteca de OCR / envio de e-mails                  |
