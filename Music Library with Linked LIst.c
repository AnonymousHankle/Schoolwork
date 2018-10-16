//
// APS105 Lab 8 Lab8.c
//
// This is a program written to maintain a personal music library, 
// using a linked list to hold the songs in the library.
//
// Author: <Hankle Liu>
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// A node in the linked list

// Each string in the node is declared as a character pointer variable,
// so they need to be dynamically allocated using the malloc() function,
// and deallocated using the free() function after use.

typedef struct node {
    char *artist ;
    char *songName ;
    char *genre ;
    struct node *nextNode ;
} Node;

Node* newNode(char artist[], char songName[], char genre[], Node* nextNode) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode -> artist = malloc(sizeof(artist));
    strcpy(newNode -> artist, artist);
    newNode -> songName = malloc(sizeof(songName));
    strcpy(newNode -> songName, songName);
    newNode -> genre = malloc(sizeof(genre));
    strcpy(newNode -> genre, genre);
    newNode -> nextNode = nextNode;
    return newNode;
}

Node* insertNodeMiddle(Node* head, char artist[], char songName[], char genre[]) {
    if (head == NULL || strcmp(songName, head -> songName) < 0) {
        if (head != NULL) {
            Node* temp = head -> nextNode;
            return newNode(artist, songName, genre, head);
        }
        return newNode(artist, songName, genre, NULL); 
    } else {
        Node* temp = head;
        while (strcmp(temp -> songName, songName) < 0 && temp -> nextNode != NULL) {
            temp = temp -> nextNode;
        } 
        temp -> nextNode = newNode(artist, songName, genre, temp -> nextNode);
        return head;
    }
    
    
}

Node* deleteNode(Node* head, char songName[]) {
    Node* current = head;
    Node* previousNode = NULL;
    Node* temp = NULL;
    if (current == NULL) {
        return NULL;
    } else if (current -> nextNode == NULL) {
        free(current);
        return NULL;
    }
    while (strcmp(current -> songName, songName) != 0) {
        previousNode = current;
        current = current -> nextNode;
    }
    if (current == head) {
        head = current -> nextNode;
        free(current);
        return head;
        
        
    }
    previousNode -> nextNode = current -> nextNode;
    temp = current;
    current = current -> nextNode;
    free(temp);
    return head;
}

Node* searchNode(Node* head, char songName[]) {
    Node* current = head; 
    if (current == NULL) {
        return NULL;
    } if (current -> nextNode == NULL) {
        if (strcmp(current -> songName, songName) == 0) {
            return current;
        } else {
            return NULL;
        }
    }
    while (strcmp(current -> songName, songName) != 0 && current -> nextNode != NULL) {
        current = current -> nextNode;
    }
    if (strcmp(current -> songName, songName) == 0) {
        return current;
    } else {
        return NULL;
    }
    
}

void deleteEntireList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        current = head -> nextNode;
        free(head);
        songNameDeleted(head -> songName);
        head = current;
    }
}
void printLinkedList(Node* head) {
    while (head != NULL) {
        printf("%s\n", head -> songName);
        printf("%s\n", head -> artist);
        printf("%s\n", head -> genre);
        head = head -> nextNode;
    }
}

// Declarations of support functions
// See below the main function for descriptions of what these functions do

void inputStringFromUser( char prompt[], char s[], int arraySize ) ;
void songNameDuplicate( char songName[] ) ;
void songNameFound( char songName[] ) ;
void songNameNotFound( char songName[] ) ;
void songNameDeleted( char songName[] ) ;
void artistFound( char artist[] ) ;
void artistNotFound( char artist[] ) ;
void printMusicLibraryEmpty( void ) ;
void printMusicLibraryTitle( void ) ;

const int MAX_LENGTH = 1024;


int main( void ) {
    Node* head = NULL;
    //   ADD YOUR STATEMENT(S) HERE
 
    // Announce the start of the program
    printf( "Personal Music Library.\n\n" ) ;
    printf( "%s", "Commands are I (insert), D (delete), S (search by song name),\n"
         "P (print), Q (quit).\n" ) ;
    
    char response ;
    char input[ MAX_LENGTH + 1 ] ;
    do {
        inputStringFromUser( "\nCommand", input, MAX_LENGTH ) ;

        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper( input[0] ) ;

        if( response == 'I' ) {
            // Insert a song into the linked list.
            // Maintain the list in alphabetical order by song name.
            char* promptName = "Song name" ;
            char* promptArtist =  "Artist" ;
            char* promptGenre = "Genre" ;
            char songName[MAX_LENGTH];
            char artist[MAX_LENGTH];
            char genre[MAX_LENGTH];
            inputStringFromUser(promptName, songName, MAX_LENGTH);
            inputStringFromUser(promptArtist, artist, MAX_LENGTH);
            inputStringFromUser(promptGenre, genre, MAX_LENGTH);
            
            if (searchNode(head, songName) == NULL) {
                head = insertNodeMiddle(head, artist, songName, genre);
            } else {
                songNameDuplicate(songName);
            }
            

        }
        else if( response == 'D' ) {
            // Delete a song from the list.

            char *prompt = "\nEnter the name of the song to be deleted" ;
            char songName[MAX_LENGTH];
            inputStringFromUser(prompt, songName, MAX_LENGTH);
            head = deleteNode(head, songName);
            songNameDeleted(songName);
        }
        else if( response == 'S' ) {
            // Search for a song by its name.

            char* prompt = "\nEnter the name of the song to search for" ;
            char* promptName = "Song name" ;
            char songName[MAX_LENGTH];
            inputStringFromUser(promptName, songName, MAX_LENGTH);
            Node* songFound = NULL;
            songFound = searchNode(head, songName);
            if (songFound == NULL) {
                songNameNotFound(songName);
            } else {
                songNameFound(songFound -> songName);
                printf("%s\n", head -> songName);
                printf("%s\n", head -> artist);
                printf("%s\n\n", head -> genre);
            }
            
        }
        else if( response == 'P' ) {
            // Print the music library.
            if (head == NULL) {
                printMusicLibraryEmpty();
                printf("\n");
            } else {
                printMusicLibraryTitle();
                printLinkedList(head);
            }
            
            

        }
        else if( response == 'Q' ) {
            ; // do nothing, we'll catch this below
        }
        else {
            // do this if no command matched ...
            printf( "\nInvalid command.\n" ) ;
        }
    } while( response != 'Q' ) ;
  
    // Delete the entire linked list.
    deleteEntireList(head);

    // Print the linked list to confirm deletion.
    printMusicLibraryEmpty();

    return 0 ;
}

// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow
void inputStringFromUser(char prompt[], char s[], int maxStrLength) {
    int i = 0;
    char c;
    
    printf( "%s --> ", prompt ) ;
    while( i < maxStrLength && (c = getchar()) != '\n' )
        s[i++] = c ;
    s[i] = '\0' ;
}

// Function to call when the user is trying to insert a song name 
// that is already in the personal music library.
void songNameDuplicate( char songName[] ) {
    printf( "\nA song with the name '%s' is already in the music library.\n"
            "No new song entered.\n", songName);
}

// Function to call when a song name was found in the personal music library.
void songNameFound( char songName[] ) {
    printf( "\nThe song name '%s' was found in the music library.\n",
           songName ) ;
}

// Function to call when a song name was not found in the personal music library.
void songNameNotFound( char songName[] ) {
    printf( "\nThe song name '%s' was not found in the music library.\n",
           songName);
}

// Function to call when a song name that is to be deleted
// was found in the personal music library.
void songNameDeleted( char songName[] ) {
    printf( "\nDeleting a song with name '%s' from the music library.\n",
           songName);
}

// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void) {
    printf( "\nThe music library is empty.\n" ) ;
}

// Function to call to print a title when the entire music library is printed.
void printMusicLibraryTitle(void) {
    printf( "\nMy Personal Music Library: \n" ) ;
}

