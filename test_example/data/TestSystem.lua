entities = {}

function onWorldChanged(world)
	Position = BlackFox.Components.Spatial.Position.id(world)
	Rotation = BlackFox.Components.Spatial.Rotation.id(world)
	Scale = BlackFox.Components.Spatial.Scale.id(world)
end

function update(dt)
    if BlackFox.Input.isKeyDown(BlackFox.Input.KeyCode.Escape) == true then
		print("Escape pressed")
		application:quit()
	end

	if BlackFox.Input.isKeyDown(BlackFox.Input.KeyCode.Space) == true then
		print("Create entity")
		local entity = world:createEntity()
		local position = world:setComponent(entity, Position)
		print("Entity position is same: ", position == world:getComponent(entity, Position))

		entities[#entities + 1] = entity
	end
	
	local entities = world:entities(
		animateEntity,
		dt,
		Rotation,
		Scale)
end

function animateEntity(entity, dt)	
	local rotation = world:getComponent(entity, Rotation)
	local scale = world:getComponent(entity, Scale)

	-- rotate
	rotation.angle = rotation.angle + 30 * dt

	-- scale ping pong
	if scale.x > 2.5 then
		scaleUp = false
	elseif scale.x < 1 then
		scaleUp = true
	end

	if scaleUp == true then
		scale.x = scale.x + 2 * dt
		scale.y = scale.y + 2 * dt
	else
		scale.x = scale.x - 2 * dt
		scale.y = scale.y - 2 * dt
	end
end