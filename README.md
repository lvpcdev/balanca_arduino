# ⚖️ Sistema de Pesagem e Dosagem Automática com Arduino

> Projeto de automação industrial desenvolvido para dosagem de precisão de plástico micronizado.

![Badge Concluído](https://img.shields.io/badge/Status-Concluído-green)
![Badge Arduino](https://img.shields.io/badge/Hardware-Arduino_UNO-blue)
![Badge C++](https://img.shields.io/badge/Language-C++-orange)

## 📋 Sobre o Projeto

Este projeto foi desenvolvido como parte da disciplina de **Sistemas Embarcados** do curso de Engenharia de Software / Automação no **SENAI**.

O objetivo foi resolver um problema real na indústria de rotomoldagem: a pesagem manual de plástico micronizado (em pó). O processo manual é lento e impreciso. Para solucionar isso, criamos um dispositivo eletromecânico capaz de:
1. Receber um peso alvo via teclado numérico.
2. Realizar a tara automática do recipiente.
3. Acionar uma microturbina para transportar o material.
4. Monitorar o peso em tempo real e desligar o sistema automaticamente ao atingir o alvo.

---

## 🛠️ Hardware Utilizado

| Componente | Função |
| :--- | :--- |
| **Arduino UNO R3** | Microcontrolador principal  |
| **Célula de Carga 5kg + HX711** | Sensor de peso e amplificador de sinal  |
| **Display LCD 16x2 (I2C)** | Interface visual para o usuário  |
| **Teclado Matricial 4x4** | Entrada de dados (Peso Alvo, Tara, Start/Stop)  |
| **Módulo Relé 5V** | Atuador para ligar/desligar a turbina  |
| **Mini Ventilador/Turbina** | Transporte do material (plástico em pó)  |

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

Um dos maiores desafios encontrados durante o desenvolvimento foi a física do transporte do material. A força da microturbina era excessiva, fazendo com que o pó de plástico fosse soprado para fora do recipiente coletor.

**A Solução:**
Projetamos e implementamos um tubo em formato de **espiral** na saída da mangueira. Isso permitiu dissipar a energia cinética do ar, fazendo com que o pó caísse suavemente no recipiente.

**Resultado:**
O sistema alcançou uma precisão extremamente alta, com uma divergência média de apenas **0.07g** em relação ao peso alvo.

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

* **Lucas Vicente Pereira Costa** 
* **Felipe Rohnelt Rodrigues dos Santos** 
* **Gabriel Andrade Cunha**
* **Guilherme Gonçalves Mendonça**
* **Miguel Melo Santos**
* **Paulo Augusto Silva Miranda**

Orientador: Prof. Silvio Vidal de Miranda Junior.

---
