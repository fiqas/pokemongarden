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
	layer = 3,
	position = {-9.0, 6.0},
	sprite = "Resources/Images/objects/bigtree.png",
	size = {7.0, 8.0},
	name = "treesprite",
	
}

