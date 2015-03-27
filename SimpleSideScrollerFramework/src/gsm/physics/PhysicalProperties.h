#pragma once
#include "stdafx.h"
#include "src\gsm\physics\Physics.h"

class PhysicalProperties
{
protected:
	float buoyancy;
	float mass;
	bool  collidable;
	float coefficientOfRestitution;
	float x;
	float y;
	float z;
	float velocityX;
	float velocityY;
	float accelerationX;
	float accelerationY;
	// i added this
	int playerFlag;
	// updated this
	int enemyFlag;
	// bm4 add
	int playerBulletFlag;
	int enemyBulletFlag;
	// detect wave
	int wave;
	// detect level
	int level;
	// determine how many enemy are left
	int enemyRemaining;

	//Upgrade & Currency Variable
	int currentHealth;
	int maxHealth;
	int atkSpd;
	int atkDmg;
	int moveSpd;
	int currency;
	int lives;

public:
	PhysicalProperties()	{accelerationX = 0; accelerationY = 0;}
	~PhysicalProperties()	{}

	// INLINED METHODS
	float getBuoyancy()						{ return buoyancy;				}
	float getMass()							{ return mass;					}
	float getCoefficientOfRestitution()		{ return coefficientOfRestitution;	}
	bool isCollidable()						{ return collidable;			}
	float getX()							{ return x;						}
	float getY()							{ return y;						}
	float getZ()							{ return z;						}
	float getVelocityX()					{ return velocityX;				}
	float getVelocityY()					{ return velocityY;				}
	float getAccelerationX()				{ return accelerationX;			}
	float getAccelerationY()				{ return accelerationY;			}
	// i added this
	int	 getPlayerFlag()					{ return playerFlag;			}
	// updated this
	int getEnemyFlag()						{ return enemyFlag;				}
	//get current lvl/wave etc.
	int getWave()							{ return wave;					}
	int getLevel()							{ return level;					}
	int getEnemyRemaining()					{ return enemyRemaining;		}

	// Access Methods for the Upgrade Variables
	int getcurrentHealth()					{ return currentHealth;			}
	int getMaxHealth()						{ return maxHealth;				}
	int getAttackSpeed()					{ return atkSpd;				}
	int getAttackDamage()					{ return atkDmg;				}
	int getMoveSpeed()						{ return moveSpd;				}
	int getCurrency()						{ return currency;				}
	int getLives()				   			{ return lives;					}

	// bm4 add
	int  getPlayerBulletFlag()				{ return playerBulletFlag;      }
	int	 getEnemyBulletFlag()				{ return enemyBulletFlag;		}
	void setBuoyancy(float initBuoyancy)	{ buoyancy = initBuoyancy;		}
	void setMass(float initMass)			{ mass = initMass;				}
	void setCofficientOfRestitution(float cR) { coefficientOfRestitution = cR; }
	void setCollidable(bool initCollidable)	{ collidable = initCollidable;	}
	void setX(float initX)					{ x = initX;					}
	void incX(float xToInc)					{ x += xToInc;					}
	void setY(float initY)					{ y = initY;					}
	void incY(float yToInc)					{ y += yToInc;					}
	void setZ(float initZ)					{ z = initZ;					}
	// i added this
	void setPlayerFlag(int initPlayerFlag)  { playerFlag = initPlayerFlag;  }
	// updated this
	void setEnemyFlag(int initEnemyFlag)	{ enemyFlag = initEnemyFlag;	}
	// bm4 add
	void setPlayerBulletFlag(int initPlayerBulletFlag) { playerBulletFlag = initPlayerBulletFlag; }
	void setEnemyBulletFlag(int initEnemyBulletFlag) { enemyBulletFlag = initEnemyBulletFlag; }

	void capVelocity(Physics *physics)
	{
		float maxVelocity = physics->getMaxVelocity();
		if (calcTotalVelocity() > maxVelocity)
		{
			// LET'S CALCULATE THE ANGLE OF
			// THE CURRENT VELOCITY VECTOR
			float xyRatio = x/y;
			float initX = x;
			float initY = y;
			if (initX < 0)	initX *= -1;
			if (initY < 0)	initY *= -1;
			float tempX = sqrt(((maxVelocity*maxVelocity)*(xyRatio*xyRatio))/(1+(xyRatio*xyRatio)));
			float tempY = sqrt((maxVelocity*maxVelocity)/((xyRatio*xyRatio)+1));
			float xRatio = tempX/initX;
			float yRatio = tempY/initY;
			x *= xRatio;
			y *= yRatio;
		}
	}

	int round(float realNum)
	{
		return (int)floor(realNum + 0.5f);
	}

	void setPosition(float initX, float initY)
	{
		x = initX;
		y = initY;
	}

	void setVelocity(float initVx, float initVy)
	{
		velocityX = initVx;
		velocityY = initVy;
	}

	void setVelocitySafely(Physics *physics, float initVx, float initVy)
	{
		velocityX = initVx;			
		velocityY = initVy;
		//capVelocity(physics);
	}
	void incVelocity(Physics *physics, float incVx, float incVy)
	{ 
		velocityX += incVx;
		velocityY += incVy;
		//capVelocity(physics);
	}
	void setAccelerationX(float initAx)		{ accelerationX = initAx;		}
	void setAccelerationY(float initAy)		{ accelerationY = initAy;		}

	float calcTotalVelocity()
	{
		float xSquared = x * x;
		float ySquared = y * y;
		float totalVelocity = xSquared + ySquared;
		totalVelocity = sqrtf(totalVelocity);
		return totalVelocity;
	}

	void setLevel(int level)
	{
		this->level = level;
	}

	void setEnemyRemaining(int enemyRemaining)
	{
		this->enemyRemaining = enemyRemaining;
	}

	void setWave(int wave)
	{
		this->wave = wave;
	}

	// Mutator methods for the upgrade and currency variables
	void setCurrentHealth(int health)
	{
		this->currentHealth = health;
	}
	void setMaxHealth(int health)
	{
		this->maxHealth = health;
	}

	void setAttackSpeed(int atkSpd)
	{
		this->atkSpd = atkSpd;
	}

	void setAttackDamage(int atkDmg)
	{
		this->atkDmg = atkDmg;
	}

	void setMoveSpeed(int moveSpd)
	{
		this->moveSpd = moveSpd;
	}

	void setCurrency(int currency)
	{
		this->currency = currency;
	}

	// game over add
	void setLives(int initLives)
	{
		lives = initLives;
	}

	void incLives(){
		lives++;
	}

	void decLives(){
		lives--;
	}
};