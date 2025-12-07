# ⚖️ Sistema de Pesagem e Dosagem Automática com Arduino

> Projeto de automação industrial desenvolvido para dosagem de precisão de plástico micronizado.

![Badge Concluído](https://img.shields.io/badge/Status-Concluído-green)
![Badge Arduino](https://img.shields.io/badge/Hardware-Arduino_UNO-blue)
![Badge C++](https://img.shields.io/badge/Language-C++-orange)

## 📋 Sobre o Projeto

[cite_start]Este projeto foi desenvolvido como parte da disciplina de **Sistemas Embarcados** do curso de Engenharia de Software / Automação no **SENAI**[cite: 1, 3].

[cite_start]O objetivo foi resolver um problema real na indústria de rotomoldagem: a pesagem manual de plástico micronizado (em pó)[cite: 10]. O processo manual é lento e impreciso. Para solucionar isso, criamos um dispositivo eletromecânico capaz de:
1. Receber um peso alvo via teclado numérico.
2. [cite_start]Realizar a tara automática do recipiente[cite: 27].
3. Acionar uma microturbina para transportar o material.
4. [cite_start]Monitorar o peso em tempo real e desligar o sistema automaticamente ao atingir o alvo[cite: 27].

---

## 🛠️ Hardware Utilizado

| Componente | Função |
| :--- | :--- |
| **Arduino UNO R3** | [cite_start]Microcontrolador principal [cite: 11] |
| **Célula de Carga 5kg + HX711** | [cite_start]Sensor de peso e amplificador de sinal [cite: 15, 16] |
| **Display LCD 16x2 (I2C)** | [cite_start]Interface visual para o usuário [cite: 16] |
| **Teclado Matricial 4x4** | [cite_start]Entrada de dados (Peso Alvo, Tara, Start/Stop) [cite: 13] |
| **Módulo Relé 5V** | [cite_start]Atuador para ligar/desligar a turbina [cite: 12] |
| **Mini Ventilador/Turbina** | [cite_start]Transporte do material (plástico em pó) [cite: 14] |

---

## ⚙️ Funcionalidades do Sistema

* **Entrada de Dados:** O usuário digita o peso desejado (em gramas) no teclado.
* **Função Tara:** Botão dedicado para zerar a balança antes do início.
* **Controle Automático:** O sistema aciona o relé (motor) e monitora o peso continuamente.
* **Parada de Precisão:** O motor é desligado imediatamente ao atingir o peso alvo.
* **Segurança:** Botão de parada de emergência e tratamento de erros (ex: peso alvo = 0).
* **Calibração:** Modo de configuração para ajustar o fator de calibração da célula de carga.

---

## 🚀 Desafios e Engenharia

Um dos maiores desafios encontrados durante o desenvolvimento foi a física do transporte do material. [cite_start]A força da microturbina era excessiva, fazendo com que o pó de plástico fosse soprado para fora do recipiente coletor[cite: 277].

**A Solução:**
Projetamos e implementamos um tubo em formato de **espiral** na saída da mangueira. [cite_start]Isso permitiu dissipar a energia cinética do ar, fazendo com que o pó caísse suavemente no recipiente[cite: 277].

**Resultado:**
[cite_start]O sistema alcançou uma precisão extremamente alta, com uma divergência média de apenas **0.07g** em relação ao peso alvo[cite: 279].

---

## 🔌 Esquema de Ligação


Exemplo de Pinagem (Configurável no código):
* **HX711:** DT (8), SCK (9)
* **Relé:** Pino 10
* **LCD:** Endereço I2C 0x27
* **Teclado:** Pinos 0 a 7

---

## 💻 Como Executar

1.  Instale a **Arduino IDE**.
2.  Instale as bibliotecas necessárias pelo Gerenciador de Bibliotecas:
    * `HX711` (por Bogdan Necula ou similar)
    * `LiquidCrystal_I2C` (por Frank de Brabander)
    * `Keypad` (por Mark Stanley, Alexander Brevig)
3.  Clone este repositório.
4.  Abra o arquivo `.ino` na IDE.
5.  Conecte o Arduino e faça o upload.
6.  **Importante:** Realize a calibração inicial (Tecla `#`) com um peso conhecido para ajustar o fator de escala.

---

## 👨‍💻 Autores

Projeto desenvolvido pela equipe:

* [cite_start]**Lucas Vicente Pereira Costa** [cite: 8]
* [cite_start]**Felipe Rohnelt Rodrigues dos Santos** [cite: 8]
* [cite_start]**Gabriel Andrade Cunha** [cite: 8]
* [cite_start]**Guilherme Gonçalves Mendonça** [cite: 8]
* [cite_start]**Miguel Melo Santos** [cite: 8]
* [cite_start]**Paulo Augusto Silva Miranda** [cite: 8]

[cite_start]Orientador: Prof. Silvio Vidal de Miranda Junior[cite: 3].

---
