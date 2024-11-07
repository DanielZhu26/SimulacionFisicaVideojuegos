#include "GravityForceGenerator.h"

void GravityForceGenerator::applyForce(Particle& particle) {
    // Calculamos la fuerza de gravedad: F = m * g
    Vector3D<> gravityForce = gravity * particle.getMass();  // Multiplicamos la gravedad por la masa de la partícula
    particle.setAccel(gravityForce);  // Aplicamos la aceleración calculada
}

