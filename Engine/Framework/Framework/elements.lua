models = {
	--id should be postion to store in the mesh array, should throw error if two id's match
	character = {
		path = '../media/character.X',
		id = 0
	},
	environment = {
		path = '../media/Environment.X',
		id = 1
	}
}
audio = {
	--sound type should be 0 or 1 depending on if its a sound effect or music track
	--id's don't necessarily have to be different providing the sound types are different
	music = {
		soundType = 0,
		path = "../Audio/music.wav",
		id = 0	
	},
	scream = {
		soundType = 1,
		path = "../Audio/scream.wav",
		id = 0
	}
}
elementList = {
	--e_type 0 = player object
	--e_type 1 = static object
	--e_type 2 = light
	character = {
		e_type = 0,
		posX = 0,
		posY = 0,
		posZ = 0,
		headX = 0,
		headY = 0,
		headZ = -1,
		scaleX = 1,
		scaleY = 1,
		scaleZ = 1,
		meshNum = 0,
	},
	otherPlayer = {
		e_type = 1,
		posX = 50,
		posY = 0,
		posZ = 50,
		headX = 0,
		headY = 0,
		headZ = -1,
		scaleX = 1,
		scaleY = 1,
		scaleZ = 1,
		meshNum = 0,
	},
	environment = {
		e_type = 1,
		posX = 0,
		posY = -100,
		posZ = 0,
		headX = 0,
		headY = 0,
		headZ = -1,
		scaleX = 5,
		scaleY = 5,
		scaleZ = 5,
		meshNum = 1,
	},
	light0 = {
		e_type = 2,
		posX = 50,
		posY = 10,
		posZ = 50,
	},
	light1 = {
		e_type = 2,
		posX = -50,
		posY = 10,
		posZ = -50,
	}
}
config = {
	width = 1000,
	height = 800
}



