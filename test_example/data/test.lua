math.randomseed(os.time())

-- Settings
local twoPlayers = false

local minBodySize = 0.25
local maxBodySize = 0.5
local bodyCount = 50

local backgroundEntityMinSize = 1
local backgroundEntityMaxSize = 3
local backgroundEntityCount = 50
local backgroundEntityStartDepth = 5

-- Aliases
local Vector2f = BlackFox.Math.Vector2f
local IntRect = BlackFox.Graphics.IntRect
local Color = BlackFox.Graphics.Color
local Screen = BlackFox.Screen

-- Default world
local world = BlackFox.getWorld("default")

-- Component IDs
local Transform = BlackFox.Components.Spatial.Transform.id()

local Sprite = BlackFox.Components.Render.Sprite.id()
local CircleShape = BlackFox.Components.Render.CircleShape.id()
local BoxShape = BlackFox.Components.Render.BoxShape.id()
local Line = BlackFox.Components.Render.Line.id()
local Text = BlackFox.Components.Render.Text.id()
local Depth = BlackFox.Components.Render.Depth.id()
local View = BlackFox.Components.Render.View.id()

local AutoRotate = BlackFox.Components.Runtime.AutoRotate.id()
local ScalePingPong = BlackFox.Components.Runtime.ScalePingPong.id()
local Laser = BlackFox.Components.Runtime.Laser.id()
local LaserTarget = BlackFox.Components.Runtime.LaserTarget.id()
local PlayerView = BlackFox.Components.Runtime.PlayerView.id()

local RigidBody = BlackFox.Components.Physics.RigidBody.id()
local BoxCollider = BlackFox.Components.Physics.BoxCollider.id()
local CircleCollider = BlackFox.Components.Physics.CircleCollider.id()

-- Archetypes
local BoxLaserTargetArchetype = world:archetype(Transform, RigidBody, BoxCollider, BoxShape, Depth, LaserTarget)
local CircleLaserTargetArchetype = world:archetype(Transform, RigidBody, CircleCollider, CircleShape, Depth, LaserTarget)

local function createBody(position)
    local e,
    transform, 
    rigidBody, 
    boxCollider, 
    boxShape,
    depth,
    laserTarget = world:createArchetype(BoxLaserTargetArchetype)
    
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
    local randomSize = BlackFox.Math.lerp(minBodySize, maxBodySize, math.random())
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

local function createCircleBody(position)
    local e,
    transform,
    rigidBody,
    circleCollider,
    circleShape,
    depth,
    laserTarget = world:createArchetype(CircleLaserTargetArchetype)

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
    circleCollider.radius = BlackFox.Math.lerp(minBodySize, maxBodySize, math.random()) / 2
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

local function createLaser(position)
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

local function createGround(position, scale)
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

local function createWall(position)
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

local function textEntity(position, textString)
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

local function createBackgroundEntity(depthValue)
    local e, 
    transform, 
    autoRotate, 
    scalePingPong,
    boxShape,
    depth = world:createEntity(
        Transform, 
        AutoRotate, 
        ScalePingPong,
        BoxShape,
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
    autoRotate.speed = BlackFox.Math.lerp(-180, 180, math.random())

    -- Scale ping pong
    scalePingPong.min = transform.scale.x
    scalePingPong.max = scalePingPong.min + 1 + math.random()
    scalePingPong.speed = BlackFox.Math.lerp(1, 3, math.random()) -- Random between 1 and 3

    local color = Color.random(false)
    color.a = math.floor(BlackFox.Math.lerp(32, 128, math.random()))

    -- Box Shape

    local randomSize = BlackFox.Math.lerp(backgroundEntityMinSize, backgroundEntityMaxSize, math.random())

    -- Extents
    boxShape.extents = Vector2f:new(randomSize / 2, randomSize / 2)
    -- Origin
    boxShape.origin = boxShape.extents
    -- Color
    boxShape.color = color

    -- Depth
    depth.depth = depthValue
end

local function createView(size, viewport, playerId)
    local e, transform, view, playerView = world:createEntity(Transform, View, PlayerView)

    -- Transform
    transform.position = Screen.pixelsToWorld(Screen.width() / 2, Screen.height() / 2)

    -- View
    view.size = size
    view.viewport = viewport

    -- Player View
    playerView.playerId = playerId
    playerView.startPosition = Vector2f:new(transform.position)

    print("Create view for player", playerId, "at position", playerView.startPosition.x, playerView.startPosition.y)
end

-- Create ground
local groundPosition = Screen.pixelsToWorld(Screen.width() / 2, Screen.height() - 100)
local groundScale = Vector2f:new(8, 2)
local ground = createGround(groundPosition, groundScale)

-- Create walls
local leftWallPosition = Vector2f:new(groundPosition.x - groundScale.x / 2.0 - 1, groundPosition.y)
local rightWallPosition = Vector2f:new(groundPosition.x + groundScale.x / 2.0 + 1, groundPosition.y)

createWall(leftWallPosition)
createWall(rightWallPosition)

-- Create roof
local roofPosition = Vector2f:new(groundPosition.x, groundPosition.y - 6)
local roofScale = groundScale
local roof = createGround(roofPosition, roofScale)

-- Create bodies
local createFunctions = { createBody, createCircleBody }

for i=1,bodyCount do
    local createFnc = createFunctions[math.random(1, #createFunctions)]
    if createFnc ~= nil then
        createFnc(Vector2f:new(
                BlackFox.Math.lerp(leftWallPosition.x + 2, rightWallPosition.x - 2, math.random()),
                BlackFox.Math.lerp(roofPosition.y + 2, groundPosition.y - 2, math.random())))
    end
end

-- Create laser line
createLaser(roofPosition)

-- Text
textEntity(Screen.pixelsToWorld(10, 10), "This is a text")

-- Create background effect
for i= 1,backgroundEntityCount do
    createBackgroundEntity(backgroundEntityStartDepth + i)
end

-- Create view
if twoPlayers == true then
    createView(Screen.pixelsToWorld(Screen.width() / 2, Screen.height()), BlackFox.Graphics.FloatRect:new(0, 0, 0.5, 1), 1) -- Player 1
    createView(Screen.pixelsToWorld(Screen.width() / 2, Screen.height()), BlackFox.Graphics.FloatRect:new(0.5, 0, 0.5, 1), 2) -- Player 2
else
    createView(Screen.pixelsToWorld(Screen.width(), Screen.height()), BlackFox.Graphics.FloatRect:new(0, 0, 1, 1), 1) -- Player 1
end

-- Create systems
world:createSystem("ScalePingPongSystem")
world:createSystem("AutoRotateSystem")
world:createSystem("QuitOnEscapePressedSystem")
world:createSystem("ImpulseOnKeyPressed")
world:createSystem("RayCastLaserSystem")
world:createSystem("LaserScanSystem")
world:createSystem("MoveViewWithKeyboard")

return true