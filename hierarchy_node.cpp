#include "hierarchy_node.hpp"
#include "texture.hpp"

#include <iostream>

extern GLuint vPosition,vColor,uModelViewMatrix,texCoord, vNormal;
extern std::vector<glm::mat4> matrixStack;

namespace csX75
{	
	int y=0;
	GLuint tex0,tex1,tex2,tex3,tex4,tex5,tex6,tex7,tex8,tex9,tex10;

	HNode::HNode(HNode* a_parent, std::size_t img_c, GLuint num_v, glm::vec4* a_vertices, glm::vec4* a_normals, glm::vec2* a_tex, std::size_t v_size, std::size_t n_size, std::size_t t_size){

		tex0=LoadTexture("images/sheets.bmp",256,256);
			tex1=LoadTexture("images/wall.bmp",256,256);
			tex2=LoadTexture("images/wood.bmp",256,256);
			tex3=LoadTexture("images/lamp.bmp",256,256);
			tex4=LoadTexture("images/mediumdarkwood.bmp",256,256);
			tex5=LoadTexture("images/grass1.bmp",256,256);
			tex6=LoadTexture("images/black.bmp",256,256);
			tex7=LoadTexture("images/silver.bmp",256,256);
			tex8=LoadTexture("images/colors.bmp",256,256);
			tex9=LoadTexture("images/papers.bmp",256,256);
			tex10=LoadTexture("images/wall2.bmp",256,256);

		num_vertices = num_v;
		vertex_buffer_size = v_size;
		color_buffer_size = n_size;
		img_choice = img_c;
		//GLuint tex;

		// initialize vao and vbo of the object;
		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (1, &vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);

		//bind them
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		
		glBufferData (GL_ARRAY_BUFFER, v_size + t_size + n_size, NULL, GL_STATIC_DRAW);
  		glBufferSubData( GL_ARRAY_BUFFER, 0, v_size, a_vertices );
  		glBufferSubData( GL_ARRAY_BUFFER, v_size, t_size, a_tex);
  		glBufferSubData( GL_ARRAY_BUFFER, t_size+v_size, n_size, a_normals );
  		// set up vertex array
  		//Position
  		glEnableVertexAttribArray( vPosition );
  		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  		//Textures
  		glEnableVertexAttribArray( texCoord );
  		glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(v_size) );

  		//Normal
  		glEnableVertexAttribArray( vNormal );
  		glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(v_size+t_size) ));

		// set parent

		if(a_parent == NULL){
			parent = NULL;
		}
		else{
			parent = a_parent;
			parent->add_child(this);
		}

		//initial parameters are set to 0;

		tx=ty=tz=rx=ry=rz=0;

		update_matrices();
	}

	void HNode::update_matrices(){

		rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rx), glm::vec3(1.0f,0.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(ry), glm::vec3(0.0f,1.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(rz), glm::vec3(0.0f,0.0f,1.0f));

		translation = glm::translate(glm::mat4(1.0f),glm::vec3(tx,ty,tz));


	}

	void HNode::add_child(HNode* a_child){
		children.push_back(a_child);

	}

	void HNode::change_parameters(GLfloat atx, GLfloat aty, GLfloat atz, GLfloat arx, GLfloat ary, GLfloat arz){
		tx = atx;
		ty = aty;
		tz = atz;
		rx = arx;
		ry = ary;
		rz = arz;

		update_matrices();
	}

	void HNode::render(){
		if(img_choice==0){
			//std::cout<<"here1";
			glBindTexture(GL_TEXTURE_2D, tex0);
			
		}else if(img_choice==1){
			//std::cout<<"here2";
			glBindTexture(GL_TEXTURE_2D, tex1);
			
		}else if(img_choice==2){
			//std::cout<<"here3";
			glBindTexture(GL_TEXTURE_2D, tex2);
		}else if(img_choice==3){
			//std::cout<<"here3";
			glBindTexture(GL_TEXTURE_2D, tex3);
		}else if(img_choice==4){
			//std::cout<<"here3";
			glBindTexture(GL_TEXTURE_2D, tex4);
		}else if(img_choice==5){
			//std::cout<<"here3";
			glBindTexture(GL_TEXTURE_2D, tex5);
		}else if(img_choice==6){
			//std::cout<<"here3";
			glBindTexture(GL_TEXTURE_2D, tex6);
		}else if(img_choice==7){
			//std::cout<<"here3";
			glBindTexture(GL_TEXTURE_2D, tex7);
		}else if(img_choice==8){
			//std::cout<<"here3";
			glBindTexture(GL_TEXTURE_2D, tex8);
		}else if(img_choice==9){
			//std::cout<<"here3";
			glBindTexture(GL_TEXTURE_2D, tex9);
		}else if(img_choice==10){
			//std::cout<<"here3";
			glBindTexture(GL_TEXTURE_2D, tex10);
		}
  		
		//matrixStack multiply
		glm::mat4* ms_mult = multiply_stack(matrixStack);

		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(*ms_mult));
		glBindVertexArray (vao);
		glDrawArrays(GL_TRIANGLES, 0, num_vertices);

		// for memory 
		delete ms_mult;

	}

	void HNode::render_tree(){
		
		matrixStack.push_back(translation);
		matrixStack.push_back(rotation);

		render();
		for(int i=0;i<children.size();i++){
			children[i]->render_tree();
		}
		matrixStack.pop_back();
		matrixStack.pop_back();

	}

	void HNode::inc_rx(){
		rx+=10;
		update_matrices();
	}


	void HNode::inc_ry(){
		ry+=10;
		update_matrices();
	}

	void HNode::inc_rz(){
		rz+=10;
		update_matrices();
	}

	void HNode::dec_rx(){
		rx-=10;
		update_matrices();
	}

	void HNode::dec_ry(){
		ry-=10;
		update_matrices();
	}

	void HNode::dec_rz(){
		rz-=10;
		update_matrices();
	}


	glm::mat4* multiply_stack(std::vector<glm::mat4> matStack){
		glm::mat4* mult;
		mult = new glm::mat4(1.0f);
	
		for(int i=0;i<matStack.size();i++){
			*mult = (*mult) * matStack[i];
		}	

		return mult;
	}

}