math.randomseed(os.time())

-- Default world
world = BlackFox.getWorld("default")

-- Component IDs
Transform = BlackFox.Components.Spatial.Transform.id(world)
Renderable = BlackFox.Components.Render.Renderable.id(world)
Sprite = BlackFox.Components.Render.Sprite.id(world)
Depth = BlackFox.Components.Render.Depth.id(world)
AutoRotate = BlackFox.Components.Runtime.AutoRotate.id(world)
ScalePingPong = BlackFox.Components.Runtime.ScalePingPong.id(world)
RigidBody = BlackFox.Components.Physics.RigidBody.id(world)
BoxCollider = BlackFox.Components.Physics.BoxCollider.id(world)

function createBody(position)
    local e, 
    transform, 
    rigidBody, 
    boxCollider, 
    renderable, 
    sprite, 
    depth = world:createEntity(Transform, RigidBody, BoxCollider, Renderable, Sprite, Depth)

    -- Position
    transform.position = position

    -- Rotation
    transform.rotation.degrees = math.random() * 360.0

    -- Scale
    transform.scale = BlackFox.Math.Vector2f:new(1,1)

    -- Rigid body
    rigidBody.type = BlackFox.Physics.BodyType.Dynamic
    --rigidBody.linearVelocity = BlackFox.Math.Vector2f:new(0,-1)
    rigidBody.angularVelocity = math.random() * 360.0

    -- Box Collider
    boxCollider.extents = transform.scale

    -- Sprite
    -- Test image
    sprite.image = BlackFox.Resources.texture("test.png")
    sprite.image.smooth = true
    -- Full rect
    sprite.rect = BlackFox.Graphics.IntRect:new(0, 0, sprite.image:width(), sprite.image:height())
    -- Pivot at center
    sprite.pivot = BlackFox.Math.Vector2f:new(sprite.image:width() / 2, sprite.image:height() / 2)
    -- Random color
    sprite.color = BlackFox.Graphics.Color.random(true)

    -- Depth
    depth.depth = 0
end

function createGround()
    local e, 
    transform, 
    rigidBody, 
    boxCollider, 
    renderable, 
    sprite, 
    depth = world:createEntity(Transform, RigidBody, BoxCollider, Renderable, Sprite, Depth)

    -- Position
    transform.position = BlackFox.Math.Vector2f:new(0,0) --BlackFox.Screen.pixelsToWorld(0, BlackFox.Screen.height())

    -- Rotation
    transform.rotation.degrees = 0

    -- Scale
    transform.scale = BlackFox.Math.Vector2f:new(50,1)

    -- Rigid body
    rigidBody.type = BlackFox.Physics.BodyType.Static

    -- Box Collider
    boxCollider.extents = transform.scale
    boxCollider.center = BlackFox.Math.Vector2f:new(25,0.5)
    
    -- Sprite
    -- Test image
    sprite.image = BlackFox.Resources.texture("test.png")
    sprite.image.smooth = true
    -- Full rect
    sprite.rect = BlackFox.Graphics.IntRect:new(0, 0, sprite.image:width(), sprite.image:height())
    -- Pivot at left bottom
    sprite.pivot = BlackFox.Math.Vector2f:new(0, 0)
    -- Random color
    sprite.color = BlackFox.Graphics.Color.Black

    -- Depth
    depth.depth = 0
end

function createEntity()
    local e, 
    transform, 
    autoRotate, 
    scalePingPong,
    renderable,
    sprite, 
    depth = world:createEntity(
        Transform, 
        AutoRotate, 
        ScalePingPong,
        Renderable,
        Sprite, 
        Depth)

    -- Position
    transform.position = BlackFox.Screen.pixelsToWorld(
        math.random() * BlackFox.Screen.width(), 
        math.random() * BlackFox.Screen.height())

    -- Rotation
    transform.rotation.degrees = math.random() * 360.0

    -- Scale
    transform.scale = BlackFox.Math.Vector2f:new(1,1)

    -- Auto Rotate
    autoRotate.speed = math.random() * 360.0

    -- Scale ping pong
    scalePingPong.min = transform.scale.x
    scalePingPong.max = scalePingPong.min + 1 + math.random()
    scalePingPong.speed = 1 + math.random() * 2 -- Random between 1 and 3

    -- Sprite
    -- Test image
    sprite.image = BlackFox.Resources.texture("test.png")
    sprite.image.smooth = true
    -- Full rect
    sprite.rect = BlackFox.Graphics.IntRect:new(0, 0, sprite.image:width(), sprite.image:height())
    -- Pivot at center
    sprite.pivot = BlackFox.Math.Vector2f:new(sprite.image:width() / 2, sprite.image:height() / 2)
    -- Random color
    sprite.color = BlackFox.Graphics.Color.random(true)

    -- Depth (between 0 and 5)
    depth.depth = math.floor(math.random() * 5)
end

-- Create some entities
--createGround()
--createBody(BlackFox.Math.Vector2f:new(5,5))

for i= 1,100 do
    createEntity()
end

-- Create systems
world:createSystem("AutoRotateSystem", BlackFox.ComponentSystemGroup.GameLoop)
world:createSystem("ScalePingPongSystem", BlackFox.ComponentSystemGroup.GameLoop)
world:createSystem("QuitOnEscapePressedSystem", BlackFox.ComponentSystemGroup.EndOfFrame)

return true