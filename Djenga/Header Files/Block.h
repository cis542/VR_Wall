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



     virtual void Draw(vec3 center);

     void drawCube(double x, double y, double z);

     //virtual void DrawCube(double x, double y, double z);

     virtual void Reset();

     //virtual void SetGridSize(int cols, int rows, int stacks);

     enum IntegrationType {EULER, MIDPOINT, RK4};
     virtual void SetIntegrationType(IntegrationType type);
     virtual IntegrationType GetIntegrationType() const;

     virtual int onMouseCheck(vec3 point);



     virtual void clearUserForces();



     virtual void InitBlock(vec3 position, double width, double height, double depth);

     virtual bool IsInside(double x, double y, double z);

     double m_width, m_height, m_depth, m_radius;

     vec3 m_center;

     vec3 m_externalForces;

     vec3 m_initialPosition;

     int m_index;

     
     

     

     vec3 pointerPosition;
     vec3 prev_pointerPosition;
     int held_flag; // to chk if the block is held

     int GetIndex(int i, int j, int k) const;

     void GetCell(int idx, int& i, int& j, int& k)const;

     virtual double GetWidth() const;
     virtual double GetHeight() const;
     virtual double GetDepth() const;
     






     //virtual glm::vec3 onClick();

  protected:


     class Intersection;
     class Particle;

     typedef std::vector<std::vector<std::vector<Particle> > > BlockGrid;
     typedef std::vector<Block*> BlockList;
     

     Particle& GetParticle(BlockGrid& grid, int index);
     Particle& GetParticle(BlockGrid& grid,int i, int j, int k);
     //const Particle& GetParticle(const BlockGrid& grid, int index) const;
     //const Particle& GetParticle(const BlockGrid& grid,int i, int j, int k) const;

     //virtual void CheckForCollisions(BlockGrid& grid, const Scene& scene);
     virtual void ResolveCollisions(BlockGrid& grid);
     virtual void ResolveContacts(BlockGrid& grid);
     virtual bool FloorIntersection(Particle& p, Intersection& intersection);
     virtual bool BlockIntersection(Particle& p, Block& block, Intersection& intersection);

     virtual void ResolveDragging(BlockGrid& grid);

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
        vec3 userforce;
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

         //SpringType m_type;
         int m_p1;
         int m_p2;
         double m_Ks;
         double m_Kd;
         double m_restLen;
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
     BlockGrid m_vparticles;
     static BlockList m_vblocks;
     
     //int m_cols, m_rows, m_stacks;

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
     

     virtual vec3 GetCenter() const;

     virtual BlockList GetBlockList() const;

     virtual void SetBlockList(BlockList& list);

     virtual double GetRadius() const;
     virtual void SetRadius(double r);

     virtual int GetBlockIndex() const;
     virtual void SetBlockIndex(int i);




};

#endif /* BLOCK_H_ */
