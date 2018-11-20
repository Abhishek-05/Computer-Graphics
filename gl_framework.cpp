#include "gl_framework.hpp"
#include "hierarchy_node.hpp"

extern GLfloat c_xrot,c_yrot,c_zrot;
extern GLfloat c_xpos,c_ypos,c_zpos;
extern bool enable_perspective;
extern csX75::HNode* node1, *node2, *node3,*curr_node, *hip, *abdomen, *thigh1, *leg1,*thigh2, *leg2, *arm1,*arm2, *head,
                      * forearm1, * forearm2, * c2_forearm1, * c2_forearm2,
                      *c2_hip, *c2_abdomen, *c2_thigh1, *c2_leg1,*c2_thigh2, *c2_leg2, *c2_arm1,*c2_arm2, *tie, *c2_head, *c2_neck, *rr, *rr6;
                      
bool c1=true, c2=false, b=false,deg_x=false,deg_y=false,deg_z=false;

int constrains[12][6];

int present_bit = 0;

namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);

    constrains[0][0] = -9000;
    constrains[0][1] = 9180;
    constrains[0][2] = -9000;
    constrains[0][3] = 9180;
    constrains[0][4] = -9000;
    constrains[0][5] = 9180;

    constrains[1][0] = -30;//bend back
    constrains[1][1] = 30;//bend front
    constrains[1][2] = -40;//rotate right
    constrains[1][3] = 40;//rotate left
    constrains[1][4] = -60;//yoga 
    constrains[1][5] = 60;//yoga

    constrains[2][0] = -50;
    constrains[2][1] = 50;
    constrains[2][2] = -30;
    constrains[2][3] = 30;
    constrains[2][4] = 0;
    constrains[2][5] = 190;

    constrains[3][0] = -180;
    constrains[3][1] = 0;
    constrains[3][2] = 0;
    constrains[3][3] = 0;
    constrains[3][4] = 0;
    constrains[3][5] = 0;

    constrains[4][0] = -180;////arm
    constrains[4][1] = 0;
    constrains[4][2] = 0;
    constrains[4][3] = 0;
    constrains[4][4] = -100;
    constrains[4][5] = 0;

    constrains[5][0] = -180;///forearm
    constrains[5][1] = 0;
    constrains[5][2] = 0;
    constrains[5][3] = 0;
    constrains[5][4] = 0;
    constrains[5][5] = 0;

    constrains[6][0] = -70;///leg
    constrains[6][1] = 70;
    constrains[6][2] = 0;
    constrains[6][3] = 0;
    constrains[6][4] = 0;
    constrains[6][5] = 70;

    constrains[7][0] = 0;///calf
    constrains[7][1] = 110;
    constrains[7][2] = 0;
    constrains[7][3] = 0;
    constrains[7][4] = 0;
    constrains[7][5] = 0;

    constrains[8][0] = -70;///leg
    constrains[8][1] = 70;
    constrains[8][2] = 0;
    constrains[8][3] = 0;
    constrains[8][4] = 0;
    constrains[8][5] = 70;

    constrains[9][0] = 0;///calf
    constrains[9][1] = 110;
    constrains[9][2] = 0;
    constrains[9][3] = 0;
    constrains[9][4] = 0;
    constrains[9][5] = 0;

    constrains[10][0] = -50;///calf
    constrains[10][1] = 30;
    constrains[10][2] = -60;
    constrains[10][3] = 60;
    constrains[10][4] = 0;
    constrains[10][5] = 0;

    constrains[11][0] = 0;
    constrains[11][1] = 0;
    constrains[11][2] = 0;
    constrains[11][3] = 0;
    constrains[11][4] = -100;
    constrains[11][5] = 0;
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_C  && action == GLFW_PRESS)
      {c1=false; c2=false; b=true;curr_node = rr;present_bit=0;}
    else if (key == GLFW_KEY_1 && action == GLFW_PRESS)
      {
        if(c1){
          curr_node = hip;
        }
        else if(c2){
          curr_node = c2_hip;
        }
        else if(b){
          curr_node = rr;
        }
        present_bit = 0;
      }
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
      {
        if(c1){
          curr_node = abdomen;
        }
        else if(c2){
          curr_node = c2_abdomen;
        }
        else if(b){
          //curr_node = rr6;
        }
        present_bit = 1;
      }
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
      {
        if(c1){
          curr_node = arm1;
        }
        else if(c2){
          curr_node = c2_arm1;
        }
        else if(b){
          // curr_node = rr;
        }
        present_bit = 2;
      }
    else if (key == GLFW_KEY_4 && action == GLFW_PRESS)
      {
        if(c1){
          curr_node = forearm1;
        }
        else if(c2){
          curr_node = c2_forearm1;
        }
        else if(b){
          // curr_node = rr;
        }
        present_bit = 3;
      } 
    else if (key == GLFW_KEY_5 && action == GLFW_PRESS)
      {
        if(c1){
          curr_node = arm2;
        }
        else if(c2){
          curr_node = c2_arm2;
        }
        else if(b){
          // curr_node = rr;
        }
        present_bit = 4;
      } 
    else if (key == GLFW_KEY_6 && action == GLFW_PRESS)
      {
        if(c1){
          curr_node = forearm2;
        }
        else if(c2){
          curr_node = c2_forearm2;
        }
        else if(b){
          // curr_node = rr;
        }
        present_bit = 5;
      }
    else if (key == GLFW_KEY_7 && action == GLFW_PRESS) 
    {
        if(c1){
          curr_node = thigh1;
        }
        else if(c2){
          curr_node = c2_thigh1;
        }
        else if(b){
          // curr_node = rr;
        }
        present_bit = 6;
      }
    else if (key == GLFW_KEY_8 && action == GLFW_PRESS)
    {
        if(c1){
          curr_node = leg1;
        }
        else if(c2){
          curr_node = c2_leg1;
        }
        else if(b){
          // curr_node = rr;
        }
        present_bit = 7;
      }
    else if (key == GLFW_KEY_9 && action == GLFW_PRESS)
    {
        if(c1){
          curr_node = thigh2;
        }
        else if(c2){
          curr_node = c2_thigh2;
        }
        else if(b){
          // curr_node = rr;
        }
        present_bit = 8;
      }
    else if (key == GLFW_KEY_0 && action == GLFW_PRESS)
    {
        if(c1){
          curr_node = leg2;
        }
        else if(c2){
          curr_node = c2_leg2;
        }
        else if(b){
          // curr_node = rr;
        }
        present_bit = 9;
      }
    else if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        if(c1){
          curr_node = head;
        }
        else if(c2){
          curr_node = c2_head;
        }
        else if(b){
          // curr_node = rr;
        }
        present_bit = 10;
      }
    else if (key == GLFW_KEY_L && action == GLFW_PRESS)
      {
        
       if(b){
          curr_node = rr6;
        }
        present_bit = 11;
      }

    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
      curr_node->dec_ry( constrains[present_bit][2], constrains[present_bit][3] );
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
      curr_node->inc_ry( constrains[present_bit][2], constrains[present_bit][3]);
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
      curr_node->dec_rx( constrains[present_bit][0], constrains[present_bit][1]);
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
      curr_node->inc_rx( constrains[present_bit][0], constrains[present_bit][1]);
    else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS)
      curr_node->dec_rz( constrains[present_bit][4], constrains[present_bit][5]);
    else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS)
      curr_node->inc_rz( constrains[present_bit][4], constrains[present_bit][5]);
    else if (key == GLFW_KEY_P && action == GLFW_PRESS)
      enable_perspective = !enable_perspective;   
    else if (key == GLFW_KEY_A  && action == GLFW_PRESS)
      c_ypos -= 0.7;
    else if (key == GLFW_KEY_D  && action == GLFW_PRESS)
      c_ypos += 0.7;
    else if (key == GLFW_KEY_W  && action == GLFW_PRESS)
      c_xpos -= 0.7;
    else if (key == GLFW_KEY_S  && action == GLFW_PRESS)
      c_xpos += 0.7;        
    else if (key == GLFW_KEY_Q  && action == GLFW_PRESS)
      c_zpos -= 0.7;
    else if (key == GLFW_KEY_E  && action == GLFW_PRESS)
      c_zpos += 0.7;
    else if (key == GLFW_KEY_E  && action == GLFW_PRESS)
      c_zpos += 0.7;   
  }
};  
  


