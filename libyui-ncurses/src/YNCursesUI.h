/*---------------------------------------------------------------------\
|                                                                      |
|                      __   __    ____ _____ ____                      |
|                      \ \ / /_ _/ ___|_   _|___ \                     |
|                       \ V / _` \___ \ | |   __) |                    |
|                        | | (_| |___) || |  / __/                     |
|                        |_|\__,_|____/ |_| |_____|                    |
|                                                                      |
|                               core system                            |
|                                                        (C) SuSE GmbH |
\----------------------------------------------------------------------/

   File:       YNCursesUI.h

   Author:     Michael Andres <ma@suse.de>
   Maintainer: Michael Andres <ma@suse.de>

/-*/
// -*- c++ -*-

#ifndef YNCursesUI_h
#define YNCursesUI_h

#include <iosfwd>

#include <Y2.h>
#include "YUI.h"

#include "NCApplication.h"

#include "NCurses.h"

class YUI;
class NCDialog;
class NCPackageSelectorPluginStub;
class NCWidgetFactory;
class NCOptionalWidgetFactory;
class YSingleChildContainerWidget;


/**
 * YaST2 Component: NCursesUI user interface
 * The YaST2 Component implements a NCursesUI based user interface.
 */
class YNCursesUI : public NCurses, public YUI
{
public:
    /**
     * Constructor
     **/
    YNCursesUI( bool withThreads );

    /**
     * Destructor
     **/
    ~YNCursesUI();


protected:
    /**
     * Create the widget factory that provides all the createXY() methods for
     * standard (mandatory, i.e. non-optional) widgets.
     *
     * Reimplemented from YUI.
     **/
    virtual YWidgetFactory * createWidgetFactory();

    /**
     * Create the widget factory that provides all the createXY() methods for
     * optional ("special") widgets and the corresponding hasXYWidget()
     * methods. 
     *
     * Reimplemented from YUI.
     **/
    virtual YOptionalWidgetFactory * createOptionalWidgetFactory();

    /*
     * Create the YApplication object that provides global methods.
     *
     * Reimplemented from YUI.
     **/
    virtual YApplication * createApplication();
    

    virtual bool want_colors();
    virtual void init_title();

    /**
     * Global reference to the UI
     **/
    static YNCursesUI * _ui;
    
public:

//    Y2NCursesUI( bool with_threads, const char * macro_file, Y2Component *callback );
//    virtual ~Y2NCursesUI();

    /**
     * Access the global Y2NCursesUI.
     */
    static YNCursesUI * ui() { return _ui; }
    
    /**
     * Idle around until fd_ycp is readable
     */
    virtual void idleLoop( int fd_ycp );

    /**
     * Set the (text) console font according to the current encoding etc.
     * See the setfont(8) command and the console HowTo for details.
     *
     * This should really be in NCApplication, but it uses so many non-exported
     * member variables that it's not easy to move it there. 
     **/
    virtual void setConsoleFont( const string & console_magic,
				 const string & font,
				 const string & screen_map,
				 const string & unicode_map,
				 const string & encoding );

    /**
     * Fills the PackageSelector widget and runs package selection.
     */
    virtual YEvent * runPkgSelection( YWidget * packageSelector );
    
    /**
     * Returns the package selector plugin singleton of this UI or creates it
     * (including loading the plugin lib) if it does not exist yet.
     **/
    NCPackageSelectorPluginStub * packageSelectorPlugin();
};


#endif // YNCursesUI_h

