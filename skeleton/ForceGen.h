#pragma once
#include "Particle.h"

class ForceGen {
public:
    virtual ~ForceGen();
    virtual void applyForce(Particle& particle) = 0; // Método que se debe implementar en cada generador de fuerza
};