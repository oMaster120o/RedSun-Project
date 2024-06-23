# RedSun Project
  
> [!WARNING]
> The RedSun Project can be classified as malware but also as an auxiliaty tool during Red Teaming to gather info about the target **(after you already have persistent access)** that has been created as a personal project for **learning** and also to acquire practical experience on writting malware, understanding how UNIX based distros work, understand how malware works and also to practice the C programming language.  
> This repo is **NOT** intented to distribute malware nor contribute to any form of illegal activity.  
> **Said that, I'm not responsible for any damage and/or missuse of this project whose intent is only for learning purposes.**  
  
> [!CAUTION]
> I consider this malware as "Non-functional" and with that, i mean it doesn't fully work the way a real malware would, however it has the potential to cause some form of damage by: weakening the device, logging data and deleting important files.  
  
> [!CAUTION]
> Using this against anyone or anything without the explicit permission of the owner of the device/system is a serious crime, which can get you behind bars pretty quickly, you are responsible for anything that happens from the time you download the sample and so on **YOU HAVE BEEN WARNED.**  
  
  
> [!TIP]
> #### Features:  
> **Basic anti-debugging.**  
> **Dropper** (Drops other files in the device).  
> **Weakener** (Weakens the device to make it possible to capture the key presses).  
> **Persistence** (It is hidden and has a mechanism to work even after reboots).  
> **Customizable** (It's features can be modified, but also has opportunity to add more features to it).  
>  
> #### IT DO NOT:  
> Make any connection to the internet.  
> Use any sophisticated anti-analysis and/or any sophisticated technique to hide itself.  
  
## Overview  
  
### Why i made this.   
This project was mainly created to learn C, but also to have a an idea of how malware works and some techniques used on making them.  
So far it not only helped me but might help someone who's starting to learn malware development for Linux, the code itself has a few comments, because i feel like you should learn and not copy-paste.  
  
### How it works.  
The sample as a Keylogger is a Spyware malware type. It doesn't need to be executed as a super user or even using sudo, it only needs to be executed by **someone with sudo access.**  
  
  
It takes the advantage of unprotected **.bashrc**, to inject code that will "hijack" the sudo command using **alias** and then the malware gets ready to infect the target, but it still needs a trigger.  
  
The trigger in question, is the user using the sudo command at any moment, after that, the infection might happen succesfully by executing an dropped shell file into the user path, after that if the infection goes succesfully, the Keylogger should be running after the next reboot.  
  
#### KeyLogger:
By capturing the bytes from '/dev/input/event4', it logs all pressed keys in a file present in a list of defined paths **(randomly chosen only if there isn't already a log file)**.  
  
> [!TIP]
> The '/dev/input/event4' file, is generated on every reboot, which means it is necessary to give Read permissions for all users on every reboot, such thing happens by creating an rc-local.service, there are other ways to do that, but would probably require someone to make them directly (ex: cron-tabs).  
  
## Protect Yourself  
To prevent this malware from infecting you device, you should be removing the writting permissions of files such as:  
/home/user/.bashrc.  
/home/user/.profile.  
  
**Note that, zsh might as well have similar files.**  
Restrict the usage permissions of **chmod**, **alias** and **gcc** commands from being executed by non-root users.
