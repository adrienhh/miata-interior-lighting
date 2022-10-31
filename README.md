# Neopixel Interior LED Strip for car
Underglow is illegal so I decided to add RGB lights inside the car instead.  
Because I can.

## Info
Project is designed for a Miata but is technically doable in any car depending on how the strip is set inside the car.  
I chose to run a 5 meter RGB LED strip along the bottom hinge of my doors and through the back of the seats. 
Works perfectly in my case since the cigarette lighter is located under the passenger airbag.

The LEDs are controlled by an ESP32 dev board at the moment as I have no circuit board for the lights.

## Lighting Effects
The idea is to have a series of static effects that can stay on while driving and dynamic effects that trigger when the car turns on (as it should not be a distraction to anyone).  

Code currently allows for "blending of effects" in a layer system like for picture editing (an effect can be played over another). For more info about the code, read the `README.md` file inside `lights_code`.  

(// Denotes "Not Implemented")

- Solid
- // Pulse
- // Fade
- // Marquee
- // Circular
- SequentialFade
- // Comet
- // Bounce
- // Twinkle (Turns on random LEDs on the strip)
- // Rainbow Twinkle (Same as above but with random colors)
