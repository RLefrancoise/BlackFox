Name = "ImpulseOnKeyPressedSystem"
Group = BlackFox.ComponentSystemGroup.GameLoop

-- Component IDs
local RigidBody = BlackFox.Components.Physics.RigidBody.id()

-- Settings
local linearImpulseMagnitude = 2
local angularImpulseMagnitude = 30

function update(dt)
    if BlackFox.Input.isKeyDown(BlackFox.Input.KeyCode.Space) == true then
        world:entities(applyImpulse, dt, RigidBody)
    end
end

function applyImpulse(entity, dt, rigidBody)
    local linearImpulse = BlackFox.Math.Vector2f:new(
            (-linearImpulseMagnitude + math.random() * linearImpulseMagnitude * 2),
            (-linearImpulseMagnitude + math.random() * linearImpulseMagnitude * 2))
    BlackFox.Physics.applyLinearImpulseToCenter(world, rigidBody, linearImpulse, true)

    local angularImpulse = (-angularImpulseMagnitude + math.random() * angularImpulseMagnitude * 2)
    BlackFox.Physics.applyAngularImpulse(world, rigidBody, angularImpulse, true)

    --print("Apply linear impulse: (", linearImpulse.x, ", ", linearImpulse.y, "), angular impulse: ", angularImpulse)
end