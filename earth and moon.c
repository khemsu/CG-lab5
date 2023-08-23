#include <GL/glut.h>
#include <math.h>

// Global variables
float angle = 0.0f;      // Angle of moon's position
float orbitRadius = 100.0f;  // Radius of moon's orbit

// Initialization function
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250);
    glMatrixMode(GL_MODELVIEW);
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw Earth
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0, 0.0);
    for (int i = 0; i <= 360; i++) {
        float angleRad = i * M_PI / 180.0;
        float x = 20 * cos(angleRad);
        float y = 20 * sin(angleRad);
        glVertex2f(x, y);
    }
    glEnd();

    // Calculate moon's position
    float moonX = orbitRadius * cos(angle);
    float moonY = orbitRadius * sin(angle);

    // Draw Moon
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(moonX, moonY);
    for (int i = 0; i <= 360; i++) {
        float angleRad = i * M_PI / 180.0;
        float x = moonX + 8 * cos(angleRad);
        float y = moonY + 8 * sin(angleRad);
        glVertex2f(x, y);
    }
    glEnd();

    // Draw moon's orbit
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float angleRad = i * M_PI / 180.0;
        float x = orbitRadius * cos(angleRad);
        float y = orbitRadius * sin(angleRad);
        glVertex2f(x, y);
    }
    glEnd();

    glutSwapBuffers();
}

// Animation update function
void update(int value) {
    angle += 0.01;  // Increment the angle for moon's position
    if (angle > 360.0) {
        angle -= 360.0;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);  // Schedule the next update
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Moon Orbit Animation");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}

