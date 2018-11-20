/*
  CSX75 Tutorial 3

  Use the arrow keys and PgUp,PgDn, 
  keys to make the arms move.

  Use the keys 1,2 and 3 to switch between arms.

  Modified from An Introduction to OpenGL Programming, 
  Ed Angel and Dave Shreiner, SIGGRAPH 2013

  Written by - 
               Harshavardhan Kode
*/


#include "assignment2.hpp"

GLuint shaderProgram;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;


glm::mat4 modelview_matrix;

GLuint uModelViewMatrix;
int num_vertices = 360*6*2;
float sq_side=5.5;
float zoom=1.0;
//###############################################################################
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
glm::vec3 toyColor(1.0f, 0.5f, 0.31f);
glm::vec3 result = lightColor * toyColor;


//-----------------------------------------------------------------

//Eight vertices in homogenous coordinates
//elongated cuboid , basic arm in the hierarchy;
glm::vec4 positions[8] = {
  glm::vec4(0.0, -0.25, 0.25, 1.0),
  glm::vec4(0.0, 0.25, 0.25, 1.0),
  glm::vec4(2.0, 0.25, 0.25, 1.0),
  glm::vec4(2.0, -0.25, 0.25, 1.0),
  glm::vec4(0.0, -0.25, -0.25, 1.0),
  glm::vec4(0.0, 0.25, -0.25, 1.0),
  glm::vec4(2.0, 0.25, -0.25, 1.0),
  glm::vec4(2.0, -0.25, -0.25, 1.0)
};

//RGBA colors
glm::vec4 colors[8] = {
  glm::vec4(0.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 1.0, 0.0, 1.0),
  glm::vec4(0.0, 1.0, 0.0, 1.0),
  glm::vec4(0.0, 0.0, 1.0, 1.0),
  glm::vec4(1.0, 0.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(0.0, 1.0, 1.0, 1.0)
};

glm::vec4 color(0.6, 0.6, 0.6, 1.0);
glm::vec4 black(0.1, 0.1, 0.1, 1.0);
glm::vec4 white(1.0, 1.0, 1.0, 1.0);
glm::vec4 red(1.0, 0.0, 0.0, 1.0);
glm::vec4 red2(0.5, 0.0, 0.0, 1.0);
glm::vec4 brown(0.20, 0.0, 0.0, 1.0);
glm::vec4 yellow(0.9, 1.0, 0.0, 1.0);
glm::vec4 green(0.2, 0.7, 0.2, 1.0);
glm::vec4 blue(0.2, 0.2, 0.7, 1.0);
glm::vec4 skin(1.0, 0.8784, 0.5, 1.0);
glm::vec4 lavendar(0.7, 0.3, 0.9, 1.0);
glm::vec4 lavendar_trans(0.7, 0.2, 0.5, 1.0);
glm::vec4 lavendar_trans1(0.7, 0.2, 0.6, 1.0);
glm::vec4 lavendar_trans2(0.7, 0.2, 0.7, 1.0);
glm::vec4 lavendar_lite(1.0, 0.82, 0.95, 1.0);
glm::vec4 cement(0.376, 0.376, 0.34, 1.0);
glm::vec4 chair(0.1274, 0.1321, 0.14, 1.0);
glm::vec4 dark_skin(.537, .38, 0.153, 1.0);


void setColor(glm::vec4 c)
{
  for(int i=0;i<8;i++) colors[i] = c;
}

int tri_idx=0;


// quad generates two triangles for each face and assigns colors to the vertices
void quad(int a, int b, int c, int d,glm::vec4 * v_positions,glm::vec4 * v_colors)
{
  v_colors[tri_idx] = colors[a]; v_positions[tri_idx] = positions[a]; tri_idx++;
  v_colors[tri_idx] = colors[b]; v_positions[tri_idx] = positions[b]; tri_idx++;
  v_colors[tri_idx] = colors[c]; v_positions[tri_idx] = positions[c]; tri_idx++;
  v_colors[tri_idx] = colors[a]; v_positions[tri_idx] = positions[a]; tri_idx++;
  v_colors[tri_idx] = colors[c]; v_positions[tri_idx] = positions[c]; tri_idx++;
  v_colors[tri_idx] = colors[d]; v_positions[tri_idx] = positions[d]; tri_idx++;
 }

csX75::HNode * ellipsoid_plus(float a,float b1,float b2,float c,float d1,float d2,float z,csX75::HNode * parent)
{
  int num_vertices = 360*6;
  glm::vec4 v_positions[num_vertices];
  glm::vec4 v_colors[num_vertices];
  for(int i=0;i<180;i++){
    positions[2] = glm::vec4(a*cos(i*0.0174533), z, b1*sin(i*0.0174533), 1.0);
    positions[1] = glm::vec4(a*cos((i+1)*0.0174533), z, b1*sin((i+1)*0.0174533), 1.0);
    positions[3] = glm::vec4(c*cos(i*0.0174533), 0.0, d1*sin(i*0.0174533), 1.0);
    positions[0] = glm::vec4(c*cos((i+1)*0.0174533), 0.0, d1*sin((i+1)*0.0174533), 1.0);
    quad( 1, 0, 3, 2 ,v_positions,v_colors);
  }
  for(int i=180;i<360;i++){
    positions[2] = glm::vec4(a*cos(i*0.0174533), z, b2*sin(i*0.0174533), 1.0);
    positions[1] = glm::vec4(a*cos((i+1)*0.0174533), z, b2*sin((i+1)*0.0174533), 1.0);
    positions[3] = glm::vec4(c*cos(i*0.0174533), 0.0, d2*sin(i*0.0174533), 1.0);
    positions[0] = glm::vec4(c*cos((i+1)*0.0174533), 0.0, d2*sin((i+1)*0.0174533), 1.0);
    quad( 1, 0, 3, 2 ,v_positions,v_colors);
  }
  tri_idx = 0;
  csX75::HNode * node = new csX75::HNode(parent,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  return node;
}

csX75::HNode * ellipsoid_minus(float a,float b1,float b2,float c,float d1,float d2,float z,csX75::HNode * parent)
{
  int num_vertices = 360*6;
  glm::vec4 v_positions[num_vertices];
  glm::vec4 v_colors[num_vertices];
  for(int i=0;i<180;i++){
    positions[2] = glm::vec4(a*cos(i*0.0174533), 0.0, b1*sin(i*0.0174533), 1.0);
    positions[1] = glm::vec4(a*cos((i+1)*0.0174533), 0.0, b1*sin((i+1)*0.0174533), 1.0);
    positions[3] = glm::vec4(c*cos(i*0.0174533), z, d1*sin(i*0.0174533), 1.0);
    positions[0] = glm::vec4(c*cos((i+1)*0.0174533), z, d1*sin((i+1)*0.0174533), 1.0);
    quad( 1, 0, 3, 2 ,v_positions,v_colors);
  }
  for(int i=180;i<360;i++){
    positions[2] = glm::vec4(a*cos(i*0.0174533), 0.0, b2*sin(i*0.0174533), 1.0);
    positions[1] = glm::vec4(a*cos((i+1)*0.0174533), 0.0, b2*sin((i+1)*0.0174533), 1.0);
    positions[3] = glm::vec4(c*cos(i*0.0174533), z, d2*sin(i*0.0174533), 1.0);
    positions[0] = glm::vec4(c*cos((i+1)*0.0174533), z, d2*sin((i+1)*0.0174533), 1.0);
    quad( 1, 0, 3, 2 ,v_positions,v_colors);
  }
  tri_idx = 0;
  csX75::HNode * node = new csX75::HNode(parent,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  return node;
}

csX75::HNode * elliptic(float a,float b1,float b2,float c1,csX75::HNode * parent)
{
  tri_idx = 0;
  const int num_vertices1 = (360*180*6)/25;
  glm::vec4 v_positions[num_vertices1];
  glm::vec4 v_colors[num_vertices1];

  //setColor(skin);
  
  for(int j=0;j<90;j++){
  for(int i=0;i<360;i++){
    positions[2] = glm::vec4(a*sin(j*0.0174533)*cos(i*0.0174533), b1*cos(j*0.0174533), c1*sin(j*0.0174533)*sin(i*0.0174533), 1.0);
    positions[1] = glm::vec4(a*sin(j*0.0174533)*cos((i+5)*0.0174533), b1*cos(j*0.0174533), c1*sin(j*0.0174533)*sin((i+5)*0.0174533), 1.0);
    positions[3] = glm::vec4(a*sin((j+5)*0.0174533)*cos(i*0.0174533), b1*cos((j+5)*0.0174533), c1*sin((j+5)*0.0174533)*sin(i*0.0174533), 1.0);
    positions[0] = glm::vec4(a*sin((j+5)*0.0174533)*cos((i+5)*0.0174533), b1*cos((j+5)*0.0174533), c1*sin((j+5)*0.0174533)*sin((i+5)*0.0174533), 1.0);
    //quad( 1, 0, 3, 2 ,v_positions,v_colors);
    v_colors[tri_idx] = colors[1]; v_positions[tri_idx] = positions[1]; tri_idx++;
    v_colors[tri_idx] = colors[0]; v_positions[tri_idx] = positions[0]; tri_idx++;
    v_colors[tri_idx] = colors[3]; v_positions[tri_idx] = positions[3]; tri_idx++;
    v_colors[tri_idx] = colors[1]; v_positions[tri_idx] = positions[1]; tri_idx++;
    v_colors[tri_idx] = colors[3]; v_positions[tri_idx] = positions[3]; tri_idx++;
    v_colors[tri_idx] = colors[2]; v_positions[tri_idx] = positions[2]; tri_idx++;
    i+=4;
    }
    j+=4;
  }

  for(int j=90;j<180;j++){
  for(int i=0;i<360;i++){
    positions[2] = glm::vec4(a*sin(j*0.0174533)*cos(i*0.0174533), b2*cos(j*0.0174533), c1*sin(j*0.0174533)*sin(i*0.0174533), 1.0);
    positions[1] = glm::vec4(a*sin(j*0.0174533)*cos((i+5)*0.0174533), b2*cos(j*0.0174533), c1*sin(j*0.0174533)*sin((i+5)*0.0174533), 1.0);
    positions[3] = glm::vec4(a*sin((j+5)*0.0174533)*cos(i*0.0174533), b2*cos((j+5)*0.0174533), c1*sin((j+5)*0.0174533)*sin(i*0.0174533), 1.0);
    positions[0] = glm::vec4(a*sin((j+5)*0.0174533)*cos((i+5)*0.0174533), b2*cos((j+5)*0.0174533), c1*sin((j+5)*0.0174533)*sin((i+5)*0.0174533), 1.0);
    //quad( 1, 0, 3, 2 ,v_positions,v_colors);
    v_colors[tri_idx] = colors[1]; v_positions[tri_idx] = positions[1]; tri_idx++;
    v_colors[tri_idx] = colors[0]; v_positions[tri_idx] = positions[0]; tri_idx++;
    v_colors[tri_idx] = colors[3]; v_positions[tri_idx] = positions[3]; tri_idx++;
    v_colors[tri_idx] = colors[1]; v_positions[tri_idx] = positions[1]; tri_idx++;
    v_colors[tri_idx] = colors[3]; v_positions[tri_idx] = positions[3]; tri_idx++;
    v_colors[tri_idx] = colors[2]; v_positions[tri_idx] = positions[2]; tri_idx++;
    i+=4;
    }
    j+=4;
  }

  tri_idx=0;
  csX75::HNode * node = new csX75::HNode(parent,num_vertices1,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  return node;
}

csX75::HNode * square(csX75::HNode * parent,float sq_side)
{
  tri_idx=0; 
  glm::vec4 v_positions[6];
  glm::vec4 v_colors[6];
  positions[0] = glm::vec4(sq_side,-sq_side,sq_side, 1.0);
  positions[1] = glm::vec4(sq_side,-sq_side,-sq_side, 1.0);
  positions[2] = glm::vec4(-sq_side,-sq_side,-sq_side, 1.0);
  positions[3] = glm::vec4(-sq_side,-sq_side,sq_side, 1.0);
  quad(0,1,2,3,v_positions,v_colors);

  tri_idx=0;
  csX75::HNode * node = new csX75::HNode(parent,6,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  return node;
}

csX75::HNode * thick_rect(csX75::HNode * parent,float sq_side1,float sq_side2,float thick)
{
  glm::vec4 thick_sq_vec[8]={
    glm::vec4(sq_side1,-sq_side,sq_side2, 1.0),
    glm::vec4(sq_side1,-sq_side,-sq_side2, 1.0),
    glm::vec4(-sq_side1,-sq_side,-sq_side2, 1.0),
    glm::vec4(-sq_side1,-sq_side,sq_side2, 1.0),
    glm::vec4(sq_side1,-sq_side + thick,sq_side2, 1.0),
    glm::vec4(sq_side1,-sq_side + thick,-sq_side2, 1.0),
    glm::vec4(-sq_side1,-sq_side + thick,-sq_side2, 1.0),
    glm::vec4(-sq_side1,-sq_side + thick,sq_side2, 1.0),
  };
  tri_idx=0; 
  glm::vec4 v_positions[6];
  glm::vec4 v_colors[6];
  positions[0] = thick_sq_vec[0];
  positions[1] = thick_sq_vec[1];
  positions[2] = thick_sq_vec[2];
  positions[3] = thick_sq_vec[3];
  quad(0,1,2,3,v_positions,v_colors);

  tri_idx=0;
  csX75::HNode * node1 = new csX75::HNode(parent,6,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  ////////another face
  tri_idx=0;
  positions[0] = thick_sq_vec[4];
  positions[1] = thick_sq_vec[5];
  positions[2] = thick_sq_vec[6];
  positions[3] = thick_sq_vec[7];
  quad(0,1,2,3,v_positions,v_colors);

  tri_idx=0;
  csX75::HNode * node2 = new csX75::HNode(node1,6,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));

  tri_idx=0;
  positions[0] = thick_sq_vec[0];
  positions[1] = thick_sq_vec[1];
  positions[2] = thick_sq_vec[5];
  positions[3] = thick_sq_vec[4];
  quad(0,1,2,3,v_positions,v_colors);

  tri_idx=0;
  csX75::HNode * node3 = new csX75::HNode(node1,6,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  tri_idx=0;
  positions[0] = thick_sq_vec[1];
  positions[1] = thick_sq_vec[2];
  positions[2] = thick_sq_vec[6];
  positions[3] = thick_sq_vec[5];
  quad(0,1,2,3,v_positions,v_colors);

  tri_idx=0;
  csX75::HNode * node4 = new csX75::HNode(node1,6,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  tri_idx=0;
  positions[0] = thick_sq_vec[2];
  positions[1] = thick_sq_vec[3];
  positions[2] = thick_sq_vec[7];
  positions[3] = thick_sq_vec[6];
  quad(0,1,2,3,v_positions,v_colors);

  tri_idx=0;
  csX75::HNode * node5 = new csX75::HNode(node1,6,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  tri_idx=0;
  positions[0] = thick_sq_vec[1];
  positions[1] = thick_sq_vec[5];
  positions[2] = thick_sq_vec[4];
  positions[3] = thick_sq_vec[7];
  quad(0,1,2,3,v_positions,v_colors);

  tri_idx=0;
  csX75::HNode * node6 = new csX75::HNode(node1,6,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
  return node1;
}

//-----------------------------------------------------------------

void initBuffersGL(void)
{

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("07_vshader.glsl");
  std::string fragment_shader_file("07_fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // getting the attributes from the shader program
  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");

  // Creating the hierarchy:
  // We are using the original colorcube function to generate the vertices of the cuboid
  //setColor(skin);

  //elliptic(1,1,2.0,1);


  //hip
//   setColor(lavendar);
//   hip = ellipsoid_minus(0.4,0.23,0.3,0.1,0.1,0.1,-0.5,NULL);
//   hip_coverdown = elliptic(0.1,0.1,0.1,0.04,hip);
//   hip_coverdown->change_parameters(0.0,-0.5,0.0,90,0,0);

//   //frock
//   setColor(lavendar_trans);
//   frock = ellipsoid_minus(0.4,0.23,0.3,1.5,1.5,1.5,-0.3,hip);
//   setColor(lavendar_trans1);
//   frock1 = ellipsoid_minus(0.4,0.23,0.3,1.5,1.5,1.5,-0.35,hip);
//   setColor(lavendar_trans2);
//   frock2 = ellipsoid_minus(0.4,0.23,0.3,1.5,1.5,1.5,-0.4,hip);
  

//   //abdomen
//   setColor(lavendar);
//   abdomen = ellipsoid_plus(0.5,0.25,0.35,0.4,0.23,0.3,1,hip);
//   abdomen_coverdown = elliptic(0.4,0.23,0.3,0.2,abdomen);
//   abdomen_coverdown->change_parameters(0.0,0.0,0.0,90,0,0);

//   //upper body
//   setColor(skin);
//   abdomen_coverup = elliptic(0.5,0.25,0.35,0.4,abdomen);
//   abdomen_coverup->change_parameters(0.0,1.0,0.0,90,0,0);

//   //neck
//   setColor(skin);
//   neck = elliptic(0.1,0.7,0.0,0.1,abdomen);
//   neck->change_parameters(0.0,1,-0.07,0,0,0);

//   //head
//   setColor(skin);
//   head = elliptic(0.3,0.2,0.5,0.25,neck);
//   head->change_parameters(0.0,1,0,0,0,0);

//   //head
//   setColor(brown);
//   hair = elliptic(0.35,0.25,0.5,0.3,head);
//   hair->change_parameters(0.0,0.1,-0.1,0,0,0);

//   //style
//   setColor(brown);
//   style = elliptic(0.2,0.2,0.2,0.2,hair);
//   style->change_parameters(0.0,0.0,-0.4,0,0,0);

//   //chest
//   setColor(lavendar_trans);
//   chest1 = elliptic(0.25,0.3,0.3,0.1,abdomen);
//   chest1->change_parameters(0.23,0.9,0.2,0,0,0);
//   chest2 = elliptic(0.25,0.3,0.3,0.1,abdomen);
//   chest2->change_parameters(-0.23,0.9,0.2,0,0,0);

//   //shoulder
//   setColor(skin);
//   shoulder1 = elliptic(0.2,0.2,0.2,0.2,abdomen);
//   shoulder1->change_parameters(0.4,1.1,-0.1,0,0,0);
//   shoulder2 = elliptic(0.2,0.2,0.2,0.2,abdomen);
//   shoulder2->change_parameters(-0.4,1.1,-0.1,0,0,0);

//   //arm
//   setColor(skin);
//   arm1 = elliptic(0.12,0.0,1.0,0.1,shoulder1);
//   arm1->change_parameters(0.1,0.0,0.0,0,0,45);
//   arm2 = elliptic(0.12,0.0,1.0,0.1,shoulder2);
//   arm2->change_parameters(-0.1,0.0,0.0,0,0,-45);

//   //forearm
//   setColor(skin);
//   forearm1 = elliptic(0.08,0.2,1.0,0.08,arm1);
//   forearm1->change_parameters(0.0,-1.0,0.0,0,0,0);
//   forearm2 = elliptic(0.08,0.2,1.0,0.08,arm2);
//   forearm2->change_parameters(-0.0,-1.0,0.0,0,0,0);

//   //palm
//   setColor(skin);
//   shoe1 = elliptic(0.07,0.0,0.4,0.1,forearm1);
//   shoe1->change_parameters(0.0,-0.8,0,0,0,0);
//   shoe2 = elliptic(0.07,0.0,0.4,0.1,forearm2);
//   shoe2->change_parameters(0.0,-0.8,0,0,0,0);

//   //thigh
//   setColor(skin);
//   thigh1 = elliptic(0.2,0.2,1.5,0.2,hip);
//   thigh1->change_parameters(0.22,-0.2,-0.07,0,0,0);
//   thigh2 = elliptic(0.2,0.2,1.5,0.2,hip);
//   thigh2->change_parameters(-0.22,-0.2,-0.07,0,0,0);

//   //leg
//   leg1 = elliptic(0.12,0.2,1.5,0.15,thigh1);
//   leg1->change_parameters(0.0,-1.34,0,0,0,0);
//   leg2 = elliptic(0.12,0.2,1.5,0.15,thigh2);
//   leg2->change_parameters(0.0,-1.34,0,0,0,0);

//   //shoe
//   setColor(lavendar_trans);
//   shoe1 = elliptic(0.08,0.0,0.4,0.1,leg1);
//   shoe1->change_parameters(0.0,-1.3,0,0,0,0);
//   shoe2 = elliptic(0.08,0.0,0.4,0.1,leg2);
//   shoe2->change_parameters(0.0,-1.3,0,0,0,0);


//   //c2_hip
//   setColor(black);
//   c2_hip = ellipsoid_minus(0.498,0.3,0.3,0.498,0.3,0.3,-0.5,NULL);
//   c2_hip->change_parameters(-4,0,0,0,0,0);
//   c2_hip_coverdown = elliptic(0.1,0.1,0.1,0.04,c2_hip);
//   c2_hip_coverdown->change_parameters(0.0,-0.5,0.0,90,0,0);

  

//   //c2_abdomen
//   setColor(black);
//   c2_abdomen = ellipsoid_plus(0.6,0.4,0.4,0.5,0.3,0.3,1,c2_hip);
//   c2_abdomen_coverdown = elliptic(0.4,0.23,0.3,0.2,c2_abdomen);
//   c2_abdomen_coverdown->change_parameters(0.0,0.0,0.0,90,0,0);

//   //setColor(red);
//   c2_abdomen_coverup = elliptic(0.6,0.35,0.4,0.3,c2_abdomen);
//   c2_abdomen_coverup->change_parameters(0.0,1.0,0.0,90,0,0);

//   //c2_shoulder
//   setColor(blue);
//   c2_shoulder1 = elliptic(0.25,0.25,0.25,0.25,c2_abdomen);
//   c2_shoulder1->change_parameters(0.4,1,0.0,0,0,0);
//   c2_shoulder2 = elliptic(0.25,0.25,0.25,0.25,c2_abdomen);
//   c2_shoulder2->change_parameters(-0.4,1.0,0.0,0,0,0);

//   //c2_arm
//   setColor(blue);
//   c2_arm1 = elliptic(0.2,0.0,1.0,0.2,c2_shoulder1);
//   c2_arm1->change_parameters(0.1,0.0,0.0,0,0,10);
//   c2_arm2 = elliptic(0.2,0.0,1.0,0.2,c2_shoulder2);
//   c2_arm2->change_parameters(-0.1,0.0,0.0,0,0,-10);

//   //c2_forearm
//   //setColor(dark_skin);
//   c2_forearm1 = elliptic(0.14,0.2,1.0,0.14,c2_arm1);
//   c2_forearm1->change_parameters(0.0,-.8,0.0,0,0,-10);
//   c2_forearm2 = elliptic(0.14,0.2,1.0,0.14,c2_arm2);
//   c2_forearm2->change_parameters(-0.0,-.8,0.0,0,0,10);

//   //c2_palm
//   setColor(dark_skin);
//   c2_shoe1 = elliptic(0.1,0.0,0.3,0.1,c2_forearm1);
//   c2_shoe1->change_parameters(0.0,-0.8,0,0,0,0);
//   c2_shoe2 = elliptic(0.1,0.0,0.3,0.1,c2_forearm2);
//   c2_shoe2->change_parameters(0.0,-0.8,0,0,0,0);

//   //c2_thigh
//   setColor(cement);
//   c2_thigh1 = elliptic(0.25,0.2,1.5,0.25,c2_hip);
//   c2_thigh1->change_parameters(0.22,-0.2,0.0,0,0,0);
//   //c2_thigh1->change_parameters(0.22,-2,-0.07,0,0,0);
//   c2_thigh2 = elliptic(0.25,0.2,1.5,0.25,c2_hip);
//   c2_thigh2->change_parameters(-0.22,-0.2,0.0,0,0,0);
//   //c2_thigh2->change_parameters(-0.22,-2,-0.07,0,0,0);

//   //c2_leg
//   c2_leg1 = elliptic(0.16,0.2,1.5,0.18,c2_thigh1);
//   c2_leg1->change_parameters(0.0,-1.3,0,0,0,0);
//   c2_leg2 = elliptic(0.16,0.2,1.5,0.18,c2_thigh2);
//   c2_leg2->change_parameters(0.0,-1.3,0,0,0,0);

//   //c2_shoe
//   setColor(black);
//   c2_shoe1 = elliptic(0.09,0.0,0.37,0.15,c2_leg1);
//   c2_shoe1->change_parameters(0.0,-1.4,-0.1,-90,0,0);
//   c2_shoe2 = elliptic(0.09,0.0,0.37,0.15,c2_leg2);
//   c2_shoe2->change_parameters(0.0,-1.4,-0.1,-90,0,0);

//   setColor(dark_skin);
//   c2_neck = ellipsoid_plus(0.1,0.1,0.1,0.1,0.1,0.1,0.5,c2_abdomen);
//   c2_neck->change_parameters(0.0,1,0,0,0,0);

//   c2_head = elliptic(0.3,.2,.5,.25,c2_neck);
//   c2_head->change_parameters(0,.87,0,0,-20,0);

//   setColor(black);
//   c2_hair = elliptic(0.3,.25,.45,.25,c2_head);
//   c2_hair->change_parameters(0,.01,-.01,0,0,0);

//   c2_hair1 = elliptic(0.3,.25,.45,.25,c2_head);
//   c2_hair1->change_parameters(-0.03,.01,-0.01,0,0,0);
//   c2_hair2 = elliptic(0.3,.25,.45,.25,c2_head);
//   c2_hair2->change_parameters(0.03,.1,-0.01,0,0,0);

// ///hat
//   setColor(brown);
//   hat_low = elliptic(0.7,.05,.05,.7,c2_head);
//   hat_low->change_parameters(0,.15,0,0,0,0);

//   hat_mid = ellipsoid_plus(.3,0.3,.3,0.35,.35,.35,.4,hat_low );
//   //hat_mid->change_parameters(-0.03,1.86,-0.06,0,0,0);

//   hat_top = elliptic(0.3,.3,.3,.0,hat_mid);
//   hat_top->change_parameters(0.0,0.4,0,90,0,0);
///////////   BOX  | ////////
///////////   BOX  | ////////
///////////   BOX  V ////////
  setColor(blue);
  rr = thick_rect(NULL,sq_side*zoom,sq_side*zoom,.4*zoom);
  rr->change_parameters(0,0,0,0,-0,0);

  setColor(red);
  rr2 = square(rr,sq_side*zoom);
  rr2->change_parameters(0,0,0,0,0,90);

  setColor(green);
  rr3 = square(rr,sq_side*zoom);
  rr3->change_parameters(0,0,0,0,0,-90);

  setColor(lavendar);
  rr4 = square(rr,sq_side*zoom);
  rr4->change_parameters(0,0,0,90,0,0);

  setColor(black);
  rr5 = square(rr,sq_side*zoom);
  rr5->change_parameters(0,0,0,-90,0,0);

  setColor(skin);
  rr6 = square(rr,sq_side*zoom);
  rr6->change_parameters(0,2*sq_side*zoom,0,0,0,0);

  setColor(brown);
  table = thick_rect(NULL,3.5*zoom,1*zoom,0.2*zoom);
  table->change_parameters(0,3*zoom,-1*zoom,0,0,0);

  setColor(brown);
  leg1 = thick_rect(table,.1*zoom,.1*zoom,2.6*zoom);
  leg1->change_parameters(3.3*zoom,-2.5*zoom,.85*zoom,0,0,0);

  setColor(brown);
  leg2 = thick_rect(table,.1*zoom,.1*zoom,2.6*zoom);
  leg2->change_parameters(3.3*zoom,-2.5*zoom,-.85*zoom,0,0,0);

  setColor(brown);
  leg3 = thick_rect(table,.1*zoom,.1*zoom,2.6*zoom);
  leg3->change_parameters(-3.3*zoom,-2.5*zoom,.85*zoom,0,0,0);

  setColor(brown);
  leg4 = thick_rect(table,.1*zoom,.1*zoom,2.6*zoom);
  leg4->change_parameters(-3.3*zoom,-2.5*zoom,-.85*zoom,0,0,0);
//////////chair
  setColor(cement);
  ch_seat = thick_rect(table,.6*zoom,.6*zoom,0.3*zoom);
  ch_seat->change_parameters(0,-.7*zoom,-01*zoom,0,0,0);

  setColor(cement);
  ch_back = thick_rect(ch_seat,.6*zoom,1*zoom,0.3*zoom);
  ch_back->change_parameters(0,-0.9*zoom,1.8*zoom,75,0,0);

  setColor(cement);
  ch_leg1 = thick_rect(ch_seat,.1*zoom,.1*zoom,1.7*zoom);
  ch_leg1->change_parameters(.5*zoom,-1.7*zoom,.5*zoom,0,0,0);

  setColor(cement);
  ch_leg2 = thick_rect(ch_seat,.1*zoom,.1*zoom,1.7*zoom);
  ch_leg2->change_parameters(.5*zoom,-1.7*zoom,-.5*zoom,0,0,0);

  setColor(cement);
  ch_leg3 = thick_rect(ch_seat,.1*zoom,.1*zoom,1.7*zoom);
  ch_leg3->change_parameters(-.5*zoom,-1.7*zoom,.5*zoom,0,0,0);

  setColor(cement);
  ch_leg4 = thick_rect(ch_seat,.1*zoom,.1*zoom,1.7*zoom);
  ch_leg4->change_parameters(-.5*zoom,-1.7*zoom,-.5*zoom,0,0,0);


  root_node = curr_node = table;//by default rotate node 

}

void renderGL(void)
{
  glClearColor(1,1,1,1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixStack.clear();

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
  glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));

  //creating the projection matrix
  if(enable_perspective)
    //projection_matrix = glm::frustum(-7.0, 7.0, -7.0, 7.0, 1.0, 40.0);
    projection_matrix = glm::frustum(-2.0, 2.0, -2.0, 2.0, 1.0, 40.0);
    //projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,5.0);
  else
    projection_matrix = glm::ortho(-7.0, 7.0, -7.0, 7.0, -5.0, 40.0);

  view_matrix = projection_matrix*lookat_matrix;

  matrixStack.push_back(view_matrix);

  // hip->render_tree();
  // c2_hip->render_tree();
  rr->render_tree();
  table->render_tree();

}

int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(1000, 1000, "Window box", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
       
      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}

//-------------------------------------------------------------------------

