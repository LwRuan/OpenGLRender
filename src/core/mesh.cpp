#include "mesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <iostream>

namespace ORTR{

bool Mesh::loadFromFile(const std::string& filename){
    name = filename;
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn;
    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials,
        &warn, &err, filename.c_str(), 0, true);

    if(!ret){
        std::cerr << "[Renderer]Unable to load model" << std::endl;
        return false;
    }

    for (size_t s = 0; s<shapes.size(); ++s){
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); ++f){
            int fv = shapes[s].mesh.num_face_vertices[f];
            for (size_t v = 0; v < fv; ++v){
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
                tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
                tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
                tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
                tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
                tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];

                tinyobj::real_t tx, ty;

                if (!attrib.texcoords.empty())
                {
                    tx = attrib.texcoords[2 * idx.texcoord_index + 0];
                    ty = attrib.texcoords[2 * idx.texcoord_index + 1];
                }
                else
                {
                    tx = ty = 0;
                }

                verticesUVX.push_back(vec4(vx, vy, vz, tx));
                normalsUVY.push_back(vec4(nx, ny, nz, ty));
            }

            index_offset += fv;
        }
    }

    return true;
}
};
