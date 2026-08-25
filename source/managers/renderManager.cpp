// #include "renderManager.h"

// #include "renderTransform.h"
// #include "meshFactory.h"

// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>



// RenderManager::RenderManager()
// { }

// void RenderManager::init()
// {
//     glEnable(GL_DEPTH_TEST);
//     glDepthFunc(GL_LEQUAL);

//     // glEnable(GL_CULL_FACE);
//     // glCullFace(GL_BACK);
//     // glFrontFace(GL_CCW);

//     if(!shaderManager.load(
//         "../shaders/basic.vert",
//         "../shaders/basic.frag"))
//     {
//         std::cout << "Shader failed!\n";
//         return;
//     }

//     camera.init(
//         640,
//         360
//     );

//     fillMeshMap();
// }



// void RenderManager::beginFrame()
// {

//     glClear(
//         GL_COLOR_BUFFER_BIT |
//         GL_DEPTH_BUFFER_BIT
//     );

//     camera.update( { 0, 0, 0 } );

//     shaderManager.bind();

//     // for(int r=0;r<4;r++)
//     // {
//     //     std::cout
//     //         << camera.getView()[0][r] << " "
//     //         << camera.getView()[1][r] << " "
//     //         << camera.getView()[2][r] << " "
//     //         << camera.getView()[3][r]
//     //         << "\n";
//     // }

//     shaderManager.setMat4(
//     "uProjection",
//     camera.getProjection()
//     );

//     shaderManager.setMat4(
//         "uView",
//         camera.getView()
//     );
// }



// void RenderManager::draw( const std::vector<GameObject*>& objects )
// {

//     for(GameObject* object : objects)
//     {

//         //bail if obj is null
//         if( !object )
//             continue;

//         //get obj render def
//         const RenderDefinition& render =
//             object->getRenderDefinition();

//         //make temp mesh ptr using obj's renderdef.meshtype
//         Mesh* mesh = findMapObject( meshMap, render.meshType );

//         //bail is mesh is null
//         if ( !mesh )
//             continue;

//         //create render transform using objs pos and size
//         RenderTransform transform =
//             createRenderTransform(
//                 object->getPosition(),
//                 object->getSize()
//             );

//         // [ debug print transforms pos & size ] ------------------------------

//         std::cout
//         << "Position: "
//         << transform.position.x << " "
//         << transform.position.y << " "
//         << transform.position.z
//         << "\n";

//         std::cout
//         << "Scale: "
//         << transform.scale.x << " "
//         << transform.scale.y << " "
//         << transform.scale.z
//         << "\n";

//         // -------------------------------------------------------------------

//         glm::mat4 model(1.0f);

//         model =
//             glm::translate(
//                 model,
//                 transform.position
//             );

//         // model =
//         //     glm::scale(
//         //         model,
//         //         transform.scale
//         //     );

//         model =
//         glm::scale(
//             model,
//             glm::vec3(20,20,20)
//         );

//         shaderManager.setMat4(
//             "uModel",
//             model
//         );

//         mesh->draw();
//     }
// }



// void RenderManager::endFrame()
// {

// }

// void RenderManager::fillMeshMap()
// {
//     float radius = 0.5;
//     float height = 0.5;
    
//     //sprite quad: meshMap.emplace ( MeshType::TRIANGLE, MeshFactory::createNgonPrism( 3, radius, height ) );
//     meshMap.emplace ( MeshType::TRIANGLE, MeshFactory::createNgonPrism( 3, radius, height ) );
//     meshMap.emplace ( MeshType::CUBE, MeshFactory::createNgonPrism( 4, radius, height ) );
//     meshMap.emplace ( MeshType::PENTAGON, MeshFactory::createNgonPrism( 5, radius, height ) );
//     meshMap.emplace ( MeshType::HEXAGON, MeshFactory::createNgonPrism( 6, radius, height ) );
//     meshMap.emplace ( MeshType::SEPTAGON, MeshFactory::createNgonPrism( 7, radius, height ) );
//     meshMap.emplace ( MeshType::OCTAGON, MeshFactory::createNgonPrism( 8, radius, height ) );
//     meshMap.emplace ( MeshType::NONAGON, MeshFactory::createNgonPrism( 9, radius, height ) );
//     meshMap.emplace ( MeshType::DECAGON, MeshFactory::createNgonPrism( 10, radius, height ) );
//     meshMap.emplace ( MeshType::HENDECAGON, MeshFactory::createNgonPrism( 11, radius, height ) );
//     meshMap.emplace ( MeshType::DODECAGON, MeshFactory::createNgonPrism( 12, radius, height ) );
// }
