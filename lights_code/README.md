# Code Design

## Lighting Effects
During execution an array of `BaseLightingEffect` is repeatedly iterated to update the frames of the lighting effects contained. As all effects inherit from this class, it makes it easy to create new effects and add them in.  
For an effect to properly be executed by the main loop, it requires a definition of the `update()` function which updates lighting effect by a single frame. However, defining other virtual methods such as `reset()` can also be useful.

### Blending effects
Still working on a proper way to design that. Currently, iterating an array of running effects allows for a mix of effects similar to layers in picture editing.  
However, that design choice becomes inconvenient when bright effects start mixing with each other. For example, a `SequentialFade` or a `Comet` effect over a solid white background will fade the trailing pixels in black when the user could instead be looking for fade to that background color.  

### Effect State
Each effect playing on the LED strip is represented by an object derived from the `BaseLightingEffect` class. When created the state of the effect is defaulted to `READY` and calling the update method for that effect will switch its state to `PLAYING`.  
When the effect is done playing (ie. for the comet effect, when the comet reaches the end of the strip) it's state will be switched to `DONE` and the update method will not do anything when called anymore. The developer can either choose to delete the item from the array of running effects or to call the reset method which will set the object back to it's state when created so that it can be played again.  
  
Some do not change state even after calling `update()` due to their nature. For example, updating the `SolidFill` effect immediately completes the effect, therefore it will never go through the `PLAYING` state. Otherwise, the `Bounce` effect will never reach the `DONE` state as the effect will never end.  
  
The `PAUSED` effect is defined but currently unused.