-- This system moves the view with the keyboard

-- Component IDs
local Transform = BlackFox.Components.Spatial.Transform.id()
local View = BlackFox.Components.Render.View.id()

local function moveView(e, dt, transform, view)
    local moveSpeed = 5

    if BlackFox.Input.isKeyPressed(BlackFox.Input.KeyCode.Right) == true then
        transform.position.x = transform.position.x + moveSpeed * dt
    end

    if BlackFox.Input.isKeyPressed(BlackFox.Input.KeyCode.Left) == true then
        transform.position.x = transform.position.x - moveSpeed * dt
    end

    if BlackFox.Input.isKeyPressed(BlackFox.Input.KeyCode.Down) == true then
        transform.position.y = transform.position.y + moveSpeed * dt
    end

    if BlackFox.Input.isKeyPressed(BlackFox.Input.KeyCode.Up) == true then
        transform.position.y = transform.position.y - moveSpeed * dt
    end
end

function update(dt)
    world:entities(moveView, dt, Transform, View)
end