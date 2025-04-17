#include "Emissive.h"

Vec3 Emissive::direct_shade(Hit& hitinfo, World& world, int depth) {
    //Only send light at one side of the surface.
    if (-hitinfo.m_normal.dot(hitinfo.m_direction) > 0) {
        return m_lightScale * m_lightColor;
    }
    else {
        return Vec3();
    }
}

Vec3 Emissive::indirect_shade(Hit& hitinfo, World& world, int depth) {
    //Only send light at one side of the surface.
    if (-hitinfo.m_normal.dot(hitinfo.m_direction) > 0) {
        return m_lightScale * m_lightColor;
    }
    else {
        return Vec3();
    }
}