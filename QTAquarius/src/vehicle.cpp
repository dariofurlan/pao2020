#include "vehicle.hpp"

#include <cstdlib>

#include "aquarius.hpp"
#include "deepptr.hpp"
#include "vect2d.hpp"

const double Vehicle::maxSpeed = 5;    // 4 pixel per frame
const double Vehicle::maxForce = .15;  // the lower the slower is to apply changes to the velocity

const double Vehicle::PURSUIT_forwardSteps = 5;  // look forward for 5 steps

const double Vehicle::WANDER_MAX_STRENGTH = 5;
const double Vehicle::WANDER_MAX_RATE = 20;
const double Vehicle::WANDER_forwardSteps = 15;
const double Vehicle::wander_strength = 1;  // 0 <= x <= 1 (where 0 is 0 and 1 is WANDER_MAX_STRENGTH)
const double Vehicle::wander_rate = 1;      // 0 <= x <= 1 (where 0 is 0 and 1 is WANDER_MAX_RATE)

Vehicle::Vehicle() : _velocity(1, 1), _wander(1, 1) {
    _velocity.setMagnitude(maxSpeed);
    _velocity.rotateDeg(std::rand() % 360 - 180);
}

Vehicle::~Vehicle() = default;

void Vehicle::setForce(const Vect2D& acc) {
    _acc = acc;
}

void Vehicle::applyForce(const Vect2D& acc, const double& weight) {
    _acc += (acc * weight);
}

Vect2D Vehicle::getVelocity() const { return _velocity; }

Vect2D Vehicle::seek(const Vect2D& target) const {  // return steering from here to that target (target - location).normalize().mult(maxspeed);
    Vect2D diff = (target - position);
    diff.setMagnitude(maxSpeed);
    return (diff - _velocity);  // .limit(maxForce);
}
double map(double n, double start1, double stop1, double start2, double stop2) {
    auto newval = (n) / (stop1 - start1) * (stop2 - start2) + start2;
    return newval;
}
Vect2D Vehicle::arrive(const Vect2D& target) const {
    Vect2D desired = (target - position);
    double distance = desired.mag();
    if (distance < 100)
        desired.setMagnitude(distance / 100 * maxSpeed);
    else
        desired.setMagnitude(maxSpeed);
    return (desired - _velocity);  // .limit(maxForce);
}

Vect2D Vehicle::flee(const Vect2D& target) const {
    Vect2D desired = (target - position);

    double distance = desired.mag();
    if (distance < 100 && distance > 0) {
        desired.setMagnitude(distance / -100 * -maxSpeed + maxSpeed);
        desired.mult(-1);
    } else
        return Vect2D(0, 0);

    return (desired - _velocity);  //.limit(maxForce);
}
Vect2D Vehicle::pursuit(const Vehicle& v) const {
    return seek(v.position + (v._velocity * Vehicle::PURSUIT_forwardSteps));
}
Vect2D Vehicle::escape(const Vehicle& v) const {
    return flee(v.position + (v._velocity * Vehicle::PURSUIT_forwardSteps));
}
Vect2D Vehicle::wander() {
    int sign = (std::rand() % 2) ? 1 : -1;  // test this

    _wander.setMagnitude(Vehicle::wander_strength * Vehicle::WANDER_MAX_STRENGTH);
    _wander.rotateDeg(sign * Vehicle::wander_rate * Vehicle::WANDER_MAX_RATE);

    return seek(position + (_velocity * Vehicle::WANDER_forwardSteps) + _wander);
}

Vect2D Vehicle::stop() const {
    return _velocity * (-maxForce);
}

Vect2D Vehicle::stayWithinBorders(const Vect2D& size, const unsigned int distance) const {
    Vect2D avoid;

    const Vect2D dtop = Vect2D(position.x(), 0);
    const Vect2D dleft = Vect2D(0, position.y());
    const Vect2D dr = Vect2D(size.x(), position.y());
    const Vect2D db = Vect2D(position.x(), size.y());

    Vect2D diff = position - dtop;
    double d = diff.mag();
    if (d < distance && d > 0) {
        diff.div(d * d);
        avoid += diff;
    }

    diff = position - dleft;
    d = diff.mag();
    if (d < distance && d > 0) {
        diff.div(d * d);
        avoid += diff;
    }

    diff = position - dr;
    d = diff.mag();
    if (d < distance && d > 0) {
        diff.div(d * d);
        avoid += diff;
    }

    diff = position - db;
    d = diff.mag();
    if (d < distance && d > 0) {
        diff.div(d * d);
        avoid += diff;
    }

    if (avoid != Vect2D(0, 0))
        return avoid.div(4).setMagnitude(maxSpeed).rem(_velocity);
    else
        return avoid;
}

#include <iostream>
using std::cout;
using std::endl;
void Vehicle::advance(Aquarius* a, int phase) {  //divide the method with 2 phase triggere within the aquarius
    if (!phase) {
        auto w = a->getWidth();
        auto h = a->getHeight();
        Vect2D bounds = Vect2D(w, h);
        this->behaviour(a);
        applyForce(stayWithinBorders(bounds, 100));
        // cout << "mag:" << _velocity.mag() << " (" << _acc.x() << "," << _acc.y() << ")" << endl;

        _acc.limit(Vehicle::maxForce);

        _computedvelocity = _velocity + _acc;
        _computedvelocity.limit(Vehicle::maxSpeed);
        _computedposition = position + _computedvelocity;
        _computedposition.bounds(bounds);  // mal che vada non farli scomparire del tutto
        
    } else {
        _velocity = _computedvelocity;
        position = _computedposition;
        _acc = Vect2D();
    }
}
