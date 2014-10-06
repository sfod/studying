#ifndef GAME_DATA_HPP
#define GAME_DATA_HPP

#include <map>
#include <string>

enum class PlayerType {
    PT_Human,
    PT_AI,
    PT_Invalid
};

static const std::map<std::string, PlayerType> player_type_map = {
    {"Human", PlayerType::PT_Human},
    {"AI", PlayerType::PT_AI}
};

#endif // GAME_DATA_HPP
