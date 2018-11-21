#include "07_hierarchical_modelling.hpp"
#include <iostream>
#include <fstream>

using namespace std;

GLuint shaderProgram;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

//glm::mat4 model_matrix;
glm::mat4 view_matrix;


//glm::mat4 modelview_matrix;

//GLuint uModelViewMatrix;

//GLuint tex;

glm::mat4 modelview_matrix;
glm::mat3 normal_matrix;


const int num_vertices = 36;
float sq_side = 8;
float zoom =2/2;

//-----------------------------------------------------------------

//Eight vertices in homogenous coordinates
//elongated cuboid , basic arm in the hierarchy;
glm::vec4 positions[8] = {
  glm::vec4(-0.5, -0.5, 0.5, 1.0),
  glm::vec4(-0.5, 0.5, 0.5, 1.0),
  glm::vec4(0.5, 0.5, 0.5, 1.0),
  glm::vec4(0.5, -0.5, 0.5, 1.0),
  glm::vec4(-0.5, -0.5, -0.5, 1.0),
  glm::vec4(-0.5, 0.5, -0.5, 1.0),
  glm::vec4(0.5, 0.5, -0.5, 1.0),
  glm::vec4(0.5, -0.5, -0.5, 1.0)
};

glm::vec4 normals[8] = {
  glm::vec4(-0.5, -0.5, 0.5, 1.0),
  glm::vec4(-0.5, 0.5, 0.5, 1.0),
  glm::vec4(0.5, 0.5, 0.5, 1.0),
  glm::vec4(0.5, -0.5, 0.5, 1.0),
  glm::vec4(-0.5, -0.5, -0.5, 1.0),
   glm::vec4(-0.5, 0.5, -0.5, 1.0),
  glm::vec4(0.5, 0.5, -0.5, 1.0),
  glm::vec4(0.5, -0.5, -0.5, 1.0)
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
glm::vec4 lemon(.749, 1, 0, 1.0);
glm::vec4 bed(.635, .4156, .2588, 1.0);

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

void setColor(glm::vec4 c)
{
  for(int i=0;i<8;i++) colors[i] = c;
}

glm::vec2 t_coords[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 1.0),
  glm::vec2( 1.0, 0.0),
  glm::vec2( 1.0, 1.0)
};

int tri_idx=0;
glm::vec4 v_positions[num_vertices];
glm::vec4 v_colors[num_vertices];
glm::vec4 v_normals[num_vertices];
glm::vec2 tex_coords[num_vertices];
// quad generates two triangles for each face and assigns colors to the vertices
void quad(int a, int b, int c, int d, glm::vec4 color)
{
  v_colors[tri_idx] = color; v_positions[tri_idx] = positions[a]; 
  v_normals[tri_idx] = normals[a]; 
  tex_coords[tri_idx] = t_coords[1];
  tri_idx++;
  v_colors[tri_idx] = color; v_positions[tri_idx] = positions[b];
  v_normals[tri_idx] = normals[b]; 
  tex_coords[tri_idx] = t_coords[0];
  tri_idx++;
  v_colors[tri_idx] = color; v_positions[tri_idx] = positions[c]; 
  v_normals[tri_idx] = normals[c]; 
  tex_coords[tri_idx] = t_coords[2];
  tri_idx++;
  v_colors[tri_idx] = color; v_positions[tri_idx] = positions[a]; 
  v_normals[tri_idx] = normals[a]; 
  tex_coords[tri_idx] = t_coords[1];
  tri_idx++;
  v_colors[tri_idx] = color; v_positions[tri_idx] = positions[c]; 
  v_normals[tri_idx] = normals[c]; 
  tex_coords[tri_idx] = t_coords[2];
  tri_idx++;
  v_colors[tri_idx] = color; v_positions[tri_idx] = positions[d]; 
  v_normals[tri_idx] = normals[d]; 
  tex_coords[tri_idx] = t_coords[3];
  tri_idx++;
 }

// generate 12 triangles: 36 vertices and 36 colors
void colorcube(void)
{
  quad( 1, 0, 3, 2, red);
  quad( 2, 3, 7, 6, green);
  quad( 3, 0, 4, 7, white);
  quad( 6, 5, 1, 2, yellow);
  quad( 4, 5, 6, 7, black);
  quad( 5, 4, 0, 1, blue);
  tri_idx = 0;
}

csX75::HNode * thick_rect(csX75::HNode * parent,size_t img_choice,float sq_side1,float sq_side2,float thick)
{
  positions[0] = glm::vec4(-sq_side1,-sq_side,sq_side2, 1.0);//1
  positions[1] = glm::vec4(-sq_side1,-sq_side + thick,sq_side2, 1.0);//2
  positions[2] = glm::vec4(sq_side1,-sq_side + thick,sq_side2, 1.0);//3
  positions[3] = glm::vec4(sq_side1,-sq_side,sq_side2, 1.0);//4
  positions[4] = glm::vec4(-sq_side1,-sq_side,-sq_side2, 1.0);//5
  positions[5] = glm::vec4(-sq_side1,-sq_side + thick,-sq_side2, 1.0);//6
  positions[6] = glm::vec4(sq_side1,-sq_side + thick,-sq_side2, 1.0);//7
  positions[7] = glm::vec4(sq_side1,-sq_side,-sq_side2, 1.0);//8

  colorcube();
  csX75::HNode * nodenode = new csX75::HNode(parent,img_choice,num_vertices,v_positions,v_normals,tex_coords,sizeof(v_positions),sizeof(v_normals),sizeof(tex_coords));
  return nodenode;
}

csX75::HNode * new_cuboid(csX75::HNode * parent,size_t img_choice,float sq_side1,float sq_side2,float thick, float xx,float yy,float zz){
  positions[0] = glm::vec4(+xx,           yy,          sq_side2+zz, 1.0);//1
  positions[1] = glm::vec4(+xx,           yy + thick,  sq_side2+zz, 1.0);//2
  positions[2] = glm::vec4(2*sq_side1+xx, yy + thick,  sq_side2+zz, 1.0);//3
  positions[3] = glm::vec4(2*sq_side1+xx, yy,          sq_side2+zz, 1.0);//4
  positions[4] = glm::vec4(xx,            yy,          -sq_side2+zz, 1.0);//5
  positions[5] = glm::vec4(xx,            yy + thick,  -sq_side2+zz, 1.0);//6
  positions[6] = glm::vec4(2*sq_side1+xx, yy + thick,  -sq_side2+zz, 1.0);//7
  positions[7] = glm::vec4(2*sq_side1+xx, yy,          -sq_side2+zz, 1.0);//8

  colorcube();
  csX75::HNode * nodenode = new csX75::HNode(parent,img_choice,num_vertices,v_positions,v_normals,tex_coords,sizeof(v_positions),sizeof(v_normals),sizeof(tex_coords));
  //nodenode->change_parameters(xx,yy,zz,0,0,0);
  return nodenode;
}

csX75::HNode * forrobo(csX75::HNode * parent,size_t img_choice,float x_value,float y_value,float z_val, float xx,float yy,float zz){
  positions[0] = glm::vec4(xx - x_value/2, yy,            zz + z_val/2, 1.0);//1
  positions[1] = glm::vec4(xx - x_value/2, yy + y_value,  zz + z_val/2, 1.0);//2
  positions[2] = glm::vec4(xx + x_value/2, yy + y_value,  zz + z_val/2, 1.0);//3
  positions[3] = glm::vec4(xx + x_value/2, yy,            zz + z_val/2, 1.0);//4
  positions[4] = glm::vec4(xx - x_value/2, yy,            zz - z_val/2, 1.0);//5
  positions[5] = glm::vec4(xx - x_value/2, yy + y_value,  zz - z_val/2, 1.0);//6
  positions[6] = glm::vec4(xx + x_value/2, yy + y_value,  zz - z_val/2, 1.0);//7
  positions[7] = glm::vec4(xx + x_value/2, yy,            zz - z_val/2, 1.0);//8

  colorcube();
  csX75::HNode * nodenode = new csX75::HNode(parent,img_choice,num_vertices,v_positions,v_normals,tex_coords,sizeof(v_positions),sizeof(v_normals),sizeof(tex_coords));
  //nodenode->change_parameters(xx,yy,zz,0,0,0);
  return nodenode;
}

int ncp = 0;
glm::vec3 curve[100];

void addnode(double x, double y, double z){
    curve[ncp][0] = x;
    curve[ncp][1] = y;
    curve[ncp][2] = z;

    ncp++;
    cout << x << " " << " " << y<< " " << z <<" " << ncp << endl;
    node3 = new csX75::HNode(rr,0,num_vertices,v_positions,v_normals,tex_coords,sizeof(v_positions),sizeof(v_normals),sizeof(tex_coords));
    node3->change_parameters(x,y,z,0,0,0);
}

//-----------------------------------------------------------------

void initBuffersGL(void)
{

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("06_vshader.glsl");
  std::string fragment_shader_file("06_fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // getting the attributes from the shader program
  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
  vNormal = glGetAttribLocation( shaderProgram, "vNormal" ); 
  texCoord = glGetAttribLocation( shaderProgram, "texCoord" ); 
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
  normalMatrix =  glGetUniformLocation( shaderProgram, "normalMatrix");
  viewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix");

  rr = thick_rect(NULL,5,sq_side*zoom,sq_side*zoom,.001*zoom);
  rr->change_parameters(0,0,0,0,0,0);

  rr2 = thick_rect(rr,10,sq_side*zoom,sq_side*zoom*2/3,.001*zoom);
  rr2->change_parameters(0,0,-3,0,0,90);

  rr2_1 = thick_rect(rr2,10,sq_side*zoom,sq_side*zoom/4.8,.001*zoom);
  rr2_1->change_parameters(0,0,9.3,0,0,-0);

  rr2_2 = thick_rect(rr2_1,10,sq_side*zoom/1.3,sq_side*zoom/4.8,.001*zoom);
  rr2_2->change_parameters(-6.4,0,-6,0,90,-0);

  rr2_3 = thick_rect(rr2_1,10,sq_side*zoom/1.3,sq_side*zoom/4.8,.001*zoom);
  rr2_3->change_parameters(-0,0,-6,0,90,-0);

  rr2_4 = thick_rect(rr2_1,10,sq_side*zoom/1.3,sq_side*zoom/4.8,.001*zoom);
  rr2_4->change_parameters(-3,0,-6,0,90,-0);

  rr2_6 = thick_rect(rr2_1,10,sq_side*zoom/1.3,sq_side*zoom/4.8,.001*zoom);
  rr2_6->change_parameters(06.4,0,-6,0,90,-0);

  rr3 = thick_rect(rr,10,sq_side*zoom,sq_side*zoom*2/3,.001*zoom);
  rr3->change_parameters(0,0,-2.8,0,0,-90);

  rr3_1 = thick_rect(rr3,10,sq_side*zoom,sq_side*zoom/4.8,.001*zoom);
  rr3_1->change_parameters(0,0,9.3,0,0,-0);

  rr3_2 = thick_rect(rr3_1,10,sq_side*zoom/1.3,sq_side*zoom/4.8,.001*zoom);
  rr3_2->change_parameters(-6.4,0,-6,0,90,-0);

  door = thick_rect(rr3_1,4,6.5*zoom,1.2*zoom,.2*zoom);
  door->change_parameters(1.4,-2.7,2,40,0,-0);

  setColor(lavendar);
  rr4 = thick_rect(rr,10,sq_side*zoom,sq_side*zoom,.001*zoom);
  rr4->change_parameters(0,0,0,90,0,0);

  setColor(black);
  rr5 = thick_rect(rr,10,sq_side*zoom,sq_side*zoom,.001*zoom);
  rr5->change_parameters(0,0,0,-90,0,0);

  setColor(skin);
  rr6 = thick_rect(rr,10,sq_side*zoom,sq_side*zoom,.001*zoom);
  rr6->change_parameters(0,2*sq_side*zoom,0,0,0,0);

  setColor(brown);
  table = thick_rect(rr,2,3.5*zoom,1*zoom,0.2*zoom);
  table->change_parameters(0,2.7*zoom,-1*zoom,0,0,0);

  setColor(brown);
  leg1 = thick_rect(table,2,.1*zoom,.1*zoom,2.6*zoom);
  leg1->change_parameters(3.3*zoom,-2.5*zoom,.85*zoom,0,0,0);

  setColor(brown);
  leg2 = thick_rect(table,2,.1*zoom,.1*zoom,2.6*zoom);
  leg2->change_parameters(3.3*zoom,-2.5*zoom,-.85*zoom,0,0,0);

  setColor(brown);
  leg3 = thick_rect(table,2,.1*zoom,.1*zoom,2.6*zoom);
  leg3->change_parameters(-3.3*zoom,-2.5*zoom,.85*zoom,0,0,0);

  setColor(brown);
  leg4 = thick_rect(table,2,.1*zoom,.1*zoom,2.6*zoom);
  leg4->change_parameters(-3.3*zoom,-2.5*zoom,-.85*zoom,0,0,0);
////////chair
  setColor(cement);
  ch_seat = thick_rect(table,6,.6*zoom,.6*zoom,0.3*zoom);
  ch_seat->change_parameters(0,-.7*zoom,-01*zoom,0,0,0);

  setColor(cement);
  ch_back = thick_rect(ch_seat,6,.6*zoom,2*zoom,0.3*zoom);
  ch_back->change_parameters(0,-4.3*zoom,6.47*zoom,70,0,0);

  setColor(cement);
  ch_leg1 = thick_rect(ch_seat,7,.1*zoom,.1*zoom,1.7*zoom);
  ch_leg1->change_parameters(.5*zoom,-1.7*zoom,.5*zoom,0,0,0);

  setColor(cement);
  ch_leg2 = thick_rect(ch_seat,7,.1*zoom,.1*zoom,1.7*zoom);
  ch_leg2->change_parameters(.5*zoom,-1.7*zoom,-.5*zoom,0,0,0);

  setColor(cement);
  ch_leg3 = thick_rect(ch_seat,7,.1*zoom,.1*zoom,1.7*zoom);
  ch_leg3->change_parameters(-.5*zoom,-1.7*zoom,.5*zoom,0,0,0);

  setColor(cement);
  ch_leg4 = thick_rect(ch_seat,7,.1*zoom,.1*zoom,1.7*zoom);
  ch_leg4->change_parameters(-.5*zoom,-1.7*zoom,-.5*zoom,0,0,0);
// ////////bed
  setColor(bed);
  bed_bottom = thick_rect(rr,4,4.6*zoom,1.5*zoom,1.3*zoom);
  bed_bottom->change_parameters(0,.4*zoom,2.75*zoom,0,0,0);

  setColor(bed);
  bed_head = thick_rect(bed_bottom,4,.4*zoom,1.5*zoom,4*zoom);
  bed_head->change_parameters(5.0*zoom,0,-0,0,0,0);

  setColor(lemon);
  bed_sheet = thick_rect(bed_bottom,0,4.55*zoom,1.4*zoom,1.3*zoom);
  bed_sheet->change_parameters(0,1.32,-0,0,0,0);

  setColor(skin);
  lamp_bottom = thick_rect(rr,7,.6,.6,.5);
  lamp_bottom->change_parameters(5,0.401,-5,0,0,0);

  lamp_stick = thick_rect(lamp_bottom,7,.06,.06,5);
  lamp_stick->change_parameters(0,0,-0,0,0,0);
//case
  setColor(skin);
  case_middle = thick_rect(rr,4,4,1,.1);
  case_middle->change_parameters(-3,6,-6,0,0,0);

  case_top = thick_rect(case_middle,4,4,1,.1);
  case_top->change_parameters(0,3,-0,0,0,0);

  book1 = thick_rect(case_middle,9,.7,.7,.9);
  book1->change_parameters(-02,0,-0,0,0,0);

  book2 = thick_rect(case_middle,9,.7,.7,.9);
  book2->change_parameters(-01.6,0.9,-0,0,0,0);

  case_back = thick_rect(case_middle,4,4,.1,6);
  case_back->change_parameters(0,-3,-1,0,0,0);

  case_left = thick_rect(case_middle,4,.1,1,9);
  case_left->change_parameters(04,-6,-0,0,0,0);

  case_right = thick_rect(case_middle,4,.1,1,9);
  case_right->change_parameters(-04,-6,-0,0,0,0);

  case_between = thick_rect(case_middle,4,.1,1,9);
  case_between->change_parameters(-00,-06,-0,0,0,0);
//stool
  setColor(brown);
  stool = thick_rect(rr,2,.8*zoom,1*zoom,0.2*zoom);
  stool->change_parameters(4*zoom,2.5*zoom,6.5*zoom,0,0,0);

  setColor(brown);
  leg11 = thick_rect(stool,2,.1*zoom,.1*zoom,2.6*zoom);
  leg11->change_parameters(.73*zoom,-2.5*zoom,.85*zoom,0,0,0);

  setColor(brown);
  leg22 = thick_rect(stool,2,.1*zoom,.1*zoom,2.6*zoom);
  leg22->change_parameters(.73*zoom,-2.5*zoom,-.85*zoom,0,0,0);

  setColor(brown);
  leg33 = thick_rect(stool,2,.1*zoom,.1*zoom,2.6*zoom);
  leg33->change_parameters(-.73*zoom,-2.5*zoom,.85*zoom,0,0,0);

  setColor(brown);
  leg44 = thick_rect(stool,2,.1*zoom,.1*zoom,2.6*zoom);
  leg44->change_parameters(-.73*zoom,-2.5*zoom,-.85*zoom,0,0,0);
//inner box
  box_bottom = thick_rect(table,7,.8,.8,0.1);
  box_bottom->change_parameters(0,.201,0,0,0,0);

  box_left = thick_rect(table,7,.8,.8,0.1);
  box_left->change_parameters(7.2,-7,0,0,0,-90);

  box_right = thick_rect(table,7,.8,.8,0.1);
  box_right->change_parameters(-7.2,-7,0,0,0,90);

  box_front = thick_rect(table,7,.8,.8,0.1);
  box_front->change_parameters(0,-7,-7.2,-90,0,0);

  box_back = thick_rect(table,7,.8,.8,0.1);
  box_back->change_parameters(0,-7,7.2,90,0,0);



////////////////////////////////////////////////////////////////////////
      float mult = 3.6; 
  // box_top = thick_rect(box_back,10,.8,.8,0.1);
  // box_top->change_parameters(0,-7.4,7.15,90,0,0);
  box_top = new_cuboid(box_left,4,.8,.8,0.1,0,0,0);
  box_top->change_parameters(-.8,-7.2,-1,90,0,90);

  base = forrobo(box_bottom,11,1.3/mult,.8/mult,1.3/mult,0,0,0);
  base->change_parameters(0,-7,0,0,0,0);

  chest = forrobo(base,11,1.3/mult,1.5/mult,1.3/mult,0,0,0);
  chest->change_parameters(0,.7/mult,0,0,0,0);

  lshoulder = forrobo(chest,11,.7/mult,.7/mult,.7/mult,0,0,0);
  lshoulder->change_parameters(-.6/mult,.9/mult,0,0,0,90);

  rshoulder = forrobo(chest,11,.7/mult,.7/mult,.7/mult,0,0,0);
  rshoulder->change_parameters(.6/mult,.9/mult,0,0,0,-90);

  lhand = forrobo(lshoulder,11,.3/mult,1.5/mult,.3/mult,0,0,0);
  lhand->change_parameters(-.4/mult,.4/mult,0,0,0,90);

  rhand = forrobo(rshoulder,11,.3/mult,1.5/mult,.3/mult,0,0,0);
  rhand->change_parameters(.4/mult,.4/mult,0,0,0,-90);

  lforehand = forrobo(lhand,11,.3/mult,1.5/mult,.3/mult,0,0,0);
  lforehand->change_parameters(-0,1.4/mult,0,0,00,0);

  rforehand = forrobo(rhand,11,.3/mult,1.5/mult,.3/mult,0,0,0);
  rforehand->change_parameters(0,1.4/mult,0,0,0,0);

  lthigh = forrobo(base,11,.4/mult,1.5/mult,.4/mult,0,0,0);
  lthigh->change_parameters(-.325/mult,0,0,180,0,0);

  rthigh = forrobo(base,11,.4/mult,1.5/mult,.4/mult,0,0,0);
  rthigh->change_parameters(.325/mult,0,0,180,0,0);

  lcalf = forrobo(lthigh,11,.4/mult,1.3/mult,.4/mult,0,0,0);
  lcalf->change_parameters(0,1.3/mult,0,0,0,0);

  rcalf = forrobo(rthigh,11,.4/mult,1.3/mult,.4/mult,0,0,0);
  rcalf->change_parameters(0,1.3/mult,0,0,0,0);

  neck = forrobo(chest,11,.3/mult,.8/mult,.3/mult,0,0,0);
  neck->change_parameters(0,1.2/mult,0,0,0,0);

  head = forrobo(neck,11,.7/mult,.7/mult,.7/mult,0,0,0);
  head->change_parameters(0,.65/mult,0,0,0,0);

  root_node = curr_node = rr;

  //for(int i=0;i<6;i++) rr->inc_ry();


}

glm::vec3 getBezierPoint( glm::vec3* points, int numPoints, float t ) {
    glm::vec3* tmp = new glm::vec3[numPoints];
    memcpy(tmp, points, numPoints * sizeof(glm::vec3));
    int i = numPoints - 1;
    while (i > 0) {
        for (int k = 0; k < i; k++)
            tmp[k] = tmp[k] + t * ( tmp[k+1] - tmp[k] );
        i--;
    }
    glm::vec3 answer = tmp[0];
    delete[] tmp;
    return answer;
}

// glm::vec3 curve[7] = {
//   glm::vec3(0.0, 0.0, 12),
//   glm::vec3(4, 0, 8),
//   glm::vec3(8, 0.0, 8),
//   glm::vec3(12, 0.0, 12),
//   glm::vec3(8, 0, 8),
//   glm::vec3(8, 0.0, 4),
//   glm::vec3(12, 0.0, 0.0)
// };

int startc = 0;

void startcam(void){
  startc = 1;
  //css = 1;
}

int st = 0, st2 = 0, css=0;

int animate = 0;

long long int y = 0;

double angle;

int angles[100][3];

int p, q, r, i=0,iter = 0;

glm::vec3 camera;

void renderGL(void)
{
  if(startc == 0){
    st = glfwGetTime();
  }
  if(animate == 0){
    st2 = glfwGetTime();
  }
  if(animate == 1){

    c_xpos = camera[0];
  c_ypos = camera[1];
  c_zpos = camera[2];

    angle = glfwGetTime() - st2;
    angle = angle / 10;

    std::cout << angle << std::endl;
    
    double diff1_x = (1-angle)*angles[iter][0] + angle*angles[iter+3][0];
    double diff1_y = (1-angle)*angles[iter][1] + angle*angles[iter+3][1];
    double diff1_z = (1-angle)*angles[iter][2] + angle*angles[iter+3][2];
    
    double diff3_x = (1-angle)*angles[iter+1][0] + angle*angles[iter+4][0];
    double diff3_y = (1-angle)*angles[iter+1][1] + angle*angles[iter+4][1];
    double diff3_z = (1-angle)*angles[iter+1][2] + angle*angles[iter+4][2];

    double diff2_x = (1-angle)*angles[iter+2][0] + angle*angles[iter+5][0];
    double diff2_y = (1-angle)*angles[iter+2][1] + angle*angles[iter+5][1];
    double diff2_z = (1-angle)*angles[iter+2][2] + angle*angles[iter+5][2];
    


    base->rx = diff2_x;
    base->ry = diff2_y;
    base->rz = diff2_z;
    base->update_matrices();

    lhand->rx = diff1_x;
    lhand->ry = diff1_y;
    lhand->rz = diff1_z;
    lhand->update_matrices();

    rhand->rx = diff3_x;
    rhand->ry = diff3_y;
    rhand->rz = diff3_z;
    rhand->update_matrices();

    iter+=3;

    //base->inc_ry();
    


    std::cout<<"interpolate " << base->ry << std::endl;
    
    if(angle > 0.99) { animate = 0;
      // if( (i-iter) == 3 )
      // animate = 0;
      // else{
      //   st2 = glfwGetTime();
      // }
    }
  }
  if(startc == 1){
  //cout << glfwGetTime() << '\n';
  
  angle = glfwGetTime()-st;

  angle = angle / 10;

  camera = getBezierPoint(curve,ncp,angle);

  y++;

  c_xpos = camera[0];
  c_ypos = camera[1];
  c_zpos = camera[2];


  if(y < 18) box_bottom->inc_y();
  if(y < 28) box_top->inc_rz();
  if(y==29) curr_node=base;


  if(angle > 0.99) {
    startc = 0;
    animate = 1;
  }
  }  // int h = ((int)(glfwGetTime()*10000))%10000;
  // // cout << glfwGetTime() << '\n';
  // cout << h << endl;
  // if( h > y){
  //   // y++;
  //   c_zpos-=0.1;
  //   //cout<<y<<endl;
  // }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixStack.clear();

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
  glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  //Creating the lookat matrix
  if(startc == 1 || angle > 0.99 || animate == 1){
    lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0,-3,-1),glm::vec3(c_up));
  }
  else{
    lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0,0,-100),glm::vec3(c_up));
  }

  //creating the projection matrix
  if(enable_perspective)
    //projection_matrix = glm::frustum(-7.0, 7.0, -7.0, 7.0, 1.0, 40.0);
    projection_matrix = glm::perspective(glm::radians(114.0),1.0,1.0,40.0);
  else
    projection_matrix = glm::ortho(-7.0, 7.0, -7.0, 7.0, -5.0, 40.0);

  view_matrix = projection_matrix*lookat_matrix;

  matrixStack.push_back(view_matrix);

  rr->render_tree();
  //base->render_tree();
  //box_top->render_tree();

}

int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  ifstream read("keyframes.txt");
  while(read >>p>>q>>r){
    angles[i][0] = p;
    angles[i][1] = q;
    angles[i][2] = r;
    i++;
    std::cout<<p<<" "<<q<<" "<<r<<" "<<std::endl;
  }

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
  window = glfwCreateWindow(1000, 1000, "CS475/CS675 Tutorial 7: Hierarchical Modelling", NULL, NULL);
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

  glfwSetMouseButtonCallback(window, csX75::mouse_button_callback);
  glfwSetCursorPosCallback(window, NULL);

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

