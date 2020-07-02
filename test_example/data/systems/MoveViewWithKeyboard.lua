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
    ["RotateRight"]={KeyCode.Numpad6, KeyCode.E},
    ["RotateLeft"]={KeyCode.Numpad4, KeyCode.A},
    ["Reset"]={KeyCode.Numpad5, KeyCode.R},
    ["ZoomUp"]={KeyCode.Numpad8, KeyCode.X},
    ["ZoomDown"]={KeyCode.Numpad2, KeyCode.W}
}

local function moveView(e, dt, transform, view, playerView)
    local moveSpeed = playerView.moveSpeed
    local rotateSpeed = playerView.rotateSpeed
    local zoomSpeed = playerView.zoomSpeed

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

    if BlackFox.Input.isKeyPressed(playerKeys["RotateRight"][playerView.playerId]) == true then
        transform.rotation.value = transform.rotation.value - rotateSpeed * dt
    end

    if BlackFox.Input.isKeyPressed(playerKeys["RotateLeft"][playerView.playerId]) == true then
        transform.rotation.value = transform.rotation.value + rotateSpeed * dt
    end

    if BlackFox.Input.isKeyPressed(playerKeys["ZoomUp"][playerView.playerId]) == true then
        view.zoom = view.zoom - zoomSpeed * dt
        if view.zoom < 0.1 then
            view.zoom = 0.1
        end
    end

    if BlackFox.Input.isKeyPressed(playerKeys["ZoomDown"][playerView.playerId]) == true then
        view.zoom = view.zoom + zoomSpeed * dt
    end

    if BlackFox.Input.isKeyDown(playerKeys["Reset"][playerView.playerId]) == true then
        print("Reset player view of player ", playerView.playerId, " at position ", playerView.startPosition.x, playerView.startPosition.y)

        transform.position = playerView.startPosition
        transform.rotation.value = 0
        view.zoom = 1
    end
end

function update(dt)
    world:entities(moveView, dt, Transform, View, PlayerView)
end