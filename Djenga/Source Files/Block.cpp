/*
 * Block.cpp
 *
 *  Created on: Mar 30, 2014
 *      Author: vrwall
 */

#include "../Header Files/Block.h"
//#include "../GL/gl.h"
#include <GL/glut.h>
//#include "../GL/glu.h"
#include <math.h>
#include <vector>
#include <map>
#include "../Header Files/vec.h"
#include "../Header Files/Scene.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdio.h>



 const double cellWidth = 1.0;
 const double cellHeight = 1.0;
 const double cellDepth = 1.0;

 const float Threshold = 0.15;

 double globalWidth;
 double globalHeight;
 double globalDepth;

   int widthNumber;
   int heightNumber;
   int depthNumber;

  const double VirtualKs = 4000;
  const double VirtualKd = 10;

  void drawCube(double x, double y, double z);

  vec3 globalCenter = vec3();


 Block::Block():
 m_integrationType(Block::RK4),m_width(0.0),m_height(0.0),m_depth(0.0)
 {
   ;

 }

 Block::~Block()
{
}

void Block::Reset()
{
 InitBlock(m_center, m_width, m_height, m_depth);
}

/*
int Block::GetIndex(int i, int j,int k) const
{
  int cols = j;
  int rows = i*(widthNumber+1);
  int stacks = k*(widthNumber+1)*(heightNumber+1);
	
  return cols+rows+stacks;
}
*/

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

int Block::onMouseCheck(vec3 point)
{
  //aditya's code for handling user input
}

void Block::dragBlock(vec3 start, vec3 end, int index)

{
  //aditya's code for handling user input
}

void Block::ResolveDragging(BlockGrid& block)
{
  //aditya's code for handling user input
}

Block::Particle& Block::GetParticle(Block::BlockGrid& grid, int index)
{
  return grid[index];
}

/*
Block::Particle& Block::GetParticle(Block::BlockGrid& grid, int i, int j, int k)
{
   return grid[i][j][k];

}
*/

/*
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
*/

void Block::clearUserForces()
{
   BlockGrid& g = m_vparticles;
   //TODO
}

void Block::InitBlock(vec3 center, double width, double height, double depth)
{

   m_width = width;
   m_height = height;
   m_depth = depth;

   globalWidth = width;
   globalHeight = height;
   globalDepth = depth;


   m_vparticles.resize(3);
   m_center = center;
   /*
   widthNumber = width/cellWidth;
   heightNumber = height/cellHeight;
   depthNumber = depth/cellDepth;
   m_center = center;

   for(int i=0;i<heightNumber+1;i++)
   {
      for(int j=0; j<widthNumber+1;j++)
      {
         for(int k=0; k<depthNumber+1;k++)
         {
            float x=0;//-width*0.5f+cellWidth*i;
            float y=0;//1.5+cellHeight*j;
            float z=0;//-depth*0.5f+cellDepth*k;
		
            m_vparticles[i][j][k] = Particle(GetIndex(i,j,k),vec3(x,y,z));    //??need to be modified

         }
      }
    }
   */

   m_vparticles[0]=Particle(0, vec3(m_center[0]-0.5*width,m_center[1],m_center[2]),vec3(0,0,0),vec3(0,0,0),vec3(0,0,0), 1.0);
   m_vparticles[1]=Particle(1, m_center,vec3(0,0,0),vec3(0,0,0),vec3(0,0,0), 1.0);
   m_vparticles[2]=Particle(2, vec3(m_center[0]+0.5*width,m_center[1],m_center[2]),vec3(0,0,0),vec3(0,0,0),vec3(0,0,0), 1.0);


   //BlockGrid& g = m_vparticles;
   
   /*
   //initial userforces
   for(int i=0;i<heightNumber+1;i++)
   {
      for(int j=0; j<widthNumber+1;j++)
      {
         for(int k=0; k<depthNumber+1;k++)
         {
		
          GetParticle(g,i,j,k).userforce = vec3(0,0,0);
          }

      }


   }

*/

}

void Block::SetIntegrationType(Block::IntegrationType type)
{
	m_integrationType = type;
}

Block::IntegrationType Block::GetIntegrationType() const
{
return m_integrationType;
}

void Block::Draw(vec3 center)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		     // Clear Screen and Depth Buffer
    glLoadIdentity();
    float red[4] = {1.0,0.4,0.4,0.8};
    float white[4] = {1.0,1.0,1.0,1.0};
    float pink[4] = {0.5,0.0,0.0,1.0};
    float black[4] = {0.0,0.0,0.0,1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, black);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, pink);
    drawCube(center[0],center[1],center[2]);

}

void drawCube(double x, double y, double z)
{
	//printf("%f %f %f\n",x,y,z);
		double half_width = 0.5*globalWidth;
		double half_height = 0.5*globalHeight;
		double half_depth = 0.5*globalDepth;

		glBegin(GL_QUADS);
			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex3f(x-half_width, y-half_height, z-half_depth);
			glVertex3f(x+half_width, y-half_height, z-half_depth);
			glVertex3f(x+half_width, y+half_height, z-half_depth);
			glVertex3f(x-half_width, y+half_height, z-half_depth);


			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex3f(x+half_width, y+half_height, z-half_depth);
			glVertex3f(x-half_width, y+half_height, z-half_depth);
			glVertex3f(x-half_width, y+half_height, z+half_depth);
			glVertex3f(x+half_width, y+half_height, z+half_depth);

			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(x-half_width, y+half_height, z+half_depth);
			glVertex3f(x-half_width, y-half_height, z+half_depth);
			glVertex3f(x+half_width, y-half_height, z+half_depth);
			glVertex3f(x+half_width, y+half_height, z+half_depth);

			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex3f(x+half_width, y-half_height, z-half_depth);
			glVertex3f(x-half_width, y-half_height, z-half_depth);
			glVertex3f(x-half_width, y-half_height, z+half_depth);
			glVertex3f(x+half_width, y-half_height, z+half_depth);

			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(x-half_width, y+half_height, z-half_depth);
			glVertex3f(x-half_width, y-half_height, z-half_depth);
			glVertex3f(x-half_width, y-half_height, z+half_depth);
			glVertex3f(x-half_width, y+half_height, z+half_depth);

			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3f(x+half_width, y+half_height, z-half_depth);
			glVertex3f(x+half_width, y-half_height, z-half_depth);
			glVertex3f(x+half_width, y-half_height, z+half_depth);
			glVertex3f(x+half_width, y+half_height, z+half_depth);

			glEnd();

}



void Block::Update(double dt, const Scene& scene, const vec3& externalForces)
{
  m_externalForces = externalForces;

  CheckForCollisions(m_vparticles, scene);

  ResolveContacts(m_vparticles);
  ResolveCollisions(m_vparticles);
  ResolveDragging(m_vparticles);

  /*
  switch(m_integrationType)
  {
  case EULER: EulerIntegration(dt); break;
  case MIDPOINT: MidPointIntegration(dt); break;
  case RK4: RK4Integration(dt); break;


  }
  error message EulerIntegration not in scope

  */

}

void Block::CheckForCollisions(BlockGrid& grid, const Scene& scene)
{
   m_vcontacts.clear();
   m_vcollisions.clear();

   /*
   for(int i=0;i<heightNumber+1;i++)
      {
         for(int j=0; j<widthNumber+1;j++)
         {
            for(int k=0; k<depthNumber+1;k++)
            {
            	Particle& p=GetParticle(grid,i,j,k);
    */

                for(int i=0;i<3;i++)
                {

                Particle& p=GetParticle(grid,i);
            	Intersection intersection;
            	if(FloorIntersection(p,intersection))
            	{
            		if(intersection.m_type==CONTACT)
            			m_vcontacts.push_back(intersection);
            		if(intersection.m_type==COLLISION)
            			m_vcollisions.push_back(intersection);

            	}

            	//Handling block intersection here TODO

                }
         
      

}

bool Block::FloorIntersection(Particle& p, Intersection& intersection)
{
  if(p.position[1]<0)
  {
	  intersection.m_p = p.index;
	  intersection.m_type = CONTACT;
	  intersection.m_distance = -p.position[1];
	  intersection.m_normal = vec3(0,1,0);
	  return true;

  }

  if(p.position[1]<Threshold)
  {
	  intersection.m_p = p.index;
	  intersection.m_type = COLLISION;
	  intersection.m_distance = -p.position[1];
	  intersection.m_normal = vec3(0,1,0);
	  return true;

  }
  return false;

}

void Block::ComputeForces(BlockGrid& grid)
{
           /*
	   //add gravity to all the particles
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
           */
           for(int i=0;i<3;i++)
          {
            Particle& p= GetParticle(grid,i);
            p.force = m_externalForces*p.mass;    
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
		  pt.force += VirtualKs*(dist*normal)+VirtualKd*(pt.velocity*normal)*normal;

	  }

	  }
}


void Block::EulerIntegrate(double dt)
{
        /*
	//BlockGrid target = m_vparticles; // target is a copy!
	BlockGrid& source = m_vparticles; // source is a ptr!
	//BlockGrid accum1 = m_vparticles;

		for (int i = 0; i < heightNumber+1; i++)
	{
		for (int j = 0; j < widthNumber+1; j++)
		{
			for (int k = 0; k < depthNumber+1; k++)
			{
				Particle& s = GetParticle(source, i,j,k);

				//Particle& t = GetParticle(target, i,j,k);
				s.velocity = s.velocity + dt * s.force * 1/s.mass;
				s.position = s.position + dt * s.velocity;
			}

            }
		}
		//ComputeForces(source);
*/
}

void Block::MidPointIntegrate(double dt)
{
        /*
	double halfdt = 0.5 * dt;
	BlockGrid target = m_vparticles; // target is a copy!
	BlockGrid& source = m_vparticles; // source is a ptr!
	//Particle& t = GetParticle(target, i,j,k);
	// Step 1
	//BlockGrid accum1 = m_vparticles;
	for (int i = 0; i < heightNumber+1; i++)
	{
		for (int j = 0; j < widthNumber+1; j++)
		{
			for (int k = 0; k < depthNumber+1; k++)
			{
				Particle& s = GetParticle(source, i,j,k);

				//Particle& k1 = GetParticle(accum1, i,j,k);
				//k1.force = s.force;
				//k1.velocity = s.velocity;

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
				//Particle& t = GetParticle(target, i,j,k);
				//Particle& k2 = GetParticle(accum2, i,j,k);

				//k2.force = t.force;
				//k2.velocity = t.velocity;
				Particle& t = GetParticle(target, i,j,k);
				Particle& s = GetParticle(source, i,j,k);
				s.velocity = s.velocity + dt * t.force * 1/t.mass;
				s.position = s.position + dt * t.velocity;
			}
		}
	}

	//ComputeForces(source);
*/
}

void Block::RK4Integrate(double dt)
{
        /*
	double halfdt = 0.5 * dt;
	BlockGrid target = m_vparticles; // target is a copy!
	BlockGrid& source = m_vparticles; // source is a ptr!

	// Step 1
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
*/
}

//---------------------------------------------------------------------
// Particle
//---------------------------------------------------------------------

Block::Particle Block::Particle::EMPTY;
 
Block::Particle::Particle(int idx, const vec3& p, const vec3& v, const vec3& f, const vec3& userf, double m)
{
//	printf("Hello");
    index = idx;
    position = p;
    velocity = v;
    force = f;
    userforce=userf;
    mass = m;
}

Block::Particle::Particle() : index(-1), position(0,0,0), velocity(0,0,0), force(0,0,0), userforce(0,0,0), mass(1.0)
{
}

Block::Particle::Particle(const Block::Particle& p) :
    index(p.index), position(p.position), velocity(p.velocity), force(p.force), userforce(p.userforce), mass(p.mass)
{
}

Block::Particle& Block::Particle::operator=(const Block::Particle& p)
{
    if (&p == this) return *this;

    index = p.index;
    position = p.position;
    velocity = p.velocity;
    force = p.force;
    userforce =p.userforce;
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



