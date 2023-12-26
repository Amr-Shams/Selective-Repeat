//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "config.h"
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
config::config(const std::string &fileName)
{
    std::string line;
    std::vector<std::string> lines;
    std::ifstream file(fileName);
    while (getline(file, line))
        lines.push_back(line);
    file.close();
    std::stringstream ss(lines[0]);
    ss >> nodeID >> startingTime;
}

