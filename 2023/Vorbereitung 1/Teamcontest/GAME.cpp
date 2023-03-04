#include <assert.h>
#include <limits.h>
#include <iostream>
#include <vector>

int pile[98];
int pileOff = 0;

std::vector<int> hand;
std::vector<int> rows[4];

int main() {
    for(int i = 0; i < 98; i++) std::cin >> pile[i];

    hand.reserve(8);
    for(int i = 0; i < 8; i++) hand.push_back(pile[pileOff++]);

    rows[0].push_back(1);
    rows[1].push_back(1);
    rows[2].push_back(100);
    rows[3].push_back(100);

    while(hand.size() > 0) {
        for(int i = 0; i < 2; i++) {
            int cost = INT_MAX, idx = -1, row = -1;
            for(int j = 0; j < hand.size(); j++) {
                for(int k = 0; k < 2; k++) {
                    int lv = rows[k][rows[k].size()-1];

                    int c;
                    if(lv - 10 == hand[j]) c = INT_MIN;
                    else if(hand[j] < lv) continue;
                    else c = hand[j] - lv;

                    if(c < cost) {
                        cost = c;
                        idx = j;
                        row = k;
                    }
                }
                for(int k = 2; k < 4; k++) {
                    int lv = rows[k][rows[k].size()-1];

                    int c;
                    if(lv + 10 == hand[j]) c = INT_MIN;
                    else if(hand[j] > lv) continue;
                    else c = lv - hand[j];

                    if(c < cost) {
                        cost = c;
                        idx = j;
                        row = k;
                    }
                }
            }

            if(idx < 0) goto end;
            assert(row >= 0 && row < 4 && idx >= 0 && idx < hand.size());
            rows[row].push_back(hand[idx]);
            hand.erase(hand.begin() + idx);
        }

        for(int i = 0; i < 2; i++) {
            if(pileOff < 98) hand.push_back(pile[pileOff++]);
        }
    }

    end:;
    for(int i = 0; i < 4; i++) {
        for(int v : rows[i]) std::cout << v << " ";
        std::cout << std::endl;
    }

    for(int v : hand) std::cout << v << " ";
    std::cout << std::endl;

    while(pileOff < 98) std::cout << pile[pileOff++] << " ";
    std::cout << std::endl;

    return 0;
}