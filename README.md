# SER486Project
Will hold raspberry pi class project and any files I will use for practice with the raspberry pi.
Party/DJ Radio was something I have been wanting to create. This repo is a hastily created prototype of one.

Details:
Project was developed in clooud9.
Time-span: 3 weeks.
Code quality: Almost no regard for code quality.
Design: Was created in the 1st week to help keep track of development structure without getting too messy--as expected to occur due to time contraints and working with new technology and possibly new concepts. 

Learned:

When working with permisions there are aspects to pay attention to.
CGI (Common Gateway Interface) is a very old method that allowed a web server to interact with external generating programs--aka CGI program of CGI script. 

In other words, it allowed programming languages to create executables and allow the server to execute them--allows programs to become the server-side script. In today's world, javascript, php, and other languages are more common to use and more commonly referred to as server-side script. Meanwhile, others languages are more commonly used for other means than to act as the server-side. Now, I can use C to develop dynamic-content on websites.

When a user executes a cgi program (a compiled program--in this case, a compiled C program) by visiting the cgi file path (the file path to the executable program in your site), the user executes the specified cgi program as the user _www-data_.

CGI programs are executable files that end with the extension _.cgi_ and belong in the /usr/lib/cgi-bin.
If you were to write a website that is an executable, you would need to print through standard output the header with 2 new lines to mention to CGI to now continue with the body (website-content). If you were to use system methods or anything were in the CGI program cause the server/system to execute a print, that print will go first before any portion of the executable program--something to watchout for and causes your program structure to change.

External Resources Used:
Library to program raspberryPi gpio pins with C: http://wiringpi.com/
Library to decode url encrypted information from the user: http://libccgi.sourceforge.net/
This is a site that I should have referred to as I found out about CGI, but here it is to know more about CGI, how to set it up on an Apache web server, and how to get started on CGI programs: https://httpd.apache.org/docs/2.4/howto/cgi.html


