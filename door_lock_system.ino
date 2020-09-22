#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

Servo ServoMotor;
char* password = "1234";
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
int position = 0;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = 
{
  	{'1','2','3','A'},
  	{'4','5','6','B'},
	{'7','8','9','C'},
	{'*','0','#','D'}
};

byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3, 2 };
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int RedpinLock = 12; // RED=LOCKED
int GreenpinUnlock = 13;// GREEEN=UNLOCKED
int LockedPosition =0;

void setup()
{
pinMode(RedpinLock, OUTPUT);
pinMode(GreenpinUnlock, OUTPUT);
ServoMotor.attach(11); 
lcd.begin(16,2);
LockedPosition=1;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("LOCKED");
}

void loop()
{
char key = keypad.getKey();
if (key == '*' || key == '#')
{
position = 0;
LockedPosition=1;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("LOCKED");
}
if (key == password[position])
{
position ++;
}
if (position == 4) 
{
LockedPosition=2;
}
delay(100);


if (LockedPosition==1)
{
digitalWrite(RedpinLock, HIGH);
digitalWrite(GreenpinUnlock, LOW);
ServoMotor.write(11);

}
else
{

digitalWrite(RedpinLock, LOW);
digitalWrite(GreenpinUnlock, HIGH);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("UNLOCKED");
ServoMotor.write(180);
}
}