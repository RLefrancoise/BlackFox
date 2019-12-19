math.randomseed(os.time())

-- Register runtime components
BlackFox.World.registerComponent("AutoRotate")
BlackFox.World.registerComponent("ScalePingPong")

-- Default world
world = BlackFox.getWorld("default")

-- Component IDs
Position = BlackFox.Components.Spatial.Position.id(world)
Rotation = BlackFox.Components.Spatial.Rotation.id(world)
Scale = BlackFox.Components.Spatial.Scale.id(world)
Sprite = BlackFox.Components.Render.Sprite.id(world)
AutoRotate = BlackFox.Components.Runtime.AutoRotate.id(world)
ScalePingPong = BlackFox.Components.Runtime.ScalePingPong.id(world)

function createEntity()
    local e = world:createEntity()

    -- Position
    local position = world:setComponent(e, Position)
    position.x = math.random() * BlackFox.Screen.width()
    position.y = math.random() * BlackFox.Screen.height()

    -- Rotation
    local rotation = world:setComponent(e, Rotation)
    rotation.angle = math.random() * 360.0

    -- Auto Rotate
    local autoRotate = world:setComponent(e, AutoRotate)
    autoRotate.speed = math.random() * 360.0

    -- Scale
    local scale = world:setComponent(e, Scale)
    scale.x = 1
    scale.y = scale.x

    -- Scale ping pong
    local scalePingPong = world:setComponent(e, ScalePingPong)
    scalePingPong.min = scale.x
    scalePingPong.max = scalePingPong.min + 2 * math.random()
    scalePingPong.speed = 1 + math.random() * 4 -- Random between 1 and 5

    -- Sprite
    local sprite = world:setComponent(e, Sprite)    
    -- Test image
    sprite.image = BlackFox.Resources.texture("test.png")
    sprite.image.smooth = true
    -- Full rect
    sprite.rect = BlackFox.Graphics.IntRect:new(0, 0, sprite.image:width(), sprite.image:height())
    -- Pivot at center
    sprite.pivot = BlackFox.Math.Vector2f:new(sprite.image:width() / 2, sprite.image:height() / 2)
    -- Random color
    sprite.color = BlackFox.Graphics.Color.random(true)
end

-- Create some entities
for i= 1,100 do
    createEntity()
end

-- Create systems
BlackFox.createSystem("AutoRotateSystem", BlackFox.ComponentSystemGroup.GameLoop)
BlackFox.createSystem("ScalePingPongSystem", BlackFox.ComponentSystemGroup.GameLoop)
BlackFox.createSystem("QuitOnEscapePressedSystem", BlackFox.ComponentSystemGroup.EndOfFrame)

return true