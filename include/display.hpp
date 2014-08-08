/*/////////////////////////////////////////////////////////////////////////////
/// @summary
/// @author Russell Klenk (contact@russellklenk.com)
///////////////////////////////////////////////////////////////////////////80*/

#ifndef GW_DISPLAY_HPP
#define GW_DISPLAY_HPP

/*////////////////
//   Includes   //
////////////////*/
#include "common.hpp"
#include "platform.hpp"

/*////////////////
//  Data Types  //
////////////////*/
/// @summary
class DisplayManager
{
public:
    GLFWwindow *main_window;

public:
    DisplayManager(void);
    ~DisplayManager(void);

public:
    bool init(GLFWwindow *win);
    void shutdown(void);

private:
    DisplayManager(DisplayManager const &other);
    DisplayManager& operator =(DisplayManager const &other);
};

#endif /* !defined(GW_DISPLAY_HPP) */
