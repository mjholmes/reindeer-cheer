# CheerLights Reindeer

![Reindeer head with CheerLights nose](/_content/reindeer-cheer.jpg)

 >With the [Cheerlights project](http://cheerlights.com/) Reindeers are no longer stuck with red noses! This is a quick guide detailing how I brought a bit of CheerLights Christmas cheer to the office.


## Laser cut head
I'm using the excellent ["Mounted Deer / Reindeer Head"](http://www.thingiverse.com/thing:34513) by [phenoptix](http://www.thingiverse.com/phenoptix) which is licensed under the Creative Commons - Attribution - Share Alike license. I've modified the design to add a couple of notches to allow cables to be threaded through from front to back and add some holes to the nose. The design files contain two noses, one with a 5mm hole for threading cables etc and another for a standard 10mm LED; my editing in AutoCAD has bloated the file size a bit.

The design was cut from 3mm (ish) birch ply on a [HPC Laserscript 3060](http://hpclaser.co.uk/index.php?main_page=product_info&products_id=39) using a power level of 97% and a speed of 12 which seems about right for the material. Once cut a little bit of gentle sanding was required to make things fit nicely.

The CheerLights "necklace" was created in [Inkscape](https://inkscape.org), modified so that the characters touched and then cut from 3mm green Acrylic. It is surprisingly rigid given how fine the lettering is.

## CheerLights integration
I'm using a WS2812B based [Neopixel](https://www.adafruit.com/products/1612) for the nose, you can pick these up from most Adafruit resellers and various other places on the web. Controlling the Neopixel is a [Particle Photon](https://www.particle.io/prototype) which is tucked into the "neck" of the Reindeer head, the Photon connects to the [CheerLights channel](https://thingspeak.com/channels/1417) on [ThingSpeak](https://thingspeak.com/) using WiFi and updates the Neopixel colour according to the latest CheerLights value. The Photon is connected to the Neopixel according to the diagram below, I used 3-core ribbon cable taken from a wider piece but any cable will do.

![Fritzing diagram of Photon Neopixel connections](/_content/photon_connections.png)

Once the Photon was [connected to WiFi](https://docs.particle.io/guide/getting-started/start/photon/#step-1-power-on-your-device) I used the [Particle Web IDE](https://build.particle.io/login) to write some code. There are lots of good examples on the web of integrating with CheerLights but the ThingSpeak library within the Particle Web IDE comes with a CheerLights example right out of the box, thanks!

> Note that within the Particle Web IDE there are two ThingSpeak libraries which are, unhelpfully, both call THINGSPEAK.
> I used the official [Mathsworks library](mathworks/thingspeak-particle) which adds "#include "ThingSpeak/ThingSpeak.h" to the top of your app.

I've modified the example code from both the ThingSpeak and Neopixel libraries so that the colours fade instead of switching when CheerLights updates. The full listing can be found in [/firmware/reindeer-cheer.ino](/firmware/reindeer-cheer.ino).

To create and compile my code in the Particle Web IDE:

1. Login to the Web IDE
2. In the "Code" section choose "Create new App"
3. Choose a title for your app and click Save
4. Click on the Libraries section and search for Neopixel
5. Click on the Neopixel library and choose "include in app"
6. Choose the app you created above and then hit "add to this app"
7. Repeat steps 4 to 6 for the ThingSpeak library
8. Copy and paste the code from [/firmware/reindeer-cheer.ino] into your app making sure you delete anything that already exists.
9. Save your changes
10. In the Devices section choose the Photon you connected earlier
11. Choose flash.

At this point your Photon should flash magenta and then your Neopixel should spring into life. Assuming all went well you are now safe to mount your Photon into the compartment formed at the back of the Reindeer head. Some foam sticky pads work very well for this.

![Cable routing within the Reindeer head](/_content/reindeer_inside.JPG)

## Useful references

* Adafruit Neopixel uber guide - https://learn.adafruit.com/adafruit-neopixel-uberguide/overview
* Particle Web IDE beginners guide - https://docs.particle.io/guide/getting-started/build/photon/
* CheerLights build guide - http://cheerlights.com/build/