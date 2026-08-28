#include "engine.hpp"
#include "network.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

int main() {
    std::cout << "========================================================\n";
    std::cout << "Distributed Netcode Engine Operational\n";
    std::cout << "========================================================\n\n";

    CombatPhysicsEngine engine;
    RollbackNetworkBridge network;
    std::vector<Player> match_players = {{1, 40.0f}, {2, 50.0f}};

    for (int frame = 1; frame <= 20; ++frame) {
        std::cout << "--- Frame: " << frame << " ---\n";
        network.save_frame_to_buffer(frame, match_players);

        const int p1_input = 1;
        const int p2_input = 0;

        if (frame == 10) {
            network.execute_rollback_reconciliation(7, frame, match_players, p1_input, 2);
        } else {
            engine.update_game_frame(match_players, p1_input, p2_input);
        }

        std::cout << "P1 Pos: " << match_players[0].x_position
                  << " | P2 Pos: " << match_players[1].x_position
                  << " | P2 Health: " << match_players[1].health << "\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return 0;
}