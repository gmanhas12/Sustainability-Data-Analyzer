#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct SustainabilityData {
    string supplier;
    double emissions;
    double waste;
    double waterUsage;
};

vector<SustainabilityData> readData(const string& filename) {
    vector<SustainabilityData> data;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return data;
    }
    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        SustainabilityData entry;
        string emissions, waste, water;
        getline(ss, entry.supplier, ',');
        getline(ss, emissions, ',');
        getline(ss, waste, ',');
        getline(ss, water, ',');
        try {
            entry.emissions = stod(emissions);
            entry.waste = stod(waste);
            entry.waterUsage = stod(water);
            data.push_back(entry);
        } catch (exception& e) {
            cerr << "Skipping invalid data row: " << line << endl;
        }
    }
    file.close();
    return data;
}

void analyzeData(const vector<SustainabilityData>& data) {
    if (data.empty()) {
        cout << "No valid data available for analysis." << endl;
        return;
    }
    
    double totalEmissions = 0, totalWaste = 0, totalWater = 0;
    double maxEmissions = numeric_limits<double>::min();
    string worstSupplier;
    for (const auto& entry : data) {
        totalEmissions += entry.emissions;
        totalWaste += entry.waste;
        totalWater += entry.waterUsage;
        
        if (entry.emissions > maxEmissions) {
            maxEmissions = entry.emissions;
            worstSupplier = entry.supplier;
        }
    }
    cout << "--- Sustainability Data Analysis Report ---" << endl;
    cout << "Total CO2 Emissions: " << totalEmissions << " tons" << endl;
    cout << "Total Waste: " << totalWaste << " kg" << endl;
    cout << "Total Water Usage: " << totalWater << " liters" << endl;
    cout << "Supplier with Highest Emissions: " << worstSupplier << " (" << maxEmissions << " tons)" << endl;
}

int main() {
    string filename = "sustainability_data.csv";
    vector<SustainabilityData> data = readData(filename);
    analyzeData(data);
    return 0;
}
