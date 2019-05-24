/**
 * CS 202 - HW 4
 * A main file
 * Please make sure that your code compiles and runs with this main file
 */
#include "graph.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
 /*You can add additional libraries here to read and process the dataset*/

using namespace std;

int main() {
    Graph g;
    std::ifstream input("flightDataset.txt");

    if (input.is_open()) {
        std::string freq;
        std::string delim = ";";
        while (std::getline(input, freq)) {
            std::stringstream toSplit(freq);
            std::string item;
            std::vector<std::string> splits;
            char delim = ';';
            while (std::getline(toSplit, item, delim))
            {
                splits.push_back(item);
            }

            int num = std::atoi(splits.back().c_str());
            //std::cout << num << std::endl;
            splits.pop_back();
            std::string airport1 = splits.back();
            //std::cout << airport1 << std::endl;
            splits.pop_back();
            std::string airport2 = splits.back();
            //std::cout << airport2 << std::endl;
            splits.pop_back();

            g.addAirport(airport1);
            g.addAirport(airport2);
            g.addConnection(airport1,airport2,num);
        }
    }
    input.close();

    std::cout << "---------------------------------------------------------------------------" << std::endl;

    std::list<string> li = g.getAdjacentAirports("NORWICH");
    std::cout << "Airports Adjacent To NORWICH: " << std::endl;
    for (auto const& i : li) {
       std::cout << i << std::endl;
    }

    std::cout << "---------------------------------------------------------------------------" << std::endl;

    int total = g.getTotalPassengers("KIRKWALL");
    std::cout << "Total Passenger Number At KIRWALL: " << total << std::endl;

    std::cout << "---------------------------------------------------------------------------" << std::endl;

    std::list<pair<string,string>> list = g.findMST();
    for (auto const& i : list) {
        std::cout << i.first << "-" << i.second << std::endl;
    }

    std::cout << "---------------------------------------------------------------------------" << std::endl;
    std::list<string> list2 = g.findShortestPath("KIRKWALL","JERSEY");
    for (auto const& i : list2) {
        std::cout << i << std::endl;
    }

    std::cout << "---------------------------------------------------------------------------" << std::endl;

    g.deleteAirport("HUMBERSIDE");
    li = g.getAdjacentAirports("NORWICH");
    std::cout << "Airports Adjacent To NORWICH: " << std::endl;
    for (auto const& i : li) {
        std::cout << i << std::endl;
    }

    std::cout << "---------------------------------------------------------------------------" << std::endl;

    g.deleteAirport("KIRKWALL");
    total = g.getTotalPassengers("KIRKWALL");
    std::cout << "After KIRKWALL Deleted: " << total << std::endl;



    return 0;
}
// End of main file