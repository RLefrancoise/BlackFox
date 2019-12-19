function onWorldChanged(world)
	Scale = BlackFox.Components.Spatial.Scale.id(world)
	ScalePingPong = BlackFox.Components.Runtime.ScalePingPong.id(world)
end

function update(dt)
	local entities = world:entities(
		scaleEntity,
		dt,
		Scale,
		ScalePingPong)
end

function scaleEntity(entity, dt)	
	local scale, scalePingPong = world:getComponents(entity, Scale, ScalePingPong)

	-- scale ping pong
	if scale.x > scalePingPong.max then
		scalePingPong.scaleUp = false
	elseif scale.x < scalePingPong.min then
		scalePingPong.scaleUp = true
	end

	if scalePingPong.scaleUp == true then
		scale.x = scale.x + scalePingPong.speed * dt
		scale.y = scale.y + scalePingPong.speed * dt
	else
		scale.x = scale.x - scalePingPong.speed * dt
		scale.y = scale.y - scalePingPong.speed * dt
	end
end