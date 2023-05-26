#pragma once
#include <list>
#include <vector>
#include <Eigen/Dense>
#include <string>
#include <fstream>
#include <iostream>


class OBJParser
{
public:
	static void getVertexesFromOBJFile(std::vector<Eigen::Vector4f>& vertexList, std::list<Eigen::Vector3i>& connectionsList, std::string fileName) {
		std::ifstream file(fileName);
        if (file.is_open()) { // sprawdzenie, czy uda�o si� otworzy� plik
            std::string line;
            while (getline(file, line)) { // odczytanie ka�dej linii pliku
                if (line.find("v") == 0) { // sprawdzenie, czy linia zaczyna si� od "v " (leci po ca�ym pliku zawsze zmieni� to!)
                    std::istringstream iss(line);
                    std::string v;
                    float x, y, z;

                    iss >> v >> x >> y >> z; // wczytanie warto�ci x, y i z

                    if (iss.fail()) { // sprawdzenie, czy nie wyst�pi� b��d podczas wczytywania
                        std::cout << "Error while reading file." << std::endl;
                        vertexList.clear();
                        return;
                    }

                    vertexList.push_back(Eigen::Vector4f(x,y,z,1)); // dodanie nowego obiektu Vector3D do wektora
                }
                if (line.find("f") == 0) {
                    std::istringstream iss(line);
                    std::string f;
                    int x, y, z;

                    iss >> f >> x >> y >> z; // wczytanie warto�ci x, y i z

                    if (iss.fail()) { // sprawdzenie, czy nie wyst�pi� b��d podczas wczytywania
                        std::cout << "Error while reading file." << std::endl;
                        vertexList.clear();
                        return;
                    }

                    connectionsList.push_back(Eigen::Vector3i(x,y,z)); // dodanie nowego obiektu Vector3D do wektora
                }
            }

            file.close(); // zamkni�cie pliku
        }
        else { // obs�uga b��du, je�li nie uda�o si� otworzy� pliku
            std::cout << "Error opening file." << std::endl;
            return;
        }
	}

private:
	std::vector<Eigen::Vector4f>* vertexesList1;
	std::list<Eigen::Vector3i>* connectionsList;
};

