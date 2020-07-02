-- This system moves the view with the keyboard

-- Component IDs
local Transform = BlackFox.Components.Spatial.Transform.id()
local View = BlackFox.Components.Render.View.id()
local PlayerView = BlackFox.Components.Runtime.PlayerView.id()

-- Aliases
local KeyCode = BlackFox.Input.KeyCode

local playerKeys = {
    ["Right"]={KeyCode.Right, KeyCode.D},
    ["Left"]={KeyCode.Left, KeyCode.Q},
    ["Up"]={KeyCode.Up, KeyCode.Z},
    ["Down"]={KeyCode.Down, KeyCode.S},
}

local function moveView(e, dt, transform, view, playerView)
    local moveSpeed = playerView.moveSpeed

    if BlackFox.Input.isKeyPressed(playerKeys["Right"][playerView.playerId]) == true then
        transform.position.x = transform.position.x + moveSpeed * dt
    end

    if BlackFox.Input.isKeyPressed(playerKeys["Left"][playerView.playerId]) == true then
        transform.position.x = transform.position.x - moveSpeed * dt
    end

    if BlackFox.Input.isKeyPressed(playerKeys["Down"][playerView.playerId]) == true then
        transform.position.y = transform.position.y + moveSpeed * dt
    end

    if BlackFox.Input.isKeyPressed(playerKeys["Up"][playerView.playerId]) == true then
        transform.position.y = transform.position.y - moveSpeed * dt
    end
end

function update(dt)
    world:entities(moveView, dt, Transform, View, PlayerView)
end