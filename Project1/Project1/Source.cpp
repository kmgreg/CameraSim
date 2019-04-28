#include <allegro5/allegro5.h>
#include <allegro5/allegro_opengl.h>
#include <allegro5/allegro_image.h>
#include <GL/freeglut.h>
#include <GL/GLU.h>
#include <cstdio>
#include <vector>
#include <cmath>

#define PI 3.14159

const float FPS = 60;
const float velocity = 0.1;

using namespace std;

//This function from nehe.gamedev.net

GLvoid glDrawCube(GLuint txtr)                 // Draw A Cube
{
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	if (txtr != 0)
		glBindTexture(GL_TEXTURE_2D, txtr);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glBegin(GL_QUADS);

	// Front Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);  // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Left Of The Texture and Quad
		
															 // Back Face

	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
	
															   
	// Top Face
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad
															  // Bottom Face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
															   // Right face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);  // Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
															  // Left Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
	
	glEnd();                    // Done Drawing Quads

	glDisable(GL_TEXTURE_2D);
}

vector<float> getLA(float deg) {
	deg = deg * PI/ 180;
	vector<float> lavals;
	float x = cosf(deg);
	float z = sinf(deg);
	lavals.push_back(x);
	lavals.push_back(z);
	return lavals;
}


int main()
{
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	bool redraw = true;

	ALLEGRO_DISPLAY * display;
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	al_set_new_display_flags(ALLEGRO_OPENGL);
	display = al_create_display(640, 480);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	if (!al_install_mouse()) {
		fprintf(stderr, "failed to initialize the mouse!\n");
		return -1;
	}

	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}

	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	al_init_image_addon();
	ALLEGRO_BITMAP * bmp = al_load_bitmap("../testtexture.png");
	GLuint txtr = al_get_opengl_texture(bmp);
	glEnable(GL_CULL_FACE);


	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1.333, 0, 3);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-4, 1, 10, 0, 0, 0, 0, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	double n = 0.0;
	int d1 = 0;
	float camx;
	float camy;
	float camz;
	float lax = 1;
	float laz = 0;
	float deg = 0;
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
	bool sleft = false;
	bool sright = false;
	vector<float> pos;
	pos.push_back(-4);
	pos.push_back(1);
	pos.push_back(-10);
	while (1) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			d1 = (d1 + 1) % 3;
		}

		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_RIGHT:
					right = true;
					break;
				case ALLEGRO_KEY_LEFT:
					left = true;
					break;
				case ALLEGRO_KEY_UP:
					up = true;
					break;
				case ALLEGRO_KEY_DOWN:
					down = true;
					break;
				case ALLEGRO_KEY_A:
					sleft = true;
					break;
				case ALLEGRO_KEY_D:
					sright = true;
					break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_RIGHT:
				right = false;
				break;
			case ALLEGRO_KEY_LEFT:
				left = false;
				break;
			case ALLEGRO_KEY_UP:
				up = false;
				break;
			case ALLEGRO_KEY_DOWN:
				down = false;
				break;
			case ALLEGRO_KEY_A:
				sleft = false;
				break;
			case ALLEGRO_KEY_D:
				sright = false;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			if (d1 == 0) {
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				redraw = false;
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				n += 0.1;
				if (n > 10.0)
					n = 0.0;
				gluPerspective(90 - n * 6, 1.333, 0, 6 - n);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				gluLookAt(-4, 1, 10 + n, 0, 0, 0, 0, 1, 0);
				glPushMatrix();
				glTranslatef(6, 0, 0);
				glRotated(90, 1, 0, 0);
				glColor3f(1, 0, 0);
				glBegin(GL_POLYGON);
				GLUquadricObj * q = gluNewQuadric();
				gluCylinder(q, 5, 5, 1, 30, 30);
				glEnd();
				glPopMatrix();
				glPushMatrix();
				glTranslatef(4, 0, 6);
				glRotated(-90, 1, 0, 0);
				glColor3f(0, 0, 1);
				glBegin(GL_POLYGON);
				GLUquadricObj * s = gluNewQuadric();
				gluCylinder(s, 5, 0, 1, 30, 30);
				glEnd();
				glPopMatrix();
				al_flip_display();
			}
			else if (d1 == 1) {
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				redraw = false;
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				n += 0.1;
				if (n > 50.0)
					n = 0.0;
				gluPerspective(75, 1.333, 0, 9);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				if (left)
					deg += 1;
				if (right)
					deg -= 1;
				if (deg > 360)
					deg = 0;
				if (deg < 0)
					deg = 360;
				vector<float> xandz = getLA(deg);
				lax = xandz[1];
				laz = xandz[0];
				vector<float> strafe = getLA((float)((int) (deg - 90.0) % 360));
				float sx = strafe[1];
				float sz = strafe[0];
				if (up) {
					pos[0] += lax * velocity;
					pos[2] += laz * velocity;
				}
				if (down) {
					pos[0] -= lax * velocity;
					pos[2] -= laz * velocity;
				}
				if (sleft){
					pos[0] -= sx * velocity;
					pos[2] -= sz * velocity;
				}
				if (sright) {
					pos[0] += sx * velocity;
					pos[2] += sz * velocity;
				}
				gluLookAt(pos[0], pos[1], pos[2], pos[0] + lax, pos[1], pos[2] + laz, 0, 1, 0);
				glPushMatrix();
				glTranslatef(-15, 0, 10);
				glRotatef(90, 1, 0, 0);
				glColor3f(1, 0, 0);
				glBegin(GL_POLYGON);
				GLUquadricObj * q = gluNewQuadric();
				gluCylinder(q, 5, 5, 1, 30, 30);
				glEnd();
				glPopMatrix();
				glDrawCube(txtr);

				al_flip_display();
			}
			else if (d1 == 2) {
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				redraw = false;
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluPerspective(75, 1.333, 0, 9);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				if (left)
					deg += 1;
				if (right)
					deg -= 1;
				if (deg > 360)
					deg = 0;
				if (deg < 0)
					deg = 360;
				vector<float> xandz = getLA(deg);
				lax = xandz[1];
				laz = xandz[0];
				gluLookAt(-15 + (lax * 20), 5, 10 + (laz * 20), -15, 0, 10, 0, 1, 0);
				glPushMatrix();
				glTranslatef(-15, 0, 10);
				glRotatef(90, 1, 0, 0);
				glColor3f(1, 0, 0);
				glBegin(GL_POLYGON);
				GLUquadricObj * q = gluNewQuadric();
				gluCylinder(q, 5, 5, 1, 30, 30);
				glEnd();
				glPopMatrix();

				glPushMatrix();
				glTranslatef(12, 0, 5);
				glRotatef(90, 1, 0, 0);
				glColor3f(0, 0, 1);
				glBegin(GL_POLYGON);
				GLUquadricObj * z = gluNewQuadric();
				gluCylinder(z, 5, 5, 1, 30, 30);
				glEnd();
				glPopMatrix();

				al_flip_display();
			}
		}
	}
	return 0;
}