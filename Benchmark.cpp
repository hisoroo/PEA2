#include "Benchmark.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

void Benchmark::runBenchmark(const Config &config)
{
    fs::create_directories("outputFiles/txt");
    fs::create_directories("outputFiles/csv");

    string outputFilePath = "outputFiles/txt/" + config.outputFile;
    ofstream outputFile(outputFilePath);
    if (!outputFile.is_open())
    {
        cerr << "Nie można otworzyć pliku wyjściowego.\n";
        exit(1);
    }
    if (!config.inputFile.empty())
    {
        Matrix distanceMatrix(config.inputFile);
        TSP tsp(distanceMatrix);

        cout << "Wczytano macierz z pliku: " << config.inputFile << "\n";
        outputFile << "Wczytano macierz z pliku: " << config.inputFile << "\n";

        // B&B BSF
        auto startBFS = chrono::high_resolution_clock::now();
        int BFSDistance = tsp.branchAndBoundBFS();
        auto endBFS = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> durationBFS = endBFS - startBFS;

        outputFile << "B&B BSF: " << BFSDistance << ", Czas: " << durationBFS.count() << " ms\n";
        cout << "B&B BSF: " << BFSDistance << ", Czas: " << durationBFS.count() << " ms\n";

        // B&B DFS
        auto startDFS = chrono::high_resolution_clock::now();
        int DFSDistance = tsp.depthFirstSearch();
        auto endDFS = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> durationDFS = endDFS - startDFS;

        outputFile << "B&B DFS: " << DFSDistance << ", Czas: " << durationDFS.count() << " ms\n";
        cout << "B&B DFS: " << DFSDistance << ", Czas: " << durationDFS.count() << " ms\n";

        // B&B BFS
        auto startBSF = chrono::high_resolution_clock::now();
        int BSFDistance = tsp.breadthFirstSearch();
        auto endBSF = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> durationBSF = endBSF - startBSF;

        outputFile << "B&B BFS: " << BSFDistance << ", Czas: " << durationBSF.count() << " ms\n";
        cout << "B&B BFS: " << BSFDistance << ", Czas: " << durationBSF.count() << " ms\n";
    }
    else
    {
        for (int n : config.NCities)
        {
            cout << "\nRozmiar problemu N = " << n << "\n";
            outputFile << "\nRozmiar problemu N = " << n << "\n";

            string csvFileName = "outputFiles/csv/output" + to_string(n) + ".csv";
            ofstream csvFile(csvFileName);

            if (!csvFile.is_open())
            {
                cerr << "Nie można otworzyć pliku CSV: " << csvFileName << "\n";
                exit(1);
            }

            csvFile << "Iteracja;B&B BSF(ms);B&B DFS(ms);B&B BFS(ms)\n";

            double totalTimeBFS = 0.0;
            double totalTimeDFS = 0.0;
            double totalTimeBSF = 0.0;

            for (int i = 0; i < config.repetitions; ++i)
            {
                Matrix distanceMatrix(n, config.distanceMin, config.distanceMax, config.isSymmetric);
                TSP tsp(distanceMatrix);

                if (config.showProgressBar)
                {
                    int progress = (i + 1) * 100 / config.repetitions;
                    int pos = 50 * progress / 100;
                    cout << "\rRozmiar problemu (ilość miast): " << n << " | Postęp: [";
                    for (int i = 0; i < 50; ++i)
                    {
                        if (i < pos)
                            cout << "=";
                        else if (i == pos)
                            cout << ">";
                        else
                            cout << " ";
                    }
                    cout << "] " << progress << "%";
                    cout.flush();
                }

                // B&B BSF
                auto startBFS = chrono::high_resolution_clock::now();
                int BFSDistance = tsp.branchAndBoundBFS();
                auto endBFS = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> durationBFS = endBFS - startBFS;
                totalTimeBFS += durationBFS.count();

                // B&B DFS
                auto startDFS = chrono::high_resolution_clock::now();
                int DFSDistance = tsp.depthFirstSearch();
                auto endDFS = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> durationDFS = endDFS - startDFS;
                totalTimeDFS += durationDFS.count();

                // B&B BFS
                auto startBSF = chrono::high_resolution_clock::now();
                int BSFDistance = tsp.breadthFirstSearch();
                auto endBSF = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> durationBSF = endBSF - startBSF;
                totalTimeBSF += durationBSF.count();

                csvFile << (i + 1) << ";" << durationBFS.count() << ";" << durationDFS.count() << ";" << durationBSF.count() << "\n";
                outputFile << "Iteracja " << i + 1 << ", BSF: " << BFSDistance << ", DFS: " << DFSDistance << ", BFS: " << BSFDistance << ", Czas BSF: " << durationBFS.count() << " ms, Czas DFS: " << durationDFS.count() << " ms, Czas BFS: " << durationBSF.count() << " ms\n";
                outputFile << "-----------------------------\n";
            }

            csvFile.close();

            double averageTimeBFS = totalTimeBFS / config.repetitions;
            double averageTimeDFS = totalTimeDFS / config.repetitions;
            double averageTimeBSF = totalTimeBSF / config.repetitions;

            cout << "\nŚredni czas dla algorytmu B&B BSF: " << averageTimeBFS << " ms";
            cout << "\nŚredni czas dla algorytmu B&B DFS: " << averageTimeDFS << " ms";
            cout << "\nŚredni czas dla algorytmu B&B BFS: " << averageTimeBSF << " ms";
        }
    }
    outputFile.close();
}
