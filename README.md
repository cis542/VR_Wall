VR_Wall
=======

A project that allows user to interact with the 3D space created by the system using a wii mote

The project will allow the user to interact with objects created using OpenGL API, by tracking the motion of the Wiimote in 3D space. A frame with 5 cameras is placed on the ceiling of xLab, and the 3D virtual space is projected onto the wall by a ground projector. The user is required to stand in a certain range to interact with the wall. 

Objective:
Phase 1: Create an object in the virtual space (Any shape, cube prefered), use the Wii Mote to select the object and drag it on the screen (need to make sure the edge condition satisfied that the object will never go out of the range of the screen).  The user can also change the camera angle using the Wii mote.
Phase 2: Implement two independent game environment: Virtual Squash and Virtual Djenga

Reach Goal:
Two virtual wall communicate with each other. Based on this, we can develop more and more interesting games. This feature can also be improved for the future ESE519 projects.

Technology/Platform:
Lab Resource: xLab funded by Comcast, mLab, Detkin Lab
VRUI Toolkit
Opti-track (Commercial Software)

System Architecture (Hardware and software)
Software: OpenGL API, VRUI Toolkit, OptiTrack (Unified optical tracking architecture)
Hardware: Wii mote, IR cameras, Power Adapter (9V and 12V AC-DC)




