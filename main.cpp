#include "GL/freeglut.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "vecmath.h"
using namespace std;

// Globals

// This is the list of points (3D vectors)
vector<Vector3f> vecv;

// This is the list of normals (also 3D vectors)
vector<Vector3f> vecn;

// This is the list of faces (indices into vecv and vecn)
vector<vector<unsigned> > vecf;


// You will need more global variables to implement color and position changes
int colorI = 0;
GLfloat translate[] = {0.f, 0.f};

// These are convenience functions which allow us to call OpenGL 
// methods on Vec3d objects
// inline void glVertex(const Vector3f &a) 
// { glVertex3fv(a); }

// inline void glNormal(const Vector3f &a) 
// { glNormal3fv(a); }


// This function is called whenever a "Normal" key press is received.
void keyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 27: // Escape key
        exit(0);
        break;
    case 'c':
        // add code to change color here
        colorI++;
        if (colorI >= 4) colorI = 0;
		//cout << "Unhandled key press " << key << "." << endl; 
        break;
    default:
        cout << "Unhandled key press " << key << "." << endl;        
    }

	// this will refresh the screen so that the user sees the color change
    glutPostRedisplay();
}

// This function is called whenever a "Special" key press is received.
// Right now, it's handling the arrow keys.
void specialFunc( int key, int x, int y )
{
    switch ( key )
    {
    case GLUT_KEY_UP:
        // add code to change light position
        translate[1] += 0.5f;
		//cout << "Unhandled key press: up arrow." << endl;
		break;
    case GLUT_KEY_DOWN:
        // add code to change light position
        translate[1] -= 0.5f;
		//cout << "Unhandled key press: down arrow." << endl;
		break;
    case GLUT_KEY_LEFT:
        // add code to change light position
        translate[0] -= 0.5f;
		//cout << "Unhandled key press: left arrow." << endl;
		break;
    case GLUT_KEY_RIGHT:
        // add code to change light position
        translate[0] += 0.5f;
		//cout << "Unhandled key press: right arrow." << endl;
		break;
    }

	// this will refresh the screen so that the user sees the light position
    glutPostRedisplay();
}

// Draw a custom OBJ that was loaded into vectors
void drawCustomObj() {
    glBegin(GL_TRIANGLES); // draws triangle(s)
    for (unsigned int i = 0; i < vecf.size(); i++) { // for each face
        vector<unsigned> idxs = vecf[i];
        unsigned a = idxs[0];
        unsigned c = idxs[1];
        unsigned d = idxs[2];
        unsigned f = idxs[3];
        unsigned g = idxs[4];
        unsigned ii = idxs[5];
        
        // Order matters! CCW!
        glNormal3d(vecn[c - 1][0], vecn[c - 1][1], vecn[c - 1][2]);
        glNormal3d(vecn[f - 1][0], vecn[f - 1][1], vecn[f - 1][2]);
        glNormal3d(vecn[ii - 1][0], vecn[ii - 1][1], vecn[ii - 1][2]);

        glVertex3d(vecv[a - 1][0], vecv[a - 1][1], vecv[a - 1][2]);
        glVertex3d(vecv[d - 1][0], vecv[d - 1][1], vecv[d - 1][2]);
        glVertex3d(vecv[g - 1][0], vecv[g - 1][1], vecv[g - 1][2]);
    }
    glEnd();
}

// This function is responsible for displaying the object.
void drawScene(void)
{
    int i;

    // Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rotate the image
    glMatrixMode( GL_MODELVIEW );  // Current matrix affects objects positions
    glLoadIdentity();              // Initialize to the identity

    // Position the camera at [0,0,5], looking at [0,0,0],
    // with [0,1,0] as the up direction.
    gluLookAt(0.0, 0.0, 5.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // Set material properties of object

	// Here are some colors you might use - feel free to add more
    GLfloat diffColors[4][4] = { {0.5, 0.5, 0.9, 1.0},
                                 {0.9, 0.5, 0.5, 1.0},
                                 {0.5, 0.9, 0.3, 1.0},
                                 {0.3, 0.8, 0.9, 1.0} };
    
	// Here we use the first color entry as the diffuse color
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffColors[colorI]);

	// Define specular color and shininess
    GLfloat specColor[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat shininess[] = {100.0};

	// Note that the specular color and shininess can stay constant
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  
    // Set light properties

    // Light color (RGBA)
    GLfloat Lt0diff[] = {1.0,1.0,1.0,1.0};
    // Light position
	GLfloat Lt0pos[] = {1.0f, 1.0f, 5.0f, 1.0f};
    Lt0pos[0] += translate[0];
    Lt0pos[1] += translate[1];

    glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
    glLightfv(GL_LIGHT0, GL_POSITION, Lt0pos);

	// This GLUT method draws a teapot.  You should replace
	// it with code which draws the object you loaded.
	// glutSolidTeapot(1.0);
    drawCustomObj();

    // Dump the image to the screen.
    glutSwapBuffers();
}

// Initialize OpenGL's rendering modes
void initRendering()
{
    glEnable(GL_DEPTH_TEST);   // Depth testing must be turned on
    glEnable(GL_LIGHTING);     // Enable lighting calculations
    glEnable(GL_LIGHT0);       // Turn on light #0.
}

// Called when the window is resized
// w, h - width and height of the window in pixels.
void reshapeFunc(int w, int h)
{
    // Always use the largest square viewport possible
    if (w > h) {
        glViewport((w - h) / 2, 0, h, h);
    } else {
        glViewport(0, (h - w) / 2, w, w);
    }

    // Set up a perspective view, with square aspect ratio
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 50 degree fov, uniform aspect ratio, near = 1, far = 100
    gluPerspective(50.0, 1.0, 1.0, 100.0);
}


// Parse a line
void parseLine(stringstream &ss) {
    string s;
    ss >> s;

    if (s == "v") {
        Vector3f v;
        ss >> v[0] >> v[1] >> v[2];
        vecv.push_back(v);
    }
    else if (s == "vn") {
        Vector3f vn;
        ss >> vn[0] >> vn[1] >> vn[2];
        vecn.push_back(vn);
    }
    else if (s == "f") {
        // Assuming a face is described by 3 vertices
        vector<unsigned> f; // [a, c, d, f, ...]

        for (int i = 0; i < 3; i++) {
            string faceString;
            ss >> faceString; // (a/b/c, d/e/f, ...)

            stringstream faceSS(faceString);
            string idx; // (a, c, ...)

            int j = 0;
            while (getline(faceSS, idx, '/')) {
                if (j != 1) f.push_back(stoi(idx));
                j += 1;
            }
        }

        vecf.push_back(f);
    }
}

bool loadFile(char* filename) {
    ifstream myfile(filename);
    
    if (myfile.is_open()) {
        string buffer;

        while (getline(myfile, buffer)) {
            stringstream ss(buffer);
            parseLine(ss);
        }
        myfile.close();

        return true;
    } else {
        std::cout << "File could not be opened!\n";
    }

    return false;
}

// Main routine.
// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char** argv )
{
    if (argc != 2) {
        std::cout << "Usage: a0 <path to OBJ file>\n";
        return -1;
    }
    loadFile(argv[1]);

    glutInit(&argc,argv);

    // We're going to animate it, so double buffer 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    // Initial parameters for window position and size
    glutInitWindowPosition( 60, 60 );
    glutInitWindowSize( 360, 360 );
    glutCreateWindow("Assignment 0");

    // Initialize OpenGL parameters.
    initRendering();

    // Set up callback functions for key presses
    glutKeyboardFunc(keyboardFunc); // Handles "normal" ascii symbols
    glutSpecialFunc(specialFunc);   // Handles "special" keyboard keys

     // Set up the callback function for resizing windows
    glutReshapeFunc( reshapeFunc );

    // Call this whenever window needs redrawing
    glutDisplayFunc( drawScene );

    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop( );

    return 0;	// This line is never reached.
}
