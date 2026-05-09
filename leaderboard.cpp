void Leaderboard::sortByScore() {
    // Function to sort players based on score (highest first)

    for (int i = 0; i < count - 1; i++) {
        // Outer loop → runs multiple passes

        for (int j = 0; j < count - i - 1; j++) {
            // Inner loop → compares adjacent players

            if (players[j].getScore() < players[j + 1].getScore()) {
                // If current player's score is LESS than next player's score
                // → we swap them to bring higher score forward

                Player temp = players[j];
                // Store current player in temporary variable

                players[j] = players[j + 1];
                // Move next player to current position

                players[j + 1] = temp;
                // Put stored player in next position (swap complete)
            }
        }
    }
    // This is Bubble Sort (descending order → highest score first)
}

void Leaderboard::display() const {
    // Function to display all players
    // 'const' → does not modify any data

    cout << "\n===== Leaderboard =====\n";
    // Prints heading

    if (count == 0) {
        // Checks if no players exist

        cout << "No players yet.\n";
        // Prints message if empty

        return;
        // Exit function early
    }

    for (int i = 0; i < count; i++) {
        // Loop through all players

        cout << i + 1 << ". ";
        // Prints ranking number (1, 2, 3...)

        players[i].displayInfo();
        // Calls function to display player details (name, score, etc.)
    }
}