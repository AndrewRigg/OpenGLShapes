#pragma once

#include <GLM/glm.hpp>

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
	std::vector <Boid> neighbouring_boids;
	float neighbourhood = 10;
	float mu = 0.01;							//This is the coefficient of static friction fot this Boid
	vector3 position;
	vector3 angular_velocity;
	vector3 velocity;
	vector3 acceleration;
	vector3 Momentum();						//Momentum of the Boid
	//vector3 RotationalMomentum();			//Rotational momentum of the Boid
	vector3 GravitationalForce();									
	vector3 Friction();						//Frictional force on the Boid from surfaces
	vector3 action;							//External force being applied to Boid
	vector3 TotalForce();						//Addition of all forces acting on Boid
	float KineticEnergy();								
	float PotentialEnergy();
	bool alive();																			
	void setMass(float mass);					//Do I need these getters and setters??!  Look into accessibility
	float getMass();
	void setAction(vector3 action);
	vector3 getAction();
	void setRadius(float radius);
	float getRadius();
	void updatePhysics(float deltaTime);
	vector3 cohesion(Boid boids []);
	vector3 alignment(Boid  boids []);
	vector3 separation(Boid boids []);
	//vector3 direction(vector3 previous[]);
	vector3 direction();
	bool operator!=(Boid rhs);
	float distance(Boid boid);

private:

};