int appId = 1108667;

struct UserData {
    std::string playFabId;
    std::string sessionTicket;
    std::string userHash;
    int userID;

    static UserData get() {
		UserData data;
		data.playFabId = ((Unity::System_String*)IL2CPP::Class::Utils::GetStaticField("DataHandler", "playFabId"))->ToString();
        data.sessionTicket = ((Unity::System_String*)IL2CPP::Class::Utils::GetStaticField("DataHandler", "sessionTicket"))->ToString();
        data.userHash = ((Unity::System_String*)IL2CPP::Class::Utils::GetStaticField("SocialSystem", "userHash"))->ToString();
        data.userID = (int)IL2CPP::Class::Utils::GetStaticField("SocialSystem", "userID");
        return data;
    }
};

std::string url_encode(const std::string& decoded)
{
    const auto encoded_value = curl_easy_escape(nullptr, decoded.c_str(), static_cast<int>(decoded.length()));
    std::string result(encoded_value);
    curl_free(encoded_value);
    return result;
}

std::string url_decode(const std::string& encoded)
{
    int output_length;
    const auto decoded_value = curl_easy_unescape(nullptr, encoded.c_str(), static_cast<int>(encoded.length()), &output_length);
    std::string result(decoded_value, output_length);
    curl_free(decoded_value);
    return result;
}

std::string cleanAsciiString(const std::string& input) {
    std::string result;
    for (char c : input) {
        if (static_cast<unsigned char>(c) <= 127) {
            result += c;
        }
    }
    return result;
}

size_t write_callback(char* ptr, size_t size, size_t nmemb, std::string* data) {
    size_t bytes = size * nmemb;
    data->append(ptr, bytes);
    return bytes;
}

std::string sendAPIRequest(const std::string& url, const std::string& postData) {
    CURL* curl;
    CURLcode res;
    std::string response_data;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "User-Agent: UnityPlayer/2021.3.29f1 (UnityWebRequest/1.0, libcurl/8.1.1-DEV)");
        headers = curl_slist_append(headers, "Accept: */*");
        headers = curl_slist_append(headers, "Proxy-Connection: Keep-Alive");
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
        headers = curl_slist_append(headers, "X-Unity-Version: 2021.3.29f1");

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            std::cerr << "sendAPIRequest failed: " << curl_easy_strerror(res) << std::endl;

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    curl_global_cleanup();
    return response_data;
}

std::string sendPlayfabRequest(const std::string& url, const std::string& postData) {
    CURL* curl;
    CURLcode res;
    std::string response_data;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        auto localUser = UserData::get();
        std::string authHeader = "X-Authorization: " + localUser.sessionTicket;

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "User-Agent: UnityPlayer/2021.3.29f1 (UnityWebRequest/1.0, libcurl/8.1.1-DEV)");
        headers = curl_slist_append(headers, "Accept: */*");
        headers = curl_slist_append(headers, "X-ReportErrorAsSuccess: true");
        headers = curl_slist_append(headers, "X-PlayFabSDK: UnitySDK-2.109.210521");
        headers = curl_slist_append(headers, cleanAsciiString(authHeader).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "X-Unity-Version: 2021.3.29f1");

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            std::cerr << "sendPlayfabRequest failed: " << curl_easy_strerror(res) << std::endl;

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    curl_global_cleanup();
    return response_data;
}

void addItem(int itemId) {
    std::string url = "http://pixelstrike3daws.com/new/buy-item.php?v=";
    url += Application$$Version()->ToString();

    UserData data = UserData::get();
    std::ostringstream postData;

    postData << "playFabId=" << data.playFabId.c_str() << 
                "&sessionTicket=" << url_decode(data.sessionTicket.c_str()) << 
                "&itemId=" << itemId;
    fslog::info("Sending API Request to: {} with params: {}", url, postData.str());

    std::string response = sendAPIRequest(url, cleanAsciiString(postData.str()));
    fslog::info("addItem({}) response: {}", itemId, response);
}

void buyVIP() {
    std::string url = "http://pixelstrike3daws.com/social/get-vip.php?v=";
    url += Application$$Version()->ToString();

    UserData data = UserData::get();
    std::ostringstream postData;

    postData << "userID=" << data.userID << "&userHash=" << data.userHash
             << "&playFabId=" << data.playFabId << "&sessionTicket=" << url_decode(data.sessionTicket);
    fslog::info("Sending API Request to: {} with params: {}", url, postData.str());

    std::string response = sendAPIRequest(url, postData.str());
    fslog::info("buyVIP response: {}", response);
}

void buyMVP() {
    std::string url = "http://pixelstrike3daws.com/social/get-mvp.php?v=";
    url += Application$$Version()->ToString();

	UserData data = UserData::get();
    std::ostringstream postData;

	postData << "userID=" << data.userID << "&userHash=" << data.userHash
		     << "&playFabId=" << data.playFabId << "&sessionTicket=" << url_decode(data.sessionTicket);
    fslog::info("Sending API Request to: {} with params: {}", url, postData.str());

    std::string response = sendAPIRequest(url, postData.str());
    fslog::info("buyMVP response: {}", response);
}


void addAllItems() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 4000; i++)
        threads.push_back(std::thread(addItem, i));

    for (auto& t : threads)
        t.join();
}