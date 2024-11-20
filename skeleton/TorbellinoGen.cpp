#include "TorbellinoGen.h"

TorbellinoGen::TorbellinoGen(float force, float friction, Vector3D<> pos, float range):
	WindForceGen(force, friction, pos, range)
{}

void TorbellinoGen::updateF(Particle* p, double t)
{
	Vector3D<> partPOs = p->getPos();
	if (onRange(partPOs)) 
	{
        Vector3D<> toCentre = position - partPOs; // Vector hacia el centro del torbellino
        float distance = toCentre.getMagnitude();

        // Evitar problemas cerca del centro
        if (distance < 1.0f)
            distance = 1.0f;

        // Dirección de la fuerza circular (plano XZ)
        Vector3D<> circularForceDir(-toCentre.z, 0, toCentre.x);
        circularForceDir.GetNormalized();

        // Fuerza circular proporcional a la distancia (menor fuerza si están lejos)
        float circularStrength = windF * (1.0f - (distance / range));
        Vector3D<> circularForce = circularForceDir * circularStrength;

        // Fuerza hacia el centro
        float centripetalStrength = windF * 0.5f; // Ajusta el peso de la atracción al centro
        Vector3D<> centripetalForce = toCentre.GetNormalized() * centripetalStrength;

        // Fuerza total aplicada a la partícula
        Vector3D<> totalForce = circularForce + centripetalForce;

        // Aplicar fricción para estabilizar el movimiento
        totalForce = totalForce * friction;

        // Aplicar la fuerza resultante
        p->ApplyForce(totalForce * t);
	}
}

bool TorbellinoGen::onRange(Vector3D<> pos) const
{
	return  (abs(pos.x - position.x) < range / 2) && (abs(pos.y - position.y) < range / 2)
		&& (abs(pos.z - position.z) < range / 2);
}
