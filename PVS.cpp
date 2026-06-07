// ============================================================
//   PAKISTAN ELECTRONIC VOTING SYSTEM
//   Professional Version
//   Language  : C++
//   Concepts  : Arrays, Functions, Loops, If/Else, I/O
// ============================================================

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// ---- Constants ----
const int MAX_CANDIDATES = 5;
const int MAX_VOTERS     = 100;

// ---- Candidate Data ----
string candidateNames[MAX_CANDIDATES] = {
    "Imran Khan",
    "Nawaz Sharif",
    "Bilawal Bhutto",
    "Siraj ul Haq",
    "Altaf Hussain"
};

string partyNames[MAX_CANDIDATES] = {
    "Pakistan Tehreek-e-Insaf",
    "Pakistan Muslim League (N)",
    "Pakistan Peoples Party",
    "Jamaat-e-Islami",
    "Muttahida Qaumi Movement"
};

string partySymbols[MAX_CANDIDATES] = {
    "Bat",
    "Lion",
    "Arrow",
    "Scale",
    "Kite"
};

int votes[MAX_CANDIDATES] = {0, 0, 0, 0, 0};

// ---- Voter Records ----
string voterNames[MAX_VOTERS];
string voterCNICs[MAX_VOTERS];
bool   voterHasVoted[MAX_VOTERS];
int    voterCount = 0;

// ---- Admin Credentials ----
string adminUsername = "admin";
string adminPassword = "admin123";

// ---- Election Status ----
bool electionOpen = false;

// ============================================================
//   HELPER FUNCTIONS
// ============================================================

void printLine(int len = 60) {
    for (int i = 0; i < len; i++) cout << "=";
    cout << "\n";
}

void printDash(int len = 60) {
    for (int i = 0; i < len; i++) cout << "-";
    cout << "\n";
}

void clearInputBuffer() {
    cin.ignore(1000, '\n');
}

void pressEnterToContinue() {
    cout << "\n  Press ENTER to continue...";
    clearInputBuffer();
    cin.get();
}

bool isValidCNIC(const string& cnic) {
    if (cnic.length() != 13) return false;
    for (char c : cnic)
        if (c < '0' || c > '9') return false;
    return true;
}

bool isCNICRegistered(const string& cnic) {
    for (int i = 0; i < voterCount; i++)
        if (voterCNICs[i] == cnic) return true;
    return false;
}

int findVoterByCNIC(const string& cnic) {
    for (int i = 0; i < voterCount; i++)
        if (voterCNICs[i] == cnic) return i;
    return -1;
}

int getTotalVotes() {
    int total = 0;
    for (int i = 0; i < MAX_CANDIDATES; i++)
        total += votes[i];
    return total;
}

int getWinnerIndex() {
    int maxVotes = votes[0], winner = 0;
    for (int i = 1; i < MAX_CANDIDATES; i++) {
        if (votes[i] > maxVotes) {
            maxVotes = votes[i];
            winner   = i;
        }
    }
    return winner;
}

string maskCNIC(const string& cnic) {
    // Show first 5 and last 1 digit only
    return cnic.substr(0, 5) + "XXXXXXX" + cnic.substr(12, 1);
}

// ============================================================
//   DISPLAY FUNCTIONS
// ============================================================

void showBanner() {
    cout << "\n";
    printLine(60);
    cout << left
         << setw(60) << "        PAKISTAN ELECTRONIC VOTING SYSTEM" << "\n"
         << setw(60) << "          Election Commission of Pakistan" << "\n";
    printLine(60);
    cout << "\n";
}

void showMainMenu() {
    cout << "\n";
    printLine(50);
    cout << "                    MAIN MENU\n";
    printLine(50);
    cout << "  1.  Voter Registration\n"
         << "  2.  Cast Your Vote\n"
         << "  3.  View Election Results\n"
         << "  4.  View Candidates List\n"
         << "  5.  View Registered Voters\n"
         << "  6.  Search Voter by CNIC\n"
         << "  7.  About This System\n"
         << "  8.  Admin Panel\n"
         << "  9.  Exit\n";
    printLine(50);
    cout << "  Enter your choice (1-9): ";
}

void showCandidatesList() {
    cout << "\n";
    printLine(62);
    cout << "                  CANDIDATES LIST\n";
    printLine(62);
    cout << left
         << setw(4)  << "No."
         << setw(18) << "Candidate Name"
         << setw(28) << "Party"
         << "Symbol\n";
    printDash(62);
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        cout << left
             << setw(4)  << (i + 1)
             << setw(18) << candidateNames[i]
             << setw(28) << partyNames[i]
             << partySymbols[i] << "\n";
    }
    printLine(62);
}

// ============================================================
//   VOTER REGISTRATION
// ============================================================

void registerVoter() {
    cout << "\n";
    printLine(50);
    cout << "              VOTER REGISTRATION\n";
    printLine(50);

    if (voterCount >= MAX_VOTERS) {
        cout << "  [!] Maximum voter limit reached (100). Cannot register more.\n";
        pressEnterToContinue();
        return;
    }

    string name, cnic;

    clearInputBuffer();
    cout << "  Enter your Full Name   : ";
    getline(cin, name);

    if (name.length() < 3) {
        cout << "  [!] Name must be at least 3 characters long.\n";
        pressEnterToContinue();
        return;
    }

    cout << "  Enter your CNIC        : ";
    cout << "  (13 digits, no dashes) : ";
    cin >> cnic;

    if (!isValidCNIC(cnic)) {
        cout << "  [!] Invalid CNIC! Must be exactly 13 numeric digits.\n";
        pressEnterToContinue();
        return;
    }

    if (isCNICRegistered(cnic)) {
        cout << "  [!] This CNIC is already registered in the system.\n";
        pressEnterToContinue();
        return;
    }

    voterNames[voterCount]    = name;
    voterCNICs[voterCount]    = cnic;
    voterHasVoted[voterCount] = false;
    voterCount++;

    cout << "\n";
    printDash(40);
    cout << "  Registration Successful!\n";
    printDash(40);
    cout << "  Name         : " << name << "\n"
         << "  CNIC         : " << maskCNIC(cnic) << "\n"
         << "  Voter Number : " << voterCount << "\n";
    printDash(40);

    pressEnterToContinue();
}

// ============================================================
//   CAST VOTE
// ============================================================

void castVote() {
    cout << "\n";
    printLine(50);
    cout << "                  CAST YOUR VOTE\n";
    printLine(50);

    if (!electionOpen) {
        cout << "  [!] The election has not started yet.\n"
             << "      Please contact the administrator.\n";
        pressEnterToContinue();
        return;
    }

    if (voterCount == 0) {
        cout << "  [!] No voters are registered in the system.\n";
        pressEnterToContinue();
        return;
    }

    string cnic;
    cout << "  Enter your CNIC (13 digits): ";
    cin >> cnic;

    if (!isValidCNIC(cnic)) {
        cout << "  [!] Invalid CNIC format. Must be 13 numeric digits.\n";
        pressEnterToContinue();
        return;
    }

    int voterIdx = findVoterByCNIC(cnic);

    if (voterIdx == -1) {
        cout << "  [!] You are not registered in the system.\n"
             << "      Please complete voter registration first.\n";
        pressEnterToContinue();
        return;
    }

    if (voterHasVoted[voterIdx]) {
        cout << "  [!] You have already cast your vote.\n"
             << "      One CNIC is allowed only one vote.\n";
        pressEnterToContinue();
        return;
    }

    cout << "\n  Voter Verified!\n"
         << "  Welcome, " << voterNames[voterIdx] << "\n";

    cout << "\n";
    printLine(58);
    cout << "                   BALLOT PAPER\n";
    printLine(58);
    cout << left
         << setw(4)  << "No."
         << setw(18) << "Candidate Name"
         << "Party\n";
    printDash(58);
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        cout << left
             << setw(4)  << (i + 1)
             << setw(18) << candidateNames[i]
             << partyNames[i] << "\n";
    }
    printLine(58);

    int choice;
    cout << "  Who would you like to vote for? (1-" << MAX_CANDIDATES << "): ";
    cin >> choice;

    if (cin.fail() || choice < 1 || choice > MAX_CANDIDATES) {
        cin.clear();
        clearInputBuffer();
        cout << "  [!] Invalid selection. Please enter a number between 1 and "
             << MAX_CANDIDATES << ".\n";
        pressEnterToContinue();
        return;
    }

    cout << "\n  You selected  : " << candidateNames[choice - 1] << "\n"
         << "  Party         : " << partyNames[choice - 1] << "\n\n"
         << "  Confirm your vote? (1 = Yes / 2 = No): ";
    int confirm;
    cin >> confirm;

    if (confirm != 1) {
        cout << "  Vote cancelled. No vote has been recorded.\n";
        pressEnterToContinue();
        return;
    }

    votes[choice - 1]++;
    voterHasVoted[voterIdx] = true;

    cout << "\n";
    printLine(40);
    cout << "  Your vote has been cast successfully!\n"
         << "  Thank you for participating.          \n"
         << "  Pakistan Zindabad!                    \n";
    printLine(40);

    pressEnterToContinue();
}

// ============================================================
//   SHOW RESULTS
// ============================================================

void showResults() {
    cout << "\n";
    printLine(62);
    cout << "                  ELECTION RESULTS\n";
    printLine(62);

    int total = getTotalVotes();
    cout << "  Total Votes Cast   : " << total << "\n"
         << "  Registered Voters  : " << voterCount << "\n";
    printDash(62);
    cout << left
         << setw(4)  << "No."
         << setw(18) << "Candidate"
         << setw(8)  << "Votes"
         << setw(7)  << "%"
         << "Bar Chart\n";
    printDash(62);

    for (int i = 0; i < MAX_CANDIDATES; i++) {
        double percent = (total > 0) ? (votes[i] * 100.0 / total) : 0.0;
        int    bars    = (int)(percent / 4);

        cout << left
             << setw(4)  << (i + 1)
             << setw(18) << candidateNames[i]
             << setw(8)  << votes[i]
             << setw(5)  << fixed << setprecision(1) << percent << "% ";

        for (int b = 0; b < bars; b++) cout << "#";
        cout << "\n";
    }

    printLine(62);

    if (total == 0) {
        cout << "  No votes have been cast yet.\n";
    } else {
        int    winnerIdx = getWinnerIndex();
        double winPct    = (votes[winnerIdx] * 100.0) / total;

        cout << "\n  *** WINNER: " << candidateNames[winnerIdx] << " ***\n"
             << "  Party  : " << partyNames[winnerIdx] << "\n"
             << "  Votes  : " << votes[winnerIdx]
             << " (" << fixed << setprecision(1) << winPct << "%)\n";
    }

    printLine(62);
    pressEnterToContinue();
}

// ============================================================
//   SHOW VOTERS LIST
// ============================================================

void showVotersList() {
    cout << "\n";
    printLine(58);
    cout << "              REGISTERED VOTERS LIST\n";
    printLine(58);

    if (voterCount == 0) {
        cout << "  No voters are registered in the system.\n";
        pressEnterToContinue();
        return;
    }

    cout << "  Total Registered Voters: " << voterCount << "\n";
    printDash(58);
    cout << left
         << setw(5)  << "No."
         << setw(22) << "Full Name"
         << setw(16) << "CNIC (Masked)"
         << "Vote Status\n";
    printDash(58);

    for (int i = 0; i < voterCount; i++) {
        string masked = voterCNICs[i].substr(0, 5) + "XXXXX"
                      + voterCNICs[i].substr(10, 3);
        cout << left
             << setw(5)  << (i + 1)
             << setw(22) << voterNames[i]
             << setw(16) << masked
             << (voterHasVoted[i] ? "Voted" : "Not Voted") << "\n";
    }

    printLine(58);
    pressEnterToContinue();
}

// ============================================================
//   SEARCH VOTER
// ============================================================

void searchVoter() {
    cout << "\n";
    printLine(50);
    cout << "              SEARCH VOTER BY CNIC\n";
    printLine(50);

    if (voterCount == 0) {
        cout << "  No voters are registered in the system.\n";
        pressEnterToContinue();
        return;
    }

    string cnic;
    cout << "  Enter CNIC (13 digits): ";
    cin >> cnic;

    int idx = findVoterByCNIC(cnic);

    cout << "\n";
    if (idx == -1) {
        cout << "  [!] This CNIC is not registered in the system.\n";
    } else {
        printDash(40);
        cout << "  Voter Found!\n";
        printDash(40);
        cout << "  Voter Number  : " << (idx + 1) << "\n"
             << "  Full Name     : " << voterNames[idx] << "\n"
             << "  CNIC          : " << maskCNIC(voterCNICs[idx]) << "\n"
             << "  Vote Status   : "
             << (voterHasVoted[idx] ? "Already Voted" : "Has Not Voted Yet")
             << "\n";
        printDash(40);
    }

    pressEnterToContinue();
}

// ============================================================
//   ABOUT
// ============================================================

void showAbout() {
    cout << "\n";
    printLine(58);
    cout << "               ABOUT THIS SYSTEM\n";
    printLine(58);
    cout << "  System Name  : Pakistan Electronic Voting System\n"
         << "  Language     : C++\n"
         << "  Version      : Professional Edition\n"
         << "\n"
         << "  Features:\n"
         << "    - Voter Registration with CNIC validation\n"
         << "    - Secure Voting (One CNIC = One Vote)\n"
         << "    - Live Results with percentage bar chart\n"
         << "    - Candidates list with party and symbol\n"
         << "    - Registered voters list (masked CNIC)\n"
         << "    - Voter search by CNIC\n"
         << "    - Admin Panel (start / stop election)\n"
         << "    - Election statistics and turnout report\n"
         << "    - Admin password change\n"
         << "    - Votes reset functionality\n"
         << "\n"
         << "  Default Admin Credentials:\n"
         << "    Username : admin\n"
         << "    Password : admin123\n";
    printLine(58);
    pressEnterToContinue();
}

// ============================================================
//   ADMIN PANEL
// ============================================================

void adminStartElection() {
    if (electionOpen) {
        cout << "  [!] The election has already started.\n";
    } else if (voterCount == 0) {
        cout << "  [!] No voters are registered. Please register voters first.\n";
    } else {
        electionOpen = true;
        cout << "  [OK] Election has been STARTED successfully.\n"
             << "       " << voterCount << " registered voter(s) may now cast their vote.\n";
    }
    pressEnterToContinue();
}

void adminStopElection() {
    if (!electionOpen) {
        cout << "  [!] The election is not currently running.\n";
    } else {
        electionOpen = false;
        cout << "  [OK] Election has been STOPPED.\n"
             << "       No further votes will be accepted.\n";
    }
    pressEnterToContinue();
}

void adminResetVotes() {
    cout << "\n  WARNING: This will permanently delete ALL recorded votes!\n"
         << "  Type RESET to confirm: ";
    string confirm;
    cin >> confirm;

    if (confirm == "RESET") {
        for (int i = 0; i < MAX_CANDIDATES; i++) votes[i] = 0;
        for (int i = 0; i < voterCount;     i++) voterHasVoted[i] = false;
        cout << "  [OK] All votes have been reset. Voters may vote again.\n";
    } else {
        cout << "  Reset cancelled. No data has been changed.\n";
    }
    pressEnterToContinue();
}

void adminShowStats() {
    cout << "\n";
    printLine(50);
    cout << "             ELECTION STATISTICS\n";
    printLine(50);

    int votedCount = 0;
    for (int i = 0; i < voterCount; i++)
        if (voterHasVoted[i]) votedCount++;

    int    notVoted = voterCount - votedCount;
    double turnout  = (voterCount > 0) ? (votedCount * 100.0 / voterCount) : 0.0;

    cout << "  Election Status    : "
         << (electionOpen ? "OPEN" : "CLOSED") << "\n"
         << "  Registered Voters  : " << voterCount    << "\n"
         << "  Votes Cast         : " << votedCount     << "\n"
         << "  Did Not Vote       : " << notVoted       << "\n"
         << "  Voter Turnout      : " << fixed << setprecision(1) << turnout << "%\n"
         << "  Total Votes        : " << getTotalVotes() << "\n";

    printDash(50);
    int bars = (int)(turnout / 5);
    cout << "  Turnout  [";
    for (int b = 0; b <  bars; b++) cout << "#";
    for (int b = bars; b < 20; b++) cout << "-";
    cout << "] " << (int)turnout << "%\n";

    printLine(50);
    pressEnterToContinue();
}

void adminChangePassword() {
    cout << "\n";
    string oldPass, newPass, confirmPass;

    cout << "  Enter Current Password    : ";
    cin >> oldPass;

    if (oldPass != adminPassword) {
        cout << "  [!] Incorrect password.\n";
        pressEnterToContinue();
        return;
    }

    cout << "  Enter New Password        : ";
    cin >> newPass;

    if (newPass.length() < 6) {
        cout << "  [!] Password too short. Minimum 6 characters required.\n";
        pressEnterToContinue();
        return;
    }

    cout << "  Confirm New Password      : ";
    cin >> confirmPass;

    if (newPass != confirmPass) {
        cout << "  [!] Passwords do not match.\n";
        pressEnterToContinue();
        return;
    }

    adminPassword = newPass;
    cout << "  [OK] Password changed successfully.\n";
    pressEnterToContinue();
}

void adminPanel() {
    cout << "\n";
    printLine(45);
    cout << "                ADMIN LOGIN\n";
    printLine(45);

    string username, password;
    cout << "  Username : ";
    cin >> username;
    cout << "  Password : ";
    cin >> password;

    if (username != adminUsername || password != adminPassword) {
        cout << "  [!] Invalid credentials. Access denied.\n";
        pressEnterToContinue();
        return;
    }

    cout << "  [OK] Login successful. Welcome, Administrator.\n";

    int choice;
    while (true) {
        cout << "\n";
        printLine(46);
        cout << "                 ADMIN PANEL\n";
        printLine(46);
        cout << "  1.  Start Election\n"
             << "  2.  Stop Election\n"
             << "  3.  View Statistics\n"
             << "  4.  Reset All Votes\n"
             << "  5.  Change Admin Password\n"
             << "  6.  View Candidates List\n"
             << "  7.  Back to Main Menu\n";
        printLine(46);
        cout << "  Enter choice (1-7): ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            clearInputBuffer();
            cout << "  [!] Invalid input. Please enter a number.\n";
            continue;
        }

        if      (choice == 1) adminStartElection();
        else if (choice == 2) adminStopElection();
        else if (choice == 3) adminShowStats();
        else if (choice == 4) adminResetVotes();
        else if (choice == 5) adminChangePassword();
        else if (choice == 6) { showCandidatesList(); pressEnterToContinue(); }
        else if (choice == 7) { cout << "  Returning to main menu...\n"; break; }
        else                    cout << "  [!] Invalid choice. Please enter 1-7.\n";
    }
}

// ============================================================
//   MAIN
// ============================================================

int main() {
    showBanner();

    cout << "  Welcome to the Pakistan Electronic Voting System!\n"
         << "  Before voting begins, please log in to the Admin Panel\n"
         << "  and start the election (Admin > Start Election).\n\n"
         << "  Default credentials -> Username: admin | Password: admin123\n";

    int choice;
    while (true) {
        showMainMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            clearInputBuffer();
            cout << "  [!] Invalid input. Please enter a number between 1 and 9.\n";
            continue;
        }

        if      (choice == 1) registerVoter();
        else if (choice == 2) castVote();
        else if (choice == 3) showResults();
        else if (choice == 4) { showCandidatesList(); pressEnterToContinue(); }
        else if (choice == 5) showVotersList();
        else if (choice == 6) searchVoter();
        else if (choice == 7) showAbout();
        else if (choice == 8) adminPanel();
        else if (choice == 9) {
            cout << "\n";
            printLine(40);
            cout << "  Thank you for using this system.\n"
                 << "  Pakistan Zindabad!\n";
            printLine(40);
            break;
        } else {
            cout << "  [!] Invalid choice. Please enter a number between 1 and 9.\n";
        }
    }

    return 0;
}