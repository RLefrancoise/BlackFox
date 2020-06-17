-- This system changes the color of the laser when it hits an entity

function onCreate()
    Transform = BlackFox.Components.Spatial.Transform.id(world)
    Line = BlackFox.Components.Render.Line.id(world)
    Laser = BlackFox.Components.Runtime.Laser.id(world)
end

function update(dt)
    world:entities(rayCastLaser, dt, Transform, Line, Laser)
end

function rayCastLaser(entity, dt, transform, line, laser)
    local direction = BlackFox.Math.direction(transform.rotation.radians)
    local ray = BlackFox.Physics.Ray:new(transform.position, direction, laser.maxLength)

    local hasHit, hitInfo = BlackFox.Physics.rayCast(world, ray)

    if hasHit == true then
        line.color = laser.hitColor
        line.length = laser.maxLength * hitInfo.fraction
    else
        line.color = laser.noHitColor
        line.length = laser.maxLength
    end
end