-- This system changes the color of the laser when it hits an entity

-- Aliases
Color = BlackFox.Graphics.Color
Ray = BlackFox.Physics.Ray

-- Component IDs
local Transform = BlackFox.Components.Spatial.Transform.id()
local Line = BlackFox.Components.Render.Line.id()
local Laser = BlackFox.Components.Runtime.Laser.id()
local LaserTarget = BlackFox.Components.Runtime.LaserTarget.id()

function update(dt)
    world:entities(rayCastLaser, dt, Transform, Line, Laser)
end

function rayCastLaser(entity, dt, transform, line, laser)
    local direction = BlackFox.Math.direction(transform.rotation)
    local ray = Ray:new(transform.position, direction, laser.maxLength)

    local hasHit, hitInfo = BlackFox.Physics.rayCast(world, ray)

    -- Reset lerp value if laser status has changed
    if hasHit ~= laser.isHitting then
        laser.colorLerp = 0
    end

    -- Store laser status
    laser.isHitting = hasHit

    -- Update laser lerp value
    laser.colorLerp = laser.colorLerp + dt * laser.colorLerpSpeed
    laser.colorLerp = BlackFox.Math.clamp(laser.colorLerp, 0, 1)

    -- If hit, lerp to hit color
    if hasHit == true then
        local targetColor = laser.hitColor

        -- Look if hit entity has LaserTarget component
        if world:hasComponent(hitInfo.hitEntity, LaserTarget) == true then
            local laserTarget = world:getComponent(hitInfo.hitEntity, LaserTarget)
            targetColor = laserTarget.color
        end

        line.color = Color.lerp(laser.noHitColor, targetColor, laser.colorLerp)
        line.length = laser.maxLength * hitInfo.fraction
    -- If no hit, lerp to no hit color
    else
        line.color = Color.lerp(laser.hitColor, laser.noHitColor, laser.colorLerp)
        line.length = laser.maxLength
    end
end