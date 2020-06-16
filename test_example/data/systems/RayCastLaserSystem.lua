-- This system changes the color of the laser when it hits an entity

-- Aliases
Vector2f = BlackFox.Math.Vector2f

function onCreate()
    Transform = BlackFox.Components.Spatial.Transform.id(world)
    Line = BlackFox.Components.Render.Line.id(world)
    Laser = BlackFox.Components.Runtime.Laser.id(world)
end

function update(dt)
    world:entities(rayCastLaser, dt, Transform, Line, Laser)
end

function rayCastLaser(entity, dt, transform, line, laser)
    local rayStart = transform.position

    local rayEnd = Vector2f:new(
        rayStart.x + laser.maxLength * math.cos(transform.rotation.radians),
        rayStart.y + laser.maxLength * math.sin(transform.rotation.radians))

    local hasHit, hitInfo = BlackFox.Physics.rayCast(world, rayStart, rayEnd)
    
    if hasHit == true then
        line.color = laser.hitColor
        line.length = laser.maxLength * hitInfo.fraction
    else
        line.color = laser.noHitColor
        line.length = laser.maxLength
    end
end