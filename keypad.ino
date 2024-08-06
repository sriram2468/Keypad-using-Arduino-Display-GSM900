
#include<Keypad.h>
#include<SoftwareSerial.h>
#include<LiquidCrystal.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); // RS, EN, D4, D5, D6, D7

SoftwareSerial SIM900(13, 12);



const byte ROWS = 4;
const byte COLS = 3;

char hexakeys[ROWS][COLS]=
{
  {'1' , '2' , '3'},
  {'4' , '5' , '6'},
  {'7' , '8' , '9'},
  {'*',  '0' , '#'},
};

byte rowPins[ROWS] = {8, 7, 6, 5};
byte colPins[COLS] = {9, 10, 11};

Keypad customKeypad = Keypad(makeKeymap(hexakeys), rowPins, colPins, ROWS, COLS);

void setup() {

  Serial.begin(9600);
  SIM900.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Keypad Input:");

  SIM900.println("AT");
  delay(100);
  SIM900.println("AT+CMGF=1");  // Set SMS mode to text
  delay(100);
}


void loop() {
  char customKey = customKeypad.getKey();
   
  
  if (customKey) {
    // Display key on LCD
    lcd.clear();
    lcd.print("Key pressed:");
    lcd.setCursor(0, 1);
    lcd.print(customKey);
    
    // Send SMS via SIM900 module
    SIM900.print("AT+CMGF=1\r"); 
    delay(100);
    SIM900.print("AT+CMGS=\"+1234567890\"\r"); // replace with the phone number
    delay(100);
    SIM900.print("Key pressed: ");
    SIM900.print("AT+CNMI=2,2,0,0,0");
    SIM900.print(customKey);
    delay(100);
    SIM900.write(26); // ASCII code for Ctrl+Z to send the SMS
    delay(100);
    lcd.print(" MESSAGE SENT");
    delay(100);
  }
}
