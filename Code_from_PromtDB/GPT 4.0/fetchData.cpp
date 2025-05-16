#include <string>
#include <future>
#include <json/json.h>
#include "HttpClientSecure.h"

using std::string;
using std::future;
using std::async;
using std::launch;
using Json::Value;

/**
 * fetchData - Fetches data from MyAPI using HTTP over TLS/SSL
 *
 * @param param1: API key used for authentication (string)
 * @param param2: Data ID to fetch from the API (int)
 * @return: JSON object containing the API response
 */
future<Value> fetchData(const string& param1, int param2) {
    return async(launch::async, [=]() -> Value {
        HttpClientSecure client("https://api.myapi.com", 443);

        string path = "/data?id=" + std::to_string(param2);
        client.setHeader("Authorization", "Bearer " + param1);
        client.setHeader("Accept", "application/json");

        if (!client.connect()) {
            throw std::runtime_error("Connection to MyAPI failed");
        }

        HttpResponse response = client.get(path);

        if (response.statusCode != 200) {
            throw std::runtime_error("HTTP error: " + std::to_string(response.statusCode));
        }

        Json::Reader reader;
        Value jsonData;
        if (!reader.parse(response.body, jsonData)) {
            throw std::runtime_error("Failed to parse JSON response");
        }

        return jsonData;
    });
}