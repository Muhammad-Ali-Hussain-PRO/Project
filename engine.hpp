#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

enum PlayerState { IDLE, MOVING, ATTACKING, HIT_STUN };

struct Player {
    int id;
    float x_position;
    float y_position = 0.0f;
    int health = 100;
    PlayerState state = IDLE;
    int state_timer = 0;
};

class CombatPhysicsEngine {
public:
    static constexpr float STAGE_WIDTH = 100.0f;
    static constexpr float HITBOX_RANGE = 5.0f;

    void update_game_frame(std::vector<Player>& players, int current_input_p1, int current_input_p2) {
        if (players.size() < 2) {
            return;
        }

        process_player_logic(players[0], current_input_p1);
        process_player_logic(players[1], current_input_p2);

        check_combat_collisions(players[0], players[1]);
        check_combat_collisions(players[1], players[0]);
    }

private:
    void process_player_logic(Player& player, int input) const {
        if (player.state_timer > 0) {
            --player.state_timer;
            if (player.state_timer == 0) {
                player.state = IDLE;
            }
        }

        if (player.state == HIT_STUN) {
            return;
        }

        if (input == 2 && player.state != ATTACKING) {
            player.state = ATTACKING;
            player.state_timer = 10;
        } else if (player.state != ATTACKING) {
            if (input == -1) {
                player.x_position = std::max(0.0f, player.x_position - 1.5f);
                player.state = MOVING;
            } else if (input == 1) {
                player.x_position = std::min(STAGE_WIDTH, player.x_position + 1.5f);
                player.state = MOVING;
            } else {
                player.state = IDLE;
            }
        }
    }

    void check_combat_collisions(Player& attacker, Player& defender) const {
        if (attacker.state == ATTACKING && attacker.state_timer == 9) {
            const float distance = std::abs(attacker.x_position - defender.x_position);
            if (distance <= HITBOX_RANGE) {
                defender.health = std::max(0, defender.health - 15);
                defender.state = HIT_STUN;
                defender.state_timer = 12;
                std::cout << "[COMBAT] Player " << attacker.id << " HIT Player " << defender.id
                          << "! Defender Health: " << defender.health << '\n';
            }
        }
    }
};