An easy video tutorial to flash the firmware to the ESP32 without building it: <br>
https://youtu.be/p8CsZYtNyKA?feature=shared
<br>
All my videos about SOCORAD32:
<br>https://youtube.com/playlist?list=PLKM5FNxF7v40e-xXsQXLKmqm96md1w-Cb&feature=shared
<br>
<br>Join SOCORAD32 Discord Community here: 
<br>
https://discord.gg/6VwVRRuCVW
<br><br>

# Why SOCORAD32-Advanced-Firmware?
<br>-We have now a menu to:
<br>--Change channel quickly
<br>--Edit VOX level
<br>--more comming...
<br>-The bootup is faster
<br>-The interface is faster (You can now change volume easily)


Todo:
<br>-VOX to EEPROM
<br>-Volume to EEPROM
<br>-TX Power submenu section + EEPROM + serial
<br>-Mute function
<br>-Clarify readme, upload how to video add links corresponding
<br>-Scan function
<br>-Try to add a "vfo" mode


# SOCORAD32 - ESP32 SOftware COntrolled RADio

<br/> (3D enclosure design already released)
<br/>
<br />Add a speaker and a battery, then you'll have a fully functional walkie talkie Radio. It shares the same properties as the commercial one. Can be used both for voice and data communication. Because it can communicate data, we can explore the amateur radio frequency for IoT.
<br/>Beyond communication, it is fully open source and hackable!
<br />The central module contains the special purpose RDA1846 IC. This same IC is used in commercial walkie talkies such as in Baofeng and Hytera. <br/>

<br/>Other of its peripherals is an onboard ESP32 for parameter settings (via Bluetooth or WiFi), control and storage. 
<br/>The ESP32 talks to the central module using simple AT commands. The specifications are listed below.

# Specifications
Frequency Range: 400-470mhz covers most countries allocated walkie talkie frequencies, especially the license free ones.
<br/> Frequency Step: 5K/6.25K/12.5K/25K
<br/> RF Output Power: 2W/1W/0.5W
<br/> Voice features, Tone Squelches, SMS capability:
<br/> Voice encryption (scrambling): 8 types
<br/> SMS Receive/Transformer, baudrate: 1200
<br/> CTCSS (38 groups) + CDCSS (83 groups)
<br/> Automatic elimination tail
<br/> Volume adjustable (1-8)
<br/> Squelch level adjustable (0-9)
<br/> MIC sensitivity level adjustable (1-8)
<br/> Sleep Mode (0.1μA)
<br/><br/>To talk to the module, a generic Bluetooth serial communication APP is used on the phone to connect to the ESP32 module which in turn communicates with the RF module via UART. Due to the SOCORAD32 rich features, it can be used for the following applications.


# Applications
Walkie Talkie
<br/>Intercom
<br/>Pager
<br/>IoT (data transmission module)
<br/><br/>The AT commands are in the repository. It includes commands for volume control, power output, RX/TX frequencies, voice activated exhange, squelching, etc.
<br/>The device contains a dedicated PTT button and extra buttons for user configurations.

## First run / Flashing
See [Final Firmware](DOCS/Final_Firmware.md) for instructions
<br> I made a very easy flash how to on windows [BIN/README.md](BIN/README.md)

<br/>![SOCORAD32 high rez](https://user-images.githubusercontent.com/88499684/215540777-c825e2d2-a014-41b9-847e-6e92eacf6c23.png)
<br><br>Menu looks like:
<br/>![SOCORAD32 menu](https://github.com/joyel24/SOCORAD32-Advanced-Firmware/blob/main/DOCS/socorad32-advanced-menu.jpg?raw=true)
<br><br>Home looks like:
<br/>![SOCORAD32 home](https://github.com/joyel24/SOCORAD32-Advanced-Firmware/blob/main/DOCS/socorad-home.jpg?raw=true)
