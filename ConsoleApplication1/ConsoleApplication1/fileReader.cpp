#define _CRT_SECURE_NO_WARNINGS

#include "filereader.h"

#include <iostream>
#include <string.h>

void loadOBJ(std::string path, Mesh &outMesh) {
    std::cout << "Loading OBJ file from '" << path << "'..." << std::endl;

    Mesh mesh;
    FILE* file = fopen(path.c_str(), "r");

    if (file == NULL) {
        printf("Impossible to open the file!\n");
        return;
    }

    while (true) {
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);

        if (res == EOF) {
            break;
        }

        if (strcmp(lineHeader, "v") == 0) {
            Vector3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            mesh.vertices.push_back(vertex);
        } else if (strcmp(lineHeader, "vt") == 0) {
            Vector2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            mesh.uvs.push_back(uv);
        } else if (strcmp(lineHeader, "vn") == 0) {
            Vector3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            mesh.normals.push_back(normal);
        } else if (strcmp(lineHeader, "f") == 0) {
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );

            if (matches != 9) {
                printf("File can't be read. Try exporting with other options\n");
                return;
            }

            Face face;

            for (int i = 0; i < 3; i++) {
                face.vertices.push_back(vertexIndex[i] - 1);
                face.uvs.push_back(uvIndex[i] - 1);
                face.normals.push_back(normalIndex[i] - 1);
            }

            mesh.faces.push_back(face);
        } else {
            char commentBuffer[1000];
            fgets(commentBuffer, 1000, file);
        }
    }

    std::cout << "File loaded successfully." << std::endl;

    fclose(file);
    outMesh = mesh;
}
