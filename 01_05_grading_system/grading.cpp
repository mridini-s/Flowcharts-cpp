#include <iostream>
using namespace std;

int getScore() {
    int score;
    cout << "Enter score: ";
    cin >> score;
    return score;
}

bool isScoreValid(int score) {
    return (score >= 0 && score <= 100);
}

char getGrade(int score) {
    if (score >= 80) return 'A';
    else if (score >= 60) return 'B';
    else if (score >= 50) return 'C';
    else return 'F';
}

void displayGrade(char grade) {
    if (grade == 'F')
        cout << "Fail\n";
    else
        cout << "Grade: " << grade << "\n";
}

int main() {
    int score = getScore();
   
    if (!isScoreValid(score)) {
        cout << "Invalid score entered.\n";
        return 0;
    }

    char grade = getGrade(score);
    displayGrade(grade);

    return 0;
}
