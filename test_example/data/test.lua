math.randomseed(os.time())

-- Default world
world = BlackFox.getWorld("default")

-- Component IDs
Position = BlackFox.Components.Spatial.Position.id(world)
Rotation = BlackFox.Components.Spatial.Rotation.id(world)
Scale = BlackFox.Components.Spatial.Scale.id(world)
Sprite = BlackFox.Components.Render.Sprite.id(world)

function createEntity()
    local e = world:createEntity()

    -- Position
    local position = world:setComponent(e, Position)
    position.x = math.random() * BlackFox.Screen.width()
    position.y = math.random() * BlackFox.Screen.height()

    -- Rotation
    local rotation = world:setComponent(e, Rotation)
    rotation.angle = math.random() * 360.0

    -- Scale
    local scale = world:setComponent(e, Scale)
    scale.x = 1
    scale.y = 1

    -- Sprite
    local sprite = world:setComponent(e, Sprite)    
    -- Test image
    sprite.image = BlackFox.Resources.getTexture("test.png")
    -- Full rect
    sprite.rect = BlackFox.Graphics.IntRect:new(0, 0, sprite.image:width(), sprite.image:height())
    -- Pivot at center
    sprite.pivot = BlackFox.Math.Vector2f:new(sprite.image:width() / 2, sprite.image:height() / 2)
    -- Random color
    sprite.color = BlackFox.Graphics.Color:new(
        math.floor(math.random() * 255), 
        math.floor(math.random() * 255), 
        math.floor(math.random() * 255), 
        128)
end

-- Create some entities
for i= 1,100 do
    createEntity()
end

-- Create test system
system = BlackFox.createSystem("TestSystem", BlackFox.ComponentSystemGroup.GameLoop)
return system ~= nil