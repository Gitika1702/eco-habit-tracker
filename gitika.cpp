#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ===== CLASS 1: PERSON =====
class Person {
protected:
    string name;
    long phone;

public:
    Person() {
        name = "Unknown";
        phone = 0;
    }

    virtual void getDetails() {
        cout << "Enter Person Name: ";
        cin >> name;
        cout << "Enter Phone Number: ";
        cin >> phone;
    }

    virtual void showDetails() const {
        cout << "Name: " << name << " | Phone: " << phone;
    }

    virtual ~Person() {}
};

// ===== CLASS 2: ACTIVITY =====
class Activity : public Person {
protected:
    int treesPlanted;
    int cyclingMinutes;
    int coinsEarned;
    static int totalTreesPlanted;
    static int totalCoinsEarned;

public:
    Activity() {
        treesPlanted = 0;
        cyclingMinutes = 0;
        coinsEarned = 0;
    }

    void logActivity() {
        getDetails();
        cout << "Enter Number of Trees Planted: ";
        cin >> treesPlanted;
        cout << "Enter Minutes Spent Cycling: ";
        cin >> cyclingMinutes;

        // Calculate coins
        coinsEarned = treesPlanted * 1 + (cyclingMinutes / 5);
        totalTreesPlanted += treesPlanted;
        totalCoinsEarned += coinsEarned;

        // Save to file
        ofstream fout("environment.txt", ios::app);
        if (!fout) {
            cout << "Error opening file!\n";
            return;
        }

        fout << "==== ENVIRONMENT ACTIVITY RECORD ====\n";
        fout << "Name: " << name << endl;
        fout << "Phone: " << phone << endl;
        fout << "Trees Planted: " << treesPlanted << endl;
        fout << "Cycling Minutes: " << cyclingMinutes << endl;
        fout << "Coins Earned: " << coinsEarned << endl;
        fout << "=====================================\n\n";
        fout.close();

        cout << "\nActivity Logged Successfully!\n";
    }

    void showActivity() const {
        cout << "Name: " << name << " | Phone: " << phone
             << " | Trees: " << treesPlanted
             << " | Cycling: " << cyclingMinutes << " mins"
             << " | Coins: " << coinsEarned << endl;
    }

    int getCoins() const { return coinsEarned; }

    static void showTotalTrees() {
        cout << "\nTotal Trees Planted So Far: " << totalTreesPlanted << endl;
    }

    static void showTotalCoins() {
        cout << "\nTotal Coins Earned So Far: " << totalCoinsEarned << endl;
    }
};

int Activity::totalTreesPlanted = 0;
int Activity::totalCoinsEarned = 0;

// ===== CLASS 3: VOLUNTEER =====
class Volunteer : public Person {
    string contributionType;

public:
    void getDetails() override {
        Person::getDetails();
        cout << "Enter Type of Contribution (TreeDonation/Cleaning/Education): ";
        cin >> contributionType;

        ofstream fout("environment.txt", ios::app);
        if (!fout) {
            cout << "Error opening file!\n";
            return;
        }

        fout << "==== VOLUNTEER RECORD ====\n";
        fout << "Name: " << name << endl;
        fout << "Phone: " << phone << endl;
        fout << "Contribution: " << contributionType << endl;
        fout << "==========================\n\n";
        fout.close();

        cout << "\nVolunteer Details Saved!\n";
    }

    void showDetails() const override {
        cout << "Volunteer: " << name << " | Phone: " << phone
             << " | Contribution: " << contributionType << endl;
    }
};

// ===== FRIEND FUNCTION FOR REWARDS =====
class Reward {
    int totalCoins;
    friend void showReward(Reward);

public:
    Reward(int c = 0) { totalCoins = c; }
    void setCoins(int c) { totalCoins = c; }
    int getCoins() const { return totalCoins; }
};

void showReward(Reward r) {
    cout << "\nTotal Coins Earned This Session: " << r.totalCoins << " 🪙\n";
}

// ===== TEMPLATE CLASS (Environmental Officers) =====
template <class T> class Officer {
    T arr[3];

public:
    void setOfficer(int i, T name) { arr[i] = name; }
    void showOfficers() {
        cout << "\nEnvironment Officers: ";
        for (int i = 0; i < 3; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};

// ===== MAIN FUNCTION =====
int main() {
    int choice;
    Activity a1;
    Activity sessionActs[20];
    int actCount = 0;
    int totalSessionCoins = 0;

    Volunteer vol;
    Officer<string> envOfficers;
    envOfficers.setOfficer(0, "Officer_A");
    envOfficers.setOfficer(1, "Officer_B");
    envOfficers.setOfficer(2, "Officer_C");

    Reward reward;

    cout << "==== ENVIRONMENT MANAGEMENT SYSTEM 🌱 ====\n";

    do {
        cout << "\n1. Log New Activity (Tree/Cycling)";
        cout << "\n2. View Current Session Activities";
        cout << "\n3. Add Volunteer";
        cout << "\n4. Show Total Trees Planted";
        cout << "\n5. Show Total Coins (This Session)";
        cout << "\n6. Show Officers";
        cout << "\n7. View All Saved Data";
        cout << "\n8. Exit";
        cout << "\nEnter Your Choice: ";
        cin >> choice;

        if (!cin) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Try again.\n";
            continue;
        }

        switch (choice) {
        case 1:
            a1.logActivity();
            if (actCount < 20) {
                sessionActs[actCount++] = a1;
                totalSessionCoins += a1.getCoins();
                reward.setCoins(totalSessionCoins);
            } else {
                cout << "Maximum session activities reached!\n";
            }
            break;

        case 2:
            if (actCount == 0)
                cout << "\nNo activities logged yet!\n";
            else {
                cout << "\nCurrent Session Activities:\n";
                for (int i = 0; i < actCount; i++)
                    sessionActs[i].showActivity();
                Activity::showTotalTrees();
            }
            break;

        case 3:
            vol.getDetails();
            vol.showDetails();
            break;

        case 4:
            Activity::showTotalTrees();
            break;

        case 5:
            showReward(reward);
            break;

        case 6:
            envOfficers.showOfficers();
            break;

        case 7: {
            ifstream fin("environment.txt");
            if (!fin) {
                cout << "No environment data file found!\n";
            } else {
                cout << "\n--- All Saved Environment Data ---\n";
                string line;
                while (getline(fin, line))
                    cout << line << endl;
                fin.close();
            }
            break;
        }

        case 8: {
            ofstream fout("environment.txt", ios::app);
            fout << "==== SESSION SUMMARY ====\n";
            fout << "Total Activities Logged: " << actCount << endl;
            fout << "Total Coins Earned: " << totalSessionCoins << " 🪙" << endl;
            fout << "==========================\n\n";
            fout.close();

            cout << "\nSession summary saved. Thank you for helping the planet! 🌏\n";
            break;
        }

        default:
            cout << "\nInvalid choice! Please select between 1–8.\n";
        }

    } while (choice != 8);

    return 0;
}