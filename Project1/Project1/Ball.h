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
	float rate;
	float mu = 0.01;							//This is the coefficient of static friction fot this ball
	vector3 position;
	vector3 angular_velocity;
	vector3 velocity;
	vector3 acceleration;
	vector3 Momentum();						//Momentum of the ball
	//vector3 RotationalMomentum();			//Rotational momentum of the ball
	vector3 GravitationalForce();									
	vector3 Friction();						//Frictional force on the ball from surfaces
	vector3 action;							//External force being applied to ball
	vector3 TotalForce();						//Addition of all forces acting on ball
	float KineticEnergy();								
	float PotentialEnergy();
	bool alive();						
	void updatePhysics(float deltaTime);


private:

};