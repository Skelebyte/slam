#include "mesh.hpp"
#include "vertex.hpp"
#include <unordered_map>

using namespace slam;
using namespace slam::math;
using namespace slam::res;
using namespace slam::err;
using namespace slam::util;

Mesh::Mesh(const str &path, bool blenderFix) {
  vertices = List<Vertex>();
  indices = List<u32>();
  data = List<f32>();

  if (File::Exists(path) == false) {
    THROW_ERROR(ERROR.Derived("", "File " + path + " does not exist!"));
    return;
  }

  ufbx_error error;
  ufbx_load_opts opts = {};
  // opts.target_faces
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
      ufbx_mesh *fbx_mesh = node->mesh;

      u32 vertCount = 0;
      for (ufbx_face face : fbx_mesh->faces) {
        for (u32 tri = 1; tri + 1 < face.num_indices; tri++) {
          u32 corners[3] = {face.index_begin, face.index_begin + tri,
                            face.index_begin + tri + 1};
          for (u32 index : corners) {
            Vec3 pos = Vec3();
            if (blenderFix) {
              pos = Vec3(fbx_mesh->vertex_position[index].x,
                         fbx_mesh->vertex_position[index].z,
                         -fbx_mesh->vertex_position[index].y);
            } else {
              pos = Vec3(fbx_mesh->vertex_position[index].x,
                         fbx_mesh->vertex_position[index].y,
                         fbx_mesh->vertex_position[index].z);
            }
            Vec2 uv = Vec2(fbx_mesh->vertex_uv[index].x,
                           fbx_mesh->vertex_uv[index].y);
            Vec3 norm = Vec3(fbx_mesh->vertex_normal[index].x,
                             fbx_mesh->vertex_normal[index].z,
                             -fbx_mesh->vertex_normal[index].y);
            vertices.Add(Vertex(pos, uv, norm));
            indices.Add(vertCount++);
            data.Add(pos.x);
            data.Add(pos.y);
            data.Add(pos.z);
            data.Add(uv.x);
            data.Add(uv.y);
            data.Add(norm.x);
            data.Add(norm.y);
            data.Add(norm.z);
          }
        }
      }
    }
  }

  ufbx_free_scene(scene);
}

Mesh Mesh::GeneratePlane(u32 divisions, const Vec2 &dimensions) {
  Vec2 planeDimensions;

  if (divisions == 0)
    divisions = 1;

  if (dimensions == Vec2(0.0f)) {
    planeDimensions = Vec2(1.0f);
  } else {
    planeDimensions = dimensions;
  }

  Mesh mesh;

  f32 triangleSideX = planeDimensions.x / divisions;
  f32 triangleSideY = planeDimensions.y / divisions;

  for (u32 row = 0; row <= divisions;
       row++) { // possibly may need to use divisions + 1
    for (u32 col = 0; col <= divisions;
         col++) { // possibly may need to use divisions + 1

      if (row < divisions && col < divisions) {
        u32 index = row * (divisions + 1) + col;

        // top triangle
        mesh.indices.Add(index);
        mesh.indices.Add(index + 1);
        mesh.indices.Add(index + (divisions + 1));

        // bottom triangle
        mesh.indices.Add(index + 1);
        mesh.indices.Add(index + (divisions + 1) + 1);
        mesh.indices.Add(index + (divisions + 1));
      }

      Vec3 pos = Vec3((col * triangleSideX) - dimensions.x / 2, 0.0f,
                      (row * -triangleSideY) + dimensions.y / 2);
      Vec2 uv = Vec2((f32)col / divisions, (f32)row / divisions);
      Vec3 normal = Vec3(0, 1, 0);
      mesh.vertices.Add(Vertex(pos, uv, normal));

      mesh.data.Add(pos.x);
      mesh.data.Add(pos.y);
      mesh.data.Add(pos.z);
      mesh.data.Add(uv.x);
      mesh.data.Add(uv.y);
      mesh.data.Add(normal.x);
      mesh.data.Add(normal.y);
      mesh.data.Add(normal.z);
    }
  }

  return mesh;
}