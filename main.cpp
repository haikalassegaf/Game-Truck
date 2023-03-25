
//  Game Truck 



#include <math.h> 
#include <GL/glut.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h>


//variabel yang digunakan

float ratio;
static int rotAngleX =0, rotAngleY =0, rotAngleZ =0;//rotate kamera
float angle=0.0, deltaAngle = 0.0; 
float x=-0.0f,y=15.0f,z=50.0f; // posisi awal kamera 
float lx=0.0f,ly=0.0f,lz=-1.0f; 
float posZTruck = -10, posXTruck = 0; //posisi awal Truck
float posYKoin1 = 2,posXKoin = 3,posZKoin1 = 5; //posisi awal koin
float posYKoin2 = 2,posZKoin2 = 5;
float posYKoin3 = 2,posZKoin3 = 5;
float posYKoin4 = 2,posZKoin4 = 5;
float posYKoin5 = 2,posZKoin5 = 5;
float posYKoin6 = 2,posXKoin6 = -3,posZKoin6 = 5;
float posYKoin7 = 2,posXKoin7 = -3,posZKoin7 = 5;
float posYKoin8 = 2,posXKoin8 = -3,posZKoin8 = 5;
float posYKoin9 = 2,posXKoin9 = -3,posZKoin9 = 5;
int deltaMove = 0,h,w;
const double PI = 3.141592653589793;
int bitmapHeight=12;
int i,j,radius,jumlah_titik,x_tengah,y_tengah,n;
int skor =0;


void Reshape(int w1, int h1) { // Fungsi reshape 

if(h1 == 0) h1 = 1; 
w = w1; 
h = h1; 
ratio = 1.0f * w / h; 
glMatrixMode(GL_PROJECTION); 
glLoadIdentity(); 
glViewport(0, 0, w, h); 
gluPerspective(45,ratio,0.1,1000); 
glMatrixMode(GL_MODELVIEW); 
glLoadIdentity(); 
gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f); 
} 
void orientMe(float ang) { // Fungsi ini untuk memutar arah kamera (tengok kiri/kanan) 
lx = sin(ang); 
lz = -cos(ang); 
glLoadIdentity(); 
gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f); 
} 
void moveMeFlat(int i) { // Fungsi ini untuk maju mundur kamera 
x = x + i*(lx)*0.1; 
z = z + i*(lz)*0.1; 
glLoadIdentity(); 
gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f); 
} 
void Grid() { // Fungsi untuk membuat grid di "lantai" 
double i; 
const float Z_MIN = -50, Z_MAX = 50; 
const float X_MIN = -50, X_MAX = 50; 
const float gap = 1.5; 
glColor3f(0.0, 1.0, 0.0); 
glBegin(GL_LINES); 

for(i=Z_MIN;i<Z_MAX;i+=gap) { 
	glVertex3f(i, 0, Z_MIN); 
	glVertex3f(i, 0, Z_MAX); 
} 

for(i=X_MIN;i<X_MAX;i+=gap) { 
	glVertex3f(X_MIN, 0, i); 
	glVertex3f(X_MAX, 0, i); 
} 
glEnd(); 

} 

//fungsi membuat roda
void wheel(){
	glPushMatrix();
		for(int j=0; j<=360; j++) {
			glPushMatrix();
				glTranslatef(1,0,-0.5);
				glRotated(90,1,0,0);
				glRotated(j,0,1,0);
				glTranslatef(0,3,0.8);
				glColor3f(0.1,0.1,0.1);
				glBegin(GL_QUADS);
				glVertex3f(0,0,0);
				glVertex3f(0.1,0,0);
				glVertex3f(0.1,0.6,0);
				glVertex3f(0,0.6,0);
				glEnd();
			glPopMatrix();
		}
	glPopMatrix();

	// lingkaran depan
	glPushMatrix();
		glTranslatef(0,0,3.1);
		glColor3f(0.1,0.1,0.1);
		glBegin(GL_TRIANGLE_FAN);
		radius=80;
		jumlah_titik=100;
		x_tengah=100;
		y_tengah=0;
		for (i=0; i<=360; i++) {
			float sudut=i*(2*PI/jumlah_titik);
			float x=x_tengah+radius*cos(sudut);
			float y=y_tengah+radius*sin(sudut);
			glVertex2f(x/100,y/100);
		}
		glEnd();
	glPopMatrix();

	// lingkaran belakang
	glPushMatrix();
		glTranslatef(0,0,2.5);
		glRotated(180,1,0,0);
		glColor3f(0.1,0.1,0.1);
		glBegin(GL_TRIANGLE_FAN);
		radius=80;
		jumlah_titik=100;
		x_tengah=100;
		y_tengah=0;
		for (i=0; i<=360; i++) {
			float sudut=i*(2*PI/jumlah_titik);
			float x=x_tengah+radius*cos(sudut);
			float y=y_tengah+radius*sin(sudut);
			glVertex2f(x/100,y/100);
		}
		glEnd();
	glPopMatrix();
}

//fungsi gambar Truck
void Truck() { 
//depan 
	//bagian badan bawah
	glPushMatrix(); 
		glTranslatef(0,0,3); 
		glBegin(GL_QUADS); 
		glColor3f(0.0,0.0,1.0);
		glVertex3f(-1.5f,1.0f,0.0f); 
		glVertex3f(2.0f,1.0f,0.0f); 
		glVertex3f(2.0f,3.0f,0.0f); 
		glVertex3f(-1.5f,3.0f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//bagian badan atas
	glPushMatrix(); 
		glTranslatef(0,0,3); 
		glBegin(GL_QUADS); 
		glColor3f(0.0,0.0,1.0);
		glVertex3f(-1.5f,3.0f,0.0f); 
		glVertex3f(2.0f,3.0f,0.0f); 
		glVertex3f(2.0f,4.5f,-0.4f); 
		glVertex3f(-1.5f,4.5f,-0.4f); 
		glEnd(); 
	glPopMatrix();
	
	//jendela depan
	glPushMatrix(); 
		glTranslatef(0,0,3); 
		glBegin(GL_QUADS); 
		glColor3f(0.5,0.5,0.5);
		glVertex3f(-1.2f,3.2f,-0.05f); 
		glVertex3f(1.7f,3.2f,-0.05f); 
		glVertex3f(1.7f,4.3f,-0.32f); 
		glVertex3f(-1.2f,4.3f,-0.32f); 
		glEnd(); 
	glPopMatrix();
	
	//cap mesin bawah
	glPushMatrix(); 
		glTranslatef(0,0,3); 
		glBegin(GL_QUADS); 
		glColor3f(0.5,0.5,0.5);
		glVertex3f(-0.6f,1.5f,0.01f); 
		glVertex3f(1.1f,1.5f,0.01f); 
		glVertex3f(1.3f,1.9f,0.01f); 
		glVertex3f(-0.8f,1.9f,0.01f); 
		glEnd(); 
	glPopMatrix();
	
	//cap mesin atas
	glPushMatrix(); 
		glTranslatef(0,0,3); 
		glBegin(GL_QUADS); 
		glColor3f(0.5,0.5,0.5);
		glVertex3f(-0.8f,2.0f,0.01f); 
		glVertex3f(1.3f,2.0f,0.01f); 
		glVertex3f(1.5f,2.4f,0.01f); 
		glVertex3f(-1.0f,2.4f,0.01f); 
		glEnd(); 
	glPopMatrix();
	
	// lampu kiri putih
	glPushMatrix(); 
		glTranslatef(0,0,3); 
		glBegin(GL_QUADS); 
		glColor3f(1.0,1.0,1.0);
		glVertex3f(-1.5f,1.3f,0.01f); 
		glVertex3f(-1.2f,1.3f,0.01f); 
		glVertex3f(-1.2f,1.6f,0.01f); 
		glVertex3f(-1.5f,1.6f,0.01f); 
		glEnd(); 
	glPopMatrix();
	
	//lampu kiri kuning
	glPushMatrix(); 
		glTranslatef(0,0,3); 
		glBegin(GL_QUADS); 
		glColor3f(1.0,1.0,0.0);
		glVertex3f(-1.2f,1.3f,0.02f); 
		glVertex3f(-0.8f,1.3f,0.02f); 
		glVertex3f(-1.0f,1.6f,0.02f); 
		glVertex3f(-1.2f,1.6f,0.02f); 
		glEnd(); 
	glPopMatrix();
	
	//lampu kanan putih
	glPushMatrix(); 
		glTranslatef(0,0,3); 
		glBegin(GL_QUADS); 
		glColor3f(1.0,1.0,1.0);
		glVertex3f(1.7f,1.3f,0.01f); 
		glVertex3f(2.0f,1.3f,0.01f); 
		glVertex3f(2.0f,1.6f,0.01f); 
		glVertex3f(1.7f,1.6f,0.01f); 
		glEnd(); 
	glPopMatrix();
	
	//lampu kanan kuning
	glPushMatrix(); 
		glTranslatef(0,0,3); 
		glBegin(GL_QUADS); 
		glColor3f(1.0,1.0,0.0);
		glVertex3f(1.3f,1.3f,0.02f); 
		glVertex3f(1.7f,1.3f,0.02f); 
		glVertex3f(1.7f,1.6f,0.02f); 
		glVertex3f(1.5f,1.6f,0.02f); 
		glEnd(); 
	glPopMatrix();
	
//kanan
	//bagian kanan
	glPushMatrix(); 
		glRotated(90, 0, 1, 0);
		glTranslatef(0,0,2.2); 
		glBegin(GL_QUADS); 
		glColor3f(0.0,0.0,1.0);
		glVertex3f(-3.0f,1.0f,-0.2f); 
		glVertex3f(-1.2f,1.0f,-0.2f); 
		glVertex3f(-1.2f,3.0f,-0.2f); 
		glVertex3f(-3.0f,3.0f,-0.2f); 
		glEnd(); 
	glPopMatrix();
	
	//pintu kanan
	glPushMatrix(); 
		glRotated(90, 0, 1, 0);
		glTranslatef(0,0,2.2); 
		glBegin(GL_QUADS); 
		glColor3f(1.0,1.0,1.0);
		glVertex3f(-2.8f,1.1f,-0.18f); 
		glVertex3f(-1.7f,1.1f,-0.18f); 
		glVertex3f(-1.7f,3.0f,-0.18f); 
		glVertex3f(-2.8f,3.0f,-0.18f); 
		glEnd(); 
	glPopMatrix();
	
	//pegangan kanan
	glPushMatrix(); 
		glRotated(90, 0, 1, 0);
		glTranslatef(0,0.3,2.2); 
		glBegin(GL_QUADS); 
		glColor3f(0.0,0.0,1.0);
		glVertex3f(-1.9f,1.6f,-0.17f); 
		glVertex3f(-2.1f,1.6f,-0.17f); 
		glVertex3f(-2.1f,1.7f,-0.17f); 
		glVertex3f(-1.9f,1.7f,-0.17f); 
		glEnd(); 
	glPopMatrix();
	
	// kanan atas 
	glPushMatrix(); 
		glRotated(90, 0, 1, 0);
		glTranslatef(0,0,2.2); 
		glBegin(GL_QUADS); 
		glColor3f(0.0,0.0,1.0);
		glVertex3f(-3.0f,3.0f,-0.2f); 
		glVertex3f(-1.2f,3.0f,-0.2f); 
		glVertex3f(-1.2f,4.5f,-0.2f); 
		glVertex3f(-2.6f,4.5f,-0.2f); 
		glEnd(); 
	glPopMatrix();
	
	//jendela kanan
	glPushMatrix(); 
		glRotated(90, 0, 1, 0);
		glTranslatef(0,0,2.2); 
		glBegin(GL_QUADS); 
		glColor3f(0.5,0.5,0.5);
		glVertex3f(-2.75f,3.2f,-0.19f); 
		glVertex3f(-1.7f,3.2f,-0.19f); 
		glVertex3f(-1.7f,4.3f,-0.19f); 
		glVertex3f(-2.5f,4.3f,-0.19f); 
		glEnd(); 
	glPopMatrix();

//kiri 
	//bagian kiri
	glPushMatrix(); 
		glRotated(-90, 0, 1, 0);
		glTranslatef(4.3,0,1.7); 
		glBegin(GL_QUADS); 
		glColor3f(0.0,0.0,1.0);
		glVertex3f(-3.1f,1.0f,-0.2f); 
		glVertex3f(-1.3f,1.0f,-0.2f); 
		glVertex3f(-1.3f,3.0f,-0.2f); 
		glVertex3f(-3.1f,3.0f,-0.2f); 
		glEnd(); 
	glPopMatrix();
	
	//pintu kiri
	glPushMatrix(); 
		glRotated(-90, 0, 1, 0);
		glTranslatef(4.3,0,1.7); 
		glBegin(GL_QUADS); 
		glColor3f(1.0,1.0,1.0);
		glVertex3f(-2.6f,1.1f,-0.18f); 
		glVertex3f(-1.5f,1.1f,-0.18f); 
		glVertex3f(-1.5f,3.0f,-0.18f); 
		glVertex3f(-2.6f,3.0f,-0.18f); 
		glEnd(); 
	glPopMatrix();
	
	//pegangan kiri
	glPushMatrix(); 
		glRotated(-90, 0, 1, 0);
		glTranslatef(4.3,0.3,1.7); 
		glBegin(GL_QUADS); 
		glColor3f(0.0,0.0,1.0);
		glVertex3f(-2.3f,1.6f,-0.17f); 
		glVertex3f(-2.5f,1.6f,-0.17f); 
		glVertex3f(-2.5f,1.7f,-0.17f); 
		glVertex3f(-2.3f,1.7f,-0.17f); 
		glEnd(); 
	glPopMatrix();
	
	// kiri atas 
	glPushMatrix(); 
		glRotated(-90, 0, 1, 0);
		glTranslatef(4.2,0,1.7); 
		glBegin(GL_QUADS); 
		glColor3f(0.0,0.0,1.0);
		glVertex3f(-3.0f,3.0f,-0.2f); 
		glVertex3f(-1.2f,3.0f,-0.2f); 
		glVertex3f(-1.6f,4.5f,-0.2f); 
		glVertex3f(-3.0f,4.5f,-0.2f); 
		glEnd(); 
	glPopMatrix();
	
	// jendela kiri
	glPushMatrix(); 
		glRotated(-90, 0, 1, 0);
		glTranslatef(4.3,0,1.7); 
		glBegin(GL_QUADS); 
		glColor3f(0.5,0.5,0.5);
		glVertex3f(-2.6f,3.2f,-0.19f); 
		glVertex3f(-1.5f,3.2f,-0.19f); 
		glVertex3f(-1.8f,4.3f,-0.19f); 
		glVertex3f(-2.6f,4.3f,-0.19f); 
		glEnd(); 
	glPopMatrix();

// belakang 
glPushMatrix(); 
	glRotated(-180, 0, 1, 0); 
	glTranslatef(0,0,-1.2); 
	glBegin(GL_QUADS); 
	glColor3f(0.0,0.0,1.0);
	glVertex3f(-2.0f,1.0f,0.0f); 
	glVertex3f(1.5f,1.0f,0.0f); 
	glVertex3f(1.5f,4.5f,0.0f); 
	glVertex3f(-2.0f,4.5f,0.0f); 
	glEnd(); 
glPopMatrix(); 
	
// atas 
glPushMatrix(); 
	glRotated(-90, 1, 0, 0); 
	glTranslatef(0.2,-2.8,4.5); 
	glBegin(GL_QUADS);
	glColor3f(0.0,0.0,1.0); 
	glVertex3f(-1.7f,0.3f,0.0f); 
	glVertex3f(1.8f,0.3f,0.0f); 
	glVertex3f(1.8f,1.4f,0.0f); 
	glVertex3f(-1.7f,1.4f,0.0f); 
	glEnd(); 
glPopMatrix(); 

// bawah 
glPushMatrix(); 
	glRotated(90, 1, 0, 0); 
	glTranslatef(0.2,1,-1.0); 
	glBegin(GL_QUADS);
	glColor3f(0.0,0.0,1.0); 
	glVertex3f(-1.7f,0.2f,0.0f); 
	glVertex3f(1.8f,0.2f,0.0f); 
	glVertex3f(1.8f,2.0f,0.0f); 
	glVertex3f(-1.7f,2.0f,0.0f); 
	glEnd(); 
glPopMatrix(); 

//roda
	//kanan
	 glPushMatrix();
	 	glRotatef(90, 0.0, 1.0, 0.0);
		glTranslatef(-2.3, 0.8, 0.3);
		glScalef(0.6,0.6,0.6);
		wheel();
	glPopMatrix();

	//kiri
	glPushMatrix();
		glRotatef(-90, 0.0, 1.0, 0.0);
		glTranslatef(1.0, 0.8, -0.2);
		glScalef(0.6,0.6,0.6);
		wheel();
	glPopMatrix();


//container
	//depan	
	glPushMatrix(); 
		glTranslatef(0,0,1.0); 
		glBegin(GL_QUADS); 
		glColor3f(1.0,0.0,0.0);
		glVertex3f(-1.5f,1.3f,0.0f); 
		glVertex3f(2.0f,1.3f,0.0f); 
		glVertex3f(2.0f,5.4f,0.0f); 
		glVertex3f(-1.5f,5.4f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//kanan
	glPushMatrix(); 
		glRotated(90, 0, 1, 0);
		glTranslatef(0,0,2); 
		glBegin(GL_QUADS); 
		glColor3f(1.0,0.0,0.0);
		glVertex3f(-1.0f,1.3f,0.0f); 
		glVertex3f(4.5f,1.3f,0.0f); 
		glVertex3f(4.5f,5.4f,0.0f); 
		glVertex3f(-1.0f,5.4f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//kiri
	glPushMatrix(); 
		glRotated(-90, 0, 1, 0);
		glTranslatef(0,0,1.5); 
		glBegin(GL_QUADS); 
		glColor3f(1.0,0.0,0.0);
		glVertex3f(-4.5f,1.3f,0.0f); 
		glVertex3f(1.0f,1.3f,0.0f); 
		glVertex3f(1.0f,5.4f,0.0f); 
		glVertex3f(-4.5f,5.4f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//belakang
	glPushMatrix(); 
		glTranslatef(0,0,-4.5); 
		glBegin(GL_QUADS); 
		glColor3f(1.0,0.0,0.0);
		glVertex3f(-1.5f,1.3f,0.0f); 
		glVertex3f(2.0f,1.3f,0.0f); 
		glVertex3f(2.0f,5.4f,0.0f); 
		glVertex3f(-1.5f,5.4f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//atas
	glPushMatrix(); 
		glRotated(-90, 1, 0, 0); 
		glTranslatef(0.2,-1.2,5.4); 
		glBegin(GL_QUADS);
		glColor3f(1.0,0.0,0.0); 
		glVertex3f(-1.7f,0.2f,0.0f); 
		glVertex3f(1.8f,0.2f,0.0f); 
		glVertex3f(1.8f,5.7f,0.0f); 
		glVertex3f(-1.7f,5.7f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//bawah
	glPushMatrix(); 
		glRotated(90, 1, 0, 0); 
		glTranslatef(0.2,-4.7,-1.3); 
		glBegin(GL_QUADS);
		glColor3f(1.0,0.0,0.0); 
		glVertex3f(-1.7f,0.2f,0.0f); 
		glVertex3f(1.8f,0.2f,0.0f); 
		glVertex3f(1.8f,5.7f,0.0f); 
		glVertex3f(-1.7f,5.7f,0.0f); 
		glEnd(); 
	glPopMatrix();

//penyangga container
	//depan	
	glPushMatrix(); 
		glTranslatef(0,0,1.19); 
		glBegin(GL_QUADS); 
		glColor3f(0.0,0.0,0.0);
		glVertex3f(-1.5f,1.0f,0.0f); 
		glVertex3f(2.0f,1.0f,0.0f); 
		glVertex3f(2.0f,1.3f,0.0f); 
		glVertex3f(-1.5f,1.3f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//kanan
	glPushMatrix(); 
		glRotated(90, 0, 1, 0);
		glTranslatef(0,0,2); 
		glBegin(GL_QUADS); 
		glColor3f(0.0,0.0,0.0);
		glVertex3f(-1.2f,1.0f,0.0f); 
		glVertex3f(4.5f,1.0f,0.0f); 
		glVertex3f(4.5f,1.3f,0.0f); 
		glVertex3f(-1.2f,1.3f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//kiri
	glPushMatrix(); 
		glRotated(-90, 0, 1, 0);
		glTranslatef(0,0,1.5); 
		glBegin(GL_QUADS); 
		glColor3f(0.0,0.0,0.0);
		glVertex3f(-4.5f,1.0f,0.0f); 
		glVertex3f(1.2f,1.0f,0.0f); 
		glVertex3f(1.2f,1.3f,0.0f); 
		glVertex3f(-4.5f,1.3f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//belakang
	glPushMatrix(); 
		glTranslatef(0,0,-4.5); 
		glBegin(GL_QUADS); 
		glColor3f(0.0,0.0,0.0);
		glVertex3f(-1.5f,1.0f,0.0f); 
		glVertex3f(2.0f,1.0f,0.0f); 
		glVertex3f(2.0f,1.3f,0.0f); 
		glVertex3f(-1.5f,1.3f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//atas
	glPushMatrix(); 
		glRotated(-90, 1, 0, 0); 
		glTranslatef(0.2,-1.4,1.3); 
		glBegin(GL_QUADS);
		glColor3f(0.0,0.0,0.0); 
		glVertex3f(-1.7f,0.2f,0.0f); 
		glVertex3f(1.8f,0.2f,0.0f); 
		glVertex3f(1.8f,5.9f,0.0f); 
		glVertex3f(-1.7f,5.9f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//bawah
	glPushMatrix(); 
		glRotated(90, 1, 0, 0); 
		glTranslatef(0.2,-4.7,-1); 
		glBegin(GL_QUADS);
		glColor3f(0.0,0.0,0.0); 
		glVertex3f(-1.7f,0.2f,0.0f); 
		glVertex3f(1.8f,0.2f,0.0f); 
		glVertex3f(1.8f,5.9f,0.0f); 
		glVertex3f(-1.7f,5.9f,0.0f); 
		glEnd(); 
	glPopMatrix();
	
	
//roda depan
	//kanan
	 glPushMatrix();
	 	glRotatef(90, 0.0, 1.0, 0.0);
		glTranslatef(-0.3, 0.8, 0.3);
		glScalef(0.6,0.6,0.6);
		wheel();
	glPopMatrix();

	//kiri
	glPushMatrix();
		glRotatef(-90, 0.0, 1.0, 0.0);
		glTranslatef(-1.0, 0.8, -0.2);
		glScalef(0.6,0.6,0.6);
		wheel();
	glPopMatrix();
	
//roda belakang
	//kanan
	 glPushMatrix();
	 	glRotatef(90, 0.0, 1.0, 0.0);
		glTranslatef(3, 0.8, 0.3);
		glScalef(0.6,0.6,0.6);
		wheel();
	glPopMatrix();

	//kiri
	glPushMatrix();
		glRotatef(-90, 0.0, 1.0, 0.0);
		glTranslatef(-4, 0.8, -0.2);
		glScalef(0.6,0.6,0.6);
		wheel();
	glPopMatrix();


//container
	//depan	
	glPushMatrix(); 
		glTranslatef(0,0,-5); 
		glBegin(GL_QUADS); 
		glColor3f(1.0,0.0,0.0);
		glVertex3f(-1.5f,1.3f,0.0f); 
		glVertex3f(2.0f,1.3f,0.0f); 
		glVertex3f(2.0f,5.4f,0.0f); 
		glVertex3f(-1.5f,5.4f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//kanan
	glPushMatrix(); 
		glRotated(90, 0, 1, 0);
		glTranslatef(6.2,0,2); 
		glBegin(GL_QUADS); 
		glColor3f(1.0,0.0,0.0);
		glVertex3f(-1.2f,1.3f,0.0f); 
		glVertex3f(4.5f,1.3f,0.0f); 
		glVertex3f(4.5f,5.4f,0.0f); 
		glVertex3f(-1.2f,5.4f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//kiri
	glPushMatrix(); 
		glRotated(-90, 0, 1, 0);
		glTranslatef(-6.2,0,1.5); 
		glBegin(GL_QUADS); 
		glColor3f(1.0,0.0,0.0);
		glVertex3f(-4.5f,1.3f,0.0f); 
		glVertex3f(1.2f,1.3f,0.0f); 
		glVertex3f(1.2f,5.4f,0.0f); 
		glVertex3f(-4.5f,5.4f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//belakang
	glPushMatrix(); 
		glTranslatef(0,0,-10.7); 
		glBegin(GL_QUADS); 
		glColor3f(1.0,0.0,0.0);
		glVertex3f(-1.5f,1.3f,0.0f); 
		glVertex3f(2.0f,1.3f,0.0f); 
		glVertex3f(2.0f,5.4f,0.0f); 
		glVertex3f(-1.5f,5.4f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
		
	//atas
	glPushMatrix(); 
		glRotated(-90, 1, 0, 0); 
		glTranslatef(0.2,4.8,5.4); 
		glBegin(GL_QUADS);
		glColor3f(1.0,0.0,0.0); 
		glVertex3f(-1.7f,0.2f,0.0f); 
		glVertex3f(1.8f,0.2f,0.0f); 
		glVertex3f(1.8f,5.9f,0.0f); 
		glVertex3f(-1.7f,5.9f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//bawah
	glPushMatrix(); 
		glRotated(90, 1, 0, 0); 
		glTranslatef(0.2,-10.9,-1.4); 
		glBegin(GL_QUADS);
		glColor3f(1.0,0.0,0.0); 
		glVertex3f(-1.7f,0.2f,0.0f); 
		glVertex3f(1.8f,0.2f,0.0f); 
		glVertex3f(1.8f,5.9f,0.0f); 
		glVertex3f(-1.7f,5.9f,0.0f); 
		glEnd(); 
	glPopMatrix();
	
//penyangga container
	//depan	
	glPushMatrix(); 
		glTranslatef(0,0,-5); 
		glBegin(GL_QUADS); 
		glColor3f(0.0,0.0,0.0);
		glVertex3f(-1.5f,1.0f,0.0f); 
		glVertex3f(2.0f,1.0f,0.0f); 
		glVertex3f(2.0f,1.3f,0.0f); 
		glVertex3f(-1.5f,1.3f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//kanan
	glPushMatrix(); 
		glRotated(90, 0, 1, 0);
		glTranslatef(6.2,0,2); 
		glBegin(GL_QUADS); 
		glColor3f(0.0,0.0,0.0);
		glVertex3f(-1.2f,1.0f,0.0f); 
		glVertex3f(4.5f,1.0f,0.0f); 
		glVertex3f(4.5f,1.3f,0.0f); 
		glVertex3f(-1.2f,1.3f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//kiri
	glPushMatrix(); 
		glRotated(-90, 0, 1, 0);
		glTranslatef(-6.2,0,1.5); 
		glBegin(GL_QUADS); 
		glColor3f(0.0,0.0,0.0);
		glVertex3f(-4.5f,1.0f,0.0f); 
		glVertex3f(1.2f,1.0f,0.0f); 
		glVertex3f(1.2f,1.3f,0.0f); 
		glVertex3f(-4.5f,1.3f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//belakang
	glPushMatrix(); 
		glTranslatef(0,0,-10.7); 
		glBegin(GL_QUADS); 
		glColor3f(0.0,0.0,0.0);
		glVertex3f(-1.5f,1.0f,0.0f); 
		glVertex3f(2.0f,1.0f,0.0f); 
		glVertex3f(2.0f,1.3f,0.0f); 
		glVertex3f(-1.5f,1.3f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
		
	//atas
	glPushMatrix(); 
		glRotated(-90, 1, 0, 0); 
		glTranslatef(0.2,4.8,1.3); 
		glBegin(GL_QUADS);
		glColor3f(0.0,0.0,0.0); 
		glVertex3f(-1.7f,0.2f,0.0f); 
		glVertex3f(1.8f,0.2f,0.0f); 
		glVertex3f(1.8f,5.9f,0.0f); 
		glVertex3f(-1.7f,5.9f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//bawah
	glPushMatrix(); 
		glRotated(90, 1, 0, 0); 
		glTranslatef(0.2,-10.9,-1); 
		glBegin(GL_QUADS);
		glColor3f(0.0,0.0,0.0); 
		glVertex3f(-1.7f,0.2f,0.0f); 
		glVertex3f(1.8f,0.2f,0.0f); 
		glVertex3f(1.8f,5.9f,0.0f); 
		glVertex3f(-1.7f,5.9f,0.0f); 
		glEnd(); 
	glPopMatrix();

	
//roda depan
	//kanan
	 glPushMatrix();
	 	glRotatef(90, 0.0, 1.0, 0.0);
		glTranslatef(6, 0.8, 0.3);
		glScalef(0.6,0.6,0.6);
		wheel();
	glPopMatrix();

	//kiri
	glPushMatrix();
		glRotatef(-90, 0.0, 1.0, 0.0);
		glTranslatef(-7.0, 0.8, -0.2);
		glScalef(0.6,0.6,0.6);
		wheel();
	glPopMatrix();
	
//roda belakang
	//kanan
	 glPushMatrix();
	 	glRotatef(90, 0.0, 1.0, 0.0);
		glTranslatef(9, 0.8, 0.3);
		glScalef(0.6,0.6,0.6);
		wheel();
	glPopMatrix();

	//kiri
	glPushMatrix();
		glRotatef(-90, 0.0, 1.0, 0.0);
		glTranslatef(-10, 0.8, -0.2);
		glScalef(0.6,0.6,0.6);
		wheel();
	glPopMatrix();
	

//sambungan
	//depan	
	glPushMatrix(); 
		glTranslatef(1,0,-4.5); 
		glBegin(GL_QUADS); 
		glColor3f(0.0,0.0,0.0);
		glVertex3f(-1.3f,1.0f,0.0f); 
		glVertex3f(0.0f,1.0f,0.0f); 
		glVertex3f(0.0f,1.2f,0.0f); 
		glVertex3f(-1.3f,1.2f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//kanan
	glPushMatrix(); 
		glRotated(90, 0, 1, 0);
		glTranslatef(3,0,1); 
		glBegin(GL_QUADS); 
		glColor3f(0.0,0.0,0.0);
		glVertex3f(1.5f,1.0f,0.0f); 
		glVertex3f(2.3f,1.0f,0.0f); 
		glVertex3f(2.3f,1.2f,0.0f); 
		glVertex3f(1.5f,1.2f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//kiri
	glPushMatrix(); 
		glRotated(-90, 0, 1, 0);
		glTranslatef(-2,0,0.3); 
		glBegin(GL_QUADS); 
		glColor3f(0.0,0.0,0.0);
		glVertex3f(-3.3f,1.0f,0.0f); 
		glVertex3f(-2.5f,1.0f,0.0f); 
		glVertex3f(-2.5f,1.2f,0.0f); 
		glVertex3f(-3.3f,1.2f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
	
	//belakang
	glPushMatrix(); 
		glTranslatef(1,0,-5); 
		glBegin(GL_QUADS); 
		glColor3f(0.0,0.0,0.0);
		glVertex3f(-1.3f,1.0f,0.0f); 
		glVertex3f(0.0f,1.0f,0.0f); 
		glVertex3f(0.0f,1.2f,0.0f); 
		glVertex3f(-1.3f,1.2f,0.0f); 
		glEnd(); 
	glPopMatrix(); 
			
	//atas
	glPushMatrix(); 
		glRotated(-90, 1, 0, 0); 
		glTranslatef(0.2,2,1.2); 
		glBegin(GL_QUADS);
		glColor3f(0.0,0.0,0.0); 
		glVertex3f(-0.5f,2.5f,0.0f); 
		glVertex3f(0.8f,2.5f,0.0f); 
		glVertex3f(0.8f,3.0f,0.0f); 
		glVertex3f(-0.5f,3.0f,0.0f); 
		glEnd(); 
	glPopMatrix();
	 
	//bawah
	glPushMatrix(); 
		glRotated(90, 1, 0, 0); 
		glTranslatef(0.2,-7.5,-1.1); 
		glBegin(GL_QUADS);
		glColor3f(0.0,0.0,0.0); 
		glVertex3f(-0.5f,2.5f,0.0f); 
		glVertex3f(0.8f,2.5f,0.0f); 
		glVertex3f(0.8f,3.0f,0.0f); 
		glVertex3f(-0.5f,3.0f,0.0f); 
		glEnd(); 
	glPopMatrix();
	
	
}

void tambahan(){
	
	//trotoar kanan
	glColor3f(0.0f, 1.0f, 0.0f);
 glBegin(GL_QUADS);
  glVertex3f(10.0f, 0.0f, -100.0f);
  glVertex3f(10.0f, 0.0f,  100.0f);
  glVertex3f( 100.0f, 0.0f,  100.0f);
  glVertex3f( 100.0f, 0.0f, -100.0f);
 glEnd();
 
 //trotoar kiri
	glColor3f(0.0f, 1.0f, 0.0f);
 glBegin(GL_QUADS);
  	glVertex3f(-100.0f, 0.0f, -100.0f);
  	glVertex3f(-100.0f, 0.0f,  100.0f);
  	glVertex3f( -10.0f, 0.0f,  100.0f);
  	glVertex3f( -10.0f, 0.0f, -100.0f);
 glEnd();
 
 	 glPushMatrix();
	 //jalan utama
	 glColor3f(0.0f, 0.0f, 0.0f);
	 glTranslatef(0.0,0.0,0.0);
	 glBegin(GL_QUADS);
	  glVertex3f(10.0f, 0.0f, -100.0f);
	  glVertex3f(10.0f, 0.0f,  100.0f);
	  glVertex3f( -10.0f, 0.0f,  100.0f);
	  glVertex3f( -10.0f, 0.0f, -100.0f);
	 glEnd();
	 
	//jalan putih
	for(int i = 100; i > -100; i = i - 20){
		glColor3f(1,1,1);
		glBegin(GL_QUADS);
			glVertex3f(-0.5,0.2,i);
			glVertex3f(-0.5,0.2,i-10);
			glVertex3f(0.5,0.2,i-10);
			glVertex3f(0.5,0.2,i);
		glEnd();
	}
	glPopMatrix();
	 
	 //jalan utama 2
	 glColor3f(0.0f, 0.0f, 0.0f);
	 glTranslatef(0.0,0.3,0.0);
	 glRotated(90,0,1,0);
	 glBegin(GL_QUADS);
	  glVertex3f(10.0f, 0.0f, -100.0f);
	  glVertex3f(10.0f, 0.0f,  100.0f);
	  glVertex3f( -10.0f, 0.0f,  100.0f);
	  glVertex3f( -10.0f, 0.0f, -100.0f);
	 glEnd();
	 
	 //jalan putih
	glPushMatrix();
	for(int i = 100; i > -100; i = i - 20){
		glColor3f(1,1,1);
		glBegin(GL_QUADS);
			glVertex3f(-0.5,0.2,i);
			glVertex3f(-0.5,0.2,i-10);
			glVertex3f(0.5,0.2,i-10);
			glVertex3f(0.5,0.2,i);
		glEnd();
	}
	glPopMatrix();
	
}

//fungsi gambar pohon sebelum perempatan
void Pohon1() {
	// Batang pohon1

	glPushMatrix();
		glTranslatef(15, 4, -70);
		glColor3f(0.5f, 0.35f, 0.05f);
		glScalef(2,10,2);
		glutSolidCube(1);
	glPopMatrix();

	// Daun pohon1
	glPushMatrix();
		glTranslatef(15, 7, -70);
		glRotated(-90,1,0,0);
		glScalef(1,2,1);
		glColor3f(0.0f, 0.4f, 0.0f);
		glutSolidCone(3,8,5,5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(15, 12.5, -70);
		glRotated(-90,1,0,0);
		glScalef(1,2,1);
		glColor3f(0.0f, 0.45f, 0.0f);
		glutSolidCone(3,6,5,5);
	glPopMatrix();
	}
	
//fungsi gambar pohon setelah perempatan
void Pohon2() {
	// Batang pohon1
	glPushMatrix();
		glTranslatef(15 , 4, -70);
		glColor3f(0.5f, 0.35f, 0.05f);
		glScalef(2,10,2);
		glutSolidCube(1);
	glPopMatrix();

	// Daun pohon1
	glPushMatrix();
		glTranslatef(15, 7, -70);
		glRotated(-90,1,0,0);
		glScalef(1,2,1);
		glColor3f(0.0f, 0.4f, 0.0f);
		glutSolidCone(3,8,5,5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(15, 12.5, -70);
		glRotated(-90,1,0,0);
		glScalef(1,2,1);
		glColor3f(0.0f, 0.45f, 0.0f);
		glutSolidCone(3,6,5,5);
	glPopMatrix();
}

//fungsi gambar rumah
void rumah(){

//tembok
 glPushMatrix();
 glColor3f(0,0,0.5);
 glRotatef(50,0,1,0);
 glutSolidCube(3);

//pintu
glPushMatrix();
glColor3f(0.5,0.8,0);
glTranslatef(-0.6,-1,1.46);
glScalef(7,10,1);
glutSolidCube(0.1);
glPopMatrix();
//jendela
glPushMatrix();
glColor3f(0.5,0.8,0);
glTranslatef(0.5,0.1,1.46);
glScalef(3,3,1);
glutSolidCube(0.1);
glPopMatrix();

glPushMatrix();
glColor3f(0.5,0.8,0);
glTranslatef(0.9,0.1,1.46);
glScalef(3,3,1);
glutSolidCube(0.1);
glPopMatrix();

glPushMatrix();
glColor3f(0.5,0.8,0);
glTranslatef(0.9,-0.3,1.46);
glScalef(3,3,1);
glutSolidCube(0.1);
glPopMatrix();

glPushMatrix();
glColor3f(0.5,0.8,0);
glTranslatef(0.5,-0.3,1.46);
glScalef(3,3,1);
glutSolidCube(0.1);
glPopMatrix();
glPopMatrix();

//atap
 glPushMatrix();
 glColor3f(0.8,0,0);
 glRotatef(5,0,1,0);
 glTranslatef(0,1.5,0);
 glScalef(3,1.3,3);
 glutSolidOctahedron();
 glPopMatrix();

}

//fungsi untuk gambar kaca hotel dan nanti dipanggil di fungsi hotel
void kacahotel()
{
	//kaca	
	int l = 0;
	int m = 0;
	for (m=0; m<8; m++){
	for (l=0; l<5; l++){
	glColor3f(1,0,0);
	glPushMatrix();
	glTranslatef((-0.8+(l*0.4)),(-0.58+(0.2*m)),1.01);
	glScalef(0.2,0.1,0.001);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0,1,0);
	glPushMatrix();
	glTranslatef((-0.8+(l*0.4)),(-0.58+(0.2*m)),1);
	glScalef(0.22,0.12,0.001);
	glutSolidCube(1);
	glPopMatrix();
	
	//balkon
	glColor3f(0,0,1);
	glPushMatrix();
	glTranslatef((-0.8+(l*0.4)),(-0.62+(0.2*m)),1);
	glScalef(0.22,0.02,0.15);
	glutSolidCube(1);
	glPopMatrix();
	}
	}
}
//fungsi gambar hotel
void hotel1(){
	//bangunan hotel
	glColor3f(0.4, 0.0, 0.0);
	glPushMatrix();
	glutSolidCube(2);
	glPopMatrix();

	//pintu masuk
	glColor3f(0,1,0);
	glPushMatrix();
	glRotated(90,0,1,0);
	glTranslatef(0,-0.83,1);
	glScalef(0.8,0.24,0.001);
	glutSolidCube(1);
	glPopMatrix();

	//kaca		
	glPushMatrix();
	kacahotel();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90,0,1,0);
	kacahotel();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180,0,1,0);
	kacahotel();
	glPopMatrix();

	glPushMatrix();
	glRotatef(270,0,1,0);
	kacahotel();
	glPopMatrix();	
}

//fungsi gambar hotel
void hotel2(){
	//bangunan hotel
	glColor3f(0.4, 0.0, 0.0);
	glPushMatrix();
	glutSolidCube(2);
	glPopMatrix();

	//pintu masuk
	glColor3f(0,1,0);
	glPushMatrix();
	glRotated(90,0,1,0);
	glTranslatef(0,-0.83,1);
	glScalef(0.8,0.24,0.001);
	glutSolidCube(1);
	glPopMatrix();

	//kaca		
	glPushMatrix();
	kacahotel();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90,0,1,0);
	kacahotel();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180,0,1,0);
	kacahotel();
	glPopMatrix();

	glPushMatrix();
	glRotatef(270,0,1,0);
	kacahotel();
	glPopMatrix();	
}

//fungsi gambar masjid
void tempatibadah() {

     //atap atas
    glPushMatrix();
    glScaled(0.2, 0.2, 0.2);//untuk mengatur ukuran benda
    glTranslatef(0.0, 80, -10); //untuk mengatur koordinat 3d
    glRotated(225, 0, 1, 0);
    glRotated(90, 1, 0, 0);
    glColor3f(0.8, 0.52, 0.25);
    glutSolidCone(4.2, 4, 4, 1);
    glPopMatrix();

    //atap
    glPushMatrix();
    glScaled(1, 1.0, 1);//untuk mengatur ukuran benda
    glTranslatef(0.0, 12, -1.9); //untuk mengatur koordinat 3d
    glRotated(45, 0, 1, 0);
    glRotated(-90, 1, 0, 0);
    glColor3d(0.48, 0.46, 0.46);
    glutSolidCone(4.2, 4, 4, 1);
    glPopMatrix();

	//Dinding Kiri Atas
    glPushMatrix();
    glScalef(0.04, 0.4, 1); //untuk mengatur ukuran benda
    glTranslatef(-56, 29, -1.7); //untuk mengatur koordinat 3d
    glColor3f(0.4613, 0.4627, 0.4174);
    glutSolidCube(4.2f);
    glPopMatrix();


	//Dinding Kanan Atas
    glPushMatrix();
    glScaled(0.04, 0.4, 1);//untuk mengatur ukuran benda
    glTranslatef(56.0, 29, -1.7);//untuk mengatur koordinat 3d
    glColor3f(0.4613, 0.4627, 0.4174);
    glutSolidCube(4.2f);
    glPopMatrix();


  	//Dinding Belakang atas
    glPushMatrix();
    //glScaled(0.035, 0.5, 0.8);
    glScaled(0.95, 0.4, 0.075);//untuk mengatur ukuran benda
    glTranslatef(0, 29.5,-49);//untuk mengatur koordinat 3d
    glColor3f(0.4613, 0.4627, 0.4174);
    glutSolidCube(5.0);
    glPopMatrix();

  	//Dinding Depan atas
    glPushMatrix();
    glScaled(0.95, 0.4, 0.075);
    glTranslatef(0,29.5,2.3);
    glColor3f(0.4613, 0.4627, 0.4174);
    glutSolidCube(5.0);
    glPopMatrix();

    glPushMatrix();
    glScaled(1.5,1.5,1.5);
    glTranslatef(0,5.5, -1.15);
    glRotated(45, 0, 1, 0);
    glRotated(-90, 1, 0, 0);
    glColor3d(0.48, 0.46, 0.46);
    glutSolidCone(4.2, 4, 4, 1);
    glPopMatrix();
	
  
  	//Dinding Depan atas2
    glPushMatrix();
    glScaled(1.5, 0.3,1.5);
    glTranslatef(0,26,-1.1);
    glColor3f(0.4613, 0.4627, 0.4174);
    glutSolidCube(5.0);
    glPopMatrix();

    //atap 3
    glPushMatrix();
    glScaled(3,1.5,3);
    glTranslatef(0,5.-2.75, -0.53);
    glRotated(45, 0, 1, 0);
    glRotated(-90, 1, 0, 0);
    glColor3d(0.48, 0.46, 0.46);
    glutSolidCone(4.2, 4, 4,2);
    glPopMatrix();

    glPushMatrix();
    glScaled(3,1.5,3);
    glTranslatef(0,5.-2.75, -0.53);
    glRotated(45, 0, 1, 0);
    glRotated(-90, 1, 0, 0);
    glColor3d(0, 0, 0);
    glutWireCone(4.2, 4, 4, 40);
    glPopMatrix();

	//Dinding dasar
    glPushMatrix();
    glScaled(2.5, 0.6,2.5);
    glTranslatef(0,3,-1.2);
    glColor3f(0.95, 0.43, 0.0);
    glutSolidCube(5.0);
    glPopMatrix();
}

//fungsi untuk gambar koin
void Koin1(){
	glPushMatrix();
	glColor3f(1.0,1.0,0.0);
	glutSolidSphere(1,20,20);
	glPopMatrix();
}

void Koin2(){
	glPushMatrix();
	glColor3f(1.0,1.0,0.0);
	glTranslatef(0,0,10);
	glutSolidSphere(1,20,20);
	glPopMatrix();
}

void Koin3(){
	glPushMatrix();
	glColor3f(1.0,1.0,0.0);
	glTranslatef(0,0,20);
	glutSolidSphere(1,20,20);
	glPopMatrix();
}

void Koin4(){
	glPushMatrix();
	glColor3f(1.0,1.0,0.0);
	glTranslatef(0,0,30);
	glutSolidSphere(1,20,20);
	glPopMatrix();
}

void Koin5(){
	glPushMatrix();
	glColor3f(1.0,1.0,0.0);
	glTranslatef(0,0,40);
	glutSolidSphere(1,20,20);
	glPopMatrix();
}

void Koin6(){
	glPushMatrix();
	glColor3f(1.0,1.0,0.0);
	glTranslatef(0,0,60);
	glutSolidSphere(1,20,20);
	glPopMatrix();
}

void Koin7(){
	glPushMatrix();
	glColor3f(1.0,1.0,0.0);
	glTranslatef(0,0,70);
	glutSolidSphere(1,20,20);
	glPopMatrix();
}

void Koin8(){
	glPushMatrix();
	glColor3f(1.0,1.0,0.0);
	glTranslatef(0,0,80);
	glutSolidSphere(1,20,20);
	glPopMatrix();
}

void Koin9(){
	glPushMatrix();
	glColor3f(1.0,1.0,0.0);
	glTranslatef(0,0,90);
	glutSolidSphere(1,20,20);
	glPopMatrix();
}

//cek menyentuh dan apa yang terjadi jika truck menyentuh cone
void PergerakanTruck(){
	if(posXTruck<=-3&&posXTruck>=-8&&posZTruck==19){
			if(posZTruck>0){
				posZTruck -= 1;				
			}			
	}	
	else if(posXTruck<=-3&&posXTruck>=-8&&posZTruck==36){
		posZTruck +=1 ;
	}
}
//cek menyentuh antara koin dengan Truck dan apa yang terjadi jika menyentuh
void PergerakanKoin1(){
	if(posXTruck==posXKoin&&posZTruck==0){
		posYKoin1 = -5;
		if(skor<10){
			skor=skor+10;
		}
				
	}
}

void PergerakanKoin2(){
	if(posXTruck==posXKoin&&posZTruck==10){
		posYKoin2 = -5;
		if(skor<20){
			skor=skor+10;
		}
			
	}
}

void PergerakanKoin3(){
	if(posXTruck==posXKoin&&posZTruck==20){
		posYKoin3 = -5;
		if(skor<30){
			skor=skor+10;
		}
			
	}
}

void PergerakanKoin4(){
	if(posXTruck==posXKoin&&posZTruck==30){
		posYKoin4 = -5;
		if(skor<40){
			skor=skor+10;
		}		
	}
}

void PergerakanKoin5(){
	if(posXTruck==posXKoin&&posZTruck==40){
		posYKoin5 = -5;
		if(skor<50){
			skor=skor+10;
		}		
	}
}

void PergerakanKoin6(){
	if(posXTruck==posXKoin6&&posZTruck==60){
		posYKoin6 = -5;	
		if(skor==60){
			skor=skor+10;
		}	
	}
}

void PergerakanKoin7(){
	if(posXTruck==posXKoin7&&posZTruck==70){
		posYKoin7 = -5;	
		if(skor<70){
			skor=skor+10;
		}	
	}
}

void PergerakanKoin8(){
	if(posXTruck==posXKoin8&&posZTruck==80){
		posYKoin8 = -5;	
		if(skor<80){
			skor=skor+10;
		}	
	}
}

void PergerakanKoin9(){
	if(posXTruck==posXKoin9&&posZTruck==90){
		posYKoin9 = -5;	
		if(skor<90){
			skor=skor+10;
		}
		
	}
}



void renderBitmapString(float x,float y,float z,char *string) {
  char *c;

  glRasterPos3f(x, y,z);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
  }
}

void RenderScore() {
    char s[100];
    glPushMatrix();
    sprintf(s,"Score: %d", skor);
    glColor3f(1,1,1);
    renderBitmapString(5, 30, 0,s); //y axis inverted
    glPopMatrix();
}

void keyboard(unsigned char key, int x, int y) {
switch (key){
case 'w': rotAngleX += 2;  
break; 
case 's': rotAngleX -= 2;  
break;
case 'a': rotAngleY+= 2; 
break; 
case 'd': rotAngleY -= 2; 
break;
case 'q': rotAngleZ += 2; 
break; 
case 'e': rotAngleZ -= 2; 
break;  
case 'o': posZTruck += 1;
break;
case 'p': posZTruck -= 1;
break;
case 'r': posXTruck += 1;
break;
case 't': posXTruck -= 1;
break;
case 32:rotAngleX=rotAngleY=rotAngleZ=0;
posZTruck=-5;posXTruck = 0;
posXKoin = 3;posZKoin1 = 5;posYKoin1 =2;
posZKoin2 = 5;posYKoin2 =2;
posZKoin3 = 5;posYKoin3 =2;
posZKoin4 = 5;posYKoin4 =2;
posZKoin5 = 5;posYKoin5 =2;
posZKoin6 = 5;posYKoin6 =2;posXKoin6 = -3;
posZKoin7 = 5;posYKoin7 =2;posXKoin7 = -3;
posZKoin8 = 5;posYKoin8 =2;posXKoin8 = -3;
posZKoin9 = 5;posYKoin9 =2;posXKoin9 = -3;
skor=0;
break;
case 27: exit(0); 
default:break; 
}
glutPostRedisplay();
}
void objek(){
	//render Truck dan pergerakan Truck
	glPushMatrix();
		glTranslatef(0,0,-3);
//		glTranslatef(posXTruck,0,posZTruckBlkg);
		glTranslatef(posXTruck,0,posZTruck);
		PergerakanTruck();
		Truck();
	glPopMatrix();
	

	//render cone di jalan sebagai penghalang 
	glPushMatrix();
	glColor3f(0.5,0.25,0.25);
	glTranslatef(-5,1,20);
	glRotated(-90,1,0,0);
	glutSolidCone(2,5,4,4);
	glPopMatrix();
	
	//render koin dan pergerakan koin jika menyentuh truck
	glPushMatrix();
	glTranslatef(posXKoin,posYKoin1,posZKoin1);
	Koin1();
	PergerakanKoin1();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(posXKoin,posYKoin2,posZKoin2);
	Koin2();
	PergerakanKoin2();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(posXKoin,posYKoin3,posZKoin3);
	Koin3();
	PergerakanKoin3();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(posXKoin,posYKoin4,posZKoin4);
	Koin4();
	PergerakanKoin4();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(posXKoin,posYKoin5,posZKoin5);
	Koin5();
	PergerakanKoin5();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(posXKoin6,posYKoin6,posZKoin5);
	Koin6();
	PergerakanKoin6();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(posXKoin7,posYKoin7,posZKoin5);
	Koin7();
	PergerakanKoin7();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(posXKoin8,posYKoin8,posZKoin5);
	Koin8();
	PergerakanKoin8();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(posXKoin9,posYKoin9,posZKoin5);
	Koin9();
	PergerakanKoin9();
	glPopMatrix();
	
	//render pohon
	for(i=0;i<10;i=i+2){
		for(j=0;j<10;j=j+2){
		glPushMatrix();
			glTranslatef(0+(i*6),0,-17+(j*6));
			Pohon1();
		glPopMatrix();
		}
	}
	for(i=0;i<10;i=i+2){
		for(j=0;j<10;j=j+2){
		glPushMatrix();
			glTranslatef(0+(i*6),0,107+(j*6));
			Pohon2();
		glPopMatrix();
		}
	}
	
	//render hotel
	for(i=0;i<20;i=i+5){
	glPushMatrix();
		glScalef(5,10,5);
		glTranslatef(-3,1,3+i);
		hotel1();
	glPopMatrix();
	}
	
	for(i=0;i<15;i=i+5){
	glPushMatrix();
	glRotated(90,0,1,0);
		glScalef(5,10,5);
		glTranslatef(-3,1,-17+i);
		hotel2();
	glPopMatrix();
	}
	
	//render masjid
	glPushMatrix();
	glTranslatef(-30,-0.5,-30.5);
	glScalef(2,2,2);
	tempatibadah();
	glPopMatrix();	
	
	//render rumah setelah perempatan
	for(i=0;i<=12;i=i+2){
	glPushMatrix();
	glTranslatef(14.5+(i*6),3,13);
	glRotated(130,0,1,0);
	glScalef(2,2,2);
	rumah();
	glPopMatrix();
	}
	
	for(i=0;i<=12;i=i+2){
	glPushMatrix();
	glTranslatef(14.5+(i*6),3,25);
	glRotated(130,0,1,0);
	glScalef(2,2,2);
	rumah();
	glPopMatrix();
	}
	
	//render rumah sebelum perempatan
	for(i=0;i<=12;i=i+2){
	glPushMatrix();
	glTranslatef(14.5+(i*6),3,-13);
	glRotated(-50,0,1,0);
	glScalef(2,2,2);
	rumah();
	glPopMatrix();
	}
	
	for(i=0;i<=12;i=i+2){
	glPushMatrix();
	glTranslatef(14.5+(i*6),3,-25);
	glRotated(-50,0,1,0);
	glScalef(2,2,2);
	rumah();
	glPopMatrix();
	}
}


void display() { 
// Kalau move dan angle tidak nol, gerakkan kamera... 
if (deltaMove) moveMeFlat(deltaMove); 
if (deltaAngle) {
 angle += deltaAngle; 
 orientMe(angle); 
 } 
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 glClearColor(0.5, 1.0, 1.0, 0.0);
 // Gambar grid 
 //Grid(); 
 // Gambar objek di sini... 
glPushMatrix();
	glRotated(rotAngleX, 1, 0, 0);  
	glRotated(rotAngleY, 0, 1, 0);
	glRotated(rotAngleZ, 0, 0, 1); 
 	objek();
 	tambahan();
glPopMatrix();
 RenderScore();
 glutSwapBuffers(); 
 glFlush(); 
 } 
void pressKey(int key, int x, int y) { 
// Fungsi ini akan dijalankan saat tombol keyboard ditekan dan belum dilepas 
// Selama tombol ditekan, variabel angle dan move diubah => kamera bergerak 
switch (key) { 
	case GLUT_KEY_LEFT : deltaAngle = -0.01f;
 	break; 
	case GLUT_KEY_RIGHT : deltaAngle = 0.01f;
	break; 
 	case GLUT_KEY_UP : deltaMove = 1;
 	break; 
 	case GLUT_KEY_DOWN : deltaMove = -1;
 	break; 
 	} 
 } 
void releaseKey(int key, int x, int y) { 
// Fungsi ini akan dijalankan saat tekanan tombol keyboard dilepas
// Saat tombol dilepas, variabel angle dan move diset nol =>kamera berhenti 
switch (key) { 
	case GLUT_KEY_LEFT : if (deltaAngle < 0.0f) deltaAngle = 0.0f; 
	break; 
	case GLUT_KEY_RIGHT : if (deltaAngle > 0.0f) deltaAngle = 0.0f; 
	break; 
	case GLUT_KEY_UP : if (deltaMove > 0) deltaMove = 0; 
	break; 
	case GLUT_KEY_DOWN : if (deltaMove < 0) deltaMove = 0; 
	break; 
	} 
} 
// Variable untuk pencahayaan 
const GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 0.0f }; 
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
const GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f }; 
const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f }; 
const GLfloat mat_diffuse[]= { 0.8f, 0.8f, 0.8f, 1.0f }; 
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
const GLfloat high_shininess[] = { 100.0f };
 
void lighting(){ 
// Fungsi mengaktifkan pencahayaan 
glEnable(GL_DEPTH_TEST); 
glDepthFunc(GL_LESS); 
glEnable(GL_LIGHT0); 
glEnable(GL_NORMALIZE); 
glEnable(GL_COLOR_MATERIAL); 
glEnable(GL_LIGHTING); 
glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient); 
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); 
glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); 
glLightfv(GL_LIGHT0, GL_POSITION, light_position); 
glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); 
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); 
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); 
glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess); 
} 

void init(void) { 
glEnable (GL_DEPTH_TEST); 
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
} 

int main(int argc, char **argv) { 
glutInit(&argc, argv); 
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);//untuk menggambar 3d
glutInitWindowPosition(100,100); 
glutInitWindowSize(640,480); 
glutCreateWindow("Game Truck"); 
//glutIgnoreKeyRepeat(1);  // Mengabaikan key repeat (saat tombol keyboard dipencet terus) 
glutSpecialFunc(pressKey);
glutSpecialUpFunc(releaseKey); 
glutDisplayFunc(display);
glutKeyboardFunc(keyboard); 
glutIdleFunc(display); // Fungsi display-nya dipanggil terus-menerus 
glutReshapeFunc(Reshape); 
lighting(); 
init(); 
glutMainLoop(); 
return(0); 
}
