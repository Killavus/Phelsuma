#include "WorldObject3D.h"

void WorldObject3D::draw() const {
  model.prepareToDraw();
  
  for (ShaderProgram& program : model.currentDrawingPipeline()) {
    program.use();
    program.uniformMat44f("model", worldTransform);
    model.rawData().indexed() ? glDrawElements(GL_TRIANGLES, model.rawData().drawCount(), GL_UNSIGNED_INT, (GLvoid*)0) : glDrawArrays(GL_TRIANGLES, 0, model.rawData().drawCount());
  }
}