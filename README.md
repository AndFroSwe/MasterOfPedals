# Master of Pedals
A guitar pedal switching rig. Readymade presets are chosen by hitting a
footswitch on the stage pedal. The final goal of the repo is to have a modular
design that can easily be modified to the given specs.

# Features

1. At the hit of a footswitch, pedals are engaged as per the corresponding
   preset. No more tapdancing!
2. Presets can be changed on the main unit.

# Units

- __Control unit__: The main control unit. All pedals are connected to this and
presets are set here. 
- __Stage pedal__: Unit placed at the front of the stage. Has a set of
  footswitches for preset choice and a simple interface that shows the user
which preset is currently chosen.

# Repository guide

- __./Software/__ contains all source code for the MCUs. Divided into subfolders
  corresponding to the stage pedal and the control unit.
- __./KiCad/__ contains electrical schematics. Divided into subfolders
  corresponding to the stage pedal and the control unit.

# Prototype unit
The repo has a fully ready-to-go (when it's done) unit. This unit has the
following specs:

- 8 pedals in the control loop.
- 3 independently controlled amp channels.
- 6 presets.
- Stage pedal is connected via cord (i.e. it is not wireless).
- It has a simple user interface at the control unit that allows the user to
  change the presets.

# Future features
- __MIDI control output__: An output that can send MIDI messages to pedals.
- __Wireless control__: The stage pedal can send control signals to the control
  unit wirelessly. This also enables multiple control units. This could be used
in a mini control unit that is carried on the guitar.
- __Internal pedal power supply__: The control unit contains a PSU that can feed
  the guitar pedals with power.
- __Battery power supply__: The stage pedal runs on battery.
- __Data logging__: The pedal remembers which presets have been used.
