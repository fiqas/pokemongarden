Ground = {

	class = "FullScreenActor",
	sprite = "Resources/Images/grass.png",
	name = "Grass",
	layer = 0,
	tag = "grass",
	
}

TopFence = {

  class = "PhysicsActor",
  tag = "fence",
  layer = 3,
  density = 0.0,
  friction = 0.0,
  restitution = 0.1,
  sprite = "Resources/Images/fence.png",
  position = {0, 9.8},
  size = {28, 0.4},
  tag = "fence",
  
}

BottomFence = {

  class = "PhysicsActor",
  tag = "fence",
  layer = 3,
  density = 0.0,
  friction = 0.0,
  restitution = 0.1,
  sprite = "Resources/Images/fence.png",
  position = {0, -9.8},
  size = {28, 0.4},
  tag = "fence",
  
}

LeftFence = {
  
  class = "PhysicsActor",
  density = 0,
  tag = "fence",
  layer = 3,
  sprite = "Resources/Images/fence.png",
  position={-13.1, 0},
  rotation = 90,
  size={28, 0.4},
  
}

RightFence = {

  class = "PhysicsActor",
  tag = "fence",
  layer = 3,
  sprite = "Resources/Images/fence.png",
  density = 0.0,
  friction = 0.0,
  restitution = 0.1,
  position={13.1, 0},
  rotation = 270,
  size={28, 0.4},
  
}

BigTreeSprite = {

	class = "Actor",
	layer = 4,
	position = {-9.0, 6.0},
	sprite = "Resources/Images/objects/bigtree.png",
	size = {7.0, 8.0},
	name = "treesprite",
	
}

KlodaSprite = {

	class = "Actor",
	layer = 4,
	position = { 1.0, 2.0},
	sprite = "Resources/Images/objects/kloda.png",
	size = {1.0, 0.5},
	name = "klodasprite",
	
}

DrzewoIglaste2 = {

	class = "Actor",
	layer = 4,
	position = { 1.0, 4.0},
	sprite = "Resources/Images/objects/drzewoiglaste2.png",
	size = {2.5, 3.0},
	name = "drzewoiglastesprite",

}

Krzak = {

	class = "Actor",
	layer = 4,
	position = { -1.0, 2.0},
	sprite = "Resources/Images/objects/krzak.png",
	size = {1.0, 1.0},
	name = "krzaksprite",
}

Krzak2 = {

	class = "Actor",
	layer = 4,
	position = { -1.0, 2.0},
	sprite = "Resources/Images/objects/krzak2.png",
	size = {1.5, 1.5},
	name = "krzak2sprite",

}

DrzewoLisciaste = {

	class = "Actor",
	layer = 4,
	position = {9.0, 6.0},
	sprite = "Resources/Images/objects/drzewolisciaste.png",
	size = {8.0, 8.0},
	name = "drzewolisciastesprite",
	

}

TreeWithLeavesHigh = {

	class = "Actor",
	layer = 4,
	position = {6.5, -6.0},
	sprite = "Resources/Images/objects/treewithleaveshigh.png",
	size = {3.0, 5.0},
	name = "drzewoprite",
	

}