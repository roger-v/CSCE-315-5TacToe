# CSCE-315-5TacToe

Programmers: Roger Villanueva (Me), Levi Uzodike, Ifrah Tariq

This project provides the user with a means of filter-searching for courses available at Texas A&M University as of June 2016.

We used a (very large) PDF file containing all the courses with their associated information (times, location, instructor, section, CRN, title, etc)
to create a MySQL database on the campus servers.

Ifrah parsed the PDF file into a .csv file so that we could open it in Microsoft Excel and make appropriate adjustments
based on our desired format for displaying the search results.

Levi derived the MySQL commands used to search for courses as well as a means of searching for rooms that are available at certain times.
If that's unclear, an example would be an organization desiring to find a room that can hold at least 60 people for 2 hours in the Physics Building.
This application allows the user to make that kind of search, which we call Room Availability Search.
Levi also worked with me to write the JDBC code.

I wrote the GUI using JavaFX as well as some of the JDBC code to connect with the database, issue commands, and retrieve results.

