# Protogen

## Frimware

- Set up `config.h`
  - Set or unset DEBUG flag as needed
  - Make sure brightness is set on a reasonable level depending on power source (high brightness may fry components if current routed through ESP)
  - Make sure WiFi name and password is set correctly

## BOM

- ESP32 [ESP32](https://dratek.cz/arduino/1581-esp-32s-esp32-esp8266-development-board-2.4ghz-dual-mode-wifi-bluetooth-antenna-module.html)
- 2x 16x16 Neopixel-compatible displays
- battery holder [SBH-341-1AS držák baterie 4xAA](https://www.gme.cz/v/1506924/sbh-341-1as-drzak-baterie-4xaa)
- 2x 470uF / 5+V capacitors [HITANO CE 470u/25VIT](https://www.gme.cz/v/1485865/hitano-ce-470u-25vit-hit-exr-10x16-rm5-bulk-elektrolyticky-kondenzator)
- 3.3V to 5V logic translator [IIC I2C 5V to 3.3V](https://dratek.cz/arduino/1481-iic-i2c-5v-na-3.3v-obousmerny-prevodnik-logicke-urovne.html)
- The rest of the protogen

![proto](https://user-images.githubusercontent.com/8028882/236701038-a80ce5f3-3012-4528-be68-1b71acf7782d.gif)

# Tooling

## Control center (protogen-phone-control)
    npm install
    npm run build
    
![photo_2023-05-07_22-11-10](https://user-images.githubusercontent.com/8028882/236700550-8f14f148-c867-41c7-8a31-d43c892e0fd3.jpg)

## Animation generator (animation-generator)
    .\env\Scripts\activate.bat
    pip install -r requirements.txt
    python img-to-str.py ./test-animations/smile
    
Then you need to manually create animation library from the outputs (see `temp.json`), minimize it and put the string in animationBookJson[] in `AnimationBook.h`. 
