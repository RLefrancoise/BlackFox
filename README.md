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
* Graphics
    * Sprite
    * Text
    * Shapes
        * Box
        * Circle
        * Line
    * View : It's basically 2D camera
* Physics
    * Ray casting
        * Ray cast for closest target
        * Ray cast for all targets in range
    * Colliders
        * Box collider
        * Circle collider

### What is ongoing ?

* Entity Archetypes
* Editor (this one will take a long time, because there is so much work to complete it !)
* Config file

### What is planned

* Physics
    * Colliders
        * Line collider
        * Polygon collider
    * Ray casting
        * Ray cast testing
    * Box cast
    * Circle cast
* Particle system
* GUI system
* Level loading
* Various data (Prefabs, ...)
* Native coding : for now I use only Lua to code games, but we should be able to use also C++
* Build system to export games
    * Use archive to embed resources and load them with virtual file system
    * Desktop : it should be the easiest to do
    * Android : I need to check if all the dependencies can be used on mobile. SFML should be fine
    * Web : I will probably use Emscripten. For now, it seems that SFML doesn't have WebGL build out of the box, so I guess I will have to find a workaround
* Probably many other stuff that will come when all of the above will be done