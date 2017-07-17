/*

Tip:
    Huge Tip. If you will use system() anywhere in code for a page in cgi-bin, 
    Make sure you add one of the following line before any standard output (printing):
            system("echo 'Content-Type: text/html\n'");
            system("printf 'Content-Type: text/html\n\n'");
    new line \n is to get out of the header and the second new line is to start page writing
        --echo only has one '\n' becuse it creates a new line automatically after execution (basically there are 2 new lines).
    Also, it is because system calls go first before anything else in the program.
    
    Just like running certain files, www-data user can access only certain things and sudo is needed.
    However, if running bash commands, like Bash's history command, is not the same as programs like whoami. whoami is seperate of bash. I assume the method of setting envVariables is a function of bash.
    
    *when executing music in system, fileName cannot have spaces.
    *running through ssh causes an unclosable vlc and does not continure through code. Suggest running code in physical raspberryPi.
    
    New Plan
        press 1 = play
        wait
        press 2 = stop (should already be playing or done playing)
            kills a playing song or imaginary process

        FormhandlerYoutube
            gets input and writes to a file. (allow overwrite)
            then can use bash script to obtain url from file
        soundplay
            -read from a file (ex:file1) and play it.
            -if none in file default to a song.
            maybe add url to another file (ex:file2) and use only when file1 is empty
                will need reset it every so often or file size.
                
    maybe change later
        change portions of bash code to C where possible.
        //see: https://www.tutorialspoint.com/cprogramming/c_file_io.htm
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <time.h>
#include "storeURL.c"

//methods
void play ();
void stop ();
int isPlaying ();
// void pauseCode (double timerAmount);

//global var
int playing = 0;
// char *program = "vlc"; //if mpg else vlc. vlc second so other code not execute... // if (*program == "mpg") {}


void play () {
    if (!playing) {
        playing = 1;
        //play music - get 1st url from urlList and store into PLAYURL. Then update urlList by removing the 1st url in urlList. Lastly, play url stored in PLAYURL;

        //if no url in urlList, play default mpg321. Else, play url.
        FILE *fp;
        char stringUrlList [5] = ""; //store contents
        if ( ! ( fp = fopen("/home/pi/Desktop/cgi-bin/main/bin/urlList", "r") ) ) {
            printf ("Sorry, file not exist.");
        }
        fgets (stringUrlList, 5, (FILE*)fp);
        fclose(fp);
        printf ("\nAnything in urlList? (if prints anything, yes): %s\n", stringUrlList);
        if ( stringUrlList[0] == '\0' ) {
            printf ("\ninside if (mpg execute)\n");
            //mpg321. the default. //bug: if playing from system dir (using mpg321), don't include quotes & path to file must not have space.
            system ("mpg321 '/home/pi/Music/Nirvana - Come As You Are.mp3' > /dev/null 2>&1 &");
            //TBD: Below code can be used to play Music in Music folder based on a counter.
            // system("PLAYURL=`cat /home/pi/Desktop/cgi-bin/main/bin/urlList | head -1` && "
                    // "tail -n +2 '/home/pi/Desktop/cgi-bin/main/bin/urlList' > /home/pi/Desktop/cgi-bin/main/bin/urlList.tmp && "
                    // "mv /home/pi/Desktop/cgi-bin/main/bin/urlList.tmp /home/pi/Desktop/cgi-bin/main/bin/urlList && "
                    // "mpg321 $PLAYURL &");
                //&> /dev/null");

    
            //mpg can sleep 0. //vlc can sleep . //note: sleep 0 diff from no sleep command.
            system("sleep 0"); //give time for above command to execute. even though it is zero, it gave time for program to have a ps. Without it, only shows sh -c that will run it.

    
            //Then store its PID in bin/PID file. //Other proccesses are usually from what it ran from (usually sh -c due to C system call or sudo as sudo user).
            //mpg321 //
            //  system("PID=`ps aux | grep mpg | head -1 | awk '{print $2}'` && ");
            //     "sudo echo $PID > /home/pi/Desktop/cgi-bin/main/bin/PID");
                    //Save: in case need to fix PID picking or sleep
                    system("echo && ps aux | grep mpg && " //print all ps
                            "PID=`ps aux | grep mpg | head -1 | awk '{print $2}'` && " //store pid
                            "sudo echo $PID > /home/pi/Desktop/cgi-bin/main/bin/PID && echo 'PID: '$PID "); //save pid in file and print contents
//TEST: make clean && make mystyle.css && make interrupt && make formYoutube && make formhandleYoutube && 
    // ls -t bin/ && ls -t && ./bin/interrupt
        } //if urlList empty, mpg
        else {
            //TBD: should get url from file with C   //and to get full value
            //vlc //TBD: may need to place into a diff file.c and exec from here.
            system("PLAYURL=`cat /home/pi/Desktop/cgi-bin/main/bin/urlList | head -1` && "
                    "tail -n +2 '/home/pi/Desktop/cgi-bin/main/bin/urlList' > /home/pi/Desktop/cgi-bin/main/bin/urlList.tmp && "
                    "mv /home/pi/Desktop/cgi-bin/main/bin/urlList.tmp /home/pi/Desktop/cgi-bin/main/bin/urlList && sudo chmod ug+rw /home/pi/Desktop/cgi-bin/main/bin/urlList &&"
                    "cvlc --play-and-exit --vout none $PLAYURL vlc://quit > /dev/null 2>&1 &"); //cvlc instead of vlc to not open gui (not waste resources).
                    //note: -I dummy; can't tell vlc to quit (except video). Need to ctrl+C or add vlc://quit as last thing to play.
                        //-I interface --extraintf extraInterface
                        //http interface is: http://ip:8080. and needs a password.
                        //vlc --play-and-exit -I ncurses --extraintf http --vout none --http-password passwordHere $PLAYURL vlc://quit > /dev/null 2>&1 & //--no-video is redundant
    
            //version: bash -c
            // system("bash -c \"PLAYURL=`cat /home/pi/Desktop/cgi-bin/main/bin/urlList | head -1` && tail -n +2 '/home/pi/Desktop/cgi-bin/main/bin/urlList' > /home/pi/Desktop/cgi-bin/main/bin/urlList.tmp && mv /home/pi/Desktop/cgi-bin/main/bin/urlList.tmp /home/pi/Desktop/cgi-bin/main/bin/urlList && sudo vlc --vout none $PLAYURL \" ");
            //version: sperate vlc call
            // system("PLAYURL=`cat /home/pi/Desktop/cgi-bin/main/bin/toPlay' && rm -rf /home/pi/Desktop/cgi-bin/main/bin/toPlay && sudo vlc $PLAYURL");
    
    
            
            //mpg can sleep 0. //vlc can sleep . //note: sleep 0 diff from no sleep command.
            system("sleep 0"); //give time for above command to execute. even though it is zero, it gave time for program to have a ps. Without it, only shows sh -c that will run it.
    
    
            
            //Then store its PID in bin/PID file. //Other proccesses are usually from what it ran from (usually sh -c due to C system call or sudo as sudo user).
            //TODO: when ps, remove grep, sudo, and sh -c from list.
            //vlc //
            // system("PID=`ps aux | grep vlc | head -1 | awk '{print $2}'` "
            //         "sudo echo $PID > /home/pi/Desktop/cgi-bin/main/bin/PID");
                    //Save: in case need to fix PID picking or sleep
                    system("echo && ps aux | grep vlc && " //print all ps
                            "PID=`ps aux | grep vlc | head -1 | awk '{print $2}'` && " //store pid
                            "sudo echo $PID > /home/pi/Desktop/cgi-bin/main/bin/PID && echo 'PID: '$PID "); //save pid in file and print contents
// make clean && make mystyle.css && make interrupt && make formYoutube && make formhandleYoutube && 
    // ls -t bin/ && ls -t && 
    // echo "https://www.youtube.com/watch?v=S-Xm7s9eGxU" > bin/urlList && cat bin/urlList && ls -tl bin/ && 
    // ./bin/interrupt
            
        } //else urlList !empty, vlc
    } //if !playing
    else {
        stop ();
    } //else playing
}


void stop () {
    //check if already finished.
    playing = isPlaying ();
    //if still playing -kill it. if it's done, play again.
    if (playing) {
        //read PID file and kill that PID. Don't care if not exist anymore.
        system ("export KILLPID=`cat /home/pi/Desktop/cgi-bin/main/bin/PID | head -1` && sudo kill -9 $KILLPID ");
        playing = 0;
    }
    else {
        system ("export KILLPID=`cat /home/pi/Desktop/cgi-bin/main/bin/PID | head -1` && sudo kill -9 $KILLPID "); // just making sure to kill PID
        play();
    }
    
    
    //below code belongs to one kill line above. Since, assuming play() will overwrite PID file, no need to rewrite PID.
    // "tail -n +2 \"/home/pi/Desktop/cgi-bin/main/bin/PID\" > /home/pi/Desktop/cgi-bin/main/bin/PID.tmp && 
    // "mv /home/pi/Desktop/cgi-bin/main/bin/PID.tmp /home/pi/Desktop/cgi-bin/main/bin/PID &&
    // "sudo kill -9 $KILLPID ");
    //^^^no need to rewrite file since when you play(), you automaticially rewrite it.^^^

}//stop()


int isPlaying () {
    int checkPlaying;
    
            //without PID file, code errors out. prepare a PID file before executing file
    //compare ran PID to the PID found running, then save in ISPLAYING file.
    //bash -c not work in environment, only through ssh--not sets vars and without bash -c, can't if. //Since we are using sh and need if statement (which allowed in bash, not sh), will use -c flag to run bash in sh.
    system ("sudo /home/pi/Desktop/cgi-bin/main/checkIsPlaying");


    //get PID result by reading file. Then, store it in an int.
    FILE *fp;
    char stringIsPlaying [5];
    if ( ! ( fp = fopen("/home/pi/Desktop/cgi-bin/main/bin/ISPLAYING", "r") ) ) {
        printf ("Sorry, file not exists.");
    }
    fgets (stringIsPlaying, 5, (FILE*)fp);
    fclose(fp);
    // convert string to int
    checkPlaying = atoi(stringIsPlaying);//atoi is 'ascii to integer'
    
    return checkPlaying;
}







// void pauseCode (double timerAmount) {
//     time_t start;
//     time_t end;
//     double elapsed;
//     start = time(NULL);
//     int exit = 0;
//     while (!exit) {
//         end = time(NULL);
//         elapsed = difftime(end, start);
//         if (elapsed >= timerAmount) {
//             exit = 1;
//         }
//     }
// }
// process = getenv("PID");
// printf ("PID is: %s\n", process);
// setenv("ENVNAME","val",1);
