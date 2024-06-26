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

#ifndef PAYLOADSTUFFER_H_
#define PAYLOADSTUFFER_H_

#include <string>
class PayLoadStuffer {
public:
    PayLoadStuffer();
    // TODO - Generated destructor
    static std::string stuff(const std::string &payload);
private:
// we use the following characters to mark the beginning and end of a packet
// static for efficiency and constexpr for compile-time evaluation
    static constexpr char FLAG = '$';
    static constexpr char ESCAPE = '/';
};

#endif /* PAYLOADSTUFFER_H_ */
