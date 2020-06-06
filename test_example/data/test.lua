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
    transform.rotation.degrees = math.random() * 360

    -- Scale
    transform.scale = BlackFox.Math.Vector2f:new(0.5, 0.5)

    -- Rigid body
    rigidBody.type = BlackFox.Physics.BodyType.Dynamic
    rigidBody.linearVelocity = BlackFox.Math.Vector2f:new(0,0)
    rigidBody.angularVelocity = math.random() * 90

    -- Box Collider
    boxCollider.extents = BlackFox.Math.Vector2f:new(0.25, 0.25)
    boxCollider.center = BlackFox.Math.Vector2f:new(0, 0)
    boxCollider.density = 1
    boxCollider.friction = 0
    boxCollider.restitution = 1

    -- Sprite
    -- Test image
    sprite.image = BlackFox.Resources.texture("test.png")
    sprite.image.smooth = true
    -- Full rect
    sprite.rect = BlackFox.Graphics.IntRect:new(0, 0, sprite.image:width(), sprite.image:height())
    -- Pivot at center
    sprite.pivot = BlackFox.Math.Vector2f:new(sprite.image:width() / 2, sprite.image:height() / 2)
    -- Random color
    sprite.color = BlackFox.Graphics.Color.Red

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
    transform.position = BlackFox.Screen.pixelsToWorld(BlackFox.Screen.width() / 2, BlackFox.Screen.height() - 20)

    -- Rotation
    transform.rotation.degrees = 0

    -- Scale
    transform.scale = BlackFox.Math.Vector2f:new(10, 0.5)

    -- Rigid body
    rigidBody.type = BlackFox.Physics.BodyType.Static

    -- Box Collider
    boxCollider.extents = BlackFox.Math.Vector2f:new(5, 0.25)
    boxCollider.center = BlackFox.Math.Vector2f:new(0, -0.25)
    boxCollider.density = 0
    boxCollider.friction = 0
    boxCollider.restitution = 1
    
    -- Sprite
    -- Test image
    sprite.image = BlackFox.Resources.texture("test.png")
    sprite.image.smooth = true
    -- Full rect
    sprite.rect = BlackFox.Graphics.IntRect:new(0, 0, sprite.image:width(), sprite.image:height())
    -- Pivot at bottom center
    sprite.pivot = BlackFox.Math.Vector2f:new(sprite.image:width() / 2, sprite.image:height())
    -- Black color
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
createGround()
createBody(BlackFox.Screen.pixelsToWorld(BlackFox.Screen.width() / 2, BlackFox.Screen.height() / 2))
createBody(BlackFox.Screen.pixelsToWorld(BlackFox.Screen.width() / 4, BlackFox.Screen.height() / 2))
createBody(BlackFox.Screen.pixelsToWorld(BlackFox.Screen.width() * 0.75, BlackFox.Screen.height() / 2))

---for i= 1,100 do
--    createEntity()
--end

-- Create systems
--world:createSystem("AutoRotateSystem", BlackFox.ComponentSystemGroup.GameLoop)
--world:createSystem("ScalePingPongSystem", BlackFox.ComponentSystemGroup.GameLoop)
world:createSystem("QuitOnEscapePressedSystem", BlackFox.ComponentSystemGroup.EndOfFrame)

return true