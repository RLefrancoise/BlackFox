function onCreate()
	print("Create TestSystem")
end

function onDestroy()
	print("Destroy TestSystem")
end

function update(dt)
    if BlackFox.Input.is_key_down(BlackFox.Input.KeyCode.ESCAPE) == true then
		print("Escape pressed")
		application:quit()
	end
	
	Position = world:component_identifier("Position")
	entities = world:entities(
		moveEntity,
		Position)
end

function moveEntity(entity)
	position = world:component(entity, Position)
	position.x = position.x + 1
	position.y = position.y + 1
end