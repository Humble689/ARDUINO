#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
   

LiquidCrystal_I2C lcd(0x27, 16, 2);

//pins
const int motorPin =8;
const int irSensorPin = 2;
const int uvLedPin = 7;
const int uvSenorPin =A0;
const int buzzerPin = 6;

const int btnNext = 5
const int btnSelect = 3;
const int btnReset =4;
 

//currencies anf denominations
String currencies[] ={"UGX", "USD"};
int denomUGX[] = {1000, 2000, 5000, 10000, 50000};
int denomUSD[] = {1, 5, 20, 50};
int* denominations;
int denomCount = 0;


int currencyIndex