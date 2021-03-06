#pragma once

#include <GLM/glm.hpp>
#include "Vectors.h"

class Boid {

public:
	Boid();
	~Boid();

	float mass;
	float radius;
	float lifeTime;
	float volume();
	float g = 0;
	float rate;
	float speed();
	float neighbourhood = 100;
	float mu = 0.01;							//This is the coefficient of static friction fot this Boid
	vector3 position;
	vector3 angular_velocity;
	vector3 velocity;
	vector3 acceleration;
	vector3 align;
	vector3 cohes;
	vector3 separ;
	vector3 Momentum();						//Momentum of the Boid
	//vector3 RotationalMomentum();			//Rotational momentum of the Boid
	vector3 GravitationalForce();
	vector3 Friction();						//Frictional force on the Boid from surfaces
	vector3 action;							//External force being applied to Boid
	vector3 TotalForce();						//Addition of all forces acting on Boid
	float KineticEnergy();
	float PotentialEnergy();
	bool alive();
	void updatePhysics(float deltaTime);
	void alignmentCohesionSeparation(Boid boids []);
	//vector3 direction(vector3 previous[]);
	vector3 direction();
	bool operator!=(Boid rhs);
	float distance(Boid boid);
};