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

package sr_aqn;

//
// TODO auto-generated module
//
simple Node
{
	parameters:
        double timerDuration = default(0.0);
        double messageDelayTime = default(0.0);
        double messageProcessingTime = default(0.0);
        int windowSize = default(0);
        string inputFile = default("");
        string outputFile = default("");
        int id = default(0);
        volatile double lossRate = default(0.0);
        volatile double random = uniform(0, 1); 
    gates:
        input in;
        input in_cor;
        output out;
}