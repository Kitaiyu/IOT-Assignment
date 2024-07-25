#include <LiquidCrystal.h>  
#include <Keypad.h>       
#include <Servo.h>         
Servo myservo;
int pos = 0;
LiquidCrystal lcd(13, 11, 5, 4, 3, 2);
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[ROWS] = { 12, 10, 9, 8 };
byte colPins[COLS] = { 7, 6, A0, A1 };
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
String pass = ""; 
void setup() {          
  myservo.attach(A2);
  myservo.write(0);
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Mat Khau Moi:");
  int x = 0;
  char customKey;
  while (true) {
    customKey = customKeypad.getKey();
    if (customKey) {
      if (customKey == '#') {
        if (pass.length() < 4) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("MK phai >=4 k.tu");
          delay(2000);
          lcd.setCursor(0, 0);
          lcd.print("Mat Khau Moi:   ");
          x = 0;
          pass = "";
          continue;
        } else break;
      }
      if (customKey == 'C' && pass.length() > 0) {
        x--;
        pass.remove(x);
        lcd.setCursor(x, 1);
        lcd.print(" ");
      } else if ((customKey - 48) >= 0 && (customKey - 48) <= 9) {
        lcd.setCursor(x, 1);
        lcd.print("*");
        pass += customKey;
        x++;
      }
    }
  }
  lcd.clear();
  menu();
}

void menu() {  
  lcd.setCursor(0, 0);
  lcd.print("1.Mo Khoa");
  lcd.setCursor(0, 1);
  lcd.print("2.Mat Khau Moi");
}

void loop() {  
  char customKey;
  customKey = customKeypad.getKey();
  if (customKey) {
    if (customKey == '1') { 
      nhapMk();
    } else if (customKey == '2') {  
      newMk();
    }
  }
}

void nhapMk() {  //(4)
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mat Khau:");
  int x = 0;
  String pass2 = "";
  char customKey;
  while (true) {
    customKey = customKeypad.getKey();
    if (customKey) {
      if (customKey == '*') {
        menu();
        return;
      }
      if (customKey == '#') {
        break;
      }
      if (customKey == 'C' && pass2.length() > 0) {
        x--;
        pass2.remove(x);
        lcd.setCursor(x, 1);
        lcd.print(" ");
      } else if ((customKey - 48) >= 0 && (customKey - 48) <= 9) {
        lcd.setCursor(x, 1);
        lcd.print("*");
        pass2 += customKey;
        x++;
      }
    }
  }

  if (pass2.equalsIgnoreCase(pass)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mo Khoa.");
    done();
    lcd.clear();
    menu();
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sai MK. Doi 3s.");
    delay(3000);
    lcd.clear();
    menu();  
  }
}

void done() { 
  for (pos = 0; pos <= 90; pos += 1) {  
    myservo.write(pos);
    delay(30); 
  }
  delay(1000);
  for (pos = 90; pos >= 0; pos -= 1) {  
    myservo.write(pos);
    delay(30);  // 
  }
}

void newMk() {  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mat Khau Cu:");
  int x = 0;
  String pass2 = "";
  char customKey;
  while (true) {
    customKey = customKeypad.getKey();
    if (customKey) {
      if (customKey == '*') {
        lcd.clear();
        menu();
        return;
      }
      if (customKey == '#') {
        if (pass2.equalsIgnoreCase(pass)) {
          break;
        } else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Sai MK. Doi 3s.");
          delay(2000);
          lcd.setCursor(0, 0);
          lcd.print("Mat Khau Cu:   ");
          pass2 = "";
          x = 0;
        }
      } else if (customKey == 'C' && pass2.length() > 0) {
        x--;
        pass2.remove(x);
        lcd.setCursor(x, 1);
        lcd.print(" ");
      } else if ((customKey - 48) >= 0 && (customKey - 48) <= 9) {
        lcd.setCursor(x, 1);
        lcd.print("*");
        pass2 += customKey;
        x++;
      }
    }
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mat Khau Moi:");
  x = 0;
  String passNew = "";
  while (true) {
    customKey = customKeypad.getKey();
    if (customKey) {
      if (customKey == '*') {
        lcd.clear();
        menu();
        return;
      }
      if (customKey == '#') {
        if (passNew.length() < 4) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("MK phai >=4 k.tu");
          delay(2000);
          lcd.setCursor(0, 0); 
          lcd.print("Mat Khau Moi:   ");
          x = 0;
          passNew = "";
          continue;
        } else {
          lcd.clear();
          lcd.setCursor(0, 0);
          String passNew2 = "";
          lcd.print("Nhap Lai:");
          x = 0;
          while (true) {
            customKey = customKeypad.getKey();
            if (customKey) {
              if (customKey == '*') {
                lcd.clear();
                menu();
                return;
              }
              if (customKey == '#') {
                if (passNew2.equalsIgnoreCase(passNew)) {
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("Thanh Cong.");
                  pass = passNew;          
                  delay(3000);
                  lcd.clear();
                  menu();
                  return;
                } else {
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("Sai, Nhap Lai:");
                  x = 0;
                  passNew2 = "";
                }
              } else if (customKey == 'C' && passNew2.length() > 0) {
                x--;
                passNew2.remove(x);
                lcd.setCursor(x, 1);
                lcd.print(" ");
              } else if ((customKey - 48) >= 0 && (customKey - 48) <= 9) {
                lcd.setCursor(x, 1);
                lcd.print("*");
                passNew2 += customKey;
                x++;
              }
            }
          }
        }
        } else if (customKey == 'C' && passNew.length() > 0) {
        x--;
        passNew.remove(x);
        lcd.setCursor(x, 1);
        lcd.print(" ");
      } else if ((customKey - 48) >= 0 && (customKey - 48) <= 9) {
        lcd.setCursor(x, 1);
        lcd.print("*");
        passNew += customKey;
        x++;
      }
    }
  }
}