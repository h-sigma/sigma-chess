#ifndef UCI_HPP
#define UCI_HPP

#include <string_view>
#include <vector>
#include <array>

namespace UCI{

    bool initEngine(std::string_view enginepath);

    void setUCI();

    void setDebug(bool val);

    bool isReady();

    void setOption( std::string_view name, std::string_view value);   //"setoption name Style value Risky\n"

    void uciNewGame();

    /*
    * position [fen  | startpos ]  moves  .... 
	* set up the position described in fenstring_view on the internal board and
	* play the moves on the internal chess board.
	* if the game was played  from the start position the string_view "startpos" will be sent
	* Note: no "new" command is needed. However, if this position is from a different game than
	* the last position sent to the engine, the GUI should have sent a "ucinewgame" inbetween.
    */
    void position();
    void position(std::string_view& fen, std::vector< std::string_view >& moves);
    void position(std::vector< std::string_view >& moves);

    struct GoContext{
        bool infinite = false;
        int wtime = 0, btime = 0, winc = 0, binc = 0, movestogo = 0, depth = 0, nodes = 0, mate = 0, movetime = 0;
        std::vector< std::array<char,5> > searchmoves;
        GoContext() = default;
    };

    void go();
    void go(GoContext context = {});

    void stop();

    void ponderhit();

    void quit();

}



#endif