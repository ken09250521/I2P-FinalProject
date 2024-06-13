#ifndef Manage_HPP
#define Manage_HPP

#include <allegro5/allegro_audio.h>
#include <memory>

class Manage {
private:
    Manage() {}          

    static int curWonStage;
    static int curStage;
public:
    static Manage& getInstance() {
        static Manage instance;  // Guaranteed to be destroyed.
                                // Instantiated on first use.
        return instance;
    }

    static void setCurStage (int val);
    int getCurStage () const;
    static void setCurWonStage (int val);
    int getCurWonStage () const;
};

#endif // Manage_HPP