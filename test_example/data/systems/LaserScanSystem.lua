-- This system moves the laser to scan from left to right

function onCreate()
    Transform = BlackFox.Components.Spatial.Transform.id(world)
    Laser = BlackFox.Components.Runtime.Laser.id(world)
end

function update(dt)
    world:entities(laserScan, dt, Transform, Laser)
end

function laserScan(entity, dt, transform, laser)
    local angle = transform.rotation.degrees

    if laser.scanDirection == 1 then
        angle = angle + laser.scanSpeed * dt
    else
        angle = angle - laser.scanSpeed * dt
    end

    -- Check if we need to change scan direction
    if angle > laser.scanMaxAngle then
        laser.scanDirection = -1
    elseif angle < laser.scanMinAngle then
        laser.scanDirection = 1
    end

    transform.rotation.degrees = angle
end