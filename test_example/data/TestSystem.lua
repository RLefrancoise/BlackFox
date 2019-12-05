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
end