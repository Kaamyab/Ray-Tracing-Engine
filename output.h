#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include <fstream>
#include <iomanip>

class output {
public:
    static void write_ppm(const char* filename, unsigned int ***image, int height, int width) {
        std::ofstream outFile(filename);

        if (!outFile.is_open()) {
            std::cerr << "Error: Unable to open the file for writing." << std::endl;
            return;
        }

        // Write PPM header
        outFile << "P3\n";
        outFile << width << " " << height << "\n";
        outFile << "255\n";
        std::cout << '\n';

        // Write pixel values
        for (int j = 0; j < height; ++j) {
            print_progressbar((j/height)*100, "Processing The Image:");
            for (int i = 0; i < width; ++i) {
                for (int c = 0; c < 3; ++c) {   
                    outFile << image[j][i][c] << " ";
                }
                outFile << "\n";
            }
            outFile << "\n";
        }
        print_progressbar(100, "Processing The Image:");
        std::cout << '\n';

        std::cout << "PPM file written successfully." << std::endl;
        outFile.close();
    }

    // Progressbar Percentage implementation
    static void print_progressbar(int percent, std::string title = "Scanlines Process:")
    {
        const int barWidth = 100;
        int progress = static_cast<int>((static_cast<double>(percent) / 100) * barWidth);

        std::cout << "\r" << title << " [";
        for (int i = 0; i < progress; ++i) std::cout << "#";
        for (int i = progress; i < barWidth; ++i) std::cout << " ";
        std::cout << "] " << std::setw(3) << percent << "% " << std::flush;
    }

};

#endif
