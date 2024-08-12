[//]: # (Main title, centered)
<h1 align="center">Dynamic.BackDoor</h1>

Dynamic.BackDoor is a simple and basic Windows backdoor that allows CMD commands to be ran remotely and silently.
***This product is NOT linked or part of Dynamic.\* products line. No support, no pre compiled exe files and/or no updates will be provided.***

## Features & Functionalities

- Send CMD commands to backdoored machines

## How does it work ?

- Client side (send):
  - Start a listener on port 667/UDP to listen for outputs of sent commands.
  - Get user's input
  - Send an unencrypted *(for now)* UDP packet to broadcast on port 666 

- Server side (receive):
  - Start a listener on port 666/UDP to listen for broadcast packets.
  - Run recieved packet's message as a CMD command
  - Send back the output of that command *(if any)* to broadcast on port 667/UDP

## Releases/Updates

For obvious reasons, no release or pre compiled exe file is provided. If you wish to use this program for your own use, please compile it yourself.

## Issues

Issues and errors/bugs will only be trated if they are judged "critical" or "impactful". Most feature requests or enhancement will be ignored.

## Contributing

Contribution are welcomed but will most likely be ignored and/or not merged or rejected. If you wish to add modifications please fork this repository and make your own modifications on your side.

## License

This project is licensed under GNU General Public License v3.0 (GPL).
