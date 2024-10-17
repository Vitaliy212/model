#include <iostream>
#include <fstream>
#include <string>
#include "model.pb.h"
#include <google/protobuf/util/json_util.h>

using namespace std;

int main() {
    
    Experiment experiment;

    // JSON з файлу
    ifstream inputFile("json_env_clohtes.json");
    if (!inputFile.is_open()) {
        cerr << "Failed to open file!" << endl;
        return -1;
    }

    string jsonInput((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();

    // Десеріалізуємо JSON в Protobuf
    auto status = google::protobuf::util::JsonStringToMessage(jsonInput, &experiment);
    if (!status.ok()) {
        cerr << "JSON deserialization error: " << status.message() << endl;
        return -1;
    }



    cout << "ID: " << experiment.id() << endl;
    cout << "Hash: " << experiment.hash() << endl;
    cout << "Title: " << experiment.title() << endl;


    for (const auto& stage : experiment.stagemodellist()) {
        cout << "\n\t" << "Stagemodellist\n" << endl;
        cout << "Stage ID: " << stage.id() << endl;
        cout << "Stage Hash: " << stage.hash() << endl;
        cout << "Stage Title: " << stage.title() << endl;

        // Перебір activity
        for (const auto& activ : stage.activity()) {
            cout << "\n\t" << "Activity\n" << endl;
            cout << "Activity ID: " << activ.id() << endl;
            cout << "Activity Hash: " << activ.hash() << endl;
            cout << "Intensity: " << activ.intensityinwatt() << " W" << endl;
            cout << "Duration: " << activ.durationinminutes() << " minutes" << endl;
            cout << "Type: " << activ.typeactivity() << endl;
        }

        // Перебір BodyItem
        for (const auto& body : stage.body()) {
            cout << "\n\t" << "Body\n" << endl;
            cout << "Body ID: " << body.id() << endl;
            cout << "Body Hash: " << body.hash() << endl;

            // Перебір head у BodyItem
            for (const auto& head : body.head()) {
                cout << "\n\t" << "Head\n" << endl;
                for (const auto& env : head.environment()) {
                    cout << "Head Environment ID: " << env.id() << endl;
                    cout << "Head Environment Hash: " << env.hash() << endl;
                    cout << "Head Environment Type: " << env.typeenv() << endl;
                    cout << "Head Environment Temperature: " << env.temperatureincelsious() << " °C" << endl;
                    cout << "Head Environment Humidity: " << env.humidityinpercent() << "%" << endl;
                    cout << "Head Environment Wind Velocity: " << env.windvelocity() << " m/s" << endl;
                }
            }
            for (const auto& footLeft : body.footleft()) {
                cout << "\n\t" << "FootLeft\n"<< endl;
                for (const auto& env : footLeft.environment()) {
                    cout << "FootLeft Environment ID: " << env.id() << endl;
                    cout << "FootLeft Environment Hash: " << env.hash() << endl;
                    cout << "FootLeft Environment Type: " << env.typeenv() << endl;
                    cout << "FootLeft Environment Temperature: " << env.temperatureincelsious() << " °C" << endl;
                    cout << "FootLeft Environment Humidity: " << env.humidityinpercent() << "%" << endl;
                    cout << "FootLeft Environment Wind Velocity: " << env.windvelocity() << " m/s" << endl;
                }

                // Перебір Clothing у footLeft
                for (const auto& clothing : footLeft.clothing()) {
                    cout << "FootLeft Clothing ID: " << clothing.id() << endl;
                    cout << "FootLeft Clothing Hash: " << clothing.hash() << endl;
                    cout << "FootLeft Clothing Covering: " << clothing.covering() << endl;

                    for (const auto& fabric : clothing.fabric()) {
                        cout << "FootLeft Clothing Fabric ID: " << fabric.id() << endl;
                        cout << "FootLeft Clothing Fabric Hash: " << fabric.hash() << endl;
                        cout << "FootLeft Clothing Fabric Ref: " << fabric.ref() << endl;
                        cout << "FootLeft Clothing Fabric Rf: " << fabric.rf() << endl;
                        cout << "FootLeft Clothing Fabric IP: " << fabric.ip() << endl;
                        cout << "FootLeft Clothing Fabric Density: " << fabric.density() << endl;
                        cout << "FootLeft Clothing Fabric Thinckness: " << fabric.thinckness() << endl;
                    }
                }
            }
        }
        break;
    }

    return 0;
}
