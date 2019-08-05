#include "UCI.hpp"
#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <unistd.h>

namespace UCI{

    bool initEngine(std::string_view enginepath){
        pid_t pid = 0;
        int pipe_to_engine[2];
        int pipe_to_gui[2];

        pipe(pipe_to_engine);
        pipe(pipe_to_gui);

        pid = fork();
        if(pid == 0)
        {
            //Child
            close(pipe_to_engine[1]);
            close(pipe_to_gui[0]);
            dup2(pipe_to_engine[0], STDIN_FILENO);
            dup2(pipe_to_gui[1], STDOUT_FILENO);
            dup2(pipe_to_gui[1], STDERR_FILENO);
            execl("/home/gursimrans/Documents/Harsh/Chess Engine/sigma-chess", "sd", nullptr);
        }
        else if(pid == -1)
            return false;
        //parent
        close(pipe_to_engine[0]);
        close(pipe_to_gui[1]);
        dup2(pipe_to_engine[1], STDOUT_FILENO);
        dup2(pipe_to_engine[1], STDERR_FILENO);
        dup2(pipe_to_gui[0], STDIN_FILENO);
        return true;
    }

    //GUI to ENGINE

    void setUCI()
    {
        std::cout << "uci\n" << std::flush;;
    }

    void setDebug(bool val)
    {
        std::cout << std::boolalpha << "debug " << val << std::noboolalpha << '\n' << std::flush;
    }


    bool isReady()
    {
        std::cout << "isready\n";
        std::string returnvalue;

        if( std::cin >> returnvalue)
        {
            if(returnvalue.find("readyok") != std::string_view::npos)
                return true;
        }
        return false;
    }

    void setOption( std::string_view name, std::string_view value)
    {
        std::cout << "setoption " << name << " " << value << '\n' << std::flush;
    }   //"setoption name Style value Risky\n"

    void uciNewGame()
    {
        std::cout << "ucinewgame\n" << std::flush;;
    }

    /*
    * position [fen  | startpos ]  moves  .... 
	* set up the position described in fenstring_view on the internal board and
	* play the moves on the internal chess board.
	* if the game was played  from the start position the string_view "startpos" will be sent
	* Note: no "new" command is needed. However, if this position is from a different game than
	* the last position sent to the engine, the GUI should have sent a "ucinewgame" inbetween.
    */
    void position()
    {
        std::cout << "position startpos\n" << std::flush;
    }
    void position(std::string_view& fen , std::vector< std::string_view >& moves)
    {
        std::cout << "position " << fen;
        for(const auto& move : moves)
            std::cout << " " << move;
        std::cout << '\n' << std::flush;
    }
    void position(std::vector< std::string_view >& moves)
    {
        std::cout << "position startpos";
        for(auto move : moves)
            std::cout << " " << move;
        std::cout << '\n' << std::flush;
    }

    void go()
    {
        
    }
    void go(GoContext& )
    {

    }

    void stop()
    {

    }

    void ponderhit()
    {

    }

    void quit()
    {

    }

}

