#ifndef CONSTANTS_H
#define CONSTANTS_H
namespace stratego {
    namespace constants {
        enum ranks {
            flag_rank = 0,
            spy_rank = 1,
            scout_rank = 2,
            miner_rank = 3,
            sergeant_rank = 4,
            lieutenant_rank = 5,
            captain_rank = 6,
            major_rank = 7,
            colonel_rank = 8,
            general_rank = 9,
            marshall_rank = 10,
            bomb_rank = 11
        };

        enum max_squares {
            spy_max_squares = 1,
            scout_max_squares = 9,
            miner_max_squares = 1,
            sergeant_max_squares = 1,
            lieutenant_max_squares = 1,
            captain_max_squares = 1,
            major_max_squares = 1,
            colonel_max_squares = 1,
            general_max_squares = 1,
            marshall_max_squares = 1,
        };

        enum numberOfPieces {
            nb_flags = 1,
            nb_spies = 1,
            nb_marshalls = 1,
            nb_generals = 1,
            nb_colonels = 2,
            nb_majors = 3,
            nb_captains = 4,
            nb_lieutenants = 4,
            nb_sergeants = 4,
            nb_miners = 5,
            nb_scouts = 8,
            nb_bombs = 6,
        };
    }
}
#endif // CONSTANTS_H
