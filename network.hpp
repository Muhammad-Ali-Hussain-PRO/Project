#pragma once

#include "engine.hpp"

#include <iostream>
#include <map>
#include <vector>

struct GameStateHistory {
    int frame_number;
    std::vector<Player> player_states;
};

class RollbackNetworkBridge {
private:
    std::map<int, GameStateHistory> history_buffer;
    CombatPhysicsEngine physics;
    static constexpr int MAX_HISTORY_FRAMES = 30;

public:
    void save_frame_to_buffer(int frame, const std::vector<Player>& current_players) {
        history_buffer[frame] = {frame, current_players};

        if (history_buffer.size() > MAX_HISTORY_FRAMES) {
            history_buffer.erase(history_buffer.begin());
        }
    }

    void execute_rollback_reconciliation(int mispredicted_frame, int current_frame,
                                         std::vector<Player>& live_players,
                                         int corrected_input, int enemy_input) {
        const auto snapshot = history_buffer.find(mispredicted_frame);
        if (snapshot == history_buffer.end()) {
            return;
        }

        std::cout << "[ROLLBACK] Network jitter detected at frame " << mispredicted_frame
                  << ". Rolling back from frame " << current_frame << " to reconcile...\n";

        live_players = snapshot->second.player_states;
        for (int frame = mispredicted_frame; frame < current_frame; ++frame) {
            physics.update_game_frame(live_players, corrected_input, enemy_input);
            save_frame_to_buffer(frame + 1, live_players);
        }

        std::cout << "[ROLLBACK] Synchronization complete. Live timeline re-aligned.\n";
    }
};