#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define IDC_INPUT 101
#define IDC_OUTPUT 102
#define IDC_BUTTON 103

// Function prototypes
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void CreateChatbotWindow(HWND);
void getTime();
void getDate();
void getBotInfo();
void getHelp();
void tellJoke();
void funFact();
void programmingAdvice();
void toLowerCase(char *str);
void basicTechQA(char user_input[]);

// Global variables to hold user input and chatbot responses
char inputText[256];
char responseText[512];

// Entry point of the application
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int nCmdShow) {
    WNDCLASSW wc = {0};  // Define a window class structure
    
    // Set the window properties
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"chatbotWindowClass";
    wc.lpfnWndProc = WindowProcedure;  // Set the window procedure callback

    // Register the window class
    if (!RegisterClassW(&wc))
        return -1;

    // Create the main window
    CreateWindowW(L"chatbotWindowClass", L"CBot GUI", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
                   100, 100, 500, 400, NULL, NULL, NULL, NULL);

    // Message loop to keep the application running
    MSG msg = {0};
    while (GetMessage(&msg, NULL, NULL, NULL)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

// Window Procedure to handle messages sent to the window
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_COMMAND:
            if (wp == IDC_BUTTON) {
                // Get user input when the button is clicked
                GetWindowText(GetDlgItem(hWnd, IDC_INPUT), inputText, 256);
                
                // Convert input to lowercase for easier matching
                toLowerCase(inputText);

                // Determine the appropriate response based on user input
                if (strstr(inputText, "time") != NULL) {
                    getTime();
                } else if (strstr(inputText, "date") != NULL) {
                    getDate();
                } else if (strstr(inputText, "info") != NULL) {
                    getBotInfo();
                } else if (strstr(inputText, "help") != NULL) {
                    getHelp();
                } else if (strstr(inputText, "joke") != NULL) {
                    tellJoke();
                } else if (strstr(inputText, "fact") != NULL) {
                    funFact();
                } else if (strstr(inputText, "advice") != NULL) {
                    programmingAdvice();
                } else {
                    // Handle tech-related questions
                    basicTechQA(inputText);
                }

                // Display the chatbot's response
                SetWindowText(GetDlgItem(hWnd, IDC_OUTPUT), responseText);
            }
            break;
        
        case WM_CREATE:
            CreateChatbotWindow(hWnd);  // Create the GUI components
            break;
        
        case WM_DESTROY:
            PostQuitMessage(0);  // Exit the application
            break;
        
        default:
            return DefWindowProcW(hWnd, msg, wp, lp);  // Default message handling
    }
    return 0;
}

// Function to create the chatbot window elements
void CreateChatbotWindow(HWND hWnd) {
    // Create a label for the input box
    CreateWindowW(L"Static", L"Enter Input:", WS_VISIBLE | WS_CHILD, 20, 20, 100, 20, hWnd, NULL, NULL, NULL);
    
    // Create an input box for user input
    CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 120, 20, 250, 20, hWnd, (HMENU)IDC_INPUT, NULL, NULL);
    
    // Create a button to submit the input
    CreateWindowW(L"Button", L"Submit", WS_VISIBLE | WS_CHILD, 380, 20, 80, 25, hWnd, (HMENU)IDC_BUTTON, NULL, NULL);
    
    // Create a label for the output area
    CreateWindowW(L"Static", L"Output:", WS_VISIBLE | WS_CHILD, 20, 60, 100, 20, hWnd, NULL, NULL, NULL);
    
    // Create a static text area for the chatbot's responses
    CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 60, 340, 200, hWnd, (HMENU)IDC_OUTPUT, NULL, NULL);
}

// Function to get the current time
void getTime() {
    time_t currentTime;
    struct tm *timeInfo;

    currentTime = time(NULL);  // Get current time
    timeInfo = localtime(&currentTime);  // Convert to local time

    // Format the time as a string
    sprintf(responseText, "The current time is %02d:%02d:%02d", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
}

// Function to get the current date
void getDate() {
    time_t currentTime;
    struct tm *dateInfo;

    currentTime = time(NULL);  // Get current time
    dateInfo = localtime(&currentTime);  // Convert to local time

    // Format the date as a string
    sprintf(responseText, "Today's date is %02d-%02d-%04d", dateInfo->tm_mday, dateInfo->tm_mon + 1, dateInfo->tm_year + 1900);
}

// Function to provide basic information about the chatbot
void getBotInfo() {
    strcpy(responseText, "I am CBot, your friendly C language chatbot. I'm here to help you with simple queries and tasks!");
}

// Function to provide help to the user
void getHelp() {
    strcpy(responseText, "You can ask me about the current date, time, or ask me basic information about myself or programming concepts!");
}

// Function to tell a joke
void tellJoke() {
    strcpy(responseText, "Why don't programmers like nature? It has too many bugs!");
}

// Function to provide a fun fact
void funFact() {
    strcpy(responseText, "Did you know? The first computer virus was created in 1983!");
}

// Function to provide programming advice
void programmingAdvice() {
    strcpy(responseText, "Remember to always comment your code. It helps others (and future you) understand what you were thinking!");
}

// Function to convert a string to lowercase
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Function to handle basic tech and programming questions
void basicTechQA(char user_input[]) {
    if (strstr(user_input, "what is a chatbot") != NULL) {
        strcpy(responseText, "A chatbot is a software application designed to simulate human conversation.");
    } else if (strstr(user_input, "how does a chatbot work") != NULL) {
        strcpy(responseText, "A chatbot works by processing user input and generating appropriate responses based on its programming.");
    } else if (strstr(user_input, "what can a chatbot do") != NULL) {
        strcpy(responseText, "A chatbot can handle tasks such as answering questions, providing information, and performing specific actions.");
    } else if (strstr(user_input, "how to start building a chatbot") != NULL) {
        strcpy(responseText, "Start by defining the chatbot's purpose, designing conversation flows, and choosing the right technology.");
    } else if (strstr(user_input, "what language to use for chatbot") != NULL) {
        strcpy(responseText, "Popular languages for chatbots include Python, JavaScript, and C, depending on your needs.");
    } else if (strstr(user_input, "how to make chatbot understand questions") != NULL) {
        strcpy(responseText, "Implement natural language processing (NLP) to help the chatbot understand and process user input.");
    } else if (strstr(user_input, "how to program chatbot responses") != NULL) {
        strcpy(responseText, "Program responses by defining rules or using machine learning models to generate replies.");
    } else if (strstr(user_input, "where to deploy chatbot") != NULL) {
        strcpy(responseText, "You can deploy your chatbot on websites, messaging platforms, or mobile apps.");
    } else if (strstr(user_input, "how to test chatbot") != NULL) {
        strcpy(responseText, "Test your chatbot by simulating conversations and checking its responses for accuracy.");
    } else if (strstr(user_input, "how to improve chatbot") != NULL) {
        strcpy(responseText, "Continuously improve your chatbot by refining its responses and expanding its knowledge base.");
    } else if (strstr(user_input, "what is programming") != NULL) {
        strcpy(responseText, "Programming is the process of writing code to create software applications.");
    } else if (strstr(user_input, "what is a variable") != NULL) {
        strcpy(responseText, "A variable is a storage location identified by a name used to hold data that can be modified during program execution.");
    } else if (strstr(user_input, "how to write a simple program") != NULL) {
        strcpy(responseText, "To write a simple program, choose a programming language, write the code, and then compile or interpret it.");
    } else if (strstr(user_input, "what is a function") != NULL) {
        strcpy(responseText, "A function is a block of code that performs a specific task and can be reused throughout a program.");
    } else if (strstr(user_input, "what is an algorithm") != NULL) {
        strcpy(responseText, "An algorithm is a step-by-step procedure for performing a task or solving a problem.");
    } else if (strstr(user_input, "how to debug code") != NULL) {
        strcpy(responseText, "Debugging involves finding and fixing errors in your code to ensure it runs correctly.");
    } else if (strstr(user_input, "what is a loop") != NULL) {
        strcpy(responseText, "A loop is a control structure that repeats a block of code until a specified condition is met.");
    } else if (strstr(user_input, "what is a programming language") != NULL) {
        strcpy(responseText, "A programming language is a formal set of instructions used to communicate with computers and create software.");
    } else if (strstr(user_input, "how to use a text editor") != NULL) {
        strcpy(responseText, "Use a text editor to write and edit code, save files, and manage projects.");
    } else if (strstr(user_input, "what is version control") != NULL) {
        strcpy(responseText, "Version control is a system that tracks changes to code and allows collaboration between multiple developers.");
    } else if (strstr(user_input, "what does API stand for") != NULL) {
        strcpy(responseText, "API stands for Application Programming Interface.");
    } else if (strstr(user_input, "what is a VPN used for") != NULL) {
        strcpy(responseText, "A VPN (Virtual Private Network) is used to secure and encrypt your internet connection and protect your privacy online.");
    } else if (strstr(user_input, "what is RAM") != NULL) {
        strcpy(responseText, "RAM stands for Random Access Memory, and it's used to temporarily store data that the computer is currently using.");
    } else if (strstr(user_input, "what does HTTP do") != NULL) {
        strcpy(responseText, "HTTP stands for HyperText Transfer Protocol, and it's used for transferring data over the web.");
    } else if (strstr(user_input, "what is cloud storage") != NULL) {
        strcpy(responseText, "Cloud storage is a service that allows you to store data on remote servers and access it via the internet.");
    } else if (strstr(user_input, "what is AI") != NULL) {
        strcpy(responseText, "AI stands for Artificial Intelligence, which is the simulation of human intelligence in computers.");
    } else if (strstr(user_input, "what is encryption") != NULL) {
        strcpy(responseText, "Encryption is the process of converting data into a secure format to prevent unauthorized access.");
    } else if (strstr(user_input, "what is a database") != NULL) {
        strcpy(responseText, "A database is an organized collection of data that can be easily accessed, managed, and updated.");
    } else if (strstr(user_input, "what does a compiler do") != NULL) {
        strcpy(responseText, "A compiler translates code written in a high-level programming language into machine code that can be executed by a computer.");
    } else if (strstr(user_input, "what is HTML") != NULL) {
        strcpy(responseText, "HTML stands for HyperText Markup Language, and it's used to create and design web pages.");
    } else {
        strcpy(responseText, "I'm not sure how to respond to that. Try asking something else or type 'help' for guidance.");
    }
}
