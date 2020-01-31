
#include "ObjParser.h"
#include <GL/freeglut.h>
#include "GL/glext.h"
#include <gl/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mmsystem.h>
#include <fmod.h>
#include <fmod.hpp>
#include <Windows.h>
#include "bmpfuncs.h"
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "fmodex_vc.lib")

#pragma warning(disable:4996)

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PI 3.14159265

struct Myblock {
	int blk_num;
	int color;
	int x, y, z;
	int rot;
};

struct Undo {
	int x_undo, y_undo, z_undo;
	int rot_undo;
	int load_undo;
};

Undo myundo;
bool undo_flag = false;

double theta = 45.0, phi = 45.0; int radius = 30;
double theta_p = 45.0, phi_p = 45.0; int radius_p = 18;
double upVector = cos(phi*PI / 180);
GLuint *sphere_t = new GLuint();
GLuint *floor_t = new GLuint();
GLUquadricObj *qobj = gluNewQuadric();
GLuint g_nCubeTex;
vector<Myblock> v;
Myblock myblk;

int count = 0, rotate_count = 0, count_;
bool enter = false;
bool new_blk = false;
bool move_whole_blocks = false;
bool move_loaded = false;
bool bgm = true;
bool preview = true;
GLsizei current_width, current_height;

double eyex, eyey, eyez;
ObjParser * blk = new ObjParser[8]{ { "obj/1X1.obj" },{ "obj/2X1.obj" },{ "obj/3X1.obj" },{ "obj/4X1.obj" },
									{ "obj/3X2.obj" },{ "obj/cylinder.obj" },{ "obj/3X2_flat.obj" },{ "obj/cylinder_flat.obj" } };
GLfloat R, G, B;
int mv = 0;
int mv_x = 0, mv_y = 0, mv_z = 0, rotate_blk = 0;
int mv_xw = 0, mv_yw = 0, mv_zw = 0, rotate_blkw = 0;
int index = 0, color = 1;

bool dragging = false;
double draw_x, draw_y;

void init(void);
void resize(int, int);

void draw(void);

void mouse(int, int, int, int);
void mouseWheel(int but, int dir, int x, int y);
void keyboard(unsigned char, int, int);
void specialkeyboard(int, int, int);
void draw_axis(void);
void light_SET(void);
void setDefault(void);
void mousemoving(int, int);
void draw_preview(void);
void draw_real(void);
void draw_sphere(void);
void draw_floor(void);
void sphereTextureMapping(void);
void floorTextureMapping(void);
void menu(void);
void main_menu(int);
void sub_menu1(int);
void sub_menu2(int);
void sub_menu3(int);

void DrawLego(int, int);
void draw_obj(ObjParser *objParser);
void draw_obj_with_texture(ObjParser *objParser);
void draw_string(void* font, const char* str, float x_position, float y_position, float red, float green, float blue);
FMOD::System *g_System;
FMOD::Sound *Sound;
FMOD::Channel *g_Channel;
void init_undo(void);
int main(int argc, char **argv) {
	FMOD::System_Create(&g_System);
	g_System->init(32, FMOD_INIT_NORMAL, nullptr);
	g_System->createSound("sound/background.mp3", FMOD_LOOP_NORMAL, 0, &Sound);
	g_System->playSound(FMOD_CHANNEL_FREE, Sound, false, &g_Channel);
	g_Channel->setVolume(0.1);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(400, 300);
	glutCreateWindow("12153310_Final_Project");
	menu();
	init();

	glutDisplayFunc(draw);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mousemoving);
	glutMouseWheelFunc(mouseWheel);

	glutMainLoop();
	return 0;
}

void init(void) {
	glClearColor(0, 0, 0, 1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	floorTextureMapping();
	sphereTextureMapping();
	glFrontFace(GL_CW);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricTexture(qobj, GL_TRUE);
	gluQuadricOrientation(qobj, GLU_INSIDE);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glutReshapeFunc(resize);

	light_SET();

	/**********Depth Test**********/
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	/************Antialiasing***************/
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glHint(GL_POINT_SMOOTH, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);

	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

}

void draw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (preview) draw_preview();
	draw_real();

	glutSwapBuffers();
}

void draw_preview(void) {
	glViewport(2.1*(current_width) / 3, 2 * (current_height) / 3, current_width / 3, current_height / 3);
	glLoadIdentity();
	gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);
	draw_axis();
	DrawLego(index, color);
	glFlush();
}
void draw_real(void) {
	if (phi >= 89) phi = 89;
	else if (phi <= 1) phi = 1;
	eyex = radius * sin(theta*PI / 180)*cos(phi*PI / 180);
	eyey = radius * sin(phi*PI / 180);
	eyez = radius * cos(theta*PI / 180)*cos(phi*PI / 180);
	upVector = cos(phi*PI / 180);
	glViewport(0, 0, current_width, current_height);
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, upVector, 0);

	if (preview) draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "Preview", 33, 20, 1, 1, 0);
	draw_floor();
	draw_sphere();
	draw_axis();

	if (new_blk) {							//N-> 새로운 블럭 생성
		glPushMatrix();
		glTranslatef(mv_x, mv_y, mv_z);
		glRotatef(rotate_count * 90, 0, 1, 0);
		if (undo_flag) {
			if (myundo.x_undo == 1) {
				init_undo();
				mv_x++;
			}
			else if (myundo.x_undo == -1) {
				mv_x--;
				init_undo();
			}
			else if (myundo.y_undo == 1) {
				mv_y++;
				init_undo();
			}
			else if (myundo.y_undo == -1) {
				mv_y--;
				init_undo();
			}
			else if (myundo.z_undo == 1) {
				mv_z++;
				init_undo();
			}
			else if (myundo.z_undo == -1) {
				mv_z--;
				init_undo();
			}
			else if (myundo.rot_undo == 1) {
				rotate_count--;
				init_undo();
			}
			undo_flag = false;
		}
		DrawLego(index, color);
		glPopMatrix();
	}

	if (enter) {							//enter->벡터에 현재 동작중인 레고 저장
		myblk.blk_num = index;				//index 저장
		myblk.color = color;				//color 저장
		myblk.x = mv_x;						//x축 위치 저장
		myblk.y = mv_y;						//y축 위치 저장
		myblk.z = mv_z;						//z축 위치 저장
		myblk.rot = rotate_count;			//회전값 저장
		count++;							//count증가
		v.push_back(myblk);					//벡터에 저장

		mv_x = 0; mv_y = 0; mv_z = 0;		//x,y,z 초기화
		enter = false;
		new_blk = false;
		rotate_count = 0;
	}
	if (undo_flag&&myundo.load_undo) {
		for (int i = 0; i < count_; i++) v.pop_back();
		count -= count_;
		undo_flag = false;
		init_undo();
	}
	if (count > 0) {						//벡터에 저장된 블록 그리기
		for (int i = 0; i < count; i++) {
			glPushMatrix();
			glTranslatef(v[i].x, v[i].y, v[i].z);
			glRotatef(v[i].rot * 90, 0, 1, 0);
			DrawLego(v[i].blk_num, v[i].color);
			glPopMatrix();
		}
	}
	glFlush();
}

void resize(int width, int height) {
	glViewport(0, 0, width, height);
	printf("[resize] WIDTH : %d,  HEIGHT : %d\n", width, height);
	current_width = width;
	current_height = height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)width / (float)height, 1, 500);
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {				//누르고 움직이면
			dragging = true;					//dragging flag 활성화
			draw_x = x;							//현재x를 저장
			draw_y = y;							//현재y를 저장
		}
		else
			dragging = false;
	}
	glutPostRedisplay();
}

void mouseWheel(int but, int dir, int x, int y)
{
	if (dir > 0) {
		if (radius > 10) radius--;
	}
	else {
		if (radius < 100) radius++;
	}
	glutPostRedisplay();
}

void light_SET() {
	GLfloat ambientLight[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specularLight[] = { 0.9f, 0.9f, 0.9f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	GLfloat specularMaterial[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, 64);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		printf("1X1 block\n");
		index = 1;
		break;
	case '2':
		printf("2X1 block\n");
		index = 2;
		break;
	case '3':
		printf("3X1 block\n");
		index = 3;
		break;
	case '4':
		printf("4X1 block\n");
		index = 4;
		break;
	case '5':
		printf("3X2 block\n");
		index = 5;
		break;
	case '6':
		printf("cylinder block\n");
		index = 6;
		break;
	case '7':
		printf("flat 3X2 block\n");
		index = 7;
		break;
	case '8':
		printf("flat cylinder block\n");
		index = 8;
		break;
	case '<':														//위 이동
		PlaySound(TEXT("sound/move.wav"), NULL, SND_ASYNC);
		if (move_whole_blocks) {									//전체
			for (int i = 0; i < count; i++) v[i].y++;
		}
		else if (move_loaded) {										//불러온 블럭
			for (int i = count - count_; i < count; i++) v[i].y++;
		}
		else {
			mv_y += 1;
			init_undo();
			myundo.y_undo = -1;
		}
		break;
	case '>':														//아래이동
		bool negative_whole, negative_loaded;
		if (move_whole_blocks) {									//전체
			for (int i = 0; i < count; i++) {
				if (v[i].y == 0) {
					negative_whole = true;
					break;
				}												//y=0인 블럭 유무 확인
				else negative_whole = false;
			}
			if (negative_whole)										//있으면 아래로 못내려감
				PlaySound(TEXT("sound/beep.wav"), NULL, SND_ASYNC);
			else {
				PlaySound(TEXT("sound/move.wav"), NULL, SND_ASYNC);
				for (int i = 0; i < count; i++) v[i].y--;
			}
		}
		else if (move_loaded) {
			for (int i = count - count_; i < count; i++) {
				if (v[i].y == 0) negative_loaded = true;
				else negative_loaded = false;
			}
			if (negative_loaded)
				PlaySound(TEXT("sound/beep.wav"), NULL, SND_ASYNC);
			else {
				PlaySound(TEXT("sound/move.wav"), NULL, SND_ASYNC);
				for (int i = count - count_; i < count; i++) v[i].y--;
			}
		}
		else {
			if (mv_y == 0) PlaySound(TEXT("sound/beep.wav"), NULL, SND_ASYNC);
			else {
				PlaySound(TEXT("sound/move.wav"), NULL, SND_ASYNC);
				mv_y -= 1;
				init_undo();
				myundo.y_undo = 1;
			}
		}
		break;
	case 13:														//블록 고정
		if (new_blk) enter = true;
		if (move_whole_blocks) move_whole_blocks = false;
		if (move_loaded) move_loaded = false;
		PlaySound(TEXT("sound/enter.wav"), NULL, SND_ASYNC);
		break;
	case 'N':														//블록 생성
		new_blk = true;
		printf("Create New block!\n");
		PlaySound(TEXT("sound/new.wav"), NULL, SND_ASYNC);
		break;
	case 'r':														//회전
		PlaySound(TEXT("sound/move.wav"), NULL, SND_ASYNC);
		rotate_count++;
		init_undo();
		myundo.rot_undo = 1;
		rotate_blk = 90 * rotate_count;
		break;
	case 127:														//최근블록삭제
		if (count == 0) {
			printf("No block existing\n");
			PlaySound(TEXT("sound/beep.wav"), NULL, SND_ASYNC);
			break;
		}
		printf("Delete the Latest Block\n");
		PlaySound(TEXT("sound/delete.wav"), NULL, SND_ASYNC);
		v.pop_back();
		count--;
		break;
	case 'c':														//색바꾸기
		color++;
		if (color == 13) color = 1;
		break;
	case 'o':														//bgm on/off
		if (bgm) {
			bgm = false;
			g_Channel->stop();
		}
		else {
			bgm = true;
			g_System->playSound(FMOD_CHANNEL_FREE, Sound, false, &g_Channel);
			g_Channel->setVolume(0.3);
		}
		break;
	case 'p':
		if (preview) preview = false;
		else preview = true;
		break;
	case'u':
		if (undo_flag == false) undo_flag = true;
		break;
	}
	glutPostRedisplay();
}

void specialkeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		PlaySound(TEXT("sound/move.wav"), NULL, SND_ASYNC);
		if (move_whole_blocks) {
			for (int i = 0; i < count; i++) v[i].x--;
		}
		else if (move_loaded) {
			for (int i = count - count_; i < count; i++) v[i].x--;
		}
		else {
			mv_x -= 1;
			init_undo();
			myundo.x_undo = 1;
		}
		break;
	case GLUT_KEY_RIGHT:
		PlaySound(TEXT("sound/move.wav"), NULL, SND_ASYNC);
		if (move_whole_blocks) {
			for (int i = 0; i < count; i++) v[i].x++;
		}
		else if (move_loaded) {
			for (int i = count - count_; i < count; i++) v[i].x++;
		}
		else {
			mv_x += 1;
			init_undo();
			myundo.x_undo = -1;
		}
		break;
	case GLUT_KEY_UP:
		PlaySound(TEXT("sound/move.wav"), NULL, SND_ASYNC);
		if (move_whole_blocks) {
			for (int i = 0; i < count; i++) v[i].z--;
		}
		else if (move_loaded) {
			for (int i = count - count_; i < count; i++) v[i].z--;
		}
		else {
			mv_z -= 1;
			init_undo();
			myundo.z_undo = 1;
		}
		break;
	case GLUT_KEY_DOWN:
		PlaySound(TEXT("sound/move.wav"), NULL, SND_ASYNC);
		if (move_whole_blocks) {
			for (int i = 0; i < count; i++) v[i].z++;
		}
		else if (move_loaded) {
			for (int i = count - count_; i < count; i++) v[i].z++;
		}
		else {
			mv_z += 1;
			init_undo();
			myundo.z_undo = -1;
		}
		break;
	}
	glutPostRedisplay();
}

void setDefault() {
	radius = 18;
	theta = 45.0;
	phi = 45.0;
}

void draw_string(void* font, const char* str, float x_position, float y_position, float red, float green, float blue) {
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-50, 50, -50, 50);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(red, green, blue);
	glRasterPos3f(x_position, y_position, 0);
	for (unsigned int i = 0; i < strlen(str); i++) {
		glutBitmapCharacter(font, str[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
	glColor3f(1, 1, 1);
}

void DrawLego(int index, int color) {
	switch (color) {
	case 1:
		R = 1, G = 0, B = 0;
		break;
	case 2:
		R = 0, G = 1, B = 0;
		break;
	case 3:
		R = 0, G = 0, B = 1;
		break;
	case 4:
		R = 0, G = 1, B = 1;
		break;
	case 5:
		R = 1, G = 0, B = 1;
		break;
	case 6:
		R = 1, G = 1, B = 0;
		break;
	case 7:
		R = 1.0f, G = 0.5f, B = 0;
		break;
	case 8:
		R = 1, G = 1, B = 1;
		break;
	case 9:
		R = 0.65, G = 0.16, B = 0.16;
		break;
	case 10:
		R = 1, G = 0.4, B = 0.7;
		break;
	case 11:
		R = 0.2, G = 0.3, B = 0.3;
		break;
	case 12:
		R = 0.5, G = 0.8, B = 1.7;
		break;
	}
	glColor3f(R, G, B);
	switch (index) {
	case 1:
		draw_obj(&blk[0]);
		break;
	case 2:
		draw_obj(&blk[1]);
		break;
	case 3:
		draw_obj(&blk[2]);
		break;
	case 4:
		draw_obj(&blk[3]);
		break;
	case 5:
		draw_obj(&blk[4]);
		break;
	case 6:
		draw_obj(&blk[5]);
		break;
	case 7:
		draw_obj(&blk[6]);
		break;
	case 8:
		draw_obj(&blk[7]);
		break;
	}
	glutPostRedisplay();
}
void draw_axis(void) {
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glLineWidth(3);
	glBegin(GL_LINES);

	glColor4f(1, 0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(6, 0, 0);

	glColor4f(0, 1, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 6, 0);

	glColor4f(0, 0, 1, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 6);

	glEnd();
	glColor3f(1, 1, 1);
	glEnable(GL_LIGHTING);
}

void mousemoving(int x, int y) {
	if (dragging) {
		theta = theta - (x - draw_x)*0.2;
		phi = phi + (y - draw_y)*0.2;
		draw_x = x;
		draw_y = y;
	} glutPostRedisplay();
}

void menu(void) {
	int submenu1 = glutCreateMenu(sub_menu1);		//Save Current Blocks
	glutAddMenuEntry("Save1", 1);
	glutAddMenuEntry("Save2", 2);
	glutAddMenuEntry("Save3", 3);

	int submenu2 = glutCreateMenu(sub_menu2);		//Load saved blocks
	glutAddMenuEntry("Save1", 1);
	glutAddMenuEntry("Save2", 2);
	glutAddMenuEntry("Save3", 3);

	int submenu3 = glutCreateMenu(sub_menu3);		//Move all
	glutAddMenuEntry("On", 1);
	glutAddMenuEntry("Off", 2);

	int mainmenu = glutCreateMenu(main_menu);
	glutAddSubMenu("Save File", submenu1);
	glutAddSubMenu("Load File", submenu2);
	glutAddSubMenu("Move all", submenu3);
	glutAddMenuEntry("Clear", 1);
	glutAddMenuEntry("Exit", 99);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void main_menu(int option) {
	switch (option) {
	case 1:
		printf("Clear current blocks\n");
		for (int i = 0; i < count; i++) v.pop_back();
		count = 0;
		PlaySound(TEXT("sound/delete.wav"), NULL, SND_ASYNC);
		break;
	case 99:
		exit(0);
	}
	glutPostRedisplay();
}

void sub_menu1(int option) {
	FILE *fp;
	switch (option) {
	case 1:
		fp = fopen("load/save1.txt", "w");
		break;
	case 2:
		fp = fopen("load/save2.txt", "w");
		break;
	case 3:
		fp = fopen("load/save3.txt", "w");
		break;
	}
	fprintf(fp, "%d ", count);
	for (int i = 0; i < count; i++)
		fprintf(fp, "%d %d %d %d %d %d ", v[i].blk_num, v[i].color, v[i].rot, v[i].x, v[i].y, v[i].z);
	glutPostRedisplay();
}

void sub_menu2(int option) {
	Myblock l_blk;
	int value;
	FILE *fp;
	switch (option) {
	case 1:
		fp = fopen("load/save1.txt", "r");
		break;
	case 2:
		fp = fopen("load/save2.txt", "r");
		break;
	case 3:
		fp = fopen("load/save3.txt", "r");
		break;
	}
	PlaySound(TEXT("sound/load.wav"), NULL, SND_ASYNC);
	fscanf(fp, "%d", &count_);
	for (int i = 0; i < count_; i++) {
		for (int j = 0; j < 6; j++) {
			fscanf(fp, "%d", &value);
			if (j == 0) l_blk.blk_num = value;
			if (j == 1) l_blk.color = value;
			if (j == 2) l_blk.rot = value;
			if (j == 3) l_blk.x = value;
			if (j == 4) l_blk.y = value;
			if (j == 5) l_blk.z = value;
		}
		v.push_back(l_blk);
	}
	move_loaded = true;
	myundo.load_undo = 1;
	count += count_;
	fclose(fp);

	glutPostRedisplay();
}

void sub_menu3(int option) {
	switch (option) {
	case 1:
		move_whole_blocks = true;
		break;
	case 2:
		move_whole_blocks = false;
		break;
	}glutPostRedisplay();
}

void sphereTextureMapping() {
	glGenTextures(1, sphere_t);
	int imgWidth, imgHeight, channels;
	char buf[100];
	sprintf(buf, "img/sphere1.bmp");
	buf[strlen(buf)] = 0;
	glBindTexture(GL_TEXTURE_2D, *sphere_t);
	unsigned char * img = readImageData(buf, &imgWidth, &imgHeight, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void draw_sphere(void) {
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, *sphere_t);
	gluSphere(qobj, 200, 10, 10);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
}

void floorTextureMapping(void) {
	glGenTextures(1, floor_t);
	int imgWidth, imgHeight, channels;
	char buf[100];
	sprintf(buf, "img/floor1.bmp");
	buf[strlen(buf)] = 0;
	glBindTexture(GL_TEXTURE_2D, *floor_t);
	unsigned char * img = readImageData(buf, &imgWidth, &imgHeight, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void draw_floor(void) {
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, *floor_t);
	glBegin(GL_QUADS);
	glNormal3f(0, 1.0, 0);
	glTexCoord2f(0, 0); glVertex3f(-200.0, 0, 200.0);
	glTexCoord2f(2, 0); glVertex3f(200.0, 0, 200.0);
	glTexCoord2f(2, 2); glVertex3f(200.0, 0, -200.0);
	glTexCoord2f(0, 2); glVertex3f(-200.0, 0, -200.0);
	glEnd();
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
}

void init_undo(void) {
	myundo.rot_undo = 0;
	myundo.x_undo = 0;
	myundo.y_undo = 0;
	myundo.z_undo = 0;
}

void draw_obj(ObjParser *objParser) {
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
			objParser->normal[objParser->normalIdx[n] - 1].y,
			objParser->normal[objParser->normalIdx[n] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
			objParser->vertices[objParser->vertexIdx[n] - 1].y,
			objParser->vertices[objParser->vertexIdx[n] - 1].z);

		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);

		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
}
void draw_obj_with_texture(ObjParser *objParser) {
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
		glTexCoord2f(objParser->textures[objParser->textureIdx[n] - 1].x, objParser->textures[objParser->textureIdx[n] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
			objParser->normal[objParser->normalIdx[n] - 1].y,
			objParser->normal[objParser->normalIdx[n] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
			objParser->vertices[objParser->vertexIdx[n] - 1].y,
			objParser->vertices[objParser->vertexIdx[n] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 1] - 1].x, objParser->textures[objParser->textureIdx[n + 1] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 2] - 1].x, objParser->textures[objParser->textureIdx[n + 2] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
}
