// #pragma once


// #include <vector>
// #include <unordered_map>

// #include <glad/glad.h>

// #include <glm/glm.hpp>


// #include "shaderLoader.h"
// #include "camera.h"
// #include "mesh.h"
// #include "gameObject.h"


// class RenderManager
// {

// public:

//     RenderManager();

//     void init();
//     void beginFrame();
//     void draw( const std::vector<GameObject*>& objects );
//     void endFrame();

//     void fillMeshMap();
//     const std::unordered_map < MeshType, Mesh >& getMeshMap() const { return meshMap; }

// private:

//     ShaderLoader shaderManager;

//     Camera camera;

//     std::unordered_map < MeshType, Mesh > meshMap;
// };