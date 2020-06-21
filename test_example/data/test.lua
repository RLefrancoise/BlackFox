math.randomseed(os.time())

minBodySize = 0.25
maxBodySize = 0.5
bodyCount = 50

-- Aliases
Vector2f = BlackFox.Math.Vector2f
IntRect = BlackFox.Graphics.IntRect
Color = BlackFox.Graphics.Color
Screen = BlackFox.Screen

-- Default world
world = BlackFox.getWorld("default")

-- Component IDs
Transform = BlackFox.Components.Spatial.Transform.id(world)

Sprite = BlackFox.Components.Render.Sprite.id(world)
CircleShape = BlackFox.Components.Render.CircleShape.id(world)
BoxShape = BlackFox.Components.Render.BoxShape.id(world)
Line = BlackFox.Components.Render.Line.id(world)
Text = BlackFox.Components.Render.Text.id(world)
Depth = BlackFox.Components.Render.Depth.id(world)

AutoRotate = BlackFox.Components.Runtime.AutoRotate.id(world)
ScalePingPong = BlackFox.Components.Runtime.ScalePingPong.id(world)
Laser = BlackFox.Components.Runtime.Laser.id(world)
LaserTarget = BlackFox.Components.Runtime.LaserTarget.id(world)

RigidBody = BlackFox.Components.Physics.RigidBody.id(world)
BoxCollider = BlackFox.Components.Physics.BoxCollider.id(world)
CircleCollider = BlackFox.Components.Physics.CircleCollider.id(world)

function createBody(position)
    local e, 
    transform, 
    rigidBody, 
    boxCollider, 
    boxShape,
    depth,
    laserTarget = world:createEntity(Transform, RigidBody, BoxCollider, BoxShape, Depth, LaserTarget)

    -- Position
    transform.position = position

    -- Rotation
    transform.rotation.degrees = math.random() * 360

    -- Scale
    transform.scale = Vector2f:new(1, 1)

    -- Rigid body
    rigidBody.type = BlackFox.Physics.BodyType.Dynamic
    rigidBody.angularDamping = 0.1
    rigidBody.bullet = true

    -- Box Collider
    local randomSize = BlackFox.Math.lerp(minBodySize, maxBodySize, math.random()) --minBodySize + math.random() * (maxBodySize - minBodySize)
    boxCollider.extents = Vector2f:new(randomSize / 2.0, randomSize / 2.0)
    boxCollider.center = Vector2f:new(0, 0)
    boxCollider.density = 1
    boxCollider.friction = 0.3
    boxCollider.restitution = 0.1

    local color = Color.random()

    -- Box Shape

    -- Extents
    boxShape.extents = boxCollider.extents
    -- Origin
    boxShape.origin = boxCollider.extents
    -- Color
    boxShape.color = color

    -- Depth
    depth.depth = 0

    -- Laser Target
    laserTarget.color = color
end

function createCircleBody(position)
    local e,
    transform,
    rigidBody,
    circleCollider,
    circleShape,
    depth,
    laserTarget = world:createEntity(Transform, RigidBody, CircleCollider, CircleShape, Depth, LaserTarget)

    -- Position
    transform.position = position

    -- Rotation
    transform.rotation.degrees = math.random() * 360

    -- Scale
    transform.scale = Vector2f:new(1, 1)

    -- Rigid body
    rigidBody.type = BlackFox.Physics.BodyType.Dynamic
    rigidBody.angularDamping = 0.1
    rigidBody.bullet = true

    -- Box Collider
    circleCollider.radius = BlackFox.Math.lerp(minBodySize, maxBodySize, math.random()) / 2 --(minBodySize + math.random() * (maxBodySize - minBodySize)) / 2
    --circleCollider.center = Vector2f:new(0, 0)
    circleCollider.density = 1
    circleCollider.friction = 0.3
    circleCollider.restitution = 0.1

    local color = Color.random()

    -- Circle Shape

    -- Circle radius
    circleShape.radius = circleCollider.radius
    -- Pivot at center
    circleShape.origin = Vector2f:new(circleShape.radius, circleShape.radius)
    -- Random color
    circleShape.color = color

    -- Depth
    depth.depth = 0

    -- Laser Target
    laserTarget.color = color
end

function createLaser(position)
    local e,
    transform,
    line,
    depth,
    laser = world:createEntity(Transform, Line, Depth, Laser)

    -- Transform
    transform.position = position
    transform.rotation.degrees = laser.scanMinAngle
    transform.scale = Vector2f:new(1,1)

    -- Line
    line.length = laser.maxLength
    line.thickness = laser.thickness
    line.color = laser.noHitColor

    -- Depth
    depth.depth = -1
end

function createGround(position, scale)
    local e, 
    transform, 
    rigidBody, 
    boxCollider, 
    sprite,
    depth = world:createEntity(Transform, RigidBody, BoxCollider, Sprite, Depth)

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
    sprite.origin = Vector2f:new(sprite.image:width() / 2, sprite.image:height())
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
    sprite, 
    depth = world:createEntity(Transform, RigidBody, BoxCollider, Sprite, Depth)

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
    sprite.origin = Vector2f:new(sprite.image:width() / 2, sprite.image:height())
    -- Black color
    sprite.color = Color.Black

    -- Depth
    depth.depth = 0
end

function text(position, textString)
    local e,
    transform,
    text,
    depth = world:createEntity(Transform, Text, Depth)

    -- Position
    transform.position = position

    -- Rotation
    transform.rotation.degrees = 0

    -- Scale
    transform.scale = Vector2f:new(1,1)

    -- Text
    text.font = BlackFox.Resources.font("Minecraft.ttf")
    text.text = textString
    text.characterSize = 0.5
    text.color = Color.Blue
    text.outlineColor = Color.Yellow
    text.outlineThickness = 2

    -- Depth
    depth.depth = -2
end

function createEntity()
    local e, 
    transform, 
    autoRotate, 
    scalePingPong,
    sprite,
    depth = world:createEntity(
        Transform, 
        AutoRotate, 
        ScalePingPong,
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
    sprite.origin = Vector2f:new(sprite.image:width() / 2, sprite.image:height() / 2)
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

-- Create bodies
createFunctions = { createBody, createCircleBody }

for i=1,bodyCount do
    local createFnc = createFunctions[math.random(1, #createFunctions)]
    if createFnc ~= nil then
        createFnc(Vector2f:new(
            math.random(math.floor(leftWallPosition.x + 2), math.floor(rightWallPosition.x - 2)),
            math.random(math.floor(roofPosition.y + 2), math.floor(groundPosition.y - 2))))
    end
end

-- Create laser line
createLaser(roofPosition)

-- Text
text(Screen.pixelsToWorld(10, 10), "This is a text")

---for i= 1,100 do
--    createEntity()
--end

-- Create systems
--world:createSystem("ScalePingPongSystem", BlackFox.ComponentSystemGroup.GameLoop)
world:createSystem("AutoRotateSystem", BlackFox.ComponentSystemGroup.GameLoop)
world:createSystem("QuitOnEscapePressedSystem", BlackFox.ComponentSystemGroup.EndOfFrame)
world:createSystem("ImpulseOnKeyPressed", BlackFox.ComponentSystemGroup.GameLoop)
world:createSystem("RayCastLaserSystem", BlackFox.ComponentSystemGroup.GameLoop)
world:createSystem("LaserScanSystem", BlackFox.ComponentSystemGroup.GameLoop)

return true