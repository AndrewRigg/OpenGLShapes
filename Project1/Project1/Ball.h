#pragma once

#include <GLM/glm.hpp>

class Ball {

public:
	Ball();
	~Ball();

	float mass;
	float radius;
	float lifeTime;
	float volume();
	float g = -9.81;
	float mu = 0.01;							//This is the coefficient of static friction fot this ball
	glm::vec3 position;
	glm::vec3 angular_velocity;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 Momentum();						//Momentum of the ball
	//glm::vec3 RotationalMomentum();			//Rotational momentum of the ball
	glm::vec3 GravitationalForce();									
	glm::vec3 Friction();						//Frictional force on the ball from surfaces
	glm::vec3 action;							//External force being applied to ball
	glm::vec3 TotalForce();						//Addition of all forces acting on ball
	float KineticEnergy();								
	float PotentialEnergy();
	bool alive();																			
	void setMass(float mass);					//Do I need these getters and setters??!  Look into accessibility
	float getMass();
	void setAction(glm::vec3 action);
	glm::vec3 getAction();
	void setRadius(float radius);
	float getRadius();
	void updatePhysics(float deltaTime);


private:

};


	//Own vector class
/*
class Ball {


	
public:
	Ball();
	~Ball();

	float mass;
	float lifeTime;
	float radius;
	float volume();
	float g = -9.81;
	float mu = 0.01;							//This is the coefficient of static friction fot this ball
	vector3 position;
	vector3 angular_velocity;
	vector3 velocity;
	vector3 acceleration;
	vector3 Momentum();						//Momentum of the ball
												//glm::vec3 RotationalMomentum();			//Rotational momentum of the ball
	vector3 GravitationalForce();
	vector3 Friction();						//Frictional force on the ball from surfaces
	vector3 action;							//External force being applied to ball
	vector3 TotalForce();						//Addition of all forces acting on ball
	float KineticEnergy();
	float PotentialEnergy();
	bool alive;
	void setMass(float mass);					//Do I need these getters and setters??!  Look into accessibility
	float getMass();
	void setAlive(bool alive);
	bool alive();	
	void setAction(vector3 action);
	vector3 getAction();
	void setRadius(float radius);
	float getRadius();

private:

};*/