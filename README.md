## How I made my keyboard from scratch (pretty much)

A while back I was looking into getting a new mechanical keyboard with linear switches. I was kind of tired of the name brand keyboards like Corsair and Logitech, as they were loud and had unlubed switches, making each keypress feel terrible as well. After researching a bit, I decided to build my own instead of buying it, as it could be a fun project.

# Design

The switch layout I went with was the Keycool84 layout, featuring both arrow keys and a function row while still being relatively compact. After spending a day or two thinking about how to keep everything together, the design I went with featured a metal plate, 4 bolts, two 3D printed supports for the bolts in the middle layer, and the PCB on the bottom. the bolts would also help to create a slight incline. By using supports in between, I could avoid having to 3D print and piece together a large case that mechanical keyboards usually have. The arduino would be on the bottom under one of the bolts. 

![image](https://user-images.githubusercontent.com/64398319/158050262-5e15bb89-1599-4170-9868-493a6f08a26c.png)
![image](https://user-images.githubusercontent.com/64398319/158050263-b1dc7c28-3cb3-4891-8bff-14244251af5b.png)
![image](https://user-images.githubusercontent.com/64398319/158050266-f7abeeda-f0f4-4549-84b6-0d24b41d1794.png)
![image](https://user-images.githubusercontent.com/64398319/158050325-4f643ca3-9047-426a-84aa-c1d8a382a4ce.png)


To get an accurate outline for the keyboard, I used the Keycool84 preset layout on keyboard-layout-editor.com.
To make sure I could use the layout as a template for plate cutout later, I selected all of the keys and set each switch to use Cherry MX Kailh switch cutouts.
![image](https://user-images.githubusercontent.com/64398319/156913471-94514249-7342-45ae-94da-e16879379bad.png)
I transfered the raw data from the layout editor to http://builder.swillkb.com/ to generate a DXF file that I could actually use in KICAD.
![image](https://user-images.githubusercontent.com/64398319/156913561-4abd1c04-be77-456a-a2bf-ec5f8076c4ff.png)

# Wiring

The most important part of this keyboard is naturally its wiring. Technically, each switch could be wired to two pins to detect switch input. This obviously is extremely inefficient and would use a lot of pins. The solution to this problem is wiring the switches in a gridlike manner. One issue with this, is that if multiple keys are pressed, some keypresses can be registered incorrectly due to current traveling backwards. This is solved by placing a diode with each switch to prevent this backwards flow and makes each keypress distinguishable from others by the Arduino. The way each switch will be connected looks approximately like this:
![image](https://user-images.githubusercontent.com/64398319/157819797-67bfb5fa-5837-4856-916b-f1252c01b59c.png)

The last thing to consider was the location for each switch in the 6x14 grid. To get an idea of where each switch on the grid should be placed, I sketched it out in my note taking app. 

![image](https://user-images.githubusercontent.com/64398319/158050202-1c3fefc8-b831-4bbc-afda-89fef113b22c.png)

# The PCB

The next step was actually designing a PCB for this keyboard. For simplicity and to make sure I had enough pins, I decided to use an Arduino Pro Micro for the controller. 
For the symbols and footprints for the switches and Arduino, I used two KiCad libraries:
https://github.com/ai03-2725/MX_Alps_Hybrid 
https://github.com/Biacco42/ProMicroKiCad 

For the necessary diodes, I downloaded the ECAD Model for the 1N4148W-7-F diode at Mouser Electronics (https://www.mouser.co.uk/ProductDetail/Diodes-Incorporated/1N4148W-7-F?qs=LHX0FizJzg7Ae9ZM8LTAWw%3D%3D) and converted it into a KiCad library using the Mouser LibraryLoader. 

After including the libraries in my KiCad project file, I placed and wired the switches in the grid format. 
![image](https://user-images.githubusercontent.com/64398319/156914644-28b6951b-53ae-49a6-a32d-6735d501118d.png)

After I was finished with the schematic, I used KiCad's Pcbnew to place footprints. Using the DXF file I generated before, I imported the file and moved each associated switch and diode footprint to each cutout on the DXF. I placed the Arduino's footprint to the left and drew a border around the entire PCB. To be able to secure my keyboard plate to the PCB, I also added four holes on each corner where I could use a nut and bolt. 

![image](https://user-images.githubusercontent.com/64398319/157821436-4c10f5d9-3811-41f9-b8b4-d5429ce21891.png)

After placing all of the footprints, I routed the PCB using Freerouter. The overall complexity of the board was not too high, so using an autorouter wouldn't cause any issues.

![image](https://user-images.githubusercontent.com/64398319/158049166-65c9d70e-f2d0-451b-9de9-b5cfaf715907.png)

After adding a random bit of silkscreen for fun, this was the finished result:

![image](https://user-images.githubusercontent.com/64398319/158049203-7c9f8214-b44d-4726-a1ab-1919ce9bcc8b.png)


Using the built in 3D PCB viewer, took a look at the 3D model of what the PCB would look like. It was really neat seeing something I had designed myself.
![image](https://user-images.githubusercontent.com/64398319/157820904-c71715d5-1f2b-48c7-a5bc-12e582cc88d9.png)

# The Plate
The easiest way to maintain the same size and location for the screw holes was to make a copy of the old PCB file. After removing the switches, diodes, and Arduino footprints on a duplicate file, I ended up with a plain outline with screw holes. 

![image](https://user-images.githubusercontent.com/64398319/156914999-5e441838-1f00-4a85-bbc8-6bfe073fd34e.png)

After exporting that to a DXF and removing any duplicate geometry, it was ready to be cut.

![image](https://user-images.githubusercontent.com/64398319/156915136-90c74858-9eef-4488-aee6-487e9e8ca6b9.png)

For the plate material, I chose stainless steel for its price and for look. After doing some research, the company I had cut the plate out for me was SendCutSend. In order for the switches to slot into the plate, the plate had to be a certain width, so the 0.060 inch (about 1.5mm) thick stainless steel material SendCutSend featured was perfect. 

# The Supports

If I didn't include supports between the metal plate and the PCB, tightening the nut and bolt could cause damage to the PCB. The 3D printer my family had at the time had a small printing area, so I couldn't print something that would encompass or fit between the entirety of the keyboard. Printing it in multiple parts would be difficult as well, since the print would be so thin. The best I could compromise was to print two small pieces with bolt holes that would fit in the ~3.5mm space between the plate and PCB.

