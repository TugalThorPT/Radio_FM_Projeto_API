#include <Wire.h>
#include <LiquidCrystal.h>
#include <TEA5767.h>
#include <TEA5767Radio.h>
#include <RTClib.h>

TEA5767 radio = TEA5767();
TEA5767Radio radio2 = TEA5767Radio();

int count = 0;
float station = 0;
float laststation = 0;
int potcf = A0;
float frequencia;
float potval = 0;

const int rs = 12, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//defições relacinadas com o botão
const int buttonStart = 8; 
byte lastbuttonStateStart;
byte lcd12 = LOW;

unsigned long LasttimebuttonStatechangedStart = millis();
unsigned long debounceDuration = 50;

bool lig = false;
bool deslig = false;
bool tela = false;

RTC_DS3231 rtc;
String horas;
String minutos;
String dia;
String mes;
String ano;
String data;
String relogio;
int mininteger;

void setup() {

  pinMode(buttonStart, INPUT);
  lastbuttonStateStart = digitalRead(buttonStart);
  Serial.begin(9600);
  lcd.begin(16, 2);
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
  pinMode(potcf, INPUT);
  radio.setMute(true);

}

void estacoes() {
  if (frequencia == 97.4){
    lcd.setCursor(0,1);
    lcd.print("Radio Comercial ");
  }
  if (frequencia == 91.6){
    lcd.setCursor(0,1);
    lcd.print("Cidade FM       ");
  }
  if (frequencia == 104.3){
    lcd.setCursor(0,1);
    lcd.print("M80             ");
  }
  if (frequencia == 103.4){
    lcd.setCursor(0,1);
    lcd.print("Radio Renascenca");
  }
  if (frequencia == 100.8){
    lcd.setCursor(0,1);
    lcd.print("Meo Sudoeste    ");
  }
  if (frequencia == 92.4){
    lcd.setCursor(0,1);
    lcd.print("Mega Hits       ");
  }
  if (frequencia == 95.7){
    lcd.setCursor(0,1);
    lcd.print("RTP Antena 1    ");
  }
  if (frequencia == 93.2){
    lcd.setCursor(0,1);
    lcd.print("RFM             ");
  }
  if (frequencia == 89.5){
    lcd.setCursor(0,1);
    lcd.print("TSF             ");
  }
  if (frequencia == 101.9){
    lcd.setCursor(0,1);
    lcd.print("Radio Orbital   ");
  }
  if (frequencia == 93.7){
    lcd.setCursor(0,1);
    lcd.print("Radio Observador");
  }
  if (frequencia == 90.4){
    lcd.setCursor(0,1);
    lcd.print("SBSR.FM         ");
  }
  if (frequencia == 101.5){
    lcd.setCursor(0,1);
    lcd.print("RDP Africa      ");
  }
  if (frequencia == 100.3){
    lcd.setCursor(0,1);
    lcd.print("Antena 3        ");
  }
  if (frequencia == 96.6){
    lcd.setCursor(0,1);
    lcd.print("Smooth FM       ");
  }
  if (frequencia == 94.4){
    lcd.setCursor(0,1);
    lcd.print("Antena 2        ");
  }
  if (frequencia == 92.0){
    lcd.setCursor(0,1);
    lcd.print("Radio Amalia    ");
  }
  if (frequencia == 93.8){
    lcd.setCursor(0,1);
    lcd.print("ON FM           ");
  }
  if (frequencia == 92.8){
    lcd.setCursor(0,1);
    lcd.print("Radio Horizonte ");
  }
  if (frequencia == 95.0){
    lcd.setCursor(0,1);
    lcd.print("Radio Positiva  ");
  }
}

void ligado() {
  lcd.clear();
  lcd.print("Radio Ligado");
  delay(2000);
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    lcd.scrollDisplayRight();
    delay(150);
  }
  lcd.clear();
  lig=false;
  tela = true;
  radio.setMute(false);
  radio.init();
}

void desligado() {
  tela = false;
  lcd.clear();
  lcd.print("Radio Desligado");
  radio.setMute(true);
  delay(2000);
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    lcd.scrollDisplayRight();
    delay(150);
  }
  lcd.clear();
  delay(50);
  lcd.print("Criadores:");
  delay(1500);
  lcd.clear();
  delay(200);
  lcd.setCursor(0,0);
  lcd.print("Pedro Armada");
  delay(1000);
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    lcd.scrollDisplayRight();
    delay(150);
  }
  lcd.clear();
  lcd.print("Joana Serra");
  delay(1000);
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    lcd.scrollDisplayRight();
    delay(150);
  }
  lcd.clear();
  lcd.print("Leonor Fernandes");
  delay(1000);
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    lcd.scrollDisplayRight();
    delay(150);
  }
  lcd.clear();
  lcd.print("Margarida Sabino");
  delay(1000);
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    lcd.scrollDisplayRight();
    delay(150);
  }
  lcd.clear();
  count=0;
  station = 0;
  laststation=0;
  deslig=false;
}

void loop() {

  byte buttonState = digitalRead(buttonStart);

  if (millis() - LasttimebuttonStatechangedStart >= debounceDuration){
    if (buttonState != lastbuttonStateStart) {
      lastbuttonStateStart = buttonState;
      if (buttonState == LOW){
        if (lcd12 == HIGH){
          lcd12 = LOW; 
          deslig = true;
        }
        else if (lcd12 == LOW){ 
          lcd12 = HIGH;
          lig = true;   
        }
      }
    }   
  }
  
  if (lig){
    ligado();
  }

  if (deslig){
    desligado();
  }

  DateTime now = rtc.now();
  dia = (String)now.day();
  mes = (String)now.month();
  ano = (String)now.year();
  horas = (String)now.hour(); 
  minutos = (String)now.minute();

  mininteger = minutos.toInt();
  data =  dia + "/" + mes + "/" + ano;

  if (mininteger>9){
    relogio = horas +":"+ minutos+"  ";  
  }
  if (mininteger < 10){
    relogio = horas +":"+"0"+minutos+"  ";
  }

  if (tela){
    potval = analogRead(potcf);
    frequencia = map(potval, 0, 1023, 875, 1080)/10.0;
    station = frequencia;
    radio2.setFrequency(frequencia);
    lcd.setCursor(0,0);
    lcd.print("Frequencia:");
    lcd.print(frequencia);
    if (station == laststation && count < 100){
      count= count+1;
    } 
    else if (count == 100){
      count=101;
    }
    else if (station != laststation){
      count = 0;
    }
    if (count > 30 && count < 60){
      estacoes();  
    }
    else{
      lcd.setCursor(0,1);
      lcd.print(data);
      lcd.print(" ");
      lcd.print(relogio);  
    }
    laststation = station;
    delay(100);
  }
}
