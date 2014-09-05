/*
 * Block.cpp
 *
 *  Created on: Mar 30, 2014
 *      Author: Jing
 */

#include "../Header Files/Block.h"
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <map>
#include "../Header Files/vec.h"
#include "../Header Files/Scene.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdio.h>

#define PI 3.1459
#define EPLISION 0.08

const double cellWidth = 0.1;
const double cellHeight = 0.1;
const double cellDepth = 0.1;
const float Threshold = 0.05;

const double GroundKs = 1000;
const double GroundKd = 30;

const double BlocksKs = 500;
const double BlocksKd = 10;
  
const double g_structuralKs=3000;
const double g_structuralKd=10;

const double frictionConst=0.1;

Block::Block():
m_integrationType(Block::RK4),m_width(0.0),m_height(0.0),m_depth(0.0),m_radius(0.0),m_index(-1),
widthNumber(0), heightNumber(0), depthNumber(0),m_alreadyfriction(false),m_friction(false) {}

Block::~Block() {}

Block::BlockList Block::m_vblocks;

void Block::Reset()
{
  InitBlock(m_center, m_width, m_height, m_depth);
}

//translating a 3D index into a 1D index
int Block::GetIndex(int i, int j,int k) const
{
  int cols=j;
  int rows=i*(widthNumber+1);
  int stacks=k*(widthNumber+1)*(heightNumber+1);
  return cols+rows+stacks;
}


double Block::GetWidth() const
{
  return m_width;
}

double Block::GetHeight() const
{
  return m_height;
}

double Block::GetDepth() const
{
  return m_depth;
}

//Called when player drags the block using wiimote
void Block::dragBlock(BlockGrid& grid)

{
  double x_disp, y_disp, z_disp;

  x_disp = pointerPosition[0] - prev_pointerPosition[0];
  y_disp = pointerPosition[1] - prev_pointerPosition[1];
  z_disp = pointerPosition[2] - prev_pointerPosition[2];


  for(int i=0;i<heightNumber+1;i++)
  {
	     for(int j=0; j<widthNumber+1;j++)
	     {
	          for(int k=0; k<depthNumber+1;k++)
	          {
	            	Particle& p=GetParticle(grid,i,j,k);
	            	p.position = p.position + vec3(x_disp, y_disp, z_disp);
	            	p.velocity = vec3();
	            	p.force = vec3();
	          }
	     }
	}
	prev_pointerPosition = pointerPosition;

}


Block::Particle& Block::GetParticle(Block::BlockGrid& grid, int index)
{
  int i,j,k;
  GetCell(index,i,j,k);
  return GetParticle(grid,i,j,k);
}

Block::Particle& Block::GetParticle(Block::BlockGrid& grid, int i, int j, int k)
{
   return grid[i][j][k];

}


#define ROUND(x) (floor(x + 0.5))
#define FLOOR(x) (floor(x))
#define FRACT(x) (x - FLOOR(x))
void Block::GetCell(int idx, int& i, int &j, int& k) const
{
    float rows = heightNumber+1;
    float cols = widthNumber+1;
    float stacks = depthNumber+1;

    // derived from idx = cols*(rows*k + i) + j
    float tmp = FLOOR(idx/cols);
    j = (int) ROUND(cols*(FRACT(idx/cols)));
    i = (int) ROUND(rows*(FRACT(tmp/rows)));
    k = (int) FLOOR(tmp/rows);
}

void Block::InitBlock(vec3 center, double width, double height, double depth)
{

   m_vsprings.clear();
   m_width = width;
   m_height = height;
   m_depth = depth;

   widthNumber = width/cellWidth;
   heightNumber = height/cellHeight;
   depthNumber = depth/cellDepth;
   m_center = center;
   double diagonal = sqrt(width*width+depth*depth);
   m_radius = 0.35*(sqrt(diagonal*diagonal+height*height));

   if (widthNumber > 0 && heightNumber > 0 && depthNumber > 0)
       {
           m_vparticles.resize(heightNumber+1);
           for (int i = 0; i < heightNumber+1; i++)
           {
               m_vparticles[i].resize(widthNumber+1);
               for (int j = 0; j < widthNumber+1; j++)
               {
                   m_vparticles[i][j].resize(depthNumber+1);
               }
           }
       }

   for(int i=0;i<heightNumber+1;i++)
   {
      for(int j=0; j<widthNumber+1;j++)
      {
         for(int k=0; k<depthNumber+1;k++)
         {
            float x=-width*0.5f+cellWidth*i+center[0];
            float y=-height*0.5f+cellHeight*j+center[1];
            float z=-depth*0.5f+cellDepth*k+center[2];
            m_vparticles[i][j][k]=Particle(GetIndex(i,j,k),vec3(x,y,z));   

         }
      }
    }

   BlockGrid& g = m_vparticles;
   //Setup Structural Spring
   for (int i = 0; i < heightNumber+1; i++)
   {
       for (int j = 0; j < widthNumber+1; j++)
       {
           for (int k = 0; k < depthNumber+1; k++)
           {
               if (j < widthNumber) {
		AddSpring(GetParticle(g,i,j,k), GetParticle(g,i,j+1,k));
		}
               if (i < heightNumber) {
		AddSpring(GetParticle(g,i,j,k), GetParticle(g,i+1,j,k));
		}
               if (k < depthNumber) {
		AddSpring(GetParticle(g,i,j,k), GetParticle(g,i,j,k+1));
		}
           }
       }
   }


	//Setup Shear springs

   for (int i = 0; i < heightNumber+1; i++)
   {
       for (int j = 0; j < widthNumber+1; j++)
       {
           for (int k = 0; k < depthNumber+1; k++)
           {

                if (j < widthNumber&&i<heightNumber) AddSpring(GetParticle(g,i,j,k), GetParticle(g,i+1,j+1,k));
	        if(j>0 && i< heightNumber) AddSpring(GetParticle(g,i,j,k), GetParticle(g,i+1,j-1,k));

		if(i<heightNumber&&k<depthNumber) AddSpring(GetParticle(g,i,j,k), GetParticle(g,i+1,j,k+1));
		if(k>0&& i<heightNumber)  AddSpring(GetParticle(g,i,j,k), GetParticle(g,i+1,j,k-1));

		if(j<widthNumber&&k<depthNumber) AddSpring(GetParticle(g,i,j,k), GetParticle(g,i,j+1,k+1));
		if(k>0&& j<widthNumber)  AddSpring(GetParticle(g,i,j,k), GetParticle(g,i,j+1,k-1));

		    }

	}
   }


	//Setup Bend Spring
   for (int i = 0; i < heightNumber+1; i++)
   {
       for (int j = 0; j < widthNumber+1; j++)
       {
           for (int k = 0; k < depthNumber+1; k++)
           {
               if (j < widthNumber-1) AddSpring(GetParticle(g,i,j,k), GetParticle(g,i,j+2,k));
               if (i < heightNumber-1) AddSpring(GetParticle(g,i,j,k), GetParticle(g,i+2,j,k));
               if (k < depthNumber-1) AddSpring(GetParticle(g,i,j,k), GetParticle(g,i,j,k+2));
           }
       }
   }


	//Setup Bend Spring across two cells
	for (int i = 0; i < heightNumber+1; i++)
   	{
      	    for (int j = 0; j < widthNumber+1; j++)
      	    {
               for (int k = 0; k < depthNumber+1; k++)
               {
		       if (j < widthNumber-2) AddSpring(GetParticle(g,i,j,k), GetParticle(g,i,j+3,k));
		       if (i < heightNumber-2) AddSpring(GetParticle(g,i,j,k), GetParticle(g,i+3,j,k));
		       if (k < depthNumber-2) AddSpring(GetParticle(g,i,j,k), GetParticle(g,i,j,k+3));
               }
       }
   }



        //Setup diagonal Spring
	for (int i = 0; i < heightNumber+1; i++)
	{
	     for (int j = 0; j < widthNumber+1; j++)
	     {
		for (int k = 0; k < depthNumber+1; k++)
		{
		        if (j < widthNumber-1 && i<heightNumber-1) AddSpring(GetParticle(g,i,j,k), GetParticle(g,i+2,j+2,k));
			if(j>1 && i< heightNumber-1) AddSpring(GetParticle(g,i,j,k), GetParticle(g,i+2,j-2,k));

			if(i<heightNumber-1&&k<depthNumber-1) AddSpring(GetParticle(g,i,j,k), GetParticle(g,i+2,j,k+2));
			if(k>1&& i<heightNumber-1)  AddSpring(GetParticle(g,i,j,k), GetParticle(g,i+2,j,k-2));

			if(j<widthNumber-1&&k<depthNumber-1) AddSpring(GetParticle(g,i,j,k), GetParticle(g,i,j+2,k+2));
			if(k>1&& j<widthNumber-1)  AddSpring(GetParticle(g,i,j,k), GetParticle(g,i,j+2,k-2));
		}

              }
        }


	for (int i = 0; i < heightNumber+1; i++)
        {
       		for (int j = 0; j < widthNumber+1; j++)
       		{
       		    for (int k = 0; k < depthNumber+1; k++)
       		    {
                        if (j < widthNumber-2 && i<heightNumber-2) AddSpring(GetParticle(g,i,j,k), GetParticle(g,i+3,j+3,k));
		        if(j>2 && i< heightNumber-2) AddSpring(GetParticle(g,i,j,k), GetParticle(g,i+3,j-3,k));

			if(i<heightNumber-2&&k<depthNumber-2) AddSpring(GetParticle(g,i,j,k), GetParticle(g,i+3,j,k+3));
			if(k>2&& i<heightNumber-2)  AddSpring(GetParticle(g,i,j,k), GetParticle(g,i+3,j,k-3));

			if(j<widthNumber-2&&k<depthNumber-2) AddSpring(GetParticle(g,i,j,k), GetParticle(g,i,j+3,k+3));
			if(k>2&& j<widthNumber-2)  AddSpring(GetParticle(g,i,j,k), GetParticle(g,i,j+3,k-3));
		    }

		}
           }

	for (int i = 0; i < heightNumber+1; i++)
	   {
	       for (int j = 0; j < widthNumber+1; j++)
	       {
		   for (int k = 0; k < depthNumber+1; k++)
		   {
		       if (j < widthNumber-3) AddSpring(GetParticle(g,i,j,k), GetParticle(g,i,j+4,k));
		       if (i < heightNumber-3) AddSpring(GetParticle(g,i,j,k), GetParticle(g,i+4,j,k));
		       if (k < depthNumber-3) AddSpring(GetParticle(g,i,j,k), GetParticle(g,i,j,k+4));
		   }
	       }
	   }
        
}

void Block::AddSpring(Particle& p1, Particle& p2)
{
    double restLen = (p1.position - p2.position).Length();
    m_vsprings.push_back(Spring(p1.index, p2.index, g_structuralKs, g_structuralKd, restLen));
}

void Block::SetIntegrationType(Block::IntegrationType type)
{
    m_integrationType = type;
}

Block::IntegrationType Block::GetIntegrationType() const
{
    return m_integrationType;
}

vec3 Block::updateCenter(BlockGrid& grid)
{
    vec3 pos = GetParticle(grid, (int)(heightNumber/2), (int)(widthNumber/2), (int)(depthNumber/2)).position;
    m_center = pos;
    return pos;
}


void Block::Update(double dt, const Scene& scene, const vec3& externalForces)
{
  if (held_flag == 0){
  	m_externalForces = externalForces;
  	CheckForCollisions(m_vparticles, scene, m_vblocks);

  	ResolveContacts(m_vparticles);
  	ResolveCollisions(m_vparticles);

        updateCenter(m_vparticles);
        ResolveFriction(m_vparticles);
  	switch(m_integrationType)
  	{
		case EULER: EulerIntegrate(dt); break;
		case MIDPOINT: MidPointIntegrate(dt); break;
		case RK4: RK4Integrate(dt); break;
  	}
  }
  else
  {
	dragBlock(m_vparticles);
  }
}

void Block::CheckForCollisions(BlockGrid& grid, const Scene& scene, BlockList& list)
{

   //Scene will be used if there are fixed object in the 3D space
   m_vcontacts.clear();
   m_vcollisions.clear();
   for(int i=0;i<heightNumber+1;i++)
      {
         for(int j=0; j<widthNumber+1;j++)
         {
            for(int k=0; k<depthNumber+1;k++)
            {
            	Particle& p=GetParticle(grid,i,j,k);
            	Intersection intersection;

                //Handling ground intersection here
            	if(FloorIntersection(p,intersection))
            	{
            		if(intersection.m_type==CONTACT)
            			m_vcontacts.push_back(intersection);
            		if(intersection.m_type==COLLISION)
            			m_vcollisions.push_back(intersection);

            	}
                
                  
            	//Handling block intersection here
                for(int i=0;i<list.size();i++)
                {
                    if(BlockIntersection(p,*(list[i]),intersection))
                    {
                        if(intersection.m_type==CONTACT)
            			m_vcontacts.push_back(intersection);
            		if(intersection.m_type==COLLISION)
            			m_vcollisions.push_back(intersection);

                    }
                }
              

            }
         }
      }

}

bool Block::FloorIntersection(Particle& p, Intersection& intersection)
{
  if(p.position[1]<-1.0f)
  {
	  intersection.m_p = p.index;
	  intersection.m_type = CONTACT;
	  intersection.m_distance = -1-p.position[1];
	  intersection.m_normal = vec3(0,1,0);
          intersection.m_collisiontype=GROUND;
	  return true;

  }

  if(p.position[1]<-1.0f+Threshold)
  {
	  intersection.m_p = p.index;
	  intersection.m_type = COLLISION;
	  intersection.m_distance = -1+Threshold-p.position[1];
	  intersection.m_normal = vec3(0,1,0);
          intersection.m_collisiontype=GROUND;
	  return true;

  }
  return false;

}

//Code for computing block intersection

vec3 Block::GetCenter() const
{
  return m_center;    //get this block's center position

}

double Block::GetRadius() const
{
 return m_radius;

}

void Block::SetRadius(double r)
{
  m_radius = r;

}

int Block::GetBlockIndex() const
{
return m_index;

}

void Block::SetBlockIndex(int i)
{
m_index = i;
}

Block::BlockList Block::GetBlockList() const
{
 return m_vblocks;

}

void Block::SetBlockList(Block::BlockList& list)
{
  m_vblocks=list;

}

void Block::AddToList(Block* block)
{
  m_vblocks.push_back(block);

}

bool Block::GetFrictionFlag() const
{
  return m_friction;

}

void Block::SetFrictionFlag(bool flag)
{
  m_friction = flag;

}

bool Block::BlockIntersection(Particle& p, Block& block, Intersection& intersection)
{
  
  if(block.m_index==this->m_index) return false;
  else {
  	if((block.GetCenter()-p.position).Length()<block.GetRadius())
    	{  	
         
                  intersection.m_p = p.index;
		  intersection.m_type = CONTACT;
                  intersection.m_collisiontype=BLOCKS;
		  intersection.m_distance = block.GetRadius()-(p.position-block.GetCenter()).Length();   
		  intersection.m_normal = (p.position-block.GetCenter()).Normalize();
		  return true;
    	}
    	if((p.position-block.GetCenter()).Length()<block.GetRadius()+Threshold)
     	{
		  intersection.m_p = p.index;
		  intersection.m_type = COLLISION;
                  intersection.m_collisiontype=BLOCKS;
		  intersection.m_distance = block.GetRadius()+Threshold-(p.position-block.GetCenter()).Length();
		  intersection.m_normal = (p.position-block.GetCenter()).Normalize();
		  return true;

      	}
        }
        return false;


  }

void Block::ComputeForces(BlockGrid& grid)
{
	   //add gravity to all the particles, it can be modified to any external forces
	   for(int i=0;i<heightNumber+1;i++)
	      {
	         for(int j=0; j<widthNumber+1;j++)
	         {
	            for(int k=0; k<depthNumber+1;k++)
	            {
	            	Particle& p=GetParticle(grid,i,j,k);
	            	p.force = m_externalForces*p.mass;
	            }
	         }
	      }

	    // Update springs
	    for(unsigned int i = 0; i < m_vsprings.size(); i++)
	    {
	        Spring& spring = m_vsprings[i];
	        Particle& a = GetParticle(grid, spring.m_p1);
	        Particle& b = GetParticle(grid, spring.m_p2);


            // Compute Internal Forces
		a.force = -(m_vsprings[i].m_Ks*((a.position - b.position).Length() - m_vsprings[i].m_restLen)+
			        m_vsprings[i].m_Kd*(((a.velocity - b.velocity)*(a.position-b.position))/((a.position - b.position).Length())))
					*(a.position - b.position)/((a.position - b.position).Length()) + a.force;
		b.force =  (m_vsprings[i].m_Ks*((a.position - b.position).Length() - m_vsprings[i].m_restLen)+
			        m_vsprings[i].m_Kd*(((a.velocity - b.velocity)*(a.position-b.position))/((a.position - b.position).Length())))
					*(a.position - b.position)/((a.position - b.position).Length()) + b.force;

	    }
}

void Block::ResolveContacts(BlockGrid& grid)
{
	  for(unsigned int i=0;i<m_vcontacts.size();i++)
	  {
		  const Intersection& contact = m_vcontacts[i];
		  Particle& p = GetParticle(grid, contact.m_p);
		  vec3 normal = contact.m_normal;
		  double dist = contact.m_distance;

		  p.position = p.position+dist*normal;
		  p.velocity += (2*(-p.velocity)*normal)*normal;

	  }
}

void Block::ResolveCollisions(BlockGrid& grid)
{
	  for(unsigned int i=0;i<m_vcollisions.size();i++)
	  {
	  Intersection result = m_vcollisions[i];
	  Particle& pt = GetParticle(grid, result.m_p);
	  vec3 normal = result.m_normal;
	  double dist = result.m_distance;

	  if(pt.velocity*normal<0)
	  {
		  
                  vec3 centerV= GetParticle(grid, (int)(heightNumber/2), (int)(widthNumber/2), (int)(depthNumber/2)).velocity;
                  if(result.m_collisiontype==GROUND) 
                  { 
                        pt.force += GroundKs*(dist*normal)+GroundKd*(pt.velocity*normal)*normal;
                  	if(std::abs(centerV[0])<=EPLISION&&std::abs(centerV[2])<=EPLISION)   
                  	{
 				for (int i = 0; i < heightNumber+1; i++)
				{
					for (int j = 0; j < widthNumber+1; j++)
					{
						for (int k = 0; k < depthNumber+1; k++)
						{
    						GetParticle(grid,i,j,k).force = vec3(0,GetParticle(grid,i,j,k).force[1],0);
                                                GetParticle(grid,i,j,k).velocity = vec3(0,GetParticle(grid,i,j,k).velocity[1],0);
						}
					}
				}
                  	SetFrictionFlag(false);
                  	m_alreadyfriction = false;
                  	}
                        else if((std::abs(centerV[0])>EPLISION||std::abs(centerV[2])>EPLISION)&&!m_alreadyfriction)  //register friction force here
                        {
                        SetFrictionFlag(true);
                        }
                  } 
                  else pt.force += BlocksKs*(dist*normal)+BlocksKd*(pt.velocity*normal)*normal;
	  }

	  }
}

void Block::ResolveFriction(BlockGrid& grid)
{
  
  if(GetFrictionFlag())
  {
  Particle& center= GetParticle(grid, (int)(heightNumber/2), (int)(widthNumber/2), (int)(depthNumber/2));
  vec3 centerV = center.velocity;
	if(std::abs(centerV[0])>EPLISION||std::abs(centerV[2])>EPLISION)
        {
        vec3 fri = -vec3(centerV[0],0,centerV[2]).Normalize();
        	for (int i = 0; i < heightNumber+1; i++)
		{
			for (int j = 0; j < widthNumber+1; j++)
			{
				for (int k = 0; k < depthNumber+1; k++)
				{
    				GetParticle(grid,i,j,k).force += frictionConst*fri;    //f = uN, the kinectic friction force is a constant
				}
			}
		}

        }
        else if(std::abs(centerV[0])<=EPLISION&&std::abs(centerV[2])<=EPLISION)
        {
		for (int i = 0; i < heightNumber+1; i++)
		{
			for (int j = 0; j < widthNumber+1; j++)
			{
				for (int k = 0; k < depthNumber+1; k++)
				{
    				GetParticle(grid,i,j,k).force = vec3(0,GetParticle(grid,i,j,k).force[1],0);
                                GetParticle(grid,i,j,k).velocity = vec3(0,GetParticle(grid,i,j,k).velocity[1],0);
				}
			}
		}
        
        }
        SetFrictionFlag(false);
        m_alreadyfriction = true;
  }


}



void Block::EulerIntegrate(double dt)
{
	BlockGrid& source = m_vparticles; // source is a ptr!

	for (int i = 0; i < heightNumber+1; i++)
	{
		for (int j = 0; j < widthNumber+1; j++)
		{
			for (int k = 0; k < depthNumber+1; k++)
			{
				Particle& s = GetParticle(source, i,j,k);

				s.velocity = s.velocity + dt * s.force * 1/s.mass;
				s.position = s.position + dt * s.velocity;
			}

                }
	}

}

void Block::MidPointIntegrate(double dt)
{

	double halfdt = 0.5 * dt;
	BlockGrid target = m_vparticles; // target is a copy!
	BlockGrid& source = m_vparticles; // source is a ptr!

	for (int i = 0; i < heightNumber+1; i++)
	{
		for (int j = 0; j < widthNumber+1; j++)
		{
			for (int k = 0; k < depthNumber+1; k++)
			{
				Particle& s = GetParticle(source, i,j,k);

				Particle& t = GetParticle(target, i,j,k);
				t.velocity = s.velocity + halfdt * s.force * 1/s.mass;
				t.position = s.position + halfdt * s.velocity;
			}
		}
	}

	ComputeForces(target);

	// Step 2
	//BlockGrid accum2 = m_vparticles;
	for (int i = 0; i < heightNumber+1; i++)
	{
		for (int j = 0; j < widthNumber+1; j++)
		{
			for (int k = 0; k < depthNumber+1; k++)
			{

				Particle& t = GetParticle(target, i,j,k);
				Particle& s = GetParticle(source, i,j,k);
				s.velocity = s.velocity + dt * t.force * 1/t.mass;
				s.position = s.position + dt * t.velocity;
			}
		}
	}

}

void Block::RK4Integrate(double dt)
{
	double halfdt = 0.5 * dt;
	BlockGrid target = m_vparticles; // target is a copy!
	BlockGrid& source = m_vparticles; // source is a ptr!

	BlockGrid accum1 = m_vparticles;
	for (int i = 0; i < heightNumber+1; i++)
	{
		for (int j = 0; j < widthNumber+1; j++)
		{
			for (int k = 0; k < depthNumber+1; k++)
			{
				Particle& s = GetParticle(source, i,j,k);

				Particle& k1 = GetParticle(accum1, i,j,k);
				k1.force = s.force;
				k1.velocity = s.velocity;

				Particle& t = GetParticle(target, i,j,k);
				t.velocity = s.velocity + halfdt * k1.force * 1/k1.mass;
				t.position = s.position + halfdt * k1.velocity;
			}
		}
	}

	ComputeForces(target);

	// Step 2
	BlockGrid accum2 = m_vparticles;
	for (int i = 0; i < heightNumber+1; i++)
	{
		for (int j = 0; j < widthNumber+1; j++)
		{
			for (int k = 0; k < depthNumber+1; k++)
			{
				Particle& t = GetParticle(target, i,j,k);
				Particle& k2 = GetParticle(accum2, i,j,k);

				k2.force = t.force;
				k2.velocity = t.velocity;

				Particle& s = GetParticle(source, i,j,k);
				t.velocity = s.velocity + halfdt * k2.force * 1/k2.mass;
				t.position = s.position + halfdt * k2.velocity;
			}
		}
	}

	ComputeForces(target);

	// Step 3
	BlockGrid accum3 = m_vparticles;
	for (int i = 0; i < heightNumber+1; i++)
	{
		for (int j = 0; j < widthNumber+1; j++)
		{
			for (int k = 0; k < depthNumber+1; k++)
			{
				Particle& t = GetParticle(target, i,j,k);
				Particle& k3 = GetParticle(accum3, i,j,k);

				k3.force = t.force;
				k3.velocity = t.velocity;

				Particle& s = GetParticle(source, i,j,k);
				t.velocity = s.velocity + dt * k3.force * 1/k3.mass;
				t.position = s.position + dt * k3.velocity;
			}
		}
	}
	ComputeForces(target);

	// Step 4
	BlockGrid accum4 = m_vparticles;
	for (int i = 0; i < heightNumber+1; i++)
	{
		for (int j = 0; j < widthNumber+1; j++)
		{
			for (int k = 0; k < depthNumber+1; k++)
			{
				Particle& t = GetParticle(target, i,j,k);
				Particle& k4 = GetParticle(accum4, i,j,k);

				k4.force = t.force;
				k4.velocity = t.velocity;
			}
		}
	}

	// Put it all together
	double asixth = 1/6.0;
	double athird = 1/3.0;
	for (int i = 0; i < heightNumber+1; i++)
	{
		for (int j = 0; j < widthNumber+1; j++)
		{
			for (int k = 0; k < depthNumber+1; k++)
			{
				Particle& p = GetParticle(m_vparticles, i,j,k);
				Particle& k1 = GetParticle(accum1, i,j,k);
				Particle& k2 = GetParticle(accum2, i,j,k);
				Particle& k3 = GetParticle(accum3, i,j,k);
				Particle& k4 = GetParticle(accum4, i,j,k);

				p.velocity = p.velocity + dt*(asixth * k1.force +
					athird * k2.force + athird * k3.force + asixth * k4.force)*1/p.mass;

				p.position = p.position + dt*(asixth * k1.velocity +
				athird * k2.velocity + athird * k3.velocity + asixth * k4.velocity);
			}
		}
	}
}

//---------------------------------------------------------------------
// Particle
//---------------------------------------------------------------------

Block::Particle Block::Particle::EMPTY;

Block::Particle::Particle(int idx, const vec3& p, const vec3& v, double m)
{
    index = idx;
    position = p;
    velocity = v;
    force = vec3(0,0,0);
    mass = m;
}

Block::Particle::Particle() : index(-1), position(0,0,0), velocity(0,0,0), force(0,0,0), mass(1.0)
{
}

Block::Particle::Particle(const Block::Particle& p) :
    index(p.index), position(p.position), velocity(p.velocity), force(p.force), mass(p.mass)
{
}

Block::Particle& Block::Particle::operator=(const Block::Particle& p)
{
    if (&p == this) return *this;

    index = p.index;
    position = p.position;
    velocity = p.velocity;
    force = p.force;
    mass = p.mass;
    return *this;
}

//---------------------------------------------------------------------
// Intersection
//---------------------------------------------------------------------

Block::Intersection::Intersection() :
    m_p(-1), m_normal(0,0,0), m_distance(0) , m_type(CONTACT)
{
}

Block::Intersection::Intersection(const Block::Intersection& p) :
    m_p(p.m_p), m_normal(p.m_normal), m_distance(p.m_distance), m_type(p.m_type)
{
}

Block::Intersection& Block::Intersection::operator=(const Block::Intersection& p)
{
    if (&p == this) return *this;
    m_p = p.m_p;
    m_normal = p.m_normal;
    m_distance = p.m_distance;
    m_type = p.m_type;
    return *this;
}

Block::Intersection::Intersection(IntersectionType type, int p, const vec3& normal, double d) :
    m_p(p), m_normal(normal), m_distance(d), m_type(type)
{
}

//---------------------------------------------------------------------
// Spring
//---------------------------------------------------------------------
Block::Spring::Spring() :
    m_p1(-1),
    m_p2(-1),
    m_Ks(1.0), m_Kd(1.0), m_restLen(1.0)
{
}

Block::Spring::Spring(const Block::Spring& p) :
    m_p1(p.m_p1), m_p2(p.m_p2),
    m_Ks(p.m_Ks), m_Kd(p.m_Kd), m_restLen(p.m_restLen)
{
}

Block::Spring& Block::Spring::operator=(const Block::Spring& p)
{
    if (&p == this) return *this;

    //m_type = p.m_type;
    m_p1 = p.m_p1;
    m_p2 = p.m_p2;
    m_Ks = p.m_Ks;
    m_Kd = p.m_Kd;
    m_restLen = p.m_restLen;
    return *this;
}

Block::Spring::Spring(
    int p1, int p2, double Ks, double Kd, double restLen) :
    m_Ks(Ks), m_Kd(Kd), m_p1(p1), m_p2(p2), m_restLen(restLen)
{
}

bool Block::IsInside(double x, double y, double z)
{
	bool retVal = false;
	if (( x > m_center[0]-0.5f*m_width && x < m_center[0]+0.5f*m_width) && ( y > m_center[1]-0.5f*m_height &&
             y < m_center[1]+0.5f*m_height) && ( z > m_center[2]-0.5f*m_depth && z < m_center[2]+0.5f*m_depth))
	{

		retVal = true;
		pointerPosition = vec3(x,y,z);
		if(held_flag == 0)
		{
			prev_pointerPosition = vec3(x,y,z);
		}
	}
	else
	{
		held_flag = 0;
	}
		
	return retVal;
}

void Block::Rotate(double deg)
{
	BlockGrid& source = m_vparticles; // source is a ptr!

	vec3 temp;
	for (int i = 0; i < heightNumber+1; i++)
	{
		for (int j = 0; j < widthNumber+1; j++)
		{
			for (int k = 0; k < depthNumber+1; k++)
			{
				Particle& s = GetParticle(source, i,j,k);
				temp = s.position;
				temp[0] = temp[0]*cos(deg*PI/180) + temp[2]*sin(deg*PI/180);
				temp[2] = -temp[0]*sin(deg*PI/180) + temp[2]*cos(deg*PI/180);
				
				s.position = temp;
			}

            	}
	}
}


