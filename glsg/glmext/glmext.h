#ifndef GLSG_GLMEXT_H
#define GLSG_GLMEXT_H

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/quaternion.hpp>

/**
* GLM namespace extensions.
*/
namespace glm {

/**
* @defgroup glmext glmext
* @ingroup glsg
* GLM extensions for convenience.
*/

/**
* An Axis Aligned Bounding Box implementation over dvec3
* @ingroup glmext
*/
class dbox3 {
public:
    /**
    * Minimim x coordinate.
    */
    double xmin;

    /**
    * Maximum x coordinate.
    */
    double xmax;

    /**
    * Minimum y coordinate.
    */
    double ymin;

    /**
    * Maximum y coordinate.
    */
    double ymax;

    /**
    * Minimum z coordinate.
    */
    double zmin;

    /**
    * Maximum z coordinate.
    */
    double zmax;

    /**
    * Maximum point.
    */
    dvec3 maximum;

    /**
    * Minimum point.
    */
    dvec3 minimum;

    /**
    * Points which describe this box.
    */
    dvec3 points[8];

    /**
    * Creates an inside-out (empty) bounding box.
    */
    dbox3() :
            xmin(INFINITY), xmax(-INFINITY),
            ymin(INFINITY), ymax(-INFINITY),
            zmin(INFINITY), zmax(-INFINITY) {
        setPoints();
    }

    /**
    * Creates a new bounding box from the set of min and max coordinate pairs.
    * @param xmin minimum x coordinate.
    * @param xmin maximum x coordinate.
    * @param ymin minimum y coordinate.
    * @param ymin maximum y coordinate.
    * @param zmin minimum z coordinate.
    * @param zmin maximum z coordinate.
    */
    dbox3(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax) :
            xmin(xmin), xmax(xmax), ymin(ymin), ymax(ymax), zmin(zmin), zmax(zmax) {
        setPoints();
    }

    /**
    * Extends bounding box to contain new point.
    * @param p point to extend bounding box to.
    */
    inline void extend(dvec3 p) {
        xmin = fmin(xmin, p.x);
        xmax = fmax(xmax, p.x);

        ymin = fmin(ymin, p.y);
        ymax = fmax(ymax, p.y);

        zmin = fmin(zmin, p.z);
        zmax = fmax(zmax, p.z);

        setPoints();
    }

    /**
    * Extends bounding box to contain new box.
    * @param b box to extend bounding box to.
    */
    inline void extend(dbox3 b) {
        xmin = fmin(xmin, b.xmin);
        ymin = fmin(ymin, b.ymin);
        zmin = fmin(zmin, b.zmin);

        xmax = fmax(xmax, b.xmax);
        ymax = fmax(ymax, b.ymax);
        zmax = fmax(zmax, b.zmax);

        setPoints();
    }

    /**
    * Returns true if bounding box contains point.
    * @param p point to check if inside box.
    */
    bool contains(dvec3 p) {
        return p.x >= xmin && p.x <= xmax && p.y >= ymin && p.y <= ymax && p.z >= zmin && p.z <= zmax;
    }

    /**
    * Computes the points which describe this box
    */
    void setPoints() {
        points[0] = dvec3(xmin, ymin, zmin);
        points[1] = dvec3(xmax, ymin, zmin);
        points[2] = dvec3(xmin, ymax, zmin);
        points[3] = dvec3(xmax, ymax, zmin);
        points[4] = dvec3(xmin, ymin, zmax);
        points[5] = dvec3(xmax, ymin, zmax);
        points[6] = dvec3(xmin, ymax, zmax);
        points[7] = dvec3(xmax, ymax, zmax);

        maximum = dvec3(xmax, ymax, zmax);
        minimum = dvec3(xmin, ymin, zmin);
    }
};

}

#endif
