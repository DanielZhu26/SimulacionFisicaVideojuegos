#include "ParticleSystem.h"

void ParticleSystem::update(double t) {

	deleteVector.clear();

	for (auto g : gList) {
		if (g != nullptr)
			g->update(t, *this);
	}

	for (auto it = pList.begin(); it != pList.end(); ) {
		if (*it != nullptr) {
			(*it)->update(t, *this);
			++it;
		}
	}

	for (auto p : deleteVector) {
		auto it = std::find(pList.begin(), pList.end(), p);
		if (it != pList.end()) {
			pList.erase(it);
			delete p;
		}
	}
}

void ParticleSystem::killParticle(Particle* p) {
	if (p != nullptr && p->getIterator() != pList.end())
		deleteVector.push_back(p);
}

void ParticleSystem::addParticle(Particle* p) {
	pList.push_back(p);
	p->setIterator(--pList.end());
}

void ParticleSystem::addGenerator(Vector3 pos, float rate, generators_type type)
{
	switch (type)
	{
	case UNIFORM:
		gList.push_back(new UniformGenerator(pos, rate, Vector3(-20, 20, 0), Vector3(20, 30, 0)));
		break;
	case NORMAL:
		gList.push_back(new NormalGenerator(pos, rate, Vector3(0, 60, 0), Vector3(8, 0.5, 8)));
		break;
	default:
		break;
	}
}