# WiFiRM04 Library

WiFiRM04 library is an Arduino WiFi library for Hi-Link HLK-RM04 module. (http://www.hlktech.com/en/productshow.asp?id=142)
This library is compatible with Arduino WiFi library and all examples of Arduino WiFi library could be compiled with this
library with just a little modification.

This repository is fork from the original library for Aduino Uno application.
Original page : https://github.com/chunlinhan/WiFiRM04

## How to Install

1. Download the WiFiRM04 library source.
1. In the Arduino IDE, go to the Sketch -> Import Library... -> Add Library...
1. Find the directory that contains the WiFiRM04 library source, and open it
1. Check if you could see "WiFiRM04" under Sketch -> Import Library...

## Basic requirement of Mine

1. Should work with Arduino Uno
1. Should work with Software Serial library
1. Only client functionlity was required for me

## How to Use

I tried this library with Uno + AltSoftSerial library. You need to modify AltSoftSerial library slightly. (patch is shared in the repository.)

I don't know the reason, but AltSoftSerial should be initialized in the main sketch file.

## Dislclaimer

This library is very unstable because of limited memory of Uno. It works anyway for my purpose. :)

## ToDo

1. Make a example application.

## Other Resources
User manual of HLK-RM04 module. (http://www.hlktech.net/inc/lib/download/download.php?DId=19)

This user manual doesn't contain the AT commands of lateset official firmware. (V1.78)
You could find more useful information from the OpenWrt forum. (https://forum.openwrt.org/viewtopic.php?id=42142)
