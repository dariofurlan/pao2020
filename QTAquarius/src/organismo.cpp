#include "organismo.hpp"

#include "aquarius.hpp"

const char** Organismo::COOL_NAMES = new const char* [26]{
    "Bowie",
    "Cardi",
    "Elvis",
    "Freddie",
    "Lennon",
    "Prince",
    "Brie",
    "Apache",
    "Kong",
    "Atari",
    "Elite",
    "Voxel",
    "Boomer",
    "Kobe",
    "Jordan",
    "Shaq",
    "Sydney",
    "Pretender",
    "Buzz",
    "Rocky",
    "Rocky II",
    "Rocky III",
    "Rocky IV",
    "Rocky V",
    "Thor",
    "Nemo",
};


Organismo::Organismo(const Vect2D& position, double maximumSpeed, double maximumForce, const std::string& name, unsigned int a, unsigned int s, double stam) : Vehicle(position, maximumSpeed, maximumForce), _name(name == "" ? COOL_NAMES[std::rand() % 26] : name), _awake(true), _gone(false), _daycycle(a, s), _stamina(stam) {}
Organismo::Organismo(const Organismo& o) : Vehicle(o), _name(o._name), _awake(o._awake), _gone(false), _daycycle(o._daycycle), _stamina(o._stamina) {}

bool Organismo::isGone() const { return _gone; }
void Organismo::setGone() { _gone = true; }

void Organismo::setName(const std::string& name) { _name = name; }
const std::string& Organismo::getName() const { return _name; }
double Organismo::getStamina() const { return _stamina.getPercentage(); }
void Organismo::sleep() { _awake = false; }
void Organismo::wakeup() { _awake = true; }
bool Organismo::isAwake() const { return _awake; }
bool Organismo::isAsleep() const { return !_awake; }

bool Organismo::canSleep() const {
    return _daycycle.isNight();
}

bool Organismo::canWakeup() const {
    return _daycycle.isDay();
}

void Organismo::behaviour(Aquarius* a) {
    _daycycle++;  //increase progress
    if (isAsleep()) {
        if (canWakeup())
            wakeup();
        setForce(stop());
        return;
    }
    // è sveglio
    _stamina -= 0.0005 * _stamina.getMax();
    if (_stamina <= 0) {
        setGone();
        setForce(stop());
        return;
    }                  //starved to death
    if (canSleep()) {  // può dormire?
        sleep();       // dorme
        setForce(stop());
        return;  // turno finito
    }
    // è sveglio e non può dormire
    if (isHungry()) {  // ha fame? then cerca cibo, mira verso il cibo con nuova accelerazione != acc parametro
        Organismo* candidato = nullptr;
        double mindist = 0;
        for (auto& o : a->getAllOrganismi()) {
            if (this != &(*o) && o->getValoreNutrizionale() < getValoreNutrizionale() && isInRange(o->getPosition())) {
                if (!candidato || Vect2D::distance(getPosition(), o->getPosition()) < mindist) {
                    mindist = Vect2D::distance(getPosition(), o->getPosition());
                    candidato = &*o;
                }
            }
        }
        if (candidato != nullptr) {
            if (mindist < getVelocity().mag()) {
                _stamina += candidato->getValoreNutrizionale();
                candidato->setGone();
            }
            setForce(pursuit(*candidato));
            return;
        }
    }
    // è sveglio, non può dormire, non ha fame || non ha trovato cibo
    // quindi vaga a caso
    applyForce(wander(), .2);
}
