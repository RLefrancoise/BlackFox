function onWorldChanged(world)
	Rotation = BlackFox.Components.Spatial.Rotation.id(world)
	AutoRotate = BlackFox.Components.Runtime.AutoRotate.id(world)
end

function update(dt)
	local entities = world:entities(
		rotateEntity,
		dt,
		Rotation,
		AutoRotate)
end

function rotateEntity(entity, dt)	
	local rotation, autoRotate = world:getComponents(entity, Rotation, AutoRotate)

	-- rotate
	rotation.angle = (rotation.angle + autoRotate.speed * dt) % 360
end