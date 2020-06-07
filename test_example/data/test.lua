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
    local randomScale = 0.25 + math.random() * 0.25
    transform.scale = BlackFox.Math.Vector2f:new(randomScale, randomScale)

    -- Rigid body
    rigidBody.type = BlackFox.Physics.BodyType.Dynamic
    rigidBody.angularDamping = math.random() * 0.1
    rigidBody.bullet = true

    -- Box Collider
    boxCollider.extents = BlackFox.Math.Vector2f:new(randomScale / 2.0, randomScale / 2.0)
    boxCollider.center = BlackFox.Math.Vector2f:new(0, 0)
    boxCollider.density = 1
    boxCollider.friction = 0.3
    boxCollider.restitution = 0.5

    local linearImpulse = BlackFox.Math.Vector2f:new(math.random(-1,1),math.random(-3,3))
    BlackFox.Physics.applyLinearImpulseToCenter(
        world, 
        rigidBody, 
        linearImpulse, 
        true)

    BlackFox.Physics.applyAngularImpulse(
        world, 
        rigidBody, 
        math.random(-45,45), 
        true)

    -- Sprite
    -- Test image
    sprite.image = BlackFox.Resources.texture("test.png")
    sprite.image.smooth = false
    -- Full rect
    sprite.rect = BlackFox.Graphics.IntRect:new(0, 0, sprite.image:width(), sprite.image:height())
    -- Pivot at center
    sprite.pivot = BlackFox.Math.Vector2f:new(sprite.image:width() / 2, sprite.image:height() / 2)
    -- Random color
    sprite.color = BlackFox.Graphics.Color.random(false)

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
    boxCollider.extents = BlackFox.Math.Vector2f:new(transform.scale.x / 2.0, transform.scale.y / 2.0)
    boxCollider.center = BlackFox.Math.Vector2f:new(0, -transform.scale.y / 2.0)
    boxCollider.density = 0
    boxCollider.friction = 0.3
    boxCollider.restitution = 0.5
    
    -- Sprite
    -- Test image
    sprite.image = BlackFox.Resources.texture("test.png")
    sprite.image.smooth = false
    -- Full rect
    sprite.rect = BlackFox.Graphics.IntRect:new(0, 0, sprite.image:width(), sprite.image:height())
    -- Pivot at bottom center
    sprite.pivot = BlackFox.Math.Vector2f:new(sprite.image:width() / 2, sprite.image:height())
    -- Black color
    sprite.color = BlackFox.Graphics.Color.Black

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
    boxCollider.extents = BlackFox.Math.Vector2f:new(transform.scale.x / 2.0, transform.scale.y / 2.0)
    boxCollider.center = BlackFox.Math.Vector2f:new(0, -transform.scale.y / 2.0)
    boxCollider.density = 0
    boxCollider.friction = 0.3
    boxCollider.restitution = 0.5
    
    -- Sprite
    -- Test image
    sprite.image = BlackFox.Resources.texture("test.png")
    sprite.image.smooth = false
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

-- Create ground
groundPosition = BlackFox.Screen.pixelsToWorld(BlackFox.Screen.width() / 2, BlackFox.Screen.height() - 20)
groundScale = BlackFox.Math.Vector2f:new(8, 2)
ground = createGround(groundPosition, groundScale)

-- Create walls
leftWallPosition = BlackFox.Math.Vector2f:new(groundPosition.x - groundScale.x / 2.0 - 1, groundPosition.y)
rightWallPosition = BlackFox.Math.Vector2f:new(groundPosition.x + groundScale.x / 2.0 + 1, groundPosition.y)

createWall(leftWallPosition)
createWall(rightWallPosition)

-- Create roof
roofPosition = BlackFox.Math.Vector2f:new(groundPosition.x, groundPosition.y - 6)
roofScale = groundScale
roof = createGround(roofPosition, groundScale)

for i=1,30 do
    createBody(BlackFox.Math.Vector2f:new(
        math.random(math.floor(leftWallPosition.x + 1), math.floor(rightWallPosition.x - 1)),
        math.random(math.floor(roofPosition.y + 1), math.floor(groundPosition.y - 1))))
end

---for i= 1,100 do
--    createEntity()
--end

-- Create systems
--world:createSystem("AutoRotateSystem", BlackFox.ComponentSystemGroup.GameLoop)
--world:createSystem("ScalePingPongSystem", BlackFox.ComponentSystemGroup.GameLoop)
world:createSystem("QuitOnEscapePressedSystem", BlackFox.ComponentSystemGroup.EndOfFrame)

return true