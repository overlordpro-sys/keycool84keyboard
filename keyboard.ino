#include <Keypad.h>
#include <Keyboard.h>

const byte ROWS = 6;
const byte COLS = 14; 
char keys[ROWS][COLS] = {
  {KEY_ESC,KEY_F1,KEY_F2,KEY_F3,KEY_F4,KEY_F5,KEY_F6,KEY_F7,KEY_F8,KEY_F9,KEY_F10,KEY_F11,206,KEY_HOME},
  {'`','1','2','3','4','5','6','7','9','0','-',KEY_F12,KEY_INSERT,KEY_PAGE_UP},
  {KEY_TAB,'q','w','e','r','t','y','8','o','p','[','=',KEY_BACKSPACE,KEY_PAGE_DOWN},
  {KEY_CAPS_LOCK,'a','s','d','f','g','u','i','l',';',39,']',92,KEY_DELETE},
  {KEY_LEFT_SHIFT,'z','x','c','v','h','j','k','.','/',KEY_RIGHT_SHIFT,KEY_RETURN,KEY_UP_ARROW,' '},
  {KEY_LEFT_CTRL,KEY_LEFT_GUI,KEY_LEFT_ALT,32,'b','n','m',',',KEY_RIGHT_ALT,KEY_RIGHT_GUI,KEY_RIGHT_CTRL,KEY_LEFT_ARROW,KEY_DOWN_ARROW,KEY_RIGHT_ARROW}
};

byte rowPins[ROWS] = {18,19,20,21,22,23}; 
byte colPins[COLS] = {13,12,11,10,9,8,7,6,5,4,3,2,0,1}; 
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
    Keyboard.begin();
}

void loop() {
    if (kpd.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   
        {
            if ( kpd.key[i].stateChanged )   
            {
                switch (kpd.key[i].kstate) { 
                    case PRESSED:
                    Keyboard.press(kpd.key[i].kchar);  
                break;
                    case HOLD:
                    Keyboard.press(kpd.key[i].kchar); 
                break;
                    case RELEASED:
                    Keyboard.release(kpd.key[i].kchar);  
                break;
                    case IDLE:
                break;
                }
            }
        }
    }
} 
