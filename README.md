# Controle de GPIOs com Teclado Matricial 4x4

Este projeto utiliza um teclado matricial 4x4 para controlar LEDs RGB e um buzzer em um microcontrolador **RP2040** simulado no **Wokwi**. A atividade é parte do curso **EmbarcaTech - CEPEDI**.

---

## 🎯 Objetivo

Desenvolver um programa em **linguagem C** que:
- Interpreta entradas do teclado matricial 4x4.
- Controla 3 LEDs RGB e um buzzer usando GPIOs.
- Simula o funcionamento no ambiente **Wokwi**.

---

## 🛠️ Ferramentas Utilizadas

- **Ferramenta educacional:** BitDogLab
- **Microcontrolador:** Raspberry Pi Pico W (RP2040).
- **Simulador:** Wokwi.
- **Ambiente de Desenvolvimento:** VS Code.
- **Linguagem de Programação:** C (usando o kit Pico SDK).
- **Controle de Versão:** GitHub.

---

## 🧩 Funcionalidades

1. **Controle dos LEDs RGB:**
   - Acionamento dos LEDs em diferentes cores baseado em entradas do teclado matricial.

2. **Controle do Buzzer:**
   - Emissão de sinais sonoros conforme comandos recebidos.

3. **Simulação:**
   - Simulação completa no **Wokwi** dispensando hardware real.
     
4. **Comandos**
- Aperta 1 = liga led vermelho
- Aperta 2 = liga led verde
- Aperta 3 = liga led azul
- Aperta 4 = desliga os LEDs
- Aperta 5 = DÓ-RÉ-MI no buzzer (2 segundos cada nota)
- Aperta D = código morse (SOS) com LED vermelho
- Aperta 0 = pisca alternando entre as cores

---

## 🚀 Como Executar

### Pré-requisitos
1. Instale o **VS Code** com o **Pico SDK** configurado.
2. Configure o simulador **Wokwi**.
3. Certifique-se de que o repositório Git está configurado.

### Passos
1. Clone este repositório:
   ```bash
   git clone https://github.com/seu-usuario/seu-repositorio.git
   ```
2. Configure o projeto no **Wokwi** utilizando o arquivo `.json` fornecido.
3. Compile e execute o código no simulador.

---

## 📝 Estrutura do Projeto

```
|-- src/
    |-- main.c
    |-- keypad_control.c
|-- include/
    |-- keypad_control.h
|-- wokwi/
    |-- simulation.json
|-- README.md
|-- LICENSE
```

---

## 🎥 Demonstração

Assista ao vídeo demonstrativo clicando [aqui](https://www.youtube.com/watch?v=0OIFq5b_DUI)
Link da simulação no wokwi: https://wokwi.com/projects/420262014836493313
---

## 📌 Organização do Projeto

- **Líder do Projeto:** Responsável pela gestão do repositório, criação e inicialização do projeto, organização de tarefas e revisão de pull requests.
- **Desenvolvedores:** Cada membro da equipe trabalhou em um branch específico desenvolvendo o código e testando funcionalidades.

---

## 💡 Contribuições

1. Faça um fork deste repositório.
2. Crie um branch com sua feature:
   ```bash
   git checkout -b minha-feature
   ```
3. Faça commits com mensagens claras.
4. Envie um pull request.

---
## Desenvolvolvido por:

Patrick Queiroz 
queirozPatrick • Collaborator

Alex Bomfim
Alex-SB7 • Collaborator

João Victor Paim
PaimJv • Collaborator

Josimar Souza
perseu120 • Collaborator

Heitor Lemos
TorRLD • Collaborator
