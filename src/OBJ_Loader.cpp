//
//  OBJ_Loader.cpp
//  TunnelRun
//
//  Created by Jas S on 2016-12-21.
//  Copyright © 2016 Jas S. All rights reserved.
//

#include "OBJ_Loader.h"

OBJ_Loader::OBJ_Loader(const char* obj_path, OBJ_Format format)
{
    if(!this->read_objects(obj_path, format)) throw -1;
}

bool OBJ_Loader::read_objects(const char* path, OBJ_Format format)
{
    FILE* file = File::open(path, "r");

    char buffer[256];
    while(true)
    {
        if(fscanf(file, "%s", buffer) == EOF) break;

        if(strcmp(buffer, "v") == 0) {
            glm::vec3 v;
            fscanf(file, "%f %f %f\n", &v[0], &v[1], &v[2]);
            this->vertices.push_back(v);
        }
        else if(strcmp(buffer, "vn") == 0) {
            glm::vec3 v;
            fscanf(file, "%f %f %f\n", &v[0], &v[1], &v[2]);
            this->normals.push_back(v);
        }
        else if(strcmp(buffer, "vt") == 0) {
            glm::vec2 v;
            fscanf(file, "%f %f\n", &v[0], &v[1]);
            this->uvs.push_back(v);
        }
        else if(strcmp(buffer, "f") == 0)
		{
            glm::uvec3 v[3] = {glm::uvec3(0), glm::uvec3(0), glm::uvec3(0)};
			switch (format)
			{
				case V:
					fscanf(file, "%u %u %u\n", &v[0][0], &v[1][0], &v[2][0]);
					break;
				case VN:
					fscanf(file, "%u//%u %u//%u %u//%u\n",
						&v[0][0], &v[0][2],
						&v[1][0], &v[1][2],
						&v[2][0], &v[2][2]);
					break;
				case VNT:
					fscanf(file, "%u/%u/%u %u/%u/%u %u/%u/%u\n",
						&v[0][0], &v[0][1], &v[0][2],
						&v[1][0], &v[1][1], &v[1][2],
						&v[2][0], &v[2][1], &v[2][2]);
					break;
				default:
					puts("OBJ_Loader unknown format.");
					throw -1;
			}

            this->indices.push_back(v[0]);
            this->indices.push_back(v[1]);
            this->indices.push_back(v[2]);
        }
        else fgets(buffer, 256, file);
    }

    fclose(file);

    return true;
}
