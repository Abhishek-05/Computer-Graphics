#include "gl_framework.hpp"
#include "hierarchy_node.hpp"

extern GLfloat c_xpos,c_ypos,c_zpos;
extern bool enable_perspective;
extern csX75::HNode* node1, *node2, *node3,*rr ,*curr_node,*box_top, *base,*head,*lhand,*rhand,*chest,*lshoulder,*rshoulder,*lforehand,*rforehand,*lthigh,*rthigh,*lcalf,*rcalf;
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
    else if (key == GLFW_KEY_O && action == GLFW_PRESS)
      curr_node = rr;
    else if (key == GLFW_KEY_B && action == GLFW_PRESS)
      curr_node = box_top;
    else if (key == GLFW_KEY_1 && action == GLFW_PRESS)
      curr_node = base;
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
      curr_node = chest;
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
      curr_node = lcalf;
    else if (key == GLFW_KEY_4 && action == GLFW_PRESS)
      curr_node = rcalf;
    else if (key == GLFW_KEY_5 && action == GLFW_PRESS)
      curr_node = lforehand;
    else if (key == GLFW_KEY_6 && action == GLFW_PRESS)
      curr_node = rforehand;
    else if (key == GLFW_KEY_7 && action == GLFW_PRESS)
      curr_node = lhand;
    else if (key == GLFW_KEY_8 && action == GLFW_PRESS)
      curr_node = rhand;
    else if (key == GLFW_KEY_9 && action == GLFW_PRESS)
      curr_node = lthigh;
    else if (key == GLFW_KEY_0 && action == GLFW_PRESS)
      curr_node = rthigh;
    else if (key == GLFW_KEY_H && action == GLFW_PRESS)
      curr_node = head;

    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
      curr_node->dec_ry();
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
      curr_node->inc_ry();
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
      curr_node->dec_rx();
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
      curr_node->inc_rx();
    else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS)
      curr_node->dec_rz();
    else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS)
      curr_node->inc_rz();
    else if (key == GLFW_KEY_P && action == GLFW_PRESS)
      enable_perspective = !enable_perspective;   
    else if (key == GLFW_KEY_A  && action == GLFW_PRESS)
      c_ypos -= .7;
    else if (key == GLFW_KEY_D  && action == GLFW_PRESS)
      c_ypos += .7;
    else if (key == GLFW_KEY_W  && action == GLFW_PRESS)
      c_xpos -= .7;
    else if (key == GLFW_KEY_S  && action == GLFW_PRESS)
      c_xpos += .7;        
    else if (key == GLFW_KEY_Q  && action == GLFW_PRESS)
      c_zpos -= .7;
    else if (key == GLFW_KEY_E  && action == GLFW_PRESS)
      c_zpos += .7;   
  }
};  
  


