//Idan Twito 311125249
/********************************************
 * Student Name: Idan Twito
 * Student ID: 311125249
 * Group Exercise Course: 89-230-05
 * Exercise 2.
 *******************************************/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//size of each letter which is saved on 2 Bytes.
#define ELEMENT_SIZE 2
//size of char
#define CHAR_READ 1
#define UNIX "-unix"
#define MAC "-mac"
#define WIN "-win"
#define SWAP_NOT_NEEDED 0
#define SWAP_NEEDED 1


void swap(char twoBytesStr[2]) {
    char temp = twoBytesStr[0];
    twoBytesStr[0] = twoBytesStr[1];
    twoBytesStr[1] = temp;
}

/************************************************************************
 * function name: SameEncodingSystem
 * the input: char *sourceName, char *destinationName - the names of the files
 * which I want to read from and write to.
 * the output: none.
 * the function operation: the function gets 2 files from the command line,
 * both of them from the same OS. In each file every letter is saved as 2
 * bytes. The function reads the text from the first file and writes it
 * on the second one.
*************************************************************************/
void SameEncodingSystem(char *sourceName, char *destinationName, int
swapNeeded) {
    FILE *sourceFile;
    FILE *destinationFile;
    //saves each letter
    char str[ELEMENT_SIZE];
    sourceFile = fopen(sourceName, "rb");
    if (sourceFile != NULL) {
        destinationFile = fopen(destinationName, "wb");
        if (destinationFile != NULL) {
            //as long as I can read 2-Bytes letters, read from the source
            while (fread(str, CHAR_READ, ELEMENT_SIZE, sourceFile) == 2) {
                if (swapNeeded == 1) {
                    swap(str);
                }
                //then write the same letter on the destination file.
                fwrite(str, CHAR_READ, ELEMENT_SIZE, destinationFile);
            }
            fclose(destinationFile);
        }
        fclose(sourceFile);
    }
}


/********************************************************************
 * function name: FromUnixToOther
 * the input: char *sourceName, char *destinationName, char *destinationOs -
 * the names of the file which I read from, the names of the file which I
 * write to, the OS in which I would like to open the destination file.
 * the output: none
 * the function operation: the function gets 2 files from the command line,
 * the source file is Unix file, and the second is Mac or Windows file. In
 * each file every letter is saved as 2 Bytes. The function reads the text
 * from the source file and writes it on the destination file according to
 * the files' sources.
 *******************************************************************/
void FromUnixToOther(char *sourceName, char *destinationName, char
*destinationOs, int swapNeeded) {
    FILE *sourceFile;
    FILE *destinationFile;
    //saves each letter while reading the file
    char str[ELEMENT_SIZE];
    char swappedMacSpace[2] = "\r";
    //gets "\0\r"
    swap(swappedMacSpace);
    //gets "\0\n"
    char swappedUnixSpace[2] = "\n";
    swap(swappedUnixSpace);
    //binary reading
    sourceFile = fopen(sourceName, "rb");
    if (sourceFile != NULL) {
        destinationFile = fopen(destinationName, "wb");
        if (destinationFile != NULL) {
            //converting to Mac
            if (strcmp(destinationOs, MAC) == 0) {
                //as long as I can read 2-Bytes letters, read from the source
                while (fread(str, CHAR_READ, ELEMENT_SIZE, sourceFile) == 2) {
                    //swap is needed to big endian
                    if (swapNeeded == 1) {
                        //if new line is needed
                        if (strcmp(str, "\n") == 0) {
                            //replace the "\n" with "\r"
                            fwrite(swappedMacSpace, CHAR_READ, ELEMENT_SIZE,
                                   destinationFile);
                        } else {
                            swap(str);
                            //otherwise - write the same letter but swapped.
                            fwrite(str, CHAR_READ, ELEMENT_SIZE,
                                   destinationFile);
                        }
                    } else {
                        //if dest' file is Mac file and the new line is needed
                        if (strcmp(str, "\n") == 0) {
                            //replace the "\n" with "\r"
                            fwrite("\r", CHAR_READ, ELEMENT_SIZE,
                                   destinationFile);
                        } else {
                            //otherwise - write the same letter.
                            fwrite(str, CHAR_READ, ELEMENT_SIZE,
                                   destinationFile);
                        }
                    }
                }
            }//converting to windows
            else {
                //as long as I can read 2-Bytes letters, read from the source
                while (fread(str, CHAR_READ, ELEMENT_SIZE, sourceFile) == 2) {
                    //swap to big endian is needed
                    if (swapNeeded == 1) {
                        if (strcmp(str, "\n") == 0) {
                            //replace the swapped "\n" with swapped "\r" "\n"
                            fwrite(swappedMacSpace, CHAR_READ, ELEMENT_SIZE,
                                   destinationFile);
                            fwrite(swappedUnixSpace, CHAR_READ, ELEMENT_SIZE,
                                   destinationFile);
                        } else {
                            swap(str);
                            //otherwise - write the same letter.
                            fwrite(str, CHAR_READ, ELEMENT_SIZE,
                                   destinationFile);
                        }
                    } else {
                        //if the current letter is "\n"
                        if (strcmp(str, "\n") == 0) {
                            //write "\r"
                            fwrite("\r", CHAR_READ, ELEMENT_SIZE,
                                   destinationFile);
                        }// then write the current letter.
                        fwrite(str, CHAR_READ, ELEMENT_SIZE, destinationFile);
                    }
                }
            }
            fclose(destinationFile);
        } //end of if
        fclose(sourceFile);
    } //end of if
}

/********************************************************************
 * function name: FromMacToOther
 * the input: char *sourceName, char *destinationName, char *destinationOs -
 * the names of the file which I read from, the names of the file which I
 * write to, the OS in which I would like to open the destination file.
 * the output: none
 * the function operation: the function gets 2 files from the command line,
 * the source file is Mac file, and the second is Unix or Windows file. In
 * each file every letter is saved as 2 Bytes. The function reads the text
 * from the source file and writes it on the destination file according to
 * the files' sources.
 *******************************************************************/
void FromMacToOther(char *sourceName, char *destinationName,
                    char *destinationOs, int swapNeeded) {
    FILE *sourceFile;
    FILE *destinationFile;
    //saves each letter while reading the file
    char str[ELEMENT_SIZE];
    char swappedMacSpace[2] = "\r";
    //gets "\0\r"
    swap(swappedMacSpace);
    //gets "\0\n"
    char swappedUnixSpace[2] = "\n";
    swap(swappedUnixSpace);
    sourceFile = fopen(sourceName, "rb");
    if (sourceFile != NULL) {
        destinationFile = fopen(destinationName, "wb");
        if (destinationFile != NULL) {
            //if the dest' file is Unix file
            if (strcmp(destinationOs, UNIX) == 0) {
                //as long as I can read 2-Bytes letters, read from the source
                while (fread(str, CHAR_READ, ELEMENT_SIZE, sourceFile) == 2) {
                    //swap is needed to big endian
                    if (swapNeeded == 1) {
                        //if new line is needed
                        if (strcmp(str, "\r") == 0) {
                            //replace the "\n" with "\r"
                            fwrite(swappedUnixSpace, CHAR_READ, ELEMENT_SIZE,
                                   destinationFile);
                        } else {
                            swap(str);
                            //otherwise - write the same letter but swapped.
                            fwrite(str, CHAR_READ, ELEMENT_SIZE,
                                   destinationFile);
                        }
                    } else {
                        //replace "\r" with "\n"
                        if (strcmp(str, "\r") == 0) {
                            fwrite("\n", CHAR_READ, ELEMENT_SIZE,
                                   destinationFile);
                        } else {
                            fwrite(str, CHAR_READ, ELEMENT_SIZE,
                                   destinationFile);
                        }
                    }
                }
            }//converting to windows
            else {
                while (fread(str, CHAR_READ, ELEMENT_SIZE, sourceFile) == 2) {
                    //swap to big endian is needed
                    if (swapNeeded == 1) {
                        if (strcmp(str, "\r") == 0) {
                            //replace the swapped "\r" with swapped "\r" "\n"
                            fwrite(swappedMacSpace, CHAR_READ, ELEMENT_SIZE,
                                   destinationFile);
                            fwrite(swappedUnixSpace, CHAR_READ, ELEMENT_SIZE,
                                   destinationFile);
                        } else {
                            swap(str);
                            //otherwise - write the same letter.
                            fwrite(str, CHAR_READ, ELEMENT_SIZE,
                                   destinationFile);
                        }
                    } else {
                        if (strcmp(str, "\r") == 0) {
                            //instead of "\n" write "\r\n"
                            fwrite(str, CHAR_READ, ELEMENT_SIZE,
                                   destinationFile);
                            fwrite("\n", CHAR_READ, ELEMENT_SIZE,
                                   destinationFile);
                        } else {
                            fwrite(str, CHAR_READ, ELEMENT_SIZE,
                                   destinationFile);
                        }
                    }
                }
            }
            fclose(destinationFile);
        } //end of if
        fclose(sourceFile);
    } //end of if
}

/********************************************************************
 * function name: FromWinToOther
 * the input: char *sourceName, char *destinationName, char *newLineSign -
 * the names of the file which I read from, the names of the file which I
 * write to, letter which dictates a new line in the dest' OS file.
 * the output: none
 * the function operation: the function gets 2 files from the command line,
 * the source file is Windows file, and the second is Unix or Mac file. In
 * each file every letter is saved as 2 Bytes. The function reads the text
 * from the source file and writes it on the destination file according to
 * the files' sources.
 *******************************************************************/
void FromWinToOther(char *sourceName, char *destinationName,
                    char *newLineSign, int swapNeeded) {
    //flag = 1 indicates the element I read before the current reading was \r.
    //flag = 0 indicates the element I read before the current reading wasn't
    // \r.
    int flag = 0;
    FILE *sourceFile;
    FILE *destinationFile;
    char str[ELEMENT_SIZE];
    char swappedMacSpace[2] = "\r";
    //gets "\0\r"
    swap(swappedMacSpace);
    //gets "\0\n"
    char swappedUnixSpace[2] = "\n";
    swap(swappedUnixSpace);
    //this is the swapped bytes indicating new line according to *newLineSign.
    char newLineSignSwapped[2];
    if (strcmp(newLineSign, "\n") == 0) {
        strcpy(newLineSignSwapped,"\n");
    } else {
        strcpy(newLineSignSwapped,"\r");
    }
    swap(newLineSignSwapped);
    sourceFile = fopen(sourceName, "rb");
    if (sourceFile != NULL) {
        destinationFile = fopen(destinationName, "wb");
        if (destinationFile != NULL) {
            while (fread(str, CHAR_READ, ELEMENT_SIZE, sourceFile) == 2) {
                //the current element isn't "\r"
                if (strcmp(str, "\r") != 0) {
                    //the previous element wasn't "\r"
                    if (flag == 0) {
                        if (swapNeeded == 1) {
                            swap(str);
                        }
                        fwrite(str, CHAR_READ, ELEMENT_SIZE, destinationFile);
                    }//the previous element was "\r" and the current
                        // element is not "\r"
                    else {
                        //the current element is "\n" -> go down one line
                        // instead of the "\r\n"
                        if (strcmp(str, "\n") == 0) {
                            if (swapNeeded == 1) {
                                fwrite(newLineSignSwapped, CHAR_READ,
                                       ELEMENT_SIZE,
                                       destinationFile);
                            } else {
                                fwrite(newLineSign, CHAR_READ, ELEMENT_SIZE,
                                       destinationFile);
                            }
                        }//the current element isn't "\n" -> write "\r"
                            // and then write the current element
                        else {
                            if (swapNeeded == 1) {
                                fwrite(swappedMacSpace, CHAR_READ, ELEMENT_SIZE,
                                       destinationFile);
                                swap(str);
                                fwrite(str, CHAR_READ, ELEMENT_SIZE,
                                       destinationFile);
                            } else {
                                fwrite("\r", CHAR_READ, ELEMENT_SIZE,
                                       destinationFile);
                                fwrite(str, CHAR_READ, ELEMENT_SIZE,
                                       destinationFile);
                            }
                        }
                    }
                    flag = 0;
                }//the current element is "\r"
                else { //also the previous element was "\r"
                    if (flag == 1) {
                        if (swapNeeded == 1) {
                            swap(str);
                        }
                        fwrite(str, CHAR_READ, ELEMENT_SIZE, destinationFile);
                    } //if the previous element wasn't "\r" don't write it.
                    //mark for the next iteration that the previous
                    // element was "\r"
                    flag = 1;
                }
            } //end of while loop
            if (flag == 1) {
                if (swapNeeded == 1) {
                    swap(str);
                }
                fwrite(str, CHAR_READ, ELEMENT_SIZE, destinationFile);
            }
            fclose(destinationFile);
        } //end of if
        fclose(sourceFile);
    } //end of if
}

int main(int argc, char *argv[]) {
    //call functions in case there are 3 or 5 or 6 args.
    if (argc == 3 || argc == 5 || argc == 6) {
        //option 1.
        if (argc == 3) {
            SameEncodingSystem(argv[1], argv[2], SWAP_NOT_NEEDED);
        } else if ((argc == 5) ||
                   (argc == 6 && strcmp(argv[5], "-keep") == 0)) {
            //option 2 in which the source and dest' are same OS files.
            if (strcmp(argv[3], argv[4]) == 0) {
                SameEncodingSystem(argv[1], argv[2], SWAP_NOT_NEEDED);
            }//option 2 in which the source and dest' aren't same OS files.
            else {
                if (strcmp(argv[3], UNIX) == 0 &&
                    (strcmp(argv[4], MAC) == 0 ||
                     strcmp(argv[4], WIN) == 0)) {
                    FromUnixToOther(argv[1], argv[2], argv[4], SWAP_NOT_NEEDED);
                } else if (strcmp(argv[3], MAC) == 0 &&
                           (strcmp(argv[4], UNIX) == 0 ||
                            strcmp(argv[4], WIN) == 0)) {
                    FromMacToOther(argv[1], argv[2], argv[4], SWAP_NOT_NEEDED);
                } else if (strcmp(argv[3], WIN) == 0) {
                    char *newLineUnix = "\n";
                    char *newLineMac = "\r";
                    if (strcmp(argv[4], UNIX) == 0) {
                        FromWinToOther(argv[1], argv[2], newLineUnix,
                                       SWAP_NOT_NEEDED);
                    } else if (strcmp(argv[4], MAC) == 0) {
                        FromWinToOther(argv[1], argv[2], newLineMac,
                                       SWAP_NOT_NEEDED);
                    }
                }
            } //end of else
        }//end of else if
        else if (argc == 6 && (strcmp(argv[5], "-swap") == 0)) {
            //option 2 in which the source and dest' are same OS files.
            if (strcmp(argv[3], argv[4]) == 0) {
                SameEncodingSystem(argv[1], argv[2], SWAP_NEEDED);
            }//option 2 in which the source and dest' aren't same OS files.
            else {
                if (strcmp(argv[3], UNIX) == 0 &&
                    (strcmp(argv[4], MAC) == 0 ||
                     strcmp(argv[4], WIN) == 0)) {
                    FromUnixToOther(argv[1], argv[2], argv[4], SWAP_NEEDED);
                } else if (strcmp(argv[3], MAC) == 0 &&
                           (strcmp(argv[4], UNIX) == 0 ||
                            strcmp(argv[4], WIN) == 0)) {
                    FromMacToOther(argv[1], argv[2], argv[4], SWAP_NEEDED);
                } else if (strcmp(argv[3], WIN) == 0) {
                    char *newLineUnix = "\n";
                    char *newLineMac = "\r";
                    if (strcmp(argv[4], UNIX) == 0) {
                        FromWinToOther(argv[1], argv[2], newLineUnix,
                                       SWAP_NEEDED);
                    } else if (strcmp(argv[4], MAC) == 0) {
                        FromWinToOther(argv[1], argv[2], newLineMac,
                                       SWAP_NEEDED);
                    }
                }
            } //end of else
        }
    } //end of if
    return 0;
}
