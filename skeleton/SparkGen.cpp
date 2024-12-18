#include "SparkGen.h"

SparkGen::SparkGen(Vector3D<> pos, float force, ParticleSystem* sysS, float lifetime) :
    Fuente(pos, Vector3D<>(0, 1, 0), 0, 0, 0, sysS, lifetime), force(force)
{
    explosionTriggered = false;
    explosionHeight = 0; // Altura de explosión basada en la fuerza.
}

SparkGen::~SparkGen()
{
}

void SparkGen::ParticleGen()
{
    if (!explosionTriggered) {
        // Movimiento inicial hacia arriba.
        Vector3D<> upwardVel(0, 10.0f, 0); // Velocidad hacia arriba.
        systemRef->addParticle(position, upwardVel, 1, PxGeometryType::Enum::eSPHERE, 0.5, PxVec4(1.0, 1.0, 0.0, 1.0));

        // Verifica si se ha alcanzado la altura de explosión.
        if (position.y >= explosionHeight) {
            explosionTriggered = true;
        }
    }
    else {
        // Genera partículas en una explosión radial.
        for (int i = 0; i < force; i++) {
            Vector3D<> rndVel(
                (rnd() % 200 - 100) / 100.0f, // Velocidad X aleatoria.
                (rnd() % 200 - 100) / 100.0f, // Velocidad Y aleatoria.
                (rnd() % 200 - 100) / 100.0f  // Velocidad Z aleatoria.
            );
            rndVel = rndVel.GetNormalized() * force; // Normaliza y escala la velocidad.

            // Colores cambiantes para simular brillo.
            PxVec4 color(
                rnd() % 100 / 100.0f, // Rojo.
                rnd() % 100 / 100.0f, // Verde.
                rnd() % 100 / 100.0f, // Azul.
                1.0f                  // Opacidad.
            );

            // Agrega las partículas al sistema.
            systemRef->addParticle(CalcRndPos(), rndVel, 1, PxGeometryType::Enum::eSPHERE, 0.3, color);
        }
    }
}

Vector3D<> SparkGen::CalcRndPos()
{
    if (!explosionTriggered) {
        // Mientras sube, la posición es fija.
        return Vector3D<>(position.x, position.y += 0.5f, position.z); // Incrementa altura.
    }
    else {
        // Durante la explosión, genera posiciones alrededor del centro.
        std::uniform_real_distribution<> uni_dist(-1, 1);
        float x = uni_dist(rnd) * force;
        float y = uni_dist(rnd) * force;
        float z = uni_dist(rnd) * force;

        return Vector3D<>(x + position.x, y + position.y, z + position.z);
    }
}
