/*
 *  Block.h
 *
 *  Created on: Mar 30, 2014
 *  Author: Jing
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

extern const double cellWidth;
extern const double cellHeight;
extern const double cellDepth;
extern const float Threshold;

extern const double GroundKs;
extern const double GroundKd;

extern const double BlocksKs;
extern const double BlocksKd;
  
extern const double g_structuralKs;
extern const double g_structuralKd;

extern const double frictionConst;

class Block
{
  public:
     Block();               		//Block constructor
     virtual ~Block();      		//Block Destructor
     virtual void Update(double dt,
                        const Scene& scene,
                        const vec3& externalForces = vec3(0.0,-9.8,0.0)
                        );
     

     friend class Game;
     //friend void Draw(vec3 center);
     virtual void Reset();
     enum IntegrationType {EULER, MIDPOINT, RK4};
     virtual void SetIntegrationType(IntegrationType type);
     virtual IntegrationType GetIntegrationType() const;

     virtual void InitBlock(vec3 position, double width, double height, double depth);

     virtual bool IsInside(double x, double y, double z);

     double m_width, m_height, m_depth, m_radius;
     int widthNumber, heightNumber, depthNumber;

     vec3 m_center;

     vec3 m_externalForces;   //the external Forces will be Gravity in this case, it will be applied to every block    

     int m_index;

     bool m_friction;    //friction flag

     bool m_alreadyfriction;

     vec3 pointerPosition;
     vec3 prev_pointerPosition;
     int held_flag; // to check if the block is held

     int GetIndex(int i, int j, int k) const;

     void GetCell(int idx, int& i, int& j, int& k)const;

     virtual double GetWidth() const;
     virtual double GetHeight() const;
     virtual double GetDepth() const;


  protected:


     class Intersection;
     class Particle;

     typedef std::vector<std::vector<std::vector<Particle> > > BlockGrid;
     typedef std::vector<Block*> BlockList;
     
     Particle& GetParticle(BlockGrid& grid, int index);
     Particle& GetParticle(BlockGrid& grid,int i, int j, int k);

     virtual void ResolveCollisions(BlockGrid& grid);
     virtual void ResolveContacts(BlockGrid& grid);
     virtual bool FloorIntersection(Particle& p, Intersection& intersection);
     virtual bool BlockIntersection(Particle& p, Block& block, Intersection& intersection);
     virtual void ComputeForces(BlockGrid& grid);

     class Particle
     {
     public:
        Particle();
        Particle(const Particle& p);
        Particle& operator=(const Particle& p);
        Particle(int idx, const vec3& pos, const vec3& vel = vec3(0,0,0), double m = 1);

        int index;
        vec3 position;
        vec3 velocity;
        vec3 force;
        double mass;

        static Particle EMPTY;
     };

     class Spring
     {
     public:
         Spring();
         Spring(const Spring& p);
         Spring& operator=(const Spring& p);
         Spring(int p1, int p2,
             double Ks, double Kd, double restLen);
         int m_p1;
         int m_p2;
         double m_Ks;
         double m_Kd;
         double m_restLen;
     };


     enum IntersectionType{CONTACT, COLLISION};
     enum CollisionType{GROUND, BLOCKS};
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
        CollisionType m_collisiontype;
     };

     public:
     BlockGrid m_vparticles;
     static BlockList m_vblocks;
     IntegrationType m_integrationType;
     std::vector<Intersection>m_vcontacts;
     std::vector<Intersection>m_vcollisions;
     std::vector<Spring>m_vsprings;

     static void AddToList(Block* block); 
     virtual void CheckForCollisions(BlockGrid& grid, const Scene& scene,BlockList& list);
     virtual vec3 updateCenter(BlockGrid& grid);
     virtual void EulerIntegrate(double dt);
     virtual void MidPointIntegrate(double dt);
     virtual void RK4Integrate(double dt);
     virtual void AddSpring(Particle& p1, Particle& p2);
     virtual void dragBlock(BlockGrid& grid);
     virtual void Rotate(double deg);
     virtual void ResolveFriction(BlockGrid& grid);
     virtual vec3 GetCenter() const;

     virtual BlockList GetBlockList() const;

     virtual void SetBlockList(BlockList& list);

     virtual double GetRadius() const;
     virtual void SetRadius(double r);

     virtual int GetBlockIndex() const;
     virtual void SetBlockIndex(int i);

     virtual bool GetFrictionFlag() const;
     virtual void SetFrictionFlag(bool flag); 




};

#endif /* BLOCK_H_ */
