// PASSA OU REPASSA
// FAÇA VOCÊ MESMO
// CRIADO POR LUCAS CARVALHO.

const int ledAzul = 2;
const int ledVermelho = 3;
const int botaoAzul = 5;
const int botaoVermelho = 4;
const int rele = 7;
const int buzzer = 10;

// Controle do jogo
bool jogoAtivo = true;

// Controle dos LEDs
unsigned long tempoInicio = 0;
bool estadoLeds = HIGH;

void setup() {

  pinMode(rele, OUTPUT);
  pinMode(buzzer, OUTPUT);

  pinMode(ledAzul, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  pinMode(botaoAzul, INPUT_PULLUP);
  pinMode(botaoVermelho, INPUT_PULLUP);

  // Estado inicial
  estadoLeds = HIGH;

  digitalWrite(ledAzul, estadoLeds);
  digitalWrite(ledVermelho, estadoLeds);

  digitalWrite(rele, LOW);

  // Garante buzzer desligado
  noTone(buzzer);
}

void loop() {

  if (jogoAtivo) {

    // ==========================================
    // BOTÃO AZUL
    // ==========================================
    if (digitalRead(botaoAzul) == LOW) {

      jogoAtivo = false;

      // Azul aceso
      digitalWrite(ledAzul, LOW);

      // Vermelho apagado
      digitalWrite(ledVermelho, HIGH);

      // Música de vitória + relé
      vitoria();

      // Rearma os LEDs sincronizados
      estadoLeds = HIGH;

      digitalWrite(ledAzul, estadoLeds);
      digitalWrite(ledVermelho, estadoLeds);

      tempoInicio = millis();

      jogoAtivo = true;
    }

    // ==========================================
    // BOTÃO VERMELHO
    // ==========================================
    else if (digitalRead(botaoVermelho) == LOW) {

      jogoAtivo = false;

      // Vermelho aceso
      digitalWrite(ledVermelho, LOW);

      // Azul apagado
      digitalWrite(ledAzul, HIGH);

      // Música de vitória + relé
      vitoria();

      // Rearma os LEDs sincronizados
      estadoLeds = HIGH;

      digitalWrite(ledAzul, estadoLeds);
      digitalWrite(ledVermelho, estadoLeds);

      tempoInicio = millis();

      jogoAtivo = true;
    }

    // ==========================================
    // PISCA OS DOIS LEDs JUNTOS
    // ==========================================

    unsigned long tempoAtual = millis();

    if (tempoAtual - tempoInicio >= 500) {

      tempoInicio = tempoAtual;

      estadoLeds = !estadoLeds;

      digitalWrite(ledAzul, estadoLeds);
      digitalWrite(ledVermelho, estadoLeds);
    }
  }
}


// ==========================================
// MÚSICA DE VITÓRIA
// ==========================================

void vitoria() {

  // Liga o relé
  digitalWrite(rele, HIGH);

  // ------------------------------------------
  // Melodia curta de vitória
  // DÓ - MI - SOL - DÓ
  // ------------------------------------------

  tone(buzzer, 523);  // Dó
  delay(180);
  noTone(buzzer);
  delay(40);

  tone(buzzer, 659);  // Mi
  delay(180);
  noTone(buzzer);
  delay(40);

  tone(buzzer, 784);  // Sol
  delay(180);
  noTone(buzzer);
  delay(40);

  tone(buzzer, 1047); // Dó agudo
  delay(450);
  noTone(buzzer);

  delay(100);

  // ------------------------------------------
  // Finalzinho de vitória
  // ------------------------------------------

  tone(buzzer, 784);  // Sol
  delay(120);
  noTone(buzzer);
  delay(30);

  tone(buzzer, 1047); // Dó agudo
  delay(600);
  noTone(buzzer);

  // Pequena pausa
  delay(300);

  // Desliga o relé
  digitalWrite(rele, LOW);
}
