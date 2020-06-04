function onCreate()
	Transform = BlackFox.Components.Spatial.Transform.id(world)
	AutoRotate = BlackFox.Components.Runtime.AutoRotate.id(world)
end

function update(dt)
	local entities = world:entities(
		rotateEntity,
		dt,
		Transform,
		AutoRotate)
end

function rotateEntity(entity, dt, transform, autoRotate)	
	-- rotate
	transform.rotation.degrees = (transform.rotation.degrees + autoRotate.speed * dt) % 360
end