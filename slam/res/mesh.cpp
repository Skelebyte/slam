#include "mesh.hpp"

using namespace slam;
using namespace slam::math;
using namespace slam::res;
using namespace slam::err;
using namespace slam::util;

Mesh::Mesh(sString path) {
  vertices = List<Vertex>();
  indices = List<sUint>();
  data = List<float>();

  if (File::Exists(path) == false) {
    THROW_ERROR(ERROR.Derived("", "File " + path + " does not exist!"));
    return;
  }

  ufbx_error error;
  ufbx_scene *scene = ufbx_load_file(path.c_str(), NULL, &error);
  if (!scene) {
    THROW_ERROR(
        ERROR.Derived("", "Failed to load FBX scene from path `" + path +
                              "`. UFBX error: " + error.description.data));
    return;
  }

  for (ufbx_node *node : scene->nodes) {
    if (node->is_root == true)
      continue;

    if (node->mesh) {
      for (uint i = 0; i < node->mesh->num_vertices; i++) {
        Vec3 pos = Vec3(node->mesh->vertex_position[i].x,
                        node->mesh->vertex_position[i].y,
                        node->mesh->vertex_position[i].z);
        Vec2 uv = Vec2(node->mesh->vertex_uv[i].x, node->mesh->vertex_uv[i].y);
        Vec3 norm =
            Vec3(node->mesh->vertex_normal[i].x, node->mesh->vertex_normal[i].y,
                 node->mesh->vertex_normal[i].z);
        this->vertices.Add(Vertex(pos, uv, norm));
      }
      for (uint i = 0; i < node->mesh->num_indices; i++) {
        this->indices.Add(node->mesh->vertex_indices[i]);
      }
    }
  }

  for (int i = 0; i < vertices.Size(); i++) {
    data.Add(vertices[i].position.x);
    data.Add(vertices[i].position.y);
    data.Add(vertices[i].position.z);
    data.Add(vertices[i].uv.x);
    data.Add(vertices[i].uv.y);
    data.Add(vertices[i].normal.x);
    data.Add(vertices[i].normal.y);
    data.Add(vertices[i].normal.z);
  }
}