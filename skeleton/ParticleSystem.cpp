#include "ParticleSystem.h"


ParticleSystem::~ParticleSystem()
{
	for (auto p : partList) {
		delete p;
		p = nullptr;
	}
	for (auto g : genList) {
		delete g;
		g = nullptr;
	}

	partList.clear();
	genList.clear();

}

void ParticleSystem::update(double t) {

	deleteVector.clear();

	for (auto g : genList) {
		if (g != nullptr)
			g->update(t, *this);
	}

	for (auto it = partList.begin(); it != partList.end(); ) {
		if (*it != nullptr) {
			(*it)->update(t, *this);
			++it;
		}
	}

	for (auto p : deleteVector) {
		auto it = std::find(partList.begin(), partList.end(), p);
		if (it != partList.end()) {
			partList.erase(it);
			delete p;
		}
	}
}

void ParticleSystem::deleteParticle(Particle* p) {
	if (p != nullptr && p->getIterator() != partList.end())
		deleteVector.push_back(p);
}

void ParticleSystem::addParticle(Particle* p) {
	partList.push_back(p);
	p->setIterator(--partList.end());
}

void ParticleSystem::addUniPartGen(Vector3 pos, Vector3 direction, float rate, float range, float spawnR, spawnDist sd)
{
	Particle p = Particle(pos, direction);

	genList.push_back(new UniPartGen(&p, rate, range, spawnR, sd));
}

void ParticleSystem::addNormalPartGen(Vector3 pos, Vector3 direction, float rate, Vector3 dev, float spawnR, spawnDist sd)
{
	Particle p = Particle(pos, direction);
	genList.push_back(new NormalPartGen(&p, rate, dev, spawnR, sd));
}