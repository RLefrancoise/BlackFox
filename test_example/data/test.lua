math.randomseed(os.time())

-- Aliases
Vector2f = BlackFox.Math.Vector2f
IntRect = BlackFox.Graphics.IntRect
Color = BlackFox.Graphics.Color
Screen = BlackFox.Screen

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
    local randomScale = 0.25 + math.random() * 0.25
    transform.scale = Vector2f:new(randomScale, randomScale)

    -- Rigid body
    rigidBody.type = BlackFox.Physics.BodyType.Dynamic
    rigidBody.angularDamping = 0.1
    rigidBody.bullet = true

    -- Box Collider
    boxCollider.extents = Vector2f:new(randomScale / 2.0, randomScale / 2.0)
    boxCollider.center = Vector2f:new(0, 0)
    boxCollider.density = 1
    boxCollider.friction = 0.3
    boxCollider.restitution = 0.1

    -- Sprite
    -- Test image
    sprite.image = BlackFox.Resources.texture("test.png")
    sprite.image.smooth = true
    -- Full rect
    sprite.rect = IntRect:new(0, 0, sprite.image:width(), sprite.image:height())
    -- Pivot at center
    sprite.pivot = Vector2f:new(sprite.image:width() / 2, sprite.image:height() / 2)
    -- Random color
    sprite.color = Color.Blue;

    -- Depth
    depth.depth = 0
end

function createGround(position, scale)
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
    transform.rotation.degrees = 0

    -- Scale
    transform.scale = scale

    -- Rigid body
    rigidBody.type = BlackFox.Physics.BodyType.Static

    -- Box Collider
    boxCollider.extents = Vector2f:new(transform.scale.x / 2.0, transform.scale.y / 2.0)
    boxCollider.center = Vector2f:new(0, -transform.scale.y / 2.0)
    boxCollider.density = 0
    boxCollider.friction = 0.3
    boxCollider.restitution = 0.1
    
    -- Sprite
    -- Test image
    sprite.image = BlackFox.Resources.texture("test.png")
    sprite.image.smooth = false
    -- Full rect
    sprite.rect = IntRect:new(0, 0, sprite.image:width(), sprite.image:height())
    -- Pivot at bottom center
    sprite.pivot = Vector2f:new(sprite.image:width() / 2, sprite.image:height())
    -- Black color
    sprite.color = Color.Black

    -- Depth
    depth.depth = 0

    return e
end

function createWall(position)
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
    transform.rotation.degrees = 0

    -- Scale
    transform.scale = BlackFox.Math.Vector2f:new(2, 6)

    -- Rigid body
    rigidBody.type = BlackFox.Physics.BodyType.Static

    -- Box Collider
    boxCollider.extents = Vector2f:new(transform.scale.x / 2.0, transform.scale.y / 2.0)
    boxCollider.center = Vector2f:new(0, -transform.scale.y / 2.0)
    boxCollider.density = 0
    boxCollider.friction = 0.3
    boxCollider.restitution = 0.1
    
    -- Sprite
    -- Test image
    sprite.image = BlackFox.Resources.texture("test.png")
    sprite.image.smooth = false
    -- Full rect
    sprite.rect = IntRect:new(0, 0, sprite.image:width(), sprite.image:height())
    -- Pivot at bottom center
    sprite.pivot = Vector2f:new(sprite.image:width() / 2, sprite.image:height())
    -- Black color
    sprite.color = Color.Black

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
    transform.position = Screen.pixelsToWorld(
        math.random() * Screen.width(), 
        math.random() * Screen.height())

    -- Rotation
    transform.rotation.degrees = math.random() * 360.0

    -- Scale
    transform.scale = Vector2f:new(1,1)

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
    sprite.rect = IntRect:new(0, 0, sprite.image:width(), sprite.image:height())
    -- Pivot at center
    sprite.pivot = Vector2f:new(sprite.image:width() / 2, sprite.image:height() / 2)
    -- Random color
    sprite.color = Color.random(true)

    -- Depth (between 0 and 5)
    depth.depth = math.floor(math.random() * 5)
end

-- Create ground
groundPosition = Screen.pixelsToWorld(Screen.width() / 2, Screen.height() - 100)
groundScale = Vector2f:new(8, 2)
ground = createGround(groundPosition, groundScale)

-- Create walls
leftWallPosition = Vector2f:new(groundPosition.x - groundScale.x / 2.0 - 1, groundPosition.y)
rightWallPosition = Vector2f:new(groundPosition.x + groundScale.x / 2.0 + 1, groundPosition.y)

createWall(leftWallPosition)
createWall(rightWallPosition)

-- Create roof
roofPosition = Vector2f:new(groundPosition.x, groundPosition.y - 6)
roofScale = groundScale
roof = createGround(roofPosition, groundScale)

for i=1,100 do
    createBody(Vector2f:new(
        math.random(math.floor(leftWallPosition.x + 2), math.floor(rightWallPosition.x - 2)),
        math.random(math.floor(roofPosition.y + 2), math.floor(groundPosition.y - 2))))
end

---for i= 1,100 do
--    createEntity()
--end

-- Create systems
--world:createSystem("AutoRotateSystem", BlackFox.ComponentSystemGroup.GameLoop)
--world:createSystem("ScalePingPongSystem", BlackFox.ComponentSystemGroup.GameLoop)
world:createSystem("QuitOnEscapePressedSystem", BlackFox.ComponentSystemGroup.EndOfFrame)
world:createSystem("ImpulseOnKeyPressed", BlackFox.ComponentSystemGroup.GameLoop)

return true