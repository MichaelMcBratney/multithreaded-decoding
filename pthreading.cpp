
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <string>
#include <regex>
#include <algorithm>

using namespace std;
bool moreMessages = true;

string firstMsg;
string secondMsg;
string thirdMsg;

int getposition(const char *array, int size, char c)
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] == c)
            return (int)i;
    }
    return -1;
}

void * summitProcess(void* part3){
    const char LETTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char* summitS = (char*) part3;
    string summitStr(summitS);
    bool part1Valid = true;
    bool part2Valid = true;
    int partSeperatorIndex = -1;

    int startInd = -1;
    for (int i = 0; i < summitStr.length(); i++){
        if (isalpha(summitStr[i]) && startInd == -1){
            startInd = i;
        }
        if (isspace(summitStr[i]) && (startInd != -1) && (partSeperatorIndex == -1)){
            partSeperatorIndex = i;
        }

    }

    for (int i = partSeperatorIndex; i < summitStr.length(); i++){
        if (isalpha(summitStr[i]) && (summitStr[i] == '-')){
            part2Valid = false;
        }

    }
    int part1Count = 0;
    int part2Count = 0;
    bool next = true;
    for (int i = 0; i < summitStr.length(); i++){
        if (i < partSeperatorIndex){
            if (isalpha(summitStr[i])){
                part1Count++;
            }else if (isdigit(summitStr[i])){
                part1Valid = false;
            }
        } else {
            if (isdigit(summitStr[i]) && next){
                part2Count++;
                next = false;
            } else if (isalpha(summitStr[i])) {
                part2Valid = false;
            } else {
                next = true;
            }
        }
    }

    next = true;

    if (part1Count % 3 != 0){
        part1Valid = false;
    }
    if (part2Count != 9){
        part2Valid = false;
    }




    int summitPart1[part1Count];
    int summitPart2[9];
    char temporaryNum[part2Count];
    int tempCounter = 0;
    int tempCounter2 = 0;
    
    if (!part1Valid && !part2Valid){
        thirdMsg = "The first and second part of the summit message is invalid.";
    }
    else if (!part1Valid){
        thirdMsg = "The first part of the summit message is invalid.";
    } else if (!part2Valid){
        thirdMsg = "The second part of the summit message is invalid.";
    } else {
        for (int i = 0; i < summitStr.length(); i++){
            
            if (i < partSeperatorIndex){
                if (isalpha(summitStr[i])){
                    summitPart1[tempCounter] = getposition(LETTERS, sizeof(LETTERS), toupper(summitStr[i]));
                    tempCounter++;
                }
            } else {

                if (i - partSeperatorIndex == 0){
                    tempCounter = 0;
                }

                if (isspace(summitStr[i])){
                    next = false;
                }


                if (isdigit(summitStr[i]) && next){
                
                temporaryNum[tempCounter2] = summitStr[i];
                tempCounter2++;
                next = true;
                
                } else {
                    if (isdigit(temporaryNum[0])){
                        
                        string temporaryStr(temporaryNum);
                        temporaryStr = temporaryStr.substr(0, tempCounter2);
                        summitPart2[tempCounter] = stoi(temporaryStr, nullptr, 10);
                        tempCounter++;
                        tempCounter2 = 0;
                        temporaryNum[0] = 'a';
                        
                    }
                    next = true;
                }
                if (i == summitStr.length() - 1){
                    if (isdigit(temporaryNum[0])){
                        string temporaryStr(temporaryNum);
                        summitPart2[tempCounter] = stoi(temporaryStr, nullptr, 10);
                    }
                }
                
            }
        }
        
        char summitDecodedMessage[part1Count];
        for (int i = 0; i < part1Count; i += 3){
            summitDecodedMessage[i] = LETTERS[((summitPart2[0] * summitPart1[i]) +(summitPart2[1]*summitPart1[i+1])+(summitPart2[2]*summitPart1[i+2])) % 26];
            summitDecodedMessage[i+1] = LETTERS[((summitPart2[3]*summitPart1[i])+(summitPart2[4]*summitPart1[i+1]) + (summitPart2[5]*summitPart1[i+2])) % 26];
            summitDecodedMessage[i+2] = LETTERS[((summitPart2[6]*summitPart1[i])+(summitPart2[7]*summitPart1[i+1])+(summitPart2[8]*summitPart1[i+2])) % 26];
        }
        string summitDecodedStr(summitDecodedMessage, part1Count);
        thirdMsg = summitDecodedStr;
    }
    return NULL;
}

void * hillProcess(void* part2){
    const char LETTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char* hillS = (char*) part2;
    string hillStr(hillS);
    bool part1Valid = true;
    bool part2Valid = true;
    int partSeperatorIndex = -1;
    int firstIndex = -1;

    for (int i = 0; i < hillStr.length(); i++){
        if (isalpha(hillStr[i]) && (firstIndex == -1)){
            firstIndex = i;
        }
        if ((firstIndex != -1) && (partSeperatorIndex == -1) && isspace(hillStr[i])){
            partSeperatorIndex = i;
        }
    }

    for (int i = partSeperatorIndex; i < hillStr.length(); i++){
        if (isalpha(hillStr[i]) && (hillStr[i] == '-')){
            part2Valid = false;
        }
    }
    int part1Count = 0;
    int part2Count = 0;
    bool next = true;
    for (int i = 0; i < hillStr.length(); i++){
        if (i < partSeperatorIndex){
            if (isalpha(hillStr[i])){
                part1Count++;
            }else if (isdigit(hillStr[i])){
                part1Valid = false;
            }
        } else {
            if (isdigit(hillStr[i]) && next){
                part2Count++;
                next = false;
            } else if (isalpha(hillStr[i])) {
                part2Valid = false;
            } else {
                next = true;
            }
        }
    }

    next = true;

    if (part1Count % 2 == 1){
        part1Valid = false;
    }
    if (part2Count != 4){
        part2Valid = false;
    }

    int hillPart1[part1Count];
    int hillPart2[4];
    char temporaryNum[part2Count];
    int tempCounter = 0;
    int tempCounter2 = 0;
    


    if (!part1Valid && !part2Valid){
        secondMsg = "The first and second part of the hill message was invalid.";
    } else if (!part1Valid){
        secondMsg = "The first part of the hill message was invalid.";
    } else if (!part2Valid){
        secondMsg = "The second part of the hill message was invalid.";
    } else {
        for (int i = 0; i < hillStr.length(); i++){
            
            if (i < partSeperatorIndex){
                if (isalpha(hillStr[i])){
                    hillPart1[tempCounter] = getposition(LETTERS, sizeof(LETTERS), toupper(hillStr[i]));
                    tempCounter++;
                }
            } else {
                if (isspace(hillStr[i])){
                    next = false;
                }
                if (i == partSeperatorIndex){
                    tempCounter = 0;
                }
                if (isdigit(hillStr[i]) && next){
                temporaryNum[tempCounter2] = hillStr[i];
                tempCounter2++;
                next = true;
                } else {
                    if (isdigit(temporaryNum[0])){
                        string temporaryStr(temporaryNum);
                        temporaryStr = temporaryStr.substr(0, tempCounter2);
                        hillPart2[tempCounter] = stoi(temporaryStr, nullptr, 10);
                        tempCounter++;
                        tempCounter2 = 0;
                        temporaryNum[0] = 'A';
                    }
                    next = true;
                }
                if (i == hillStr.length() - 1){
                    if (isdigit(temporaryNum[0])){
                        string temporaryStr(temporaryNum);
                        hillPart2[tempCounter] = stoi(temporaryStr, nullptr, 10);
                    }
                }
                
            }
        }

        char hillDecodedMessage[part1Count];
        for (int i = 0; i < part1Count; i += 2){
            hillDecodedMessage[i] = LETTERS[((hillPart2[0] * hillPart1[i]) +(hillPart2[1]*hillPart1[i+1])) % 26];
            hillDecodedMessage[i+1] = LETTERS[((hillPart2[2]*hillPart1[i])+(hillPart2[3]*hillPart1[i+1])) % 26];
        }
        string decodedStr(hillDecodedMessage, part1Count);
        secondMsg = decodedStr;
    }
    return NULL;
}

void * substituteProcess(void* part1){
    const char LETTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char* substituteS = (char*)part1;
    char* final_message;
    string substitureStr = substituteS;
    int firstIndex;

    for (int i = 0; i < substitureStr.length(); i++){
        if (substitureStr[i] != ' '){
            firstIndex = i;
            i = substitureStr.length();
        }
    }

    if (isalpha(substitureStr[firstIndex])){

    int n;
    n = getposition(LETTERS, sizeof(LETTERS), (char)toupper(substitureStr[firstIndex]));
    n = (n % 10)+2;
    n = n % 26;
    substitureStr = substitureStr.substr(firstIndex+1, substitureStr.length());
    while(isspace(substitureStr[0])){
        substitureStr = substitureStr.substr(1, substitureStr.length());
    }
    for (int i = 0; i < substitureStr.length(); i++){
        if (substitureStr[i] != ' '){
        int tempPos = getposition(LETTERS, sizeof(LETTERS), (char)toupper(substitureStr[i])) - (n % 26);
        if (tempPos < 0){
            tempPos = 26 + tempPos;
        }
        substitureStr[i] =  LETTERS[tempPos];
        }
    }

    firstMsg = substitureStr;
    } else {
        firstMsg = "The substitute message was invalid.";
    }
    return NULL;
}

void * decoderProcess(void* message){
    // This method will split the message into three parts and give each part to it's respective thread.
    const char *REGARGS[] = {"[^\\*][\\*]{1}[a-zA-Z0-9 ]+|^[\\*]{1}[a-zA-Z0-9 ]+", "[^\\*][\\*]{2}[a-zA-Z0-9 ]+|^[\\*]{2}[a-zA-Z0-9 ]+", "[\\*]{3}[a-zA-Z0-9 ]*"};
    char* decoderS = (char*)message;
    string decoderStr(decoderS);
    char msg1[decoderStr.length()];
    char msg2[decoderStr.length()];
    char msg3[decoderStr.length()];
    string decoderTemp;
    smatch decoderMatch;
    
    for (int i = 0; i < 3; i++){
        regex decoderReg (REGARGS[i]);
        regex_search(decoderStr, decoderMatch, decoderReg);
        decoderTemp = decoderMatch[0];
        if (!(decoderTemp.front() == '*')){
            decoderTemp = decoderTemp.substr(1, decoderTemp.length());
        }
        decoderTemp.erase(std::remove(decoderTemp.begin(), decoderTemp.end(), '*'), decoderTemp.end());
        if (i == 0){
            strcpy(msg1, decoderTemp.c_str());
        } else if (i == 1){
            strcpy(msg2, decoderTemp.c_str());
        } else {
            strcpy(msg3, decoderTemp.c_str());
        }
    }

      
    pthread_t substitute;
    pthread_t hill;
    pthread_t summit;
    int substituteResult;
    int hillResult;
    int summitResult;
    // Create and execute all three algorithm threads in tandem.
    substituteResult = pthread_create(&substitute, NULL, substituteProcess, (char*)msg1);
    hillResult = pthread_create(&hill, NULL, hillProcess, (char*)msg2);
    summitResult = pthread_create(&summit, NULL, summitProcess, (char*)msg3);
    substituteResult = pthread_join(substitute, NULL);
    hillResult = pthread_join(hill, NULL);
    summitResult = pthread_join(summit, NULL);


    return NULL;
}
void * checkMessage(void*){
    // List of Regular expression statements for each part of the string.
    const char *REGARGS[] = {"[^\\*][\\*]{1}[a-zA-Z0-9 ]+|^[\\*]{1}[a-zA-Z0-9 ]+", "[^\\*][\\*]{2}[a-zA-Z0-9 ]+|^[\\*]{2}[a-zA-Z0-9 ]+", "[\\*]{3}[a-zA-Z0-9 ]*"};
    
    char* s = NULL;
    int validStrings;
    bool isValidMessage = false;
    int count = 3;

    do{
        validStrings = 0;
        if (count < 3){
            cout << "Invalid Message: try again \n";
        }



    // Dynamically give memory to a string of any size that the user can enter.
    #define CHUNK 400 // Setting a constant value of 400 to CHUNK
    cout << "Enter a message: (" << count << " tries remaining Type quit to exit)";
     // Creating a char* array
    char tempBuffer[CHUNK]; // Creating a buffer char array at a buffer of 400 characters
    size_t sLength = 0, tempLength = 0; // Creates two unsigned integers for the temporary length and current string length
    do {
        fgets(tempBuffer, CHUNK, stdin); // Puts 400 characters into tempBuffer from standard input
        tempLength = strlen(tempBuffer); // Sets the temporary length of the string to the length of the temporary buffer
        s = static_cast<char*>(realloc(s, sLength+tempLength+1)); // Reallocated the memory assigned to the string to the memory needed 
        // to store the characters in the buffer and returns a pointer to that memory block back to the char pointer
        strcpy(s+sLength, tempBuffer); // copies the new characters to the location in memory where the next part of the string is to be written to
        sLength += tempLength; // updates the string length
    } while (tempLength==CHUNK-1 && tempBuffer[CHUNK-2]!='\n'); // continues until there is a new line
  
    string str(s);
    if (str.compare("quit") == 1){
        moreMessages = false; // Exit the program if the user does not wish to continue.
        count = 0;
    } 
    else{
    // Error handling for out of bounds errors from the wrong number of regexes.
    try{
    for (int i = 0; i < 3; i++){
        regex reg (REGARGS[i]);
        string temp;
        smatch match;
        string refStr;
        refStr = str;
        // Iterate through each instance of each regex match to endure that all three parts of the strings exist, and that none of them exist more than once.
        if (!regex_search(refStr, match, reg)){
            validStrings = 5;
        }
        while(regex_search(refStr, match, reg)){    
        if (regex_match(temp=match[0], reg)){
        if (!(temp.front() == '*')){
            temp = temp.substr(1, temp.length());
        }

        if (temp.length() != 0){
            validStrings++;
        }
        refStr = match.suffix();
        } 
      }
    }

    } catch (const std::out_of_range&){
        validStrings  = 1;
    }
    if (validStrings == 3){
        isValidMessage = true;
    }
    count--;    
    
    if (isValidMessage == 1){
        count = 0;
    }
    }
   } while (count > 0);
    if (isValidMessage == 1){
        // If the message is valid send it to decoder.
        pthread_t decoder;
        int decoderThreadResult;
        
        decoderThreadResult = pthread_create(&decoder, NULL, decoderProcess, (void*)s);
        decoderThreadResult = pthread_join(decoder, NULL);
        
        cout << "Success!\n";
    } else if (!moreMessages){
        // If the user types exit, then we will exit the program normally.
        cout << "Exiting...\n";
        
    } else {
        // If the user enters 3 invalid strings, the program will end.
        cout << "Failure!\n";
        moreMessages = false;
    }
    return NULL;
}

int main(){
        // Continue until the user is done, or enters 3 invalid strings.
        while (moreMessages){
        pthread_t sifter;
        int result;
        // Run sifter threads.
        result = pthread_create(&sifter, NULL, checkMessage, NULL);
        result = pthread_join(sifter, NULL);
        if (moreMessages){
            cout << "We have decoded the following:\n" << firstMsg << "\n" << secondMsg  << "\n" << thirdMsg << "\n";
        }
    }
    
}