#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

void print_welcome_message() {
  cout << " ██████  █████  ███████ ███████  █████  ██████  \n";
  cout << "██      ██   ██ ██      ██      ██   ██ ██   ██ \n";
  cout << "██      ███████ █████   ███████ ███████ ██████  \n";
  cout << "██      ██   ██ ██           ██ ██   ██ ██   ██ \n";
  cout << " ██████ ██   ██ ███████ ███████ ██   ██ ██   ██ ";
  cout << "by 01!v3r\n" << endl;
}

int getkey() {
  int key = 0;
  while (key <= 0 || key > 25) {
    cout << "Enter your key (1-25): " << endl;
    cin >> key;
    if (cin.fail()) {
      cout << "ERROR: You did not enter an integer." << endl;
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  return key;
}

string encrypt(string text, int key) {
  string result = "";

  key %= 26; // only allow 0-25;
  for (int i = 0; i < text.length(); i++) {
    unsigned char ch = text[i] + key; // prevent buffer overflow (0 - 256)

    if (isupper(text[i])) {
      if (ch > 'Z') {
        ch -= 26;
      }
      result += ch;
    } else if (islower(text[i])) {
      if (ch >= 'a' && ch <= 'z') {
      } else if (ch > 'z') {
        ch -= 26;
      }
      result += ch;
    } else {
      result += text[i];
    }
  }
  return result;
}

string decrypt(string text, int key) {
  string result = "";

  key %= 26; // only allow 0-25;
  for (int i = 0; i < text.length(); i++) {
    char ch = text[i] - key; // (-128 - 127)
    if (isupper(text[i])) {
      if (ch < 'A') {
        ch += 26;
      }
      result += ch;
    } else if (islower(text[i])) {
      if (ch < 'a') {
        ch += 26;
      }
      result += ch;
    } else {
      result += text[i];
    }
  }
  return result;
}

void bruteforce(string text) {
  cout << "n   |   OUTPUT" << endl;
  for (int i = 1; i < 26; i++) {
    string seperator = (i < 10) ? "   |   " : "  |   ";
    cout << "----|";
    for (int i = 0; i < 55; i++)
      cout << "-";
    cout << endl;
    cout << i << seperator << decrypt(text, i) << endl;
  }
}

void interactive_mode() {

  char option;
  print_welcome_message();
  cout << "Welcome to caesar!" << endl;

  while (option != 'e' || option != 'd' || option != 'b') {
    int key = 0;
    for (int i = 0; i < 40; i++)
      cout << "-";
    cout << endl
         << " e) encode\n d) decode\n b) bruteforce ( try any possible keys "
            ")\n Select your option (Ctrl+c to quit) > ";
    cin >> option;
    if (cin.fail()) {
      cout << "ERROR: You did not enter an integer." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
      cin.clear();
      if (cin.fail()) {
        cout << "ERROR: You did not enter an integer." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      } else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (option == 'e') { // encrypt
          cout << endl << "Enter some text to encrypt: " << endl;
          string text;
          getline(cin, text);

          key = getkey();

          string result = encrypt(text, key);
          cout << result << endl;
        } else if (option == 'd') { // decrypt
          cout << endl << "Enter some text to decrypt: " << endl;
          string text;
          getline(cin, text);

          key = getkey();

          string result = decrypt(text, key);
          cout << result << endl;
        } else if (option == 'b') {
          cout << endl << "Enter some text to bruteforce: " << endl;
          string text;
          getline(cin, text);
          bruteforce(text);
        } else {
          cout << "invalid option" << endl;
          cin.clear();
          cin.sync();
        }
      }
    }
  }
}

void print_help() {
  cout << "Caesar 1.0.0 (https://github.com/knhn1004/caesar)" << endl;
  cout << "Usage: caesar [Options] {target string} (-k {key})" << endl;
  cout << "OPTIONS: " << endl;
  cout << "  -h: help message" << endl;
  cout << "  -e: encrypt string" << endl;
  cout << "  -d: decrypt code" << endl;
  cout << "  -k: key (number to cypher)" << endl;
  cout << "  -b: brute force code" << endl;
  cout << "  -i: enter interactive mode" << endl;
  cout << "EXAMPLES: " << endl;
  cout << "  caesar -e oliver -k 15" << endl;
  cout << "  caesar -d daxktg -k 15" << endl;
  cout << "  caesar -b daxktg" << endl;
}

int main(int argc, char *argv[]) {
  print_welcome_message();
  if (argc > 1) {
    /* ------------------
     * for comparison
     * ---------------- */

    string intera("-i"); // interactive
    string encr("-e");   // encrypt
    string decr("-d");   // decrypt
    string brute("-b");  // bruteforce
    string key("-k");    // key

    if (intera.compare(argv[1]) == 0) { // option '-i'
      interactive_mode();
    } else if (encr.compare(argv[1]) == 0) {       // option '-e'
      if (argc < 4 || key.compare(argv[3]) != 0) { // check if '-k' is specified
        print_help();
        return 0;
      }
      try {
        string result = encrypt(argv[2], int(*argv[4]));
        cout << result << endl;
      } catch (int e) {
        cerr << "invalid syntax" << endl;
        print_help();
      }

    } else if (decr.compare(argv[1]) == 0) { // option '-d'
      if (argc < 4 || key.compare(argv[3]) != 0) {
        print_help();
        return 0;
      }
      try {
        string result = decrypt(argv[2], int(*argv[4]));
        cout << result << endl;
      } catch (int e) {
        cerr << "invalid syntax" << endl;
        print_help();
      }

    } else if (brute.compare(argv[1]) == 0) { // option '-b'
      if (argc < 3) {
        print_help();
        return 0;
      }
      try {
        bruteforce(argv[2]);
      } catch (int e) {
        cerr << "invalid syntax" << endl;
        print_help();
      }
    } else {
      print_help();
    }
  } else {
    print_help();
  }
  return 0;
}
