#ifndef GAME_DATA_HPP
#define GAME_DATA_HPP

#include <map>
#include <string>

enum class PlayerType {
    PT_Human,
    PT_AI,
    PT_Invalid
};

static const std::map<std::string, PlayerType> player_type_to_str = {
    {"human", PlayerType::PT_Human},
    {"AI", PlayerType::PT_AI}
};

static const std::map<PlayerType, std::string> str_to_player_type = {
    {PlayerType::PT_Human, "human"},
    {PlayerType::PT_AI, "AI"}
};

#endif // GAME_DATA_HPP
