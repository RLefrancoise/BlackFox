-- Component IDs
local Transform = BlackFox.Components.Spatial.Transform.id()
local AutoRotate = BlackFox.Components.Runtime.AutoRotate.id()

function update(dt)
	world:entities(
		rotateEntity,
		dt,
		Transform,
		AutoRotate)
end

function rotateEntity(entity, dt, transform, autoRotate)	
	-- rotate
	transform.rotation.degrees = (transform.rotation.degrees.value + autoRotate.speed * dt) % 360
end