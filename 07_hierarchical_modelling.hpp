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
GLfloat c_xpos = 0.0, c_ypos = 0.0, c_zpos = 15.0;
GLfloat c_up_x = 0.0, c_up_y = 1.0, c_up_z = 0.0;
GLfloat c_xrot=0.0,c_yrot=0.0,c_zrot=0.0;

//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;
//Enable/Disable perspective view
bool enable_perspective=true;
//bool enable_perspective=false;
//Shader program attribs
GLuint uModelViewMatrix;
GLuint viewMatrix;
GLuint normalMatrix;

GLuint vPosition,vColor,texCoord, vNormal;

//global matrix stack for hierarchical modelling
std::vector<glm::mat4> matrixStack;

csX75::HNode* root_node;
csX75::HNode* curr_node;
csX75::HNode* node1;
csX75::HNode* node2;
csX75::HNode* node3;

//box
csX75::HNode* rr;
csX75::HNode* rr2;
csX75::HNode* rr2_1;
csX75::HNode* rr2_2;
csX75::HNode* rr2_3;
csX75::HNode* rr2_4;
csX75::HNode* rr2_5;
csX75::HNode* rr2_6;
csX75::HNode* rr3;
csX75::HNode* rr3_1;
csX75::HNode* rr3_2;
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

//lamp
csX75::HNode* lamp_bottom;
csX75::HNode* lamp_stick;
csX75::HNode* lamp_light;

//case
csX75::HNode* case_middle;
csX75::HNode* case_top;
csX75::HNode* case_left;
csX75::HNode* case_right;
csX75::HNode* case_between;
csX75::HNode* case_back;
csX75::HNode* book1;
csX75::HNode* book2;
//stool
csX75::HNode* stool;
csX75::HNode* leg11;
csX75::HNode* leg22;
csX75::HNode* leg33;
csX75::HNode* leg44;

//door
csX75::HNode* door;

//inner box
csX75::HNode* box_bottom;
csX75::HNode* box_left;
csX75::HNode* box_right;
csX75::HNode* box_front;
csX75::HNode* box_back;
csX75::HNode* box_top;

//robot
csX75::HNode* head;
csX75::HNode* chest;
csX75::HNode* lthigh;
csX75::HNode* rthigh;
csX75::HNode* lhand;
csX75::HNode* rhand;
csX75::HNode* lcalf;
csX75::HNode* rcalf;
csX75::HNode* lfoot;
csX75::HNode* rfoot;
csX75::HNode* lforehand;
csX75::HNode* rforehand;
csX75::HNode* lwrist;
csX75::HNode* rwrist;
csX75::HNode* base;
csX75::HNode* neck;
csX75::HNode* lshoulder;
csX75::HNode* rshoulder;
//csX75::HNode* head;


//-------------------------------------------------------------------------

#endif
