#include <iostream>
#include <vector>
#include <string>
#include <curl/curl.h>

bool isRef(std::string &str, int i) { 
	return str.substr(i, 7) == "http://" || str.substr(i, 8) == "https://";
} 

bool isRefEnd(char ch) {
	return  ch == '"' || ch == ')' || ch == ';' || ch == '\'' || ch == '\n' || ch == ' ';
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

void findReference(std::vector<std::vector<std::string>> &array, std::string &readBuffer, int DEPTH, int level) {
	bool isThere;
	int size = readBuffer.size();
	std::string ref;
	for (int k = 0; k < size - 4; ++k) {
		if (isRef(readBuffer, k)) {
			k += 4;
			ref = "http";
			while (!isRefEnd(readBuffer[k])) {
				ref += readBuffer[k++];
			}
			isThere = false;
			for (int l = 0; l < DEPTH + 1; ++l) {
				for (int k = 0; k < array[l].size(); ++k) {
					if (array[l][k] == ref) {
						isThere = true;
						break;
					}
				}
			}
			if (isThere) {
				continue;
			}
			array[level + 1].push_back(ref);
			std::cout << ref << std::endl;
		}
	}
}

int main(int argc, char **argv) {
	int DEPTH = std::stoi(argv[1]);
	bool isThere;
	std::string ref, readBuffer;
	std::vector<std::vector<std::string>> array;
	array.resize(DEPTH + 1);
	array[0].push_back(argv[2]);
	CURL *curl;
  	CURLcode res;
	for (int i = 0; i < DEPTH; ++i) {
		for (int j = 0; j < array[i].size(); ++j) {
  			curl = curl_easy_init();
    			curl_easy_setopt(curl, CURLOPT_URL, array[i][j].c_str());
    			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
			res = curl_easy_perform(curl);
			int size = readBuffer.size();
			if (size == 0) {
				continue;
			}
			findReference(array, readBuffer, DEPTH, i);
			curl_easy_cleanup(curl);
		}
	}
	return 0;
}

