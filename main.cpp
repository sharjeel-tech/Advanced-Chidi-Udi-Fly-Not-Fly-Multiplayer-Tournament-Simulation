#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
 
using namespace std;
 
const int N = 5;
const int ROUNDS = 5;
 
struct Player {
    bool active = true;
    string response;
    int survived = 0;
};
 
Player p[N];
 
vector<pair<string, bool>> items = {
    {"Eagle", true},
    {"Parrot", true},
    {"Crow", true},
    {"Pigeon", true},
    {"Duck", true},
    {"Dog", false},
    {"Cat", false},
    {"Horse", false},
    {"Lion", false},
    {"Elephant", false}
};
 
pthread_mutex_t mtx;
 
sem_t playerSem[N];
sem_t done;
sem_t evaluate;
 
string announcement;
bool isBird;
 
int activePlayers = N;
int roundNo = 0;
bool gameOver = false;
 
void* announcer(void*) {
 
    while (!gameOver && roundNo < ROUNDS && activePlayers > 1) {
 
        pthread_mutex_lock(&mtx);
 
        int idx = rand() % items.size();
        announcement = items[idx].first;
        isBird = items[idx].second;
        roundNo++;
 
        cout << "\n===== Round " << roundNo << " =====\n";
        cout << "Announcement: " << announcement << endl;
 
        pthread_mutex_unlock(&mtx);
 
        for (int i = 0; i < N; i++)
            sem_post(&playerSem[i]);
 
        sem_wait(&evaluate);
    }
 
    gameOver = true;
 
    for (int i = 0; i < N; i++)
        sem_post(&playerSem[i]);
 
    return NULL;
}
 
void* player(void* arg) {
 
    int id = *(int*)arg;
 
    while (true) {
 
        sem_wait(&playerSem[id]);
 
        if (gameOver)
            break;
 
        pthread_mutex_lock(&mtx);
 
        if (p[id].active) {
 
            bool answer = isBird;
 
            if (rand() % 100 < 20)
                answer = !answer;
 
            p[id].response = answer ? "Fly" : "Not Fly";
 
            cout << "Player "
                 << id + 1
                 << " -> "
                 << p[id].response
                 << endl;
        }
 
        pthread_mutex_unlock(&mtx);
 
        sem_post(&done);
    }
 
    return NULL;
}
 
void* referee(void*) {
 
    while (!gameOver) {
 
        for (int i = 0; i < N; i++)
            sem_wait(&done);
 
        pthread_mutex_lock(&mtx);
 
        if (gameOver) {
            pthread_mutex_unlock(&mtx);
            break;
        }
 
        string correct = isBird ? "Fly" : "Not Fly";
 
        cout << "\nReferee Result:\n";
 
        for (int i = 0; i < N; i++) {
 
            if (!p[i].active)
                continue;
 
            if (p[i].response == correct) {
                p[i].survived++;
            }
            else {
                p[i].active = false;
                activePlayers--;
 
                cout << "Player "
                     << i + 1
                     << " Eliminated\n";
            }
        }
 
        cout << "Active Players: "
             << activePlayers
             << endl;
 
        if (activePlayers <= 1 || roundNo >= ROUNDS)
            gameOver = true;
 
        pthread_mutex_unlock(&mtx);
 
        sem_post(&evaluate);
    }
 
    return NULL;
}
 
int main() {
 
    srand(time(0));
 
    pthread_mutex_init(&mtx, NULL);
 
    sem_init(&done, 0, 0);
    sem_init(&evaluate, 0, 0);
 
    for (int i = 0; i < N; i++)
        sem_init(&playerSem[i], 0, 0);
 
    pthread_t ann, ref, players[N];
    int ids[N];
 
    pthread_create(&ann, NULL, announcer, NULL);
    pthread_create(&ref, NULL, referee, NULL);
 
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&players[i], NULL, player, &ids[i]);
    }
 
    pthread_join(ann, NULL);
    pthread_join(ref, NULL);
 
    for (int i = 0; i < N; i++)
        pthread_join(players[i], NULL);
 
    cout << "\n===== Final Result =====\n";
 
    bool winnerFound = false;
 
    for (int i = 0; i < N; i++) {
        if (p[i].active) {
            cout << "Winner: Player " << i + 1 << endl;
            winnerFound = true;
        }
    }
 
    if (!winnerFound)
        cout << "No Winner\n";
 
    cout << "\nSurvival Statistics:\n";
 
    for (int i = 0; i < N; i++) {
        cout << "Player "
             << i + 1
             << " survived "
             << p[i].survived
             << " rounds "
             << (p[i].active ? "(Active)" : "(Eliminated)")
             << endl;
    }
 
    pthread_mutex_destroy(&mtx);
 
    sem_destroy(&done);
    sem_destroy(&evaluate);
 
    for (int i = 0; i < N; i++)
        sem_destroy(&playerSem[i]);
 
    return 0;
}
 
