function onWorldChanged(world)
	Transform = BlackFox.Components.Spatial.Transform.id(world)
	ScalePingPong = BlackFox.Components.Runtime.ScalePingPong.id(world)
end

function update(dt)
	local entities = world:entities(
		scaleEntity,
		dt,
		Transform,
		ScalePingPong)
end

function scaleEntity(entity, dt, transform, scalePingPong)	
	-- scale ping pong
	if transform.scale.x > scalePingPong.max then
		scalePingPong.scaleUp = false
	elseif transform.scale.x < scalePingPong.min then
		scalePingPong.scaleUp = true
	end

	if scalePingPong.scaleUp == true then
		transform.scale.x = transform.scale.x + scalePingPong.speed * dt
		transform.scale.y = transform.scale.y + scalePingPong.speed * dt
	else
		transform.scale.x = transform.scale.x - scalePingPong.speed * dt
		transform.scale.y = transform.scale.y - scalePingPong.speed * dt
	end
end