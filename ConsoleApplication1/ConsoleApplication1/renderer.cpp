#include "renderer.h"

#include <GL/glut.h>

void render(const Mesh &mesh) {
    for (Face face : mesh.faces) {
        glColor3f(face.rColor, face.gColor, face.bColor);

        for (int i = 0; i < face.vertices.size(); i++) {
            Vector3 currentVertice = mesh.vertices[face.vertices[i]];
            glVertex3f(currentVertice.x, currentVertice.y, currentVertice.z);
        }
    }
}
