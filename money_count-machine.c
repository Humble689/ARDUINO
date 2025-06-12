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


int currencyIndex = 0;
int denomIndex = 3; // default index
int selectedDenom = 10000;


volatile int billCount = 0;
volatile bool checkingNote = false;
bool countingStarted = false;



void setup() {
    pinMode(motorPin, OUTPUT):
    pinMode(irSensorPin, INPUT_PULLUP);
    pinMode(uvLedPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT)

    pinMode(btnNext, INPUT_PULLUP);
    pinMode(btnSelect, INPUT_PULLUP);
    pinMode(btnReset, INPUT_PULLUP);



    attachInterrupt(digitalPinToInterrupt(irSensorPin), billDetected, FALLING);


    lcd.begin();
    lcd.backlight();


    loadFromEEPROM(); // load saved  data


    if (!countingStarted) {
        showCurrencyMenu();
    }
}


void loop() {
    if (!countingStarted) {
        handleCurrencyAndDenominationSelection();
        return;
    }

    if (checkingNote) {
        checkingNote = false;
        if (checkingNote()) {
            lcd.setCursor(0,1);
            lcd.print("Fake note!    ");
            buzzFakeNote();
            delay(1000);

        } else {
            billCount++;
            saveToEEPROM();


            lcd.setCursor(0,1);
            lcd.print("count:");
            lcd.print(billCount);
            lcd.print(" ");
        }
    }
}