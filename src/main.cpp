#include "Window.h"
// #include <matplot/matplot.h>
// #include <fstream>
// #include <sstream>
// #include <string>
// #include <vector>
// using namespace std;

// #undef CloseWindow
// #undef ShowCursor
// void show_output()
// {
//     // Vectors for each column
//     vector<double> time, population, deaths, sick, diseases;

//     // Read CSV
//     ifstream file("outputData.csv");
//     string line;

//     // Skip header
//     getline(file, line);

//     // Parse rows
//     while (getline(file, line))
//     {
//         stringstream ss(line);
//         string value;
//         vector<double> row;

//         while (getline(ss, value, ','))
//             row.push_back(stod(value));

//         time.push_back(row[0]);
//         population.push_back(row[1]);
//         deaths.push_back(row[2]);
//         sick.push_back(row[3]);
//         diseases.push_back(row[4]);
//     }

//     // Plot
//     matplot::hold(matplot::on);

//     matplot::plot(time, population)->display_name("population");
//     matplot::plot(time, deaths)->display_name("deaths");
//     matplot::plot(time, sick)->display_name("sick");
//     matplot::plot(time, diseases)->display_name("diseases");

//     matplot::legend();
//     matplot::show();
// }

int main()
{
    Window win;
    win.Run();

    return 0;
}
