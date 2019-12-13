# BlackFox
BlackFox is a Game Engine written in C++ based on the ECS paradigm.
For now, the project has just begun, and I don't know yet how far I'm going with it.
I'm doing it as a challenge and to learn new things about C++ and about game engines
architecture in general.

## Build

You will need CMake to build the engine as well as a compiler with C++17 support.

### Dependencies

You will need to have somewhere on your computer the following libraries. 

* SFML 2.5.1 or newer : https://www.sfml-dev.org/index.php
* RTTR : https://www.rttr.org/

## Current state

Below is the details about the current status of the engine.

### What is done

* Opening the game window (That's the first step right ?)
* ECS paradigm by using the EnTT framework :
    * Worlds: A class grouping entities together
    * Systems: You can manually create systems or auto creating them at application start (kind of like how ECS works on Unity3D)
    * Components: They are just simple structs
* Dependency injection by using CInject, and by using contexts and installers (inspired by Zenject on Unity3D)
* Scripting language : Lua (and Javascript later)

### What is planned

* Level loading
* Entity Archetypes
* Various data (Prefabs, config file, ...)
* An editor obviously !
* Probably many other stuff that will come when all of the above will be done