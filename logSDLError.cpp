#include "logSDLerror.h"

void logSDLError(const std::string & msg, std::ostream & os)
{
    os << msg << " error: " << SDL_GetError() << '\n';
}