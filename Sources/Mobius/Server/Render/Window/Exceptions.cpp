/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Exceptions.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 05/05/2019.
 */

#include <Mobius/Server/Render/Window/Exceptions.hpp>


namespace Mobius {
namespace Render {
namespace Window {

Exception::Exception(const char * message) :
    std::exception() {
    // Store the message.
    _message = message;
}
    

const char * Exception::what() const throw() {
    // Return the message.
    return _message;
}

}
}
}
