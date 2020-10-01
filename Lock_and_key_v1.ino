#include <LiquidCrystal_I2C.h>

#include <Wire.h>

#include <EEPROM.h>

//Declarations
int time1=A0;
int time2=A1;
unsigned long waiting_time=0;
int buzzer = 12; // Can be a buzzer or a light does no matter(Both can be connected at the same time)
int relay = 11;
int change = 10;
int green = 13;
int max_length = 15;  //Change the max length of the password here (IF MORE THAN 15 THAN CHANGE IN THIS LINE AND 2 LINES BELOW IT)
char Combination[15];
char current_combination[15];
int current_max = 4;
int address = 0;
int address1 = 0;
char temp;
int status1 = 0;
unsigned long saved_millis;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x20, 16, 2);
void setup() {
  // put your setup code here, to run once:
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  lcd.init();
  lcd.backlight();
  // current_password();
  EEPROM.write(0, 'A');
  EEPROM.write(1, 'B');
  EEPROM.write(2, 'C');
  EEPROM.write(3, 'D');
  EEPROM.write(4, '~');
}
void loop()
{
  //lcd.clear();
  //lcd.setCursor(0, 0);
  if (digitalRead(change) == LOW)
    new_password();
  current_password();

  lcd.setCursor(0, 0);
  lcd.print(Combination);
  lcd.setCursor(0, 1);
  lcd.print(current_combination);
  // addtostring(keypress1());
  keypress1();


  if(status1==0 && equality_check())
  {
    status1=1;
    saved_millis=millis();
    digitalWrite(relay,HIGH);
    addtostring('~');
  }
   if(status1==1 && (millis()-saved_millis)>waiting_time)
  {
    status1=0;
    digitalWrite(relay,LOW);
  }
  lcd.setCursor(6, 0);
  lcd.print(equality_check());
  lcd.setCursor(6,1);
  lcd.print((float)waiting_time/1000);
  waiting_time_update();
}
void waiting_time_update()
{
  if (status1==0 && digitalRead(time1)==false && digitalRead(time2)==false )
  {
    waiting_time=5000;
  }
  if (status1==0 && digitalRead(time1)==true && digitalRead(time2)==false )
  {
    waiting_time=60000;
  }
  if (status1==0 && digitalRead(time1)==false && digitalRead(time2)==true )
  {
    waiting_time=1200000;
  }
  if (status1==0 && digitalRead(time1)==true && digitalRead(time2)==true )
  {
    waiting_time=3600000;
  }
}
bool equality_check()
{
  for (int i = 0; i < current_max; i++)
  {
    if (Combination[i] != current_combination[i])
      return false;
  }
  return true;
}
void addtostring(int x)
{
  digitalWrite(13, HIGH);
    delay(250);
    digitalWrite(13, LOW);
  if (current_max > address1)
  {
    current_combination[address1] = x;
    address1++;
  }
  else
  {
    current_combination[current_max] = x;
    for (int a = 0; a < current_max; a++)
    {
      current_combination[a] = current_combination[a + 1];
      // address1++;
    }
    current_combination[current_max] = {};
  }
  while (digitalRead(0) == HIGH || digitalRead(1) == HIGH || digitalRead(2) == HIGH || digitalRead(3) == HIGH || digitalRead(4) == HIGH || digitalRead(5) == HIGH || digitalRead(6) == HIGH || digitalRead(7) == HIGH || digitalRead(8) == HIGH || digitalRead(9) == HIGH);
}
int keypress1()
{
  if (digitalRead(0) == HIGH || digitalRead(1) == HIGH || digitalRead(2) == HIGH || digitalRead(3) == HIGH || digitalRead(4) == HIGH || digitalRead(5) == HIGH || digitalRead(6) == HIGH || digitalRead(7) == HIGH || digitalRead(8) == HIGH || digitalRead(9) == HIGH)
  {
    if (digitalRead(0) == HIGH)
      addtostring('A');
    if (digitalRead(1) == HIGH)
      addtostring('B');
    if (digitalRead(2) == HIGH)
      addtostring('C');
    if (digitalRead(3) == HIGH)
      addtostring('D');
    if (digitalRead(4) == HIGH)
      addtostring('E');
    if (digitalRead(5) == HIGH)
      addtostring('F');
    if (digitalRead(6) == HIGH)
      addtostring('G');
    if (digitalRead(7) == HIGH)
      addtostring('H');
    if (digitalRead(8) == HIGH)
      addtostring('I');
    if (digitalRead(9) == HIGH)
      addtostring('J');
  }
}
int keypress()
{
  while (digitalRead(0) == LOW && digitalRead(1) == LOW && digitalRead(2) == LOW && digitalRead(3) == LOW && digitalRead(4) == LOW && digitalRead(5) == LOW && digitalRead(6) == LOW && digitalRead(7) == LOW && digitalRead(8) == LOW && digitalRead(9) == LOW)
  {
    if (digitalRead(change) == HIGH)
      return '~';
  }
  if (digitalRead(0) == HIGH)
    return 'A';
  if (digitalRead(1) == HIGH)
    return 'B';
  if (digitalRead(2) == HIGH)
    return 'C';
  if (digitalRead(3) == HIGH)
    return 'D';
  if (digitalRead(4) == HIGH)
    return 'E';
  if (digitalRead(5) == HIGH)
    return 'F';
  if (digitalRead(6) == HIGH)
    return 'G';
  if (digitalRead(7) == HIGH)
    return 'H';
  if (digitalRead(8) == HIGH)
    return 'I';
  if (digitalRead(9) == HIGH)
    return 'J';

}

void current_password()
{

  address = 0;
  while (EEPROM.read(address) != '~')
  {
    Combination[address] = EEPROM.read(address);

    address++;

  }
  //  Combination[address + 1] = '~';

  current_max = address;
}
void new_password()
{
  address = 0;
  while (digitalRead(change) == LOW)
  {
    EEPROM.write(address, keypress());

    lcd.setCursor(0, 0);
    lcd.print(EEPROM.read(address));
    address++;
    digitalWrite(13, HIGH);
    delay(250);
    digitalWrite(13, LOW);
    while (digitalRead(0) == HIGH || digitalRead(1) == HIGH || digitalRead(2) == HIGH || digitalRead(3) == HIGH || digitalRead(4) == HIGH || digitalRead(5) == HIGH || digitalRead(6) == HIGH || digitalRead(7) == HIGH || digitalRead(8) == HIGH || digitalRead(9) == HIGH);
    lcd.clear();
  }

  EEPROM.write(address + 1, '~');
  current_max = address;
}
