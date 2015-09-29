CREATE TABLE Product(
	maker VARCHAR(30), 
	model INT,
	ptype VARCHAR(30)
);

CREATE TABLE PC (
	model VARCHAR(30),
	speed DECIMAL(10, 2),
	ram INT,
	hd_size INT,
	price DECIMAL(10, 2)
);

CREATE TABLE Laptop(
	model VARCHAR(30),
	speed DECIMAL(10,2),
	ram INT,
	hd_size INT,
	screen_size DECIMAL(10,1),
	price DECIMAL(10,2)
);

CREATE TABLE Printer(
	model VARCHAR(30),
	color BIT,
	ptype VARCHAR(30),
	price DECIMAL(10,2)
);	