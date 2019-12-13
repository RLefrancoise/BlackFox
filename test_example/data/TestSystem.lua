function onCreate()
	print("Create TestSystem")
end

function onDestroy()
	print("Destroy TestSystem")
end

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
	
	local entities = world:entities(
		animateEntity,
		dt,
		Rotation,
		Scale)
end

function animateEntity(entity, dt)	
	local rotation = BlackFox.Components.Spatial.Rotation.get(world, entity)
	local scale = BlackFox.Components.Spatial.Scale.get(world, entity)

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