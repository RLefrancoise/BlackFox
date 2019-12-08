function onCreate()
	print("Create TestSystem")
end

function onDestroy()
	print("Destroy TestSystem")
end

function onWorldChanged(world)
	Position = BlackFox.Components.Position.id(world)
end

function update(dt)
    if BlackFox.Input.is_key_down(BlackFox.Input.KeyCode.ESCAPE) == true then
		print("Escape pressed")
		application:quit()
	end
	
	entities = world:entities(
		moveEntity,
		Position)
end

function moveEntity(entity)
	position = BlackFox.Components.Position.get(world, entity)
	position.x = position.x + 1
	position.y = position.y + 1
end