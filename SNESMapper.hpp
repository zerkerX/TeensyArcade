#ifndef SNES_MAPPER_HPP
#define SNES_MAPPER_HPP

#include "ArcadeStick.hpp"

namespace SNESMapper
{
    void init(void);
    
    void load(const ArcadeStick & stick);
}

#endif
