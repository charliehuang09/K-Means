#include <iostream>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <cmath>
using namespace std;
struct coord{
    int x;
    int y;
    coord(int x_, int y_){
        x = x_;
        y = y_;
    };
};
class K_Means {
private:
    vector<coord> data;
    int k;
    vector<coord> random(){
        vector<coord> out;
        for (int i = 0; i < k; i++) out.emplace_back(rand() % 100, rand() % 100);
        return out;
    }
    bool equal( vector<coord> a,  vector<coord> b){
        for (int i = 0; i < a.size(); i++) if (a[i].x != b[i].x && a[i].y != b[i].y) return false;
        return true;
    }
    int get_closest(coord input, vector<coord> a){
        int distance = INT16_MAX;
        int index;
        for (int i = 0; i < a.size(); i++){
            int t1 = (input.x - a[i].x) * (input.x - a[i].x);
            int t2 = (input.y - a[i].y) * (input.y - a[i].y);
            int curr_distance = sqrt(t1 + t2);
            if (curr_distance < distance){
                distance = curr_distance;
                index = i;
            }
        }
        return index;
    }
    int sse(vector<coord> input){
        int output = 0;
        for (int i = 0; i < data.size(); i++) output += data[get_closest(data[get_closest(data[i], input)], input)].x - input[i].x ^ 2 + data[get_closest(data[i], input)].y - input[i].y ^ 2;
        return output;
    }
public:
    vector<coord> centroids;
    int curr_sse;
    void initialize(vector<coord> data_, int k_){
        centroids.clear();
        data = data_;
        k = k_;
        for (int i = 0; i < k; i++){
            centroids.emplace_back(rand() % 100, rand() % 100);
        }
        curr_sse = sse(centroids);
    }
    void cycle(){
        vector<coord> prev = random();
        vector<coord> curr = random();
        while(!equal(prev, curr)){
            int meanx[k];
            int meany[k];
            int len[k];
            memset(meanx, 0, sizeof(meanx));
            memset(meany, 0, sizeof(meany));
            memset(len, 0, sizeof(len));
            for (int i = 0; i < data.size(); i++){
                int closest = get_closest(data[i], curr);
                meanx[closest] += data[i].x;
                meany[closest] += data[i].y;
                len[closest]++;
            }
            prev = curr;
            for (int i = 0; i < k; i++){
                curr[i].x = meanx[i] / len[i];
                curr[i].y = meany[i] / len[i];
            }
        }
        int t = sse(prev);
        if (curr_sse < t){
            centroids = prev;
            curr_sse = t;
        }
    }
    void fit(int times){
        for (int i = 0; i < times; i++) cycle();
    }
    void print_centroids(){
        for (int i = 0; i < centroids.size(); i++) cout << centroids[i].x << " " << centroids[i].y << "\n";
        cout << "\n\n";
    }
    void print_data(){
        for (int i = 0; i < data.size(); i++) cout << data[i].x << " " << data[i].y << "\n";
        cout << "\n\n";
    }
};

// Driver code
int main(){
    K_Means k_Means;
    vector<coord> data;
    for (int i = 0; i < 10000; i++){
        data.emplace_back(rand() % 20, rand() % 20);
        data.emplace_back((rand() % 20) + 40, (rand() % 20) + 40);
    }
    for (int i = 0; i < data.size(); i++){
        cout << data[i].x << " " << data[i].y << "\n";
    }
    k_Means.initialize(data, 2);
    k_Means.print_data();
    k_Means.fit(10);
    k_Means.print_centroids();
}
