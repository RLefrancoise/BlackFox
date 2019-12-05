function onCreate()
	print("Create TestSystem")
	world = BlackFox.get_world("default")
	positionId = world:component("Position")
	print("Position id ", positionId)
end

function onDestroy()
	print("Destroy TestSystem")
end

function update(dt)
    if BlackFox.Input.is_key_down(BlackFox.Input.KeyCode.ESCAPE) == true then
		print("Escape pressed")
		application:quit()
	end
	
	view = world:entity_view({Position})
end