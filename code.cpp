#include <iostream>
#include <vector>
#include <tuple>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <string>

//File to be input
std::string filename = "input.txt";
//Stores each process (key), and their allocated resources vs their max resources
std::unordered_map<int, std::tuple<std::vector<int>, std::vector<int>>> pcs;
//Stores running resource pool
std::vector<int> avl;
//Current running process #
int curr = 0;

void start();
std::vector<int> bankersAlgo();
void printV(std::vector<int>);


int main() {
    //Initializes all values
    start();
    //Bankers algo
    std::vector<int> ord = bankersAlgo();


    //Printing
    std::cout << "\nORDER: ";
    for (std::vector<int>::iterator it = ord.begin(); it != ord.end(); it++)
        std::cout << "P" << *it << " ";
    
    std::cout << std::endl << std::endl;
    return 0;
}

//Was used for debugging ignore
void printV(std::vector<int> v) {
    for (std::vector<int>::iterator i = v.begin(); i != v.end(); i++)
        std::cout << *i;
    return;

}

//Reads values from input.txt and sets global values accordingly
void start() {
    std::ifstream file(filename);
    
    if (!file) {
        std::cerr << "Could not open file: " << filename;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> vals;
        std::istringstream iss (line);
        int val;

        while(iss >> val)
            vals.push_back(val);
        
        if (avl.empty()) {
            avl = vals;
            continue;
        }
        
        size_t half = vals.size() / 2;
        std::vector<int> alloc(vals.begin(), vals.begin() + half);
        std::vector<int> max(vals.begin() + half, vals.end());
        
        if (alloc.size() != avl.size() || max.size() != avl.size()) {
            std::cerr << "Invalid size on process: " << curr;
            return;
        }
        pcs[curr] = {alloc, max};
        curr++;
    }
    return;
}
//Finds deadlocks with bankers algorithm
std::vector<int> bankersAlgo() {
    std::vector<int> order;

    while (!pcs.empty()) {
        bool progress = false;

        //auto is used instead of std::unordered_map<int, std:tuple<std::vector<int>, std::vector>>>::iterator
        //for ease of reading
        for (auto it = pcs.begin(); it != pcs.end(); ) {
            int pid = it->first;

            //Grab values from process map
            std::vector<int> alloc = std::get<0>(it->second);
            std::vector<int> max = std::get<1>(it->second);

            bool canRun = true;
            
            //Looks through maxValues of current process to see if it fits
            //Within available resources
            for (size_t i = 0; i < avl.size(); i++) {
                if (max[i] > avl[i] + alloc[i] ) {
                    canRun = false;
                    break;
                }
            }
            //If there are enough resources, add the process to the list
            //And remove it from the map of processes to run
            if (canRun) {
                order.push_back(pid);
                for (size_t i = 0; i < avl.size(); i++)
                    avl[i] += alloc[i];

                it = pcs.erase(it);
                progress = true;
            } else {
                ++it;
            }
        }
        //If reached end of process list without finding a process to run, deadlock detected
        if (!progress) {
            std::cerr << "Deadlock detected, cannot continue!\n";
            break;
        }
    }

    return order;
}
