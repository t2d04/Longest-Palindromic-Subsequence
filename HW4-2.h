#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class FILES {
public:
	int num;
	string** filelist;

	FILES() {
		num = 0;
		filelist = nullptr;
	}

	FILES(string filename) {
		ifstream file(filename);
		if (!file.is_open()) {
			cout << "error: there is no such file" << endl;
			num = 0;
			filelist = nullptr;
			return;
		}

		file >> num;
		filelist = new string * [num];
		for (int i = 0; i < num; i++) {
			filelist[i] = new string[2];
		}

		for (int i = 0; i < num; i++) {
			file >> filelist[i][0] >> filelist[i][1];
		}
	}

	~FILES() {
		if (filelist) {
			for (int i = 0; i < num; i++)
				delete[] filelist[i];
			delete[] filelist;
		}
	}
};

class BLOCK {
public:
	int num;
	vector<string> org;
	vector<string> lps;

	BLOCK(string filename) {
		ifstream file(filename);
		if (!file.is_open()) {
			cout << "error: there is no such file" << endl;
			num = 0;
			return;
		}

		file >> num;
		org.resize(num);
		lps.resize(num);

		for (int i = 0; i < num; i++) {
			int length = 0;
			file >> length;

			file >> org[i];
			org[i].resize(length);
		}
	}

	void get_LPS(int index) {
		string s = org[index];
		int n = s.length();

		if (n == 0) {
			lps[index] = "";
			return;
		}

		// 2D DP table
		vector<vector<int>> dp(n, vector<int>(n, 0));

		// Fill the table
		for (int i = n - 1; i >= 0; i--) {
			dp[i][i] = 1;
			for (int j = i + 1; j < n; j++) {
				if (s[i] == s[j]) {
					dp[i][j] = dp[i + 1][j - 1] + 2;
				}
				else {
					dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
				}
			}
		}

		// Reconstruct the LPS from the DP table
		string lps_left = "";
		string lps_right = "";
		int i = 0, j = n - 1;
		while (i <= j) {
			if (s[i] == s[j]) {
				lps_left += s[i];
				if (i != j) {
					lps_right = s[j] + lps_right;
				}
				i++;
				j--;
			}
			else if (dp[i + 1][j] > dp[i][j - 1]) {
				i++;
			}
			else {
				j--;
			}
		}

		// Combine the two
		lps[index] = lps_left + lps_right;
	}


	void get_all_LPS() {
		for (int i = 0; i < num; i++) {
			get_LPS(i);
		}
	}

	void write(string filename) {
		ofstream file(filename);

		if (!file.is_open()) {
			cout << "error: cannot open file " << filename << endl;
			return;
		}
		file << num << endl;

		for (int i = 0; i < num; i++) {
			file << lps[i].length() << endl;
			file << lps[i] << endl;
		}
	}
};