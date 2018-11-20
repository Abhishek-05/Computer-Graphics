/*
  A program which opens a window and draws three arms in a hierarchy

  Use the arrow keys and PgUp,PgDn, 
  keys to make the arms move.

  Use the keys 1,2 and 3 to switch between arms.

  Written by - 
               Harshavardhan Kode
*/
#ifndef _COLORCUBE_HPP_
#define _COLORCUBE_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include <vector>
#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "hierarchy_node.hpp"

/*// Translation Parameters
GLfloat xpos=0.0,ypos=0.0,zpos=0.0;
// Rotation Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;*/
// Camera position and rotation Parameters
GLfloat c_xpos = 0.0, c_ypos = 0.0, c_zpos = 10.0;
GLfloat c_up_x = 0.0, c_up_y = 1.0, c_up_z = 0.0;
GLfloat c_xrot=0.0,c_yrot=0.0,c_zrot=0.0;

//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;
//Enable/Disable perspective view
bool enable_perspective=true;
//Shader program attribs
GLuint vPosition,vColor;

//global matrix stack for hierarchical modelling
std::vector<glm::mat4> matrixStack;

csX75::HNode* root_node;
csX75::HNode* curr_node;
csX75::HNode* node1;
csX75::HNode* node2;
csX75::HNode* node3;

// abdomen
csX75::HNode* abdomen;
csX75::HNode* abdomen_coverup;
csX75::HNode* abdomen_coverdown;

//hip
csX75::HNode* hip;
csX75::HNode* hip_coverdown;

//frock
csX75::HNode* frock;
csX75::HNode* frock1;
csX75::HNode* frock2;

//chest
csX75::HNode* chest1;
csX75::HNode* chest2;

//shoulder
csX75::HNode* shoulder1;
csX75::HNode* shoulder2;

//thigh
csX75::HNode* thigh1;
csX75::HNode* thigh2;

// //leg
// csX75::HNode* leg1;
// csX75::HNode* leg2;

//shoes
csX75::HNode* shoe1;
csX75::HNode* shoe2;

//arm
csX75::HNode* arm1;
csX75::HNode* arm2;

//forearm
csX75::HNode* forearm1;
csX75::HNode* forearm2;

//palm
csX75::HNode* palm1;
csX75::HNode* palm2;

//neck
csX75::HNode* neck;

//head
csX75::HNode* head;

//hair
csX75::HNode* hair;

//hair_syle
csX75::HNode* style;

// c2_abdomen
csX75::HNode* c2_abdomen;
csX75::HNode* c2_abdomen_coverup;
csX75::HNode* c2_abdomen_coverdown;

//c2_hip
csX75::HNode* c2_hip;
csX75::HNode* c2_hip_coverdown;

//c2_shoulder
csX75::HNode* c2_shoulder1;
csX75::HNode* c2_shoulder2;

//c2_thigh
csX75::HNode* c2_thigh1;
csX75::HNode* c2_thigh2;

//c2_leg
csX75::HNode* c2_leg1;
csX75::HNode* c2_leg2;

//c2_shoes
csX75::HNode* c2_shoe1;
csX75::HNode* c2_shoe2;

//c2_arm
csX75::HNode* c2_arm1;
csX75::HNode* c2_arm2;

//c2_forearm
csX75::HNode* c2_forearm1;
csX75::HNode* c2_forearm2;

//c2_palm
csX75::HNode* c2_palm1;
csX75::HNode* c2_palm2;


//c2_head
csX75::HNode* c2_head;

//c2_neck
csX75::HNode* c2_neck;

//c2_neck
csX75::HNode* c2_hair;
csX75::HNode* c2_hair1;
csX75::HNode* c2_hair2;

//hat
csX75::HNode* hat_low;
csX75::HNode* hat_mid;
csX75::HNode* hat_top;

//box
csX75::HNode* rr;
csX75::HNode* rr2;
csX75::HNode* rr3;
csX75::HNode* rr4;
csX75::HNode* rr5;
csX75::HNode* rr6;

//table & chair
csX75::HNode* table;
csX75::HNode* leg1;
csX75::HNode* leg2;
csX75::HNode* leg3;
csX75::HNode* leg4;

csX75::HNode* ch_seat;
csX75::HNode* ch_back;
csX75::HNode* ch_leg1;
csX75::HNode* ch_leg2;
csX75::HNode* ch_leg3;
csX75::HNode* ch_leg4;

///bed
csX75::HNode* bed_head;
csX75::HNode* bed_bottom;
csX75::HNode* bed_sheet;





//-------------------------------------------------------------------------

#endif
