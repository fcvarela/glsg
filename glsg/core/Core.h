#ifndef GLSG_CORE_H
#define GLSG_CORE_H

#include <string>
#include <application/Application.h>

namespace glsg {

/**
* @defgroup core core
* @ingroup glsg
* GLSG core support. Exposes App.
*/

typedef Application App;

/**
* General purpose hashing function for procedural generation:
*  - A single iteration of Bob Jenkins' One-At-A-Time hashing algorithm.
*  @param x the thing to hash (or proc gen seed)
*/
uint32_t hash(uint32_t x);

/**
* Utility function to convert a string to a seed for the hashing function.
* @param string to convert to hash (ie: planet-51-moons)
*/
uint32_t hash_seed(std::string string);

}


#endif
