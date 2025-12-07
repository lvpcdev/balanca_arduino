/*
 * PROJETO: Dosador Automático V6 (Melhoria de Interface)
 * HARDWARE: 
 * - Arduino Uno, LCD I2C (0x27), HX711 (Pinos 8/9), Relé (Pino 10), Teclado (0-7)
 */

#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HX711.h>

// --- LÓGICA DO RELÉ
const int RELE_LIGADO = LOW;     
const int RELE_DESLIGADO = HIGH; 
// --- CONFIGURAÇÕES ---
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int HX711_DT_PIN = 8;
const int HX711_SCK_PIN = 9;
HX711 scale;
float calibration_factor = -420.0; // SEU FATOR

const int RELE_PIN = 10;

// --- TECLADO ---
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {7, 6, 5, 4}; 
byte colPins[COLS] = {3, 2, 1, 0}; 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// --- VARIÁVEIS ---
String currentInput = "";
float targetWeight = 0;
float currentWeight = 0;
bool motorOn = false;
float lastDisplayWeight = -999;
unsigned long lastReadTime = 0;
const int READ_INTERVAL = 100;

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(RELE_PIN, OUTPUT);
  digitalWrite(RELE_PIN, RELE_DESLIGADO); 

  lcd.print("Iniciando...");
  scale.begin(HX711_DT_PIN, HX711_SCK_PIN);
  scale.set_scale(calibration_factor);
  scale.tare(); 

  delay(1000);
  resetSystem();
}

void loop() {
  char key = keypad.getKey();
  if (key) handleKeypad(key);

  unsigned long currentTime = millis();
  if (currentTime - lastReadTime >= READ_INTERVAL) {
    lastReadTime = currentTime;
    
    if (scale.is_ready()) {
      float reading = scale.get_units(1);
      if (reading < 0) reading = 0.0; 
      currentWeight = reading;

      if (motorOn) checkTargetReached();
      updateLCD();
    }
  }
}

// --- LÓGICA DO TECLADO ---
void handleKeypad(char key) {
  
  // 1. DIGITAÇÃO DE NÚMEROS
  if (key >= '0' && key <= '9' && !motorOn) {
    currentInput += key;
    
    // Trava em 5 digitos
    if (currentInput.length() > 5) currentInput = currentInput.substring(0, 5);
    
    lcd.setCursor(0, 1);
    lcd.print("Novo:          "); // Mostra que está editando
    lcd.setCursor(6, 1);
    lcd.print(currentInput);
  }

  // 2. TECLA A: CONFIRMAR NOVO PESO
  if (key == 'A' && !motorOn) {
    if (currentInput.length() > 0) {
      targetWeight = currentInput.toFloat();
      currentInput = ""; // Limpa a entrada para a próxima vez
      
      lcd.clear();
      lcd.print("ALVO SALVO:");
      lcd.setCursor(0, 1);
      lcd.print(targetWeight, 0);
      lcd.print("g");
      delay(1000);
      resetSystem(); // Atualiza a tela principal
    }
  }

  // 3. TECLA B: TARA
  if (key == 'B' && !motorOn) {
    lcd.clear();
    lcd.print("Zerando Balanca");
    scale.tare();
    delay(1000);
    resetSystem();
  }

  // 4. TECLA C: INICIAR (LIGAR RELÉ)
  if (key == 'C' && !motorOn) {
    if (targetWeight > 0) {
      motorOn = true;
      digitalWrite(RELE_PIN, RELE_LIGADO); 
      lcd.clear();
      lcd.print("Enchendo...");
    } else {
      lcd.clear();
      lcd.print("ERRO: Peso=0");
      lcd.setCursor(0, 1);
      lcd.print("Digite Peso+A"); // Instruir o usuário
      delay(2000);
      resetSystem();
    }
  }

  // 5. TECLA D: PARAR / CANCELAR
  if (key == 'D') {
    motorOn = false;
    digitalWrite(RELE_PIN, RELE_DESLIGADO); 
    lcd.clear();
    lcd.print("PARADA MANUAL!");
    delay(1500);
    resetSystem();
  }
  
  // 6. TECLA *: LIMPAR ALVO (RESET)
  // mudar peso alvo
  if (key == '*') {
    targetWeight = 0;
    currentInput = "";
    motorOn = false;
    digitalWrite(RELE_PIN, RELE_DESLIGADO);
    
    lcd.clear();
    lcd.print("ALVO ZERADO!");
    delay(1000);
    resetSystem();
  }
  
  // 7. TECLA #: CALIBRAÇÃO
  if (key == '#' && !motorOn) {
    calibrateScale();
  }
}

void checkTargetReached() {
  if (currentWeight >= targetWeight) {
    motorOn = false;
    digitalWrite(RELE_PIN, RELE_DESLIGADO); 
    
    lcd.clear();
    lcd.print("PRONTO!");
    lcd.setCursor(0, 1);
    lcd.print("Final: ");
    lcd.print(currentWeight, 1);
    lcd.print("g");
    
    delay(3000); 
    resetSystem();
  }
}

void updateLCD() {
  if (abs(currentWeight - lastDisplayWeight) > 0.1 || motorOn) {
    lastDisplayWeight = currentWeight;
    
    if (motorOn) {
      // Tela ENCHENDO
      lcd.setCursor(0, 1);
      lcd.print(currentWeight, 0);
      lcd.print("/");
      lcd.print(targetWeight, 0);
      lcd.print("g    ");
    } else if (currentInput == "") {
      // Tela ESPERA (Mostra Alvo e Peso Atual)
      lcd.setCursor(0, 0);
      lcd.print("Alvo: ");
      if(targetWeight > 0) lcd.print(targetWeight, 0);
      else lcd.print("---");
      lcd.print("g     "); // Espaços para limpar sujeira
      
      lcd.setCursor(0, 1);
      lcd.print("Atual: ");
      lcd.print(currentWeight, 1);
      lcd.print("g    ");
    }
  }
}

void resetSystem() {
  motorOn = false;
  digitalWrite(RELE_PIN, RELE_DESLIGADO); 
  currentInput = ""; // Limpa qualquer digitação pendente
  
  lcd.clear();
  // Se não tem alvo definido, pede para digitar
  if (targetWeight <= 0) {
    lcd.print("DIGITE PESO + A");
    lcd.setCursor(0, 1);
    lcd.print("Atual: ");
    lcd.print(scale.get_units(1), 1);
  } else {
    // Se tem alvo, mostra pronto para iniciar
    lcd.print("C=INICIAR  B=0");
    updateLCD(); // Chama a atualização para desenhar os pesos
  }
}

void calibrateScale() {
  lcd.clear();
  lcd.print("Coloque 100g");
  lcd.setCursor(0, 1);
  lcd.print("A=Ok  D=Sair");

  while(true) {
    char key = keypad.getKey();
    if (key == 'A') break; 
    if (key == 'D') {
      lcd.clear();
      lcd.print("Cancelado!");
      delay(1000);
      resetSystem();
      return; 
    }
    delay(10);
  }
  
  lcd.clear();
  lcd.print("Lendo...");
  
  float reading = scale.get_units(20);
  calibration_factor = reading / 100.0; 
  scale.set_scale(calibration_factor);
  
  lcd.clear();
  lcd.print("Fator salvo!");
  delay(1500);
  resetSystem();
}
