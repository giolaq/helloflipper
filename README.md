# Flipper Hello World app
This project is an Hello World app for Flipper Zero.

<img src="https://github.com/giolaq/helloflipper/blob/main/gif/helloworld.gif" alt="Demo" width="600"/>

It was tested with the firmware version 0.70.1.

The app will shown on the Flipper Zero display an airplane image and you can move the airplane
by using the directional pad.

## Build the app

1.Clone [flipperzero-firmware](https://github.com/flipperdevices/flipperzero-firmware). 
```sh 
git clone --recursive https://github.com/flipperdevices/flipperzero-firmware.git
```
2.Create a folder inside the *flipperzero-firmware/applications_user* directory
```sh
$ cd applications_user/
$ mkdir helloflipper
```
3.Add the content of this project in the *helloflipper* folder
4.From the directory flipperzero-firmware run
```sh
$ pip3 install -r scripts/requirements.txt
```
5.Build the firmware running
```sh
$ ./fbt
```
6.Build the Hello World app running
```sh
./fbt fap_helloflipper
```
7.Connect the Flipper Zero with via the USB-C
8.Launch the Hello World app running
```sh
./fbt launch_app APPSRC=applications/helloflipper
```
