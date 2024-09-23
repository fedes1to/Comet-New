/*
    the hex patch shit is pasted from KittyMemory but ported over to windows :)
    TODO: FIGURE OUT IF WINDOWS HAS ADDRESS PROTECTION
*/ 

/*
    Convert a hex string to a block of data
*/
void dataFromHex(
        const std::string &in, //!< Input hex string
        void *data       //!< Data store
) {
    size_t length = in.length();
    auto *byteData = reinterpret_cast<unsigned char *>(data);

    std::stringstream hexStringStream;
    hexStringStream >> std::hex;
    for (size_t strIndex = 0, dataIndex = 0; strIndex < length; ++dataIndex) {
        // Read out and convert the string two characters at a time
        const char tmpStr[3] = {in[strIndex++], in[strIndex++], 0};

        // Reset and fill the string stream
        hexStringStream.clear();
        hexStringStream.str(tmpStr);

        // Do the conversion
        int tmpValue = 0;
        hexStringStream >> tmpValue;
        byteData[dataIndex] = static_cast<unsigned char>(tmpValue);
    }
}

/*
    Convert a block of data to a hex string
*/
std::string data2Hex(
    const void* data,        //!< Data to convert
    const size_t dataLength //!< Length of the data to convert
) {
    const auto* byteData = reinterpret_cast<const unsigned char*>(data);
    std::stringstream hexStringStream;

    hexStringStream << std::hex << std::setfill('0');
    for (size_t index = 0; index < dataLength; ++index)
        hexStringStream << std::setw(2) << static_cast<int>(byteData[index]);
    return hexStringStream.str();
}

void Trim(std::string& str)
{
    // https://www.techiedelight.com/remove-whitespaces-string-cpp/
    str.erase(std::remove_if(str.begin(), str.end(), [](char c)
        { return (c == ' ' || c == '\n' || c == '\r' ||
            c == '\t' || c == '\v' || c == '\f'); }),
        str.end());
}

bool ValidateHex(std::string &hex) 
{
    if (hex.empty()) return false;

    if (hex.compare(0, 2, "0x") == 0)
        hex.erase(0, 2);

    Trim(hex); // first remove spaces
    
    if (hex.length() < 2 || hex.length() % 2 != 0) return false;

    for (size_t i = 0; i < hex.length(); i++) {
        if (!std::isxdigit((unsigned char) hex[i]))
            return false;
    }
    
    return true;
}

class MemoryPatch
{
private:
    uintptr_t _address;
    size_t _size;

    std::vector<uint8_t> _orig_code;
    std::vector<uint8_t> _patch_code;

public:
    MemoryPatch() {
        _address = 0;
        _size = 0;
        _orig_code.clear();
        _patch_code.clear();
    }

    ~MemoryPatch() {
        _orig_code.clear();
        _orig_code.shrink_to_fit();

        _patch_code.clear();
        _patch_code.shrink_to_fit();
    }

    static MemoryPatch createWithBytes(uintptr_t absolute_address, const void *patch_code, size_t patch_size) {
        MemoryPatch patch;

        if (!absolute_address || !patch_code || patch_size < 1)
            return patch;

        patch._address = absolute_address;
        patch._size = patch_size;

        patch._orig_code.resize(patch_size);
        patch._patch_code.resize(patch_size);

        // initialize patch & backup current content
        memcpy(&patch._patch_code[0], patch_code, patch_size);
        memcpy(&patch._orig_code[0], reinterpret_cast<const void *>(patch._address), patch_size);
        return patch;
    }

    static MemoryPatch createWithHex(uintptr_t absolute_address, std::string hex) {
        MemoryPatch patch;

        if (!absolute_address || !ValidateHex(hex))
            return patch;

        patch._address = absolute_address;
        patch._size = hex.length() / 2;

        patch._orig_code.resize(patch._size);
        patch._patch_code.resize(patch._size);

        // initialize patch
        dataFromHex(hex, &patch._patch_code[0]);

        // backup current content
        memcpy(&patch._orig_code[0], reinterpret_cast<const void *>(patch._address), patch._size);
        return patch;
    }

    static MemoryPatch createWithHex(uintptr_t absolute_address, std::string hex, bool enabled) {
        MemoryPatch patch;

        if (!absolute_address || !ValidateHex(hex))
            return patch;

        patch._address = absolute_address;
        patch._size = hex.length() / 2;

        patch._orig_code.resize(patch._size);
        patch._patch_code.resize(patch._size);

        // initialize patch
        dataFromHex(hex, &patch._patch_code[0]);

        // backup current content
        memcpy(&patch._orig_code[0], reinterpret_cast<const void*>(patch._address), patch._size);

        if (enabled)
            patch.Modify();

        return patch;
    }

    bool isValid() const {
        return (_address != 0 && _size > 0 && _orig_code.size() == _size && _patch_code.size() == _size);
    }

    size_t get_PatchSize() const {
        return _size;
    }

    uintptr_t get_TargetAddress() const {
        return _address;
    }

    /*
     * Restores the patch to the original value
     */
    bool Restore() {
        if (!isValid()) return false;
        return memcpy(reinterpret_cast<void *>(_address), &_orig_code[0], _size);
    }

    /*
     * Applies patch modifications to the target address
     */
    bool Modify() {
        if (!isValid()) return false;
        return memcpy(reinterpret_cast<void *>(_address), &_patch_code[0], _size);
    }

    /*
     * Returns hex string of the current target address bytes
     */
    std::string get_CurrBytes() const {
        if (!isValid()) return "";
        return data2Hex(reinterpret_cast<const void *>(_address), _size);
    }

    /*
     * Returns hex string of the original bytes
     */
    std::string get_OrigBytes() const {
        if (!isValid()) return "";
        return data2Hex( _orig_code.data(), _orig_code.size());
    }
    
    /*
     * Returns hex string of the patch bytes
     */
    std::string get_PatchBytes() const {
        if (!isValid()) return "";
        return data2Hex(_patch_code.data(), _patch_code.size());
    }
};