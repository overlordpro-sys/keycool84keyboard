# How I Made My Mechanical Keyboard

A few months ago, I was looking into getting a new mechanical keyboard with linear switches. I had grown tired of the name brand keyboards like Corsair and Logitech who did not lubricate their switches. This made each keypress loud and unsatisfying. After doing some research, I decided to build my own instead of buying it. Most people who build custom keyboards buy a predesigned PCB. However, I wanted to design the PCB myself because I thought it would be fun. In the end, that proved true and I learned a lot about the inner workings of mechanical keyboards and PCB design. 

## Design

The switch layout I chose was the Keycool84 layout, featuring both arrow keys and a function row while still being relatively compact. After spending a day or two thinking about how to piece each component together, the design I went with featured a metal plate, 4 M4x10 bolts, two 3D printed supports for the bolts in the middle layer, and the PCB on the bottom. The bolts would also serve as a stand and create a slight incline. By using supports in between, I could avoid having to 3D print and piece together a large case that mechanical keyboards usually have. The Arduino would be placed to the side under one of the bolts. 

![image](https://user-images.githubusercontent.com/64398319/158050262-5e15bb89-1599-4170-9868-493a6f08a26c.png)
![image](https://user-images.githubusercontent.com/64398319/158050263-b1dc7c28-3cb3-4891-8bff-14244251af5b.png)
![image](https://user-images.githubusercontent.com/64398319/158050266-f7abeeda-f0f4-4549-84b6-0d24b41d1794.png)
![image](https://user-images.githubusercontent.com/64398319/158050325-4f643ca3-9047-426a-84aa-c1d8a382a4ce.png)


To get an accurate outline for the keyboard, I used the Keycool84 preset layout on keyboard-layout-editor.com.
In addition, I selected all of the keys and set each switch to use Cherry MX Kailh switch cutouts for my switch of choice, Kailh speed silvers, so I could use it to help with the plate cutout later on.
![image](https://user-images.githubusercontent.com/64398319/156913471-94514249-7342-45ae-94da-e16879379bad.png)
I transfered the raw data from the layout editor to a [plate and case builder website](http://builder.swillkb.com/) to generate a DXF file that I could actually use in KiCAD.
![image](https://user-images.githubusercontent.com/64398319/156913561-4abd1c04-be77-456a-a2bf-ec5f8076c4ff.png)

## Wiring

The most important part of this keyboard is naturally its wiring. Technically, each switch could be wired to two pins to detect switch input. This obviously is extremely inefficient and would use a lot of pins. The solution to this problem is wiring the switches in a gridlike manner. One issue with this, is that if multiple keys are pressed, some keypresses can be registered incorrectly due to current traveling backwards. This is solved by placing a diode with each switch to prevent this backwards flow and makes each keypress distinguishable from other keys by the Arduino. Each switch is wired approximately like so:
![image](https://user-images.githubusercontent.com/64398319/157819797-67bfb5fa-5837-4856-916b-f1252c01b59c.png)

The last thing to consider was the location for each switch in the 6x14 grid. To get an idea of where each switch on the grid should be placed, I sketched it out in an app. 

![image](https://user-images.githubusercontent.com/64398319/158050202-1c3fefc8-b831-4bbc-afda-89fef113b22c.png)

## The PCB

The next step was designing the PCB for this keyboard. For simplicity and to ensure I had enough pins, I decided to use an Arduino Pro Micro for the controller. 
For the symbols and footprints for the switches and Arduino, I used two KiCad libraries:
https://github.com/ai03-2725/MX_Alps_Hybrid 
https://github.com/Biacco42/ProMicroKiCad 

For the necessary diodes, I downloaded the ECAD Model for the [1N4148W-7-F diode](https://www.mouser.co.uk/ProductDetail/Diodes-Incorporated/1N4148W-7-F?qs=LHX0FizJzg7Ae9ZM8LTAWw%3D%3D) at Mouser Electronics  and converted it into a KiCad library using the Mouser LibraryLoader. 

After including the libraries in my KiCad project file, I first wired the switches in a grid format in the schematics file. Then I assigned each row and column to a pin on the Arduino's symbol.
![image](https://user-images.githubusercontent.com/64398319/156914644-28b6951b-53ae-49a6-a32d-6735d501118d.png)

After I was finished with the schematic, I used KiCad's Pcbnew to design the PCB. Using the DXF file I generated before, I imported the file and moved each associated switch and diode footprint to each cutout on the DXF. I placed the Arduino's footprint to the left and drew a border around the entire PCB. To be able to secure my keyboard plate to the PCB, I also added four holes with a diameter slightly larger than the bolt diameter on each corner where I could use a nut and bolt. 

![image](https://user-images.githubusercontent.com/64398319/157821436-4c10f5d9-3811-41f9-b8b4-d5429ce21891.png)

After placing all of the footprints, I routed the PCB using Freerouter. Overall, the board was simple and using an autorouter wouldn't cause any issues.

![image](https://user-images.githubusercontent.com/64398319/158049166-65c9d70e-f2d0-451b-9de9-b5cfaf715907.png)

After adding some silkscreeneening out of curiosity, this was the finished result:

![image](https://user-images.githubusercontent.com/64398319/158049203-7c9f8214-b44d-4726-a1ab-1919ce9bcc8b.png)


Using the built in 3D PCB viewer, took a look at the 3D model of what the PCB would look like. It was really neat seeing something I had designed myself.
![image](https://user-images.githubusercontent.com/64398319/157820904-c71715d5-1f2b-48c7-a5bc-12e582cc88d9.png)

After generating the neccessary Gerber files, I placed my order with JLCPCB and chose a white PCB. Here's what the PCBs looked like when they came:
![image](https://user-images.githubusercontent.com/64398319/163095199-d4282166-2887-47cb-b82f-f2c585919dc5.png)

## The Plate
The easiest way to maintain the same size and location for the screw holes was to make a copy of the old PCB file. After removing the switches, diodes, and Arduino footprints on the duplicate project, I ended up with a plain outline with screw holes. 

![image](https://user-images.githubusercontent.com/64398319/156914999-5e441838-1f00-4a85-bbc8-6bfe073fd34e.png)

After exporting that to a DXF and removing any duplicate geometry in LibreCAD, it was ready to be cut.

![image](https://user-images.githubusercontent.com/64398319/156915136-90c74858-9eef-4488-aee6-487e9e8ca6b9.png)

After doing some research, I chose SendCutSend to cut my plate. In order for the switches to slot into the plate, the plate had to be a certain width, so the 0.060 inch (about 1.5mm) thick stainless steel material SendCutSend supplied was great. 

Unfortunately, I didn't take a very good picture before I soldered everything together, so this is the only picture I have of the plate by itself. 
![image](https://user-images.githubusercontent.com/64398319/163095856-64816638-67b0-4505-9fdb-85be14e450b3.png)

## 3D Printing the middle

At first, I wanted to make a case that would encompass the entirety of the keyboard. However, the 3D printer I had at home would not be large enough to print it in one piece. Printing it in multiple pieces would require me to glue the pieces together and would make it less durable. I also didn't want to bother sending an order to a third party printing service and increasing my total build cost. At the very least, I wanted to make something that would fill some of the ugly gap between the plate and PCB. Filling in the gaps in the front and back of the keyboard would make it too large to print on my printer, so I could only make something for the right and left. In the end, I decided to make two rectangles with the cutouts for the bolts. 
![image](https://user-images.githubusercontent.com/64398319/163069469-5db6c803-8254-4282-bb52-5a77cc765ab5.png)

In order to move it from KiCad to my modeling software of choice, Fusion 360, I plotted it into a DXF file and imported it with a 3.5mm thickness (approximate amount of space between the PCB and plate) using [DXF Import Utility.](https://apps.autodesk.com/FUSION/en/Detail/Index?id=3146198746757677787&appLang=en&os=Win64) 
![image](https://user-images.githubusercontent.com/64398319/163076669-806fe629-d160-4fd3-8334-9b8d3aad0fc6.png)
After that, I exported each part into Cura with Fusion's built in exporter, merged the models into one project, and exported the G-code file for my 3D printer. 

![image](https://user-images.githubusercontent.com/64398319/163076444-9f08e2bd-0422-494a-8ac4-8bb8a6fc309e.png)
![image](https://user-images.githubusercontent.com/64398319/163076477-ad4a812a-ee4c-41ad-8c8a-6064a645b61d.png)
![image](https://user-images.githubusercontent.com/64398319/163076375-7473896c-d5f1-4080-9028-d571c682d53a.png)

## Software
To communicate the keystrokes, I used the Arduino libararies [Keypad](https://playground.arduino.cc/Code/Keypad/) and [Keyboard](https://www.arduino.cc/reference/en/language/functions/usb/keyboard/). The best thing about the Keypad library is that it supports N-key rollover to intepret multiple keypresses at the same time. For my keyboard, I edited Keypad's provided example. I added which keys I needed, edited the pins to use, and had it use Keyboard to send keystrokes instead of just printing them to console. 

```javascript
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
```
## The Finished Product
After tediously placing and soldering each switch and surface mounted diode, it was almost complete. After fixing a small issue with my soldering using a spare wire and tightening the bolts, it was finished! If I do make a another keyboard in the future, I would definitely try to use something other than an Arduino that I could fully integrate into the PCB.
![image](https://user-images.githubusercontent.com/64398319/163095992-90e54a77-97ab-4044-b17c-40da664bfaed.png)
![image](https://user-images.githubusercontent.com/64398319/163123863-2121ebb1-3a9c-4fe3-bfff-c6a5e213ee7c.png)
