## Mini-Arduino-Keyboard
Last version: ![image](https://user-images.githubusercontent.com/77449049/200173822-5b18476d-9134-4d5e-897b-ea924eec0aec.png)
First version: ![image](https://user-images.githubusercontent.com/77449049/200174062-8e706e7f-1180-4cae-99fb-114de2bc6a27.png)


Bad code on Arduino c++ for keyboard with my binds
```c++

#include <EasyHID.h>
#include <GyverButton.h>

#define pot A2
boolean led_flag = 1;
int x_flag = 0;
int x = 0;
int val = 0;
uint32_t myTimer1;
GButton rbt (A4);
GButton cbt (A3);
GButton lbt (A2);
GButton sbt (A5);

void setup() {
  HID.begin();
  pinMode(A2, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(13, 1);
  digitalWrite(6, 1);
}

void loop() {
  if (x_flag == 1 && millis() - myTimer1 > 400) {
    Keyboard.println("***mypassword***");
    x_flag = 2;
  }

  rbt.tick();
  cbt.tick();
  lbt.tick();
  sbt.tick();
  //val = analogRead(pot);
  //val = map(val, 0, 1023, 0, 1);
  //val = constrain(val, 0, 1);

  /*if (x - val < 4 && x - val > -4 && val > 5 && val < 1018) {
    if (val > 500)
      Keyboard.clickMultimediaKey(KEY_VOL_UP);
    if (val < 500)
      Keyboard.clickMultimediaKey(KEY_VOL_DOWN);
    x = val;
    }*/
  if (x_flag == 0 && (lbt.isClick() || rbt.isClick() || cbt.isClick() || sbt.isClick())) {
    Keyboard.click(KEY_ENTER);
    x_flag = 1;
    myTimer1 = millis();

  }
  //int a = val < 500 ? 0 : 1;

  if (sbt.isClick()) {
    val++;
    if (val % 2 == 0)
      Keyboard.clickMultimediaKey(KEY_VOL_DOWN);
    else Keyboard.clickMultimediaKey(KEY_VOL_UP);
  }
  switch (val % 2)
  {
    case 0:
      if (x_flag != 0)
        digitalWrite(7, 1);
      digitalWrite(3, 0);
      if (lbt.isClick()) {
        Keyboard.click(KEY_HOME);
      }
      if (rbt.isClick()) {
        Keyboard.click(KEY_ARROW_RIGHT, KEY_ARROW_LEFT);
        led_flag = !led_flag;
        digitalWrite(13, led_flag);
        digitalWrite(6, led_flag);
      }
      if (cbt.isClick()) {
        Keyboard.print("`");
        for (int i = 1000; i > 900 ; i -= 7) 
        {
          Keyboard.print("say ");
          Keyboard.print(i);
          Keyboard.print(" - 7 = ");
          Keyboard.println(i - 7);
        }
        Keyboard.print("`");
      }
      break;
    case 1:
      digitalWrite(7, 0);
      digitalWrite(3, 1);
      if (lbt.isClick())
        Keyboard.clickMultimediaKey(KEY_SCAN_PREV_TRACK);
      if (rbt.isClick())
        Keyboard.clickMultimediaKey(KEY_SCAN_NEXT_TRACK);
      if (cbt.isClick())
        Keyboard.clickMultimediaKey(KEY_PLAYPAUSE);
      break;

  }
  HID.tick();
}
```
