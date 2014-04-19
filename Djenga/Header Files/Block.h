// vrwall is not a person (as far as I know)
/*
 * Block.h
 *
 *  Created on: Mar 30, 2014
 *      Author: vrwall
 */

#ifndef BLOCK_H_
#define BLOCK_H_



#include <GL/gl.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>

#include <math.h>
#include <vector>
#include <map>
#include "vec.h"
#include "Scene.h"

class Block
{
  public:
     Block();
     //Block(const Block& block);

    // Block& operator=(const Block& block);

     virtual ~Block();

     virtual void Update(double dt,
                        const Scene& scene,
                        const vec3& externalForces = vec3(0.0,-9.8,0.0)
                        );


	 // Again, it is better to put graphiucs functionality of a Block into a separate (possibly friend) class.
	 // This will decouple the physical simulation of the Block from the graphical display of the block. 
	 virtual void Draw(vec3 center);

     //virtual void DrawCube(double x, double y, double z);
	 // why do you reset blocks instead of destroying them and creating new ones?
     virtual void Reset();
	 // why is this a property of a block?
     enum IntegrationType {EULER, MIDPOINT, RK4};
     virtual void SetIntegrationType(IntegrationType type);
     virtual IntegrationType GetIntegrationType() const;

	 // Blocks should not take a dependence on mouse gestures.
     virtual int onMouseCheck(vec3 point);

     virtual void dragBlock(vec3 start, vec3 end, int index);

	 // I don't really understand what you are doing, but I assume that you are accumulating forces on the block
	 // in the computational step of moving time forward. This is stylistically questionable, because you are storing
	 // what amounts to the state of an algorithm in the object, even though it doesn't have anything to do with the 
	 // state of the object. It is generally preferable to make an instance of the algorithm into a separate object 
	 // (perhaps of a friend class).
	 virtual void clearUserForces();

	 // why is initialization not in the constructor?
     // why is position conflated with shape?
	 virtual void InitBlock(vec3 position, double width, double height, double depth);

     double m_width, m_height, m_depth;

     vec3 m_center;
	 // the forces on a block should not be part of the state of a block
     vec3 m_externalForces;
	 // why do you need this?
     vec3 m_initialPosition;

     //int GetIndex(int i, int j, int k) const;
     //int GetIndex()
     
     //void GetCell(int idx, int& i, int& j, int& k)const;

     virtual double GetWidth() const;
     virtual double GetHeight() const;
     virtual double GetDepth() const;







     //virtual glm::vec3 onClick();

  protected:


     class Intersection;
     class Particle;

	 // Clocks should not take a dependence on the BlockAGrid data structure

     //typedef std::vector<std::vector<std::vector<Particle> > > BlockGrid;
	 // prefer using to typedef
     typedef std::vector<Particle> BlockGrid;

     Particle& GetParticle(BlockGrid& grid, int index);
     //Particle& GetParticle(BlockGrid& grid,int i, int j, int k);
     //const Particle& GetParticle(const BlockGrid& grid, int index) const;
     //const Particle& GetParticle(const BlockGrid& grid,int i, int j, int k) const;

     //virtual void CheckForCollisions(BlockGrid& grid, const Scene& scene);
     virtual void ResolveCollisions(BlockGrid& grid);
     virtual void ResolveContacts(BlockGrid& grid);
     virtual bool FloorIntersection(Particle& p, Intersection& intersection);
     //virtual void BlockIntersection(Block& grid, Intersection& intersection);

     virtual void ResolveDragging(BlockGrid& grid);

     virtual void ComputeForces(BlockGrid& grid);

     virtual void EulerIntegrate(double dt);
     virtual void MidPointIntegrate(double dt);
     virtual void RK4Integrate(double dt);


     class Particle
     {
     public:
        Particle();
        Particle(const Particle& p);
        Particle& operator=(const Particle& p);
        Particle(int idx, const vec3& pos,const vec3& vel,const vec3& force,const vec3& userforce, double mass);

        int index;
        vec3 position;
        vec3 velocity;
        vec3 force;
        vec3 userforce;
        double mass;

        static Particle EMPTY;
     };

     enum IntersectionType{CONTACT, COLLISION};
     class Intersection
     {
     public:
        Intersection();
        Intersection(const Intersection& p);
        Intersection& operator=(const Intersection& p);
        Intersection(IntersectionType type, int p, const vec3& normal, double d=0);

        int m_p;
        vec3 m_normal;
        double m_distance;
        IntersectionType m_type;
     };

     public:
		 // why is this public? or perhaps more pointedly, if you want to subclass blocks, why isn't this 
		 // exposed through a virtual function?
     BlockGrid m_vparticles;

     IntegrationType m_integrationType;
     std::vector<Intersection>m_vcontacts;
     std::vector<Intersection>m_vcollisions;
	 // I assume that this doesn't take a block as an argument because you want to subclass blocks to yield
	 // different particle grids. But then why take a blockgrid instead of just a particle?
	 // Why should a block take a dependence on the scene data structure?
     virtual void CheckForCollisions(BlockGrid& grid, const Scene& scene);






};

#endif /* BLOCK_H_ */
