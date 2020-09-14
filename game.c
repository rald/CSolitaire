#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include <GL/glfw.h>
#include <GL/gl2d.h>

#include "uvcoord_sprites.h"

#define GAME_TITLE "CSolitaire" 

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int mouseX=0,mouseY=0;

typedef struct Card Card;

struct Card {
	int x,y;
	int value;
	bool show;
};

bool inrect(int i,int j,int x,int y,int w,int h) {
	return i>=x && i<=x+w && j>=y && j<=y+h;
}

int main(int argc, char *argv[]) {

	glImage sprites_images[SPRITES_NUM_IMAGES];

	GLuint sprites_texture;

	int i,j,k;

	int x,y;

	int cx,cy;

	bool quit = false;
	
	Card cards[52];	

	bool isDrag=false;
	int dragDiffX,dragDiffY;

	bool mouseButtonRightHold=false;
	
	Card tmp;

	srand(time(NULL));

	glScreenInit(SCREEN_WIDTH,SCREEN_HEIGHT);
	glfwSetWindowTitle(GAME_TITLE);
	glfwSwapInterval(1);

	sprites_texture = glLoadSpriteSet(
			"images/cards.tga",
			sprites_images,
			SPRITES_BITMAP_WIDTH,
			SPRITES_BITMAP_HEIGHT,
			SPRITES_NUM_IMAGES,
			sprites_texcoords,
			GL_NEAREST
	); 


	for(i=0;i<52;i++) {
		cards[i].x=8;
		cards[i].y=8;
		cards[i].value=i;
		cards[i].show=false;
	}

	for(i=51;i>0;i--) {
		j=rand()%(i+1);
		tmp=cards[i];
		cards[i]=cards[j];
		cards[j]=tmp;
	}

	while(!quit) {

		glfwGetMousePos(&mouseX,&mouseY);

		glClearScreen();

		for(i=0;i<52;i++) {
			if(cards[i].show) {
				glSprite(cards[i].x,cards[i].y,GL2D_FLIP_NONE,&sprites_images[cards[i].value]);
			} else {
				glSprite(cards[i].x,cards[i].y,GL2D_FLIP_NONE,&sprites_images[52]);
			}
		}



		
		if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS) {
			if(isDrag) {
				cards[51].x=mouseX+dragDiffX;
				cards[51].y=mouseY+dragDiffY;
			} else {
				for(i=51;i>=0;i--) {
					if(inrect(mouseX,mouseY,cards[i].x,cards[i].y,71,96)) {

						dragDiffX=cards[i].x-mouseX;
						dragDiffY=cards[i].y-mouseY;
						isDrag=true;

						tmp=cards[i];
						for(j=i;j<=50;j++) {
							cards[j]=cards[j+1];
						}
						cards[51]=tmp;
						
						break;			
					}
				}
			}
		} else {
			isDrag=false;
		}

		if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_RIGHT)==GLFW_PRESS) {
			if(!mouseButtonRightHold) {
				mouseButtonRightHold=true;
				for(i=51;i>=0;i--) {
					if(inrect(mouseX,mouseY,cards[i].x,cards[i].y,71,96)) {
						cards[i].show=!cards[i].show;
						break;
					}
				}
			}
		}	else {
			mouseButtonRightHold=false;
		}

		float TimeStart=glfwGetTime();
		while((glfwGetTime()-TimeStart)<(1.0/100.0)){};
	
		glfwSwapBuffers();
	
		quit=glfwGetKey(GLFW_KEY_ESC) | !glfwGetWindowParam(GLFW_OPENED);
	}
	
	glfwTerminate();

	return 0;
}

