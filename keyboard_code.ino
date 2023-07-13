#include <EasyHID.h>
#include <GyverButton.h>

#define pot A2
boolean led_flag = 1;
boolean all_led_flag = 1;
int x_flag = -1;
int x = 0;
int val = 0;
uint32_t myTimer1;
GButton rbt(A3);
GButton cbt(A4);
GButton lbt(A5);
GButton sbt(A2);

void setup()
{
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
    digitalWrite(6, 0);
    digitalWrite(7, 0);
    digitalWrite(3, 0);
}

void loop()
{
    if (x_flag == -1)
    {
        myTimer1 = millis();
        digitalWrite(3, 1);
        digitalWrite(7, 0);
        x_flag = 0;
    }

    if (x_flag == 1 && millis() - myTimer1 > 400)
    {
        Keyboard.println("2323");
        x_flag = 2;
    }

    rbt.tick();
    cbt.tick();
    lbt.tick();
    sbt.tick();
    if (x_flag == 0)
    {
        if (millis() - myTimer1 > 500)
        {
            digitalWrite(7, 1);
            digitalWrite(3, 0);
        }

        if (millis() - myTimer1 > 1000)
            x_flag = -1;
        if (rbt.isClick() || cbt.isClick() || sbt.isClick())
        {
            Keyboard.click(KEY_ENTER);
            x_flag = 1;
            myTimer1 = millis();
        }

        if (lbt.isClick())
            x_flag = 2;
    }

    if (x_flag == 2)
    {
        digitalWrite(13, 1);
        digitalWrite(6, 1);
        digitalWrite(7, 0);
        digitalWrite(3, 0);
        x_flag = 3;
    }

    if (x_flag == 3)
    {
        if (sbt.isClick())
        {
            if (val % 2 == 0)
                val++;
            else val = 0;
        }

        if (sbt.isHold())
        {
            if (rbt.isClick())
            {
                all_led_flag = !all_led_flag;
                digitalWrite(13, led_flag & all_led_flag);
                digitalWrite(6, led_flag & all_led_flag);
                if (val % 2 == 0)
                    digitalWrite(7, all_led_flag);
                else digitalWrite(3, all_led_flag);
            }

            if (cbt.isClick())
                for (int i = 0; i < 5; i++)
                    Keyboard.clickMultimediaKey(KEY_VOL_UP);
            if (cbt.isHold())
                Keyboard.clickMultimediaKey(KEY_VOL_UP);
            if (lbt.isClick())
                for (int i = 0; i < 5; i++)
                    Keyboard.clickMultimediaKey(KEY_VOL_DOWN);
            if (lbt.isHold())
                Keyboard.clickMultimediaKey(KEY_VOL_DOWN);
        }

        switch (val % 2)
        {
            case 0:
                if (all_led_flag)
                    digitalWrite(7, 1);
                digitalWrite(3, 0);
                if (lbt.isClick())
                {
                    Keyboard.click(KEY_HOME);
                }

                if (rbt.isClick())
                {
                    Keyboard.click(KEY_ARROW_LEFT, KEY_ARROW_RIGHT);
                    led_flag = !led_flag;
                    if (all_led_flag)
                    {
                        digitalWrite(13, led_flag);
                        digitalWrite(6, led_flag);
                    }
                }

                if (cbt.isClick())
                {
                    Keyboard.print("`");
                    for (int i = 1000; i > 900; i -= 7)
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
                if (all_led_flag)
                    digitalWrite(3, 1);
                if (lbt.isClick())
                    Keyboard.clickMultimediaKey(KEY_SCAN_NEXT_TRACK);
                if (rbt.isClick())
                    Keyboard.clickMultimediaKey(KEY_SCAN_PREV_TRACK);
                if (cbt.isClick())
                    Keyboard.clickMultimediaKey(KEY_PLAYPAUSE);
                break;
        }
    }

    HID.tick();
}
