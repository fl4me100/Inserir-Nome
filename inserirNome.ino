#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);
char letras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz .<";
int indiceLetra = 0;
char nome[15] = "";
int posicao = 0;
unsigned long InicioA = 0, InicioB = 0;
bool longoA = false, longoB = false;

void setup() {
  lcd.begin(16, 2);
  pinMode(5, INPUT_PULLUP); // Botão A
  pinMode(6, INPUT_PULLUP); // Botão B
  lcd.print("Introd. Nome:");
  lcd.setCursor(0, 1);
  lcd.print(letras[indiceLetra]);
}

void loop() {
  unsigned long tempoAtual = millis();

  // Botão A
  if (digitalRead(5) == LOW) {
    if (InicioA == 0) {
      InicioA = tempoAtual;
    } else if (tempoAtual - InicioA > 2000 && !longoA) {
      indiceLetra = 0;
      posicao = 0;
      nome[0] = '\0';
      lcd.setCursor(0, 1);
      lcd.print("                "); // Limpa a linha
      lcd.setCursor(0, 1);
      lcd.print(letras[indiceLetra]); // Reinicia exibição
      longoA = true;
    }
  } else {
    if (InicioA != 0 && !longoA && tempoAtual - InicioA <= 2000) {
      indiceLetra = (indiceLetra + 1) % (sizeof(letras) - 1); // Navega letras
      lcd.setCursor(posicao, 1);
      lcd.print(letras[indiceLetra]);
    }
    InicioA = 0;
    longoA = false;
  }

  // Botão B
  if (digitalRead(6) == LOW) {
    if (InicioB == 0) {
      InicioB = tempoAtual;
    } else if (tempoAtual - InicioB > 2000 && !longoB) {
      lcd.setCursor(0, 1);
      lcd.print("Nome Aceite!");
      delay(2000);
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print(nome);
      delay(3000);
      indiceLetra = 0;
      posicao = 0;
      nome[0] = '\0';
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print(letras[indiceLetra]);
      longoB = true;
    }
  } else {
    if (InicioB != 0 && !longoB && tempoAtual - InicioB <= 2000) {
      char letraSelecionada = letras[indiceLetra];
      if (letraSelecionada == '<' && posicao > 0) {
        posicao--;
        nome[posicao] = '\0'; // Remove último caractere
        lcd.setCursor(posicao, 1);
        lcd.print(" ");
        lcd.setCursor(posicao, 1);
      } else if (letraSelecionada != '<' && posicao < 14) {
        nome[posicao] = letraSelecionada;
        nome[posicao + 1] = '\0';
        lcd.setCursor(posicao, 1);
        lcd.print(letraSelecionada);
        posicao++;
      }
    }
    InicioB = 0;
    longoB = false;
  }
}
