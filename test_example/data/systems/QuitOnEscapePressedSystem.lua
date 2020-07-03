Name = "QuitOnEscapePressedSystem"

function update(dt)
    if BlackFox.Input.isKeyDown(BlackFox.Input.KeyCode.Escape) == true then
		print("Escape pressed")
		application:quit()
	end
end