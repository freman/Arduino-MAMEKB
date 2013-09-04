Arduino-MAMEKB
==============

Keyboard encoder based on an Arduino for MAME

Back Story
--------------

My neighbor and his child hood buddy have gotten into a habit of making arcade machines.

They started off using Jammer 60-in-one cards and the likes which work with a button/wireing harness and does all the hard work for you.

This last weekend they decided to upgrade one of the machines to a MAME machine but didn't put enough forthought or planning into it to buy a keyboard encoder with time to allow for shipping (this is Australia after all) and given the cabinet was coming up from the gold coast (hours away)...

Off to Jaycar we come back with one of these http://www.jaycar.com.au/productView.asp?ID=XC4266 a bunch of resistors and a positive outlook.


Setup
---------------

I pulled all the pins to ground with 10k pull down resistors - you don't have to do this, in fact you can use the pull-ups built in to the microcontroller but you'll have to add external pull ups for at least pins D13, D9, D10 and possibly D11 (although you could cut the trace for the Peizo speaker)...

Hook all the pins up to the buttons/joysticks.

Define DEBUG and NOKB, compile and upload the sketch.

Open up the serial monitor and push buttons to find out which wires went where (you could plan ahead but this is easier on the brain).

Edit the code to map to the keys you want, remove the DEBUG and NOKB flags, compile and upload the sketch

Enjoy!
