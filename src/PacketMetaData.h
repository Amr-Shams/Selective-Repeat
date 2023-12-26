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

#ifndef PACKETMETADATA_H_
#define PACKETMETADATA_H_

#include <string>
class PacketMetaData {
public:
    PacketMetaData(const std::string &line);
    // getter to the payload
    std::string getPayload() const
    {
        return payload;
    }
    // getter to the error code
    std::string getErrorCode() const
    {
        return errorCode;
    }
    // check if it has a modification error
    bool hasModificationError() const
    {
        return errorCode[0] == '1';
    }
    // check if it has a loss error
    bool hasLossError() const
    {
        return errorCode[1] == '1';
    }
    // check if it has a duplication error
    bool hasDuplicationError() const
    {
        return errorCode[2] == '1';
    }
    // check if it has a delay error
    bool hasDelayError() const
    {
        return errorCode[3] == '1';
    }
    // unset all errors
    void unsetAllErrors()
    {
        errorCode = "0000";
        modifiedBitPosition = -1;
    }
    // modified bit position
    int modifiedBitPosition { -1 };

    virtual ~PacketMetaData();
private:
    std::string payload;
    std::string errorCode;
    static constexpr int LENGTH_OF_ERROR_CODE = 4, BEGIN_OF_PAYLOAD = 5;
};

#endif /* PACKETMETADATA_H_ */
